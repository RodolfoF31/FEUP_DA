#include "FileMan.h"
#include <fstream>
#include <sstream>

vector<Network> FileMan::loadNetworks() {
    vector<Network> networks;

    ifstream network;
    network.open("../../dataset/network.csv");

    string line;
    getline(network, line); // Passar á frente a primeira linha

    while(getline(network, line)) {

        string temp;
        int capacity;
        stringstream input(line);

        getline(input, temp, ','); // Obter Station_A
        string station_A = temp;
        getline(input, temp, ','); // Obter Station_B
        string station_B = temp;
        getline(input, temp, ','); // Obter Capacity
        capacity = stoi(temp);
        getline(input, temp, ','); // Obter Service
        string service = temp;

        Network anetwork(station_A, station_B, capacity, service);
        networks.push_back(anetwork);
    }
    return networks;
}

vector<Station> FileMan::loadStations(){
    vector<Station> stations;

    ifstream station;
    station.open("../../dataset/stations.csv");

    string line;
    getline(station, line); // Passar á frente a primeira linha

    while(getline(station, line)){

        string temp;
        stringstream input(line);

        getline(input, temp, ','); // Obter Name
        string name = temp;
        getline(input, temp, ','); // Obter District
        string district = temp;
        getline(input, temp, ','); // Obter Municipality
        string municipality = temp;
        getline(input, temp, ','); // Obter Township
        string township = temp;
        getline(input, temp, ','); // Obter Line
        string station_line = temp;

        Station astation(name, district, municipality, township, station_line);
        stations.push_back(astation);
    }
    return stations;
}




