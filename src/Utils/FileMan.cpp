#include "FileMan.h"
#include <fstream>
#include <sstream>

vector<Network> FileMan::loadNetworks(const std::string &filename) {
    vector<Network> networks;

    ifstream network(filename);
    if(!network.is_open()){
        cerr << "Error opening the file!" << endl;
        return networks;
    }

    string line;
    getline(network, line); // Passar á frente a primeira linha

    while(getline(network, line)) {

        string temp;
        string station_A, station_B, capacity_to_str, service_to_str;
        int capacity;
        ServiceType service;
        istringstream input(line); // obter valores por cada linha

        getline(input, station_A, ','); // Obter Station_A
        getline(input, station_B, ','); // Obter Station_B
        getline(input, capacity_to_str, ','); // Obter Capacity
        capacity = stoi(capacity_to_str);
        getline(input, service_to_str, ','); // Obter Service
        if(service_to_str == "STANDARD") service = ServiceType::STANDARD;
        else service = ServiceType::ALFA_PENDULAR;

        networks.emplace_back(station_A,station_B,capacity,service);
    }
    network.close();
    return networks;
}

vector<Station> FileMan::loadStations(const std::string &filename){
    vector<Station> stations;

    ifstream station(filename);
    if(!station.is_open()){
        cerr << "Error opening the file!" << endl;
        return stations;
    }

    string line;
    getline(station, line); // Passar á frente a primeira linha

    while(getline(station, line)){

        string name,district, municipality, township, station_line;
        istringstream input(line); // obter valores por cada linha

        getline(input, name, ','); // Obter Name
        getline(input, district, ','); // Obter District
        getline(input, municipality, ','); // Obter Municipality
        getline(input, township, ','); // Obter Township
        getline(input, station_line, ','); // Obter Line

        stations.emplace_back(name, district, municipality, township, station_line);
    }
    station.close();
    return stations;
}




