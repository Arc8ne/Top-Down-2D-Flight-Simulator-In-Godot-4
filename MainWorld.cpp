#include "MainWorld.hpp"

void MainWorld::Generate()
{
	this->workerThread = std::thread(&MainWorld::PBFFileReader::Read, this->pbfFileReader);
}

void MainWorld::OnNodeRead()
{
	// godot::UtilityFunctions::print("Node being read from MainWorld.");

	this->loadingBarPtr->set_value(
		this->loadingBarPtr->get_value() + 1
	);

	this->numOSMNodesRead++;

	this->osmNodesCountLabel->set_text(
		"OSM Nodes read: " + godot::String::num(this->numOSMNodesRead)
	);
}

void MainWorld::OnWayRead()
{
	// godot::UtilityFunctions::print("Way being read.");

	this->loadingBarPtr->set_value(
		this->loadingBarPtr->get_value() + 1
	);

	this->numOSMWaysRead++;

	this->osmWaysCountLabel->set_text(
		"OSM Ways read: " + godot::String::num(this->numOSMWaysRead)
	);
}

void MainWorld::OnRelationRead()
{
	// godot::UtilityFunctions::print("Relation being read.");

	this->loadingBarPtr->set_value(
		this->loadingBarPtr->get_value() + 1
	);

	this->numOSMRelationsRead++;

	this->osmRelationsCountLabel->set_text(
		"OSM Relations read: " + godot::String::num(this->numOSMRelationsRead)
	);
}

void MainWorld::_bind_methods()
{
	bind_signals();
}

void MainWorld::bind_signals()
{
	godot::ClassDB::add_signal(
		MainWorld::get_class_static(),
		godot::MethodInfo("node_read")
	);

	godot::ClassDB::add_signal(
		MainWorld::get_class_static(),
		godot::MethodInfo("way_read")
	);

	godot::ClassDB::add_signal(
		MainWorld::get_class_static(),
		godot::MethodInfo("relation_read")
	);

	godot::ClassDB::bind_method(
		godot::D_METHOD("OnNodeRead"),
		&MainWorld::OnNodeRead
	);

	godot::ClassDB::bind_method(
		godot::D_METHOD("OnWayRead"),
		&MainWorld::OnWayRead
	);

	godot::ClassDB::bind_method(
		godot::D_METHOD("OnRelationRead"),
		&MainWorld::OnRelationRead
	);
}

void MainWorld::_ready()
{
	if (godot::Engine::get_singleton()->is_editor_hint() == false)
	{
		this->loadingBarPtr = this->get_node<LoadingBar>("LoadingBar");

		this->osmNodesCountLabel = this->get_node<godot::Label>(
			"OSMNodesCountLabel"
		);

		this->osmWaysCountLabel = this->get_node<godot::Label>(
			"OSMWaysCountLabel"
		);

		this->osmRelationsCountLabel = this->get_node<godot::Label>(
			"OSMRelationsCountLabel"
		);

		this->connect("node_read", godot::Callable(this, "OnNodeRead"));

		this->connect("way_read", godot::Callable(this, "OnWayRead"));

		this->connect("relation_read", godot::Callable(this, "OnRelationRead"));

		this->Generate();
	}
	else
	{
		this->set_process_internal(false);

		this->set_physics_process_internal(false);
	}
}

void MainWorld::_process()
{

}

MainWorld::MainWorld()
{
	this->loadingBarPtr = nullptr;

	this->pbfFileReader = PBFFileReader(this);

	this->osmNodesCountLabel = nullptr;

	this->osmWaysCountLabel = nullptr;

	this->osmRelationsCountLabel = nullptr;
}

MainWorld::~MainWorld()
{

}

MainWorld::PBFFileReader::PBFFileReader(MainWorld* mainWorldPtr)
{
	this->pbfFileHandler = PBFFileHandler(mainWorldPtr);
}

void MainWorld::PBFFileReader::Read()
{
	std::string pbfFilePath = "C:/dev/godot_native_cpp_projects/Experimental_Top_Down_2D_Flight_Simulator/singapore-latest.osm.pbf";

	godot::UtilityFunctions::print(
		"Reading PBF file at path: " + godot::String(pbfFilePath.c_str()) + "..."
	);

	try
	{
		osmium::io::Reader* readerPtr = new osmium::io::Reader(pbfFilePath);

		osmium::apply(*readerPtr, this->pbfFileHandler);

		readerPtr->close();
	}
	catch (std::exception e)
	{
		godot::UtilityFunctions::printerr("Error occurred. Error information: " + godot::String(e.what()));
	}
}

MainWorld::PBFFileHandler::PBFFileHandler(MainWorld* mainWorldPtr)
{
	this->mainWorldPtr = mainWorldPtr;

	this->signalEmitInterval = std::chrono::milliseconds(2);
}

void MainWorld::PBFFileHandler::node(const osmium::Node& node)
{
	/*
	godot::UtilityFunctions::print(
		"Node read by MainWorld PBF file handler."
	);
	*/

	std::this_thread::sleep_for(this->signalEmitInterval);

	this->mainWorldPtr->call_deferred("emit_signal", "node_read");
}

void MainWorld::PBFFileHandler::way(const osmium::Way& way)
{
	// godot::UtilityFunctions::print("Way read by MainWorld PBF file handler.");

	std::this_thread::sleep_for(this->signalEmitInterval);

	this->mainWorldPtr->call_deferred("emit_signal", "way_read");
}

void MainWorld::PBFFileHandler::relation(const osmium::Relation& relation)
{
	// godot::UtilityFunctions::print("Relation read by MainWorld PBF file handler.");

	std::this_thread::sleep_for(this->signalEmitInterval);

	this->mainWorldPtr->call_deferred("emit_signal", "relation_read");
}

void MainWorld::PBFFileHandler::flush()
{
	godot::UtilityFunctions::print("Flushing PBFFileHandler...");

	this->mainWorldPtr->workerThread.join();
}
