#pragma once

#include <thread>

#include <vector>

#include <godot_cpp/variant/packed_string_array.hpp>

#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/classes/tile_map.hpp>

#include <godot_cpp/classes/http_client.hpp>

#include <godot_cpp/classes/file_access.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include "PBFHelper.hpp"

namespace fs 
{
    using godot::HTTPClient;
    using godot::Node2D;
    using godot::PackedStringArray;
    using godot::String;
    using godot::TileMap;
    using godot::UtilityFunctions;
    using godot::Vector2;
    using godot::Error;
    using godot::FileAccess;

    class SimulatorCore
    {
    private:
        static const inline String OVERPASS_API_ENDPOINT_URL = "https://maps.mail.ru/osm/tools/overpass/api/interpreter";

        HTTPClient *httpClientPtr;

        PackedStringArray defaultHTTPRequestHeaders;

        String GenerateOverpassAPISingaporeLocationDataURL();

        bool HandleError(Error error);

        void FetchOSMDataForWorldMap();

    public:
        static SimulatorCore *instancePtr;

        SimulatorCore();

        static String GetBooleanAsString(bool boolean);

        void GenerateRandomWorld(TileMap *tileMapPtr);

        void GenerateWorld(Node2D *mainWorldRootPtr);
    };
}