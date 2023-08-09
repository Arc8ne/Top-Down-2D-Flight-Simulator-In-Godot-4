#pragma once

#include <string>

#include <fstream>

#include <vector>

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
	template<class C>
	class PBFHandler : public osmium::handler::Handler
	{
	private:
		std::vector<void(C::*)(const osmium::Node&)> nodeCallbackPtrs;

		std::vector<void(C::*)(const osmium::Way&)> wayCallbackPtrs;

		std::vector<void(C::*)(const osmium::Relation&)> relationCallbackPtrs;
	public:
		PBFHandler()
		{
			this->nodeCallbackPtrs = std::vector<void(C::*)(const osmium::Node&)>();

			this->wayCallbackPtrs = std::vector<void(C::*)(const osmium::Way&)>();

			this->relationCallbackPtrs = std::vector<void(C::*)(const osmium::Relation&)>();
		}

		void node(const osmium::Node& node)
		{
			godot::UtilityFunctions::print("Node found.");

			for (auto currentNodeCallbackPtr : this->nodeCallbackPtrs)
			{
				currentNodeCallbackPtr(node);
			}
		}

		void way(const osmium::Way& way)
		{
			godot::UtilityFunctions::print("Way found.");

			for (auto currentWayCallbackPtr : this->wayCallbackPtrs)
			{
				currentWayCallbackPtr(way);
			}
		}

		void relation(const osmium::Relation& relation)
		{
			godot::UtilityFunctions::print("Relation found.");

			for (auto currentRelationCallbackPtr : this->relationCallbackPtrs)
			{
				currentRelationCallbackPtr(relation);
			}
		}

		void RegisterNodeCallback(void(C::* nodeCallbackPtr)(const osmium::Node&))
		{
			this->nodeCallbackPtrs.push_back(nodeCallbackPtr);
		}

		void UnregisterNodeCallback(void(C::* nodeCallbackPtr)(const osmium::Node&))
		{
			int indexToRemove = -1;

			for (int currentIndex = 0; currentIndex < this->nodeCallbackPtrs.size(); currentIndex++)
			{
				if (this->nodeCallbackPtrs[currentIndex] == nodeCallbackPtr)
				{
					indexToRemove = currentIndex;

					break;
				}
			}

			if (indexToRemove != -1)
			{
				this->nodeCallbackPtrs.erase(
					this->nodeCallbackPtrs.begin() + indexToRemove
				);
			}
		}

		void RegisterWayCallback(void(C::* wayCallbackPtr)(const osmium::Way&))
		{
			this->wayCallbackPtrs.push_back(wayCallbackPtr);
		}

		void UnregisterWayCallback(void(C::* wayCallbackPtr)(const osmium::Way&))
		{
			int indexToRemove = -1;

			for (int currentIndex = 0; currentIndex < this->wayCallbackPtrs.size(); currentIndex++)
			{
				if (this->wayCallbackPtrs[currentIndex] == wayCallbackPtr)
				{
					indexToRemove = currentIndex;

					break;
				}
			}

			if (indexToRemove != -1)
			{
				this->wayCallbackPtrs.erase(
					this->wayCallbackPtrs.begin() + indexToRemove
				);
			}
		}

		void RegisterRelationCallback(void(C::* relationCallbackPtr)(const osmium::Relation&))
		{
			this->relationCallbackPtrs.push_back(relationCallbackPtr);
		}

		void UnregisterRelationCallback(void(C::* relationCallbackPtr)(const osmium::Relation&))
		{
			int indexToRemove = -1;

			for (int currentIndex = 0; currentIndex < this->relationCallbackPtrs.size(); currentIndex++)
			{
				if (this->relationCallbackPtrs[currentIndex] == relationCallbackPtr)
				{
					indexToRemove = currentIndex;

					break;
				}
			}

			if (indexToRemove != -1)
			{
				this->relationCallbackPtrs.erase(
					this->relationCallbackPtrs.begin() + indexToRemove
				);
			}
		}
	};

	template<class C>
	class PBFReader
	{
	private:

	public:
		PBFHandler<C>* pbfHandlerPtr;

		PBFReader()
		{
			this->pbfHandlerPtr = new PBFHandler<C>();
		}

		void Read(std::string pbfFilePath)
		{
			godot::UtilityFunctions::print(
				"Reading PBF file at path: " + godot::String(pbfFilePath.c_str()) + "..."
			);

			try
			{
				osmium::io::Reader* readerPtr = new osmium::io::Reader(pbfFilePath);

				osmium::apply(*readerPtr, this->pbfHandlerPtr);

				readerPtr->close();
			}
			catch (std::exception e)
			{
				godot::UtilityFunctions::printerr("Error occurred. Error information: " + godot::String(e.what()));
			}
		}
	};
}