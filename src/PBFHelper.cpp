#include "PBFHelper.hpp"

PBFHelper::PBFReader::PBFReader()
{

}

void PBFHelper::PBFReader::Read(std::string pbfFilePath)
{
	try
	{
		// Crash occurs after executing this line of code.
		osmium::io::Reader* readerPtr = new osmium::io::Reader(pbfFilePath);

		PBFHandler* pbfHandlerPtr = new PBFHandler();

		osmium::apply(*readerPtr, *pbfHandlerPtr);

		readerPtr->close();
	}
	catch (std::exception e)
	{
		godot::UtilityFunctions::printerr("Error occurred. Error information: " + godot::String(e.what()));
	}
}

PBFHelper::PBFHandler::PBFHandler()
{

}

void PBFHelper::PBFHandler::node(const osmium::Node& node)
{
	godot::UtilityFunctions::print("Node found.");
}

void PBFHelper::PBFHandler::way(const osmium::Way& way)
{
	godot::UtilityFunctions::print("Way found.");
}

void PBFHelper::PBFHandler::relation(const osmium::Relation& relation)
{
	godot::UtilityFunctions::print("Relation found.");
}
