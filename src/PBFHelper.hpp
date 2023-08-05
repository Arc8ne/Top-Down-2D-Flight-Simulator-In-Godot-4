#pragma once

#include <string>

#include <fstream>

#include <godot_cpp/godot.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <osmium/io/reader.hpp>

#include <osmium/handler.hpp>

#include <osmium/osm/node.hpp>

#include <osmium/osm/way.hpp>

#include <osmium/osm/relation.hpp>

#include <osmium/visitor.hpp>

#include <osmium/io/pbf.hpp>

#include <osmium/io/pbf_input.hpp>

#include <osmium/io/pbf_output.hpp>

namespace PBFHelper
{
	class PBFReader
	{
	private:

	public:
		PBFReader();

		void Read(std::string pbfFilePath);
	};

	class PBFHandler : public osmium::handler::Handler
	{
	private:

	public:
		PBFHandler();

		void node(const osmium::Node& node);

		void way(const osmium::Way& way);

		void relation(const osmium::Relation& relation);
	};
}