#include "FileMan.h"
#include <fstream>
#include <sstream>

/**
 * @brief Loads the networks from a file with the given filename and returns them as a vector.
 * @note Time-complexity -> O(N)
 * @param filename
 * @return vector with all the networks
 */

vector<Network> FileMan::loadNetworks(const std::string &filename) {
    vector<Network> networks;

    ifstream network(filename);
    if(!network.is_open()){
        cerr << "Error opening the file!" << endl;
        return networks;
    }

    string line;
    getline(network, line); // Advance first line

    while(getline(network, line)) {

        string temp;
        string station_A, station_B, capacity_to_str, service_to_str;
        int capacity;
        ServiceType service;
        istringstream input(line); // get values for each line

        getline(input, station_A, ','); // Get station_A
        getline(input, station_B, ','); // Get station_B
        getline(input, capacity_to_str, ','); // Get capacity
        capacity = stoi(capacity_to_str);
        getline(input, service_to_str, ','); // Get service
        if(service_to_str == "STANDARD") service = ServiceType::STANDARD;
        else service = ServiceType::ALFA_PENDULAR;

        networks.emplace_back(station_A,station_B,capacity,service);
    }
    network.close();
    return networks;
}

/**
 * @brief Loads the stations from a file with the given filename and returns them as a vector.
 * @note Time-complexity -> O(N)
 * @param filename
 * @return vector with all the stations
 */

vector<Station> FileMan::loadStations(const std::string &filename){
    vector<Station> stations;

    ifstream station(filename);
    if(!station.is_open()){
        cerr << "Error opening the file!" << endl;
        return stations;
    }

    string line;
    getline(station, line); // Advance first line

    while(getline(station, line)){

        string name,district, municipality, township, station_line;
        istringstream input(line); // get values for each line

        getline(input, name, ','); // Get name
        getline(input, district, ','); // Get district
        getline(input, municipality, ','); // Get municipality
        getline(input, township, ','); // Get township
        getline(input, station_line, ','); // Get line

        stations.emplace_back(name, district, municipality, township, station_line);
    }
    station.close();
    return stations;
}




