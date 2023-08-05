#include <thread>

#include <vector>

#include <godot_cpp/variant/packed_string_array.hpp>

#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/classes/tile_map.hpp>

#include <godot_cpp/classes/http_client.hpp>

#include <godot_cpp/classes/file_access.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include "PBFHelper.hpp"

class SimulatorCore
{
private:
	const godot::String OVERPASS_API_ENDPOINT_URL = "https://maps.mail.ru/osm/tools/overpass/api/interpreter";

	godot::HTTPClient* httpClientPtr;

	godot::PackedStringArray defaultHTTPRequestHeaders;

	godot::String GenerateOverpassAPISingaporeLocationDataURL();

	bool HandleError(godot::Error error);

	void FetchOSMDataForWorldMap();
public:
	static SimulatorCore* instancePtr;

	SimulatorCore();

	static godot::String GetBooleanAsString(bool boolean);

	void GenerateRandomWorld(godot::TileMap* tileMapPtr);

	void GenerateWorld(godot::Node2D* mainWorldRootPtr);
};