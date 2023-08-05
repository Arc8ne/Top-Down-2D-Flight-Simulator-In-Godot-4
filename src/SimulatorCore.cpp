#include "SimulatorCore.hpp"

namespace fs 
{
    SimulatorCore* SimulatorCore::instancePtr = nullptr;

    SimulatorCore::SimulatorCore()
    {
	    this->httpClientPtr = new godot::HTTPClient();

	    this->defaultHTTPRequestHeaders = godot::PackedStringArray();

	    this->defaultHTTPRequestHeaders.push_back(
		    "User-Agent: Experimental Top Down 2D Flight Simulator"
	    );

	    this->defaultHTTPRequestHeaders.push_back(
		    "Accept: */*"
	    );
    }

    String SimulatorCore::GenerateOverpassAPISingaporeLocationDataURL()
    {
	    // Request URL returning smaller amount of data used for testing purposes.
	    // return "/osm/tools/overpass/api/interpreter?data=[out:json][timeout:25];(node[\"name\"=\"Yishun\"](1.20017,103.58047,1.48573,104.03915);way[\"name\"=\"Yishun\"](1.20017,103.58047,1.48573,104.03915);relation[\"name\"=\"Yishun\"](1.20017,103.58047,1.48573,104.03915););out body;>;out skel qt;";

	    // Request URL returning data for Singapore and some parts of its surrounding islands.
	    return "/osm/tools/overpass/api/interpreter?data=[out:json][timeout:25];(node(1.20017,103.58047,1.48573,104.03915);way(1.20017,103.58047,1.48573,104.03915);relation(1.20017,103.58047,1.48573,104.03915););out body;> ;out skel qt;";
    }

    bool SimulatorCore::HandleError(godot::Error error)
    {
	    if (error != godot::Error::OK)
	    {
		    godot::UtilityFunctions::print(
			    "An error occurred while attempting to send a HTTP request to the Overpass API."
		    );

		    return false;
	    }

	    return true;
    }

    String SimulatorCore::GetBooleanAsString(bool boolean)
    {
	    return boolean ? "true" : "false";
    }

    void SimulatorCore::GenerateRandomWorld(godot::TileMap* tileMapPtr)
    {
	    Vector2 minNoGenZonePos{0, 0};
	    Vector2 maxNoGenZonePos{64, 64};
        Vector2 chunkSize{64, 64};
    }

    void SimulatorCore::FetchOSMDataForWorldMap()
    {
	    if (this->HandleError(this->httpClientPtr->connect_to_host(
		    "maps.mail.ru",
		    443
	    )) == false)
	    {
		    return;
	    }

	    UtilityFunctions::print("Connecting...");

	    while (this->httpClientPtr->get_status() == godot::HTTPClient::STATUS_CONNECTING || this->httpClientPtr->get_status() == godot::HTTPClient::STATUS_RESOLVING)
	    {
		    this->httpClientPtr->poll();

		    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    }

	    if (this->httpClientPtr->get_status() != godot::HTTPClient::STATUS_CONNECTED)
	    {
		    return;
	    }

	    UtilityFunctions::print("Connected successfully.");

	    if (this->HandleError(this->httpClientPtr->request(
		    godot::HTTPClient::METHOD_GET,
		    this->GenerateOverpassAPISingaporeLocationDataURL(),
		    this->defaultHTTPRequestHeaders
	    )) == false)
	    {
		    return;
	    }

	    UtilityFunctions::print("Requesting started.");

	    while (httpClientPtr->get_status() == HTTPClient::STATUS_REQUESTING)
	    {
		    UtilityFunctions::print("Polling...");

		    this->httpClientPtr->poll();

		    UtilityFunctions::print("Polled.");

		    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    }

	    UtilityFunctions::print("Requesting finished.");

	    HTTPClient::Status status = this->httpClientPtr->get_status();

	    if (status != HTTPClient::STATUS_BODY && status != HTTPClient::STATUS_CONNECTING)
	    {
		    return;
	    }

	    bool responsePresenceStatus = this->httpClientPtr->has_response();

	    UtilityFunctions::print("Response presence status: " + GetBooleanAsString(responsePresenceStatus));

	    if (responsePresenceStatus == true)
	    {
		    UtilityFunctions::print("Response status code: " + godot::String::num(
			    this->httpClientPtr->get_response_code()
		    ));

		    std::vector<godot::PackedByteArray> responseBodyChunks = std::vector<godot::PackedByteArray>();

		    while (this->httpClientPtr->get_status() == godot::HTTPClient::STATUS_BODY)
		    {
			    this->httpClientPtr->poll();

			    godot::PackedByteArray responseBodyChunk = this->httpClientPtr->read_response_body_chunk();

			    if (responseBodyChunk.size() == 0)
			    {
				    std::this_thread::sleep_for(std::chrono::microseconds(1000));
			    }
			    else
			    {
				    responseBodyChunks.push_back(
					    responseBodyChunk
				    );
			    }
		    }

		    UtilityFunctions::print("Response vector size: " + godot::String::num(
			    responseBodyChunks.size()
		    ));

		    String responseBodyString = "";

		    for (int currentChunkIndex = 0; currentChunkIndex < responseBodyChunks.size(); currentChunkIndex++)
		    {
			    for (int currentByteIndex = 0; currentByteIndex < responseBodyChunks[currentChunkIndex].size(); currentByteIndex++)
			    {
				    responseBodyString += responseBodyChunks[currentChunkIndex][currentByteIndex];
			    }
		    }

		    // godot::UtilityFunctions::print("Response body: " + responseBodyString);

		    UtilityFunctions::print("Response body retrieved successfully. Storing data...");

		    FileAccess* worldOverpassAPIDataJsonFilePtr = new FileAccess();

		    worldOverpassAPIDataJsonFilePtr->open(
			    "res://world-overpass-api-data.json",
			    FileAccess::WRITE
		    );

		    worldOverpassAPIDataJsonFilePtr->store_string(responseBodyString);

		    worldOverpassAPIDataJsonFilePtr->close();

		    UtilityFunctions::print("Data stored successfully.");
	    }
    }

    void SimulatorCore::GenerateWorld(godot::Node2D* mainWorldRootPtr)
    {
	    PBFHelper::PBFReader pbfReader = PBFHelper::PBFReader();

	    pbfReader.Read(
		    "C:/dev/godot_native_cpp_projects/Experimental_Top_Down_2D_Flight_Simulator/singapore-latest.osm.pbf"
	    );
    }
}

