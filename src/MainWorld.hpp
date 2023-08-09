#pragma once

#include <thread>

#include <godot_cpp/godot.hpp>

#include <godot_cpp/classes/node2d.hpp>

#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/label.hpp>

#include "LoadingBar.hpp"

#include "PBFHelper.hpp"

class LoadingBar;

class MainWorld : public godot::Node2D
{
	GDCLASS(MainWorld, godot::Node2D)
private:
	class PBFFileHandler : public osmium::handler::Handler
	{
	private:
		MainWorld* mainWorldPtr;

		std::chrono::milliseconds signalEmitInterval;
	protected:

	public:
		PBFFileHandler() = default;

		PBFFileHandler(MainWorld* mainWorldPtr);

		void node(const osmium::Node& node);

		void way(const osmium::Way& way);

		void relation(const osmium::Relation& relation);

		void flush();
	};

	class PBFFileReader
	{
	private:
		PBFFileHandler pbfFileHandler;
	protected:

	public:
		PBFFileReader() = default;

		PBFFileReader(MainWorld* mainWorldPtr);

		void Read();
	};

	LoadingBar* loadingBarPtr;

	PBFFileReader pbfFileReader;

	std::thread workerThread;

	godot::Label* osmNodesCountLabel;

	godot::Label* osmWaysCountLabel;

	godot::Label* osmRelationsCountLabel;

	int numOSMNodesRead = 0;

	int numOSMWaysRead = 0;

	int numOSMRelationsRead = 0;

	void Generate();

	void OnNodeRead();

	void OnWayRead();

	void OnRelationRead();
protected:
	static void _bind_methods();

	static void bind_signals();
public:
	void _ready();

	void _process();

	MainWorld();

	~MainWorld();
};
