#include "FileMan.h"

static vector<Network> loadNetworks() {
    Network anetwork;
    vector <Network> networks;

    ifstream network;
    network.open("../../dataset/network.csv");

    string line;
    getline(network, line); // Passar á frente a primeira linha

    while (getline(network, line)) {

        string temp;
        string number;
        stringstream input(line);

        getline(input, temp, ','); // Obter Station_A
        anetwork.setStation_A(temp);
        getline(input, temp, ','); // Obter Station_B
        anetwork.setStation_B(temp);
        getline(input, number, ','); // Obter Capacity
        anetwork.setCapacity(number);
        getline(input, temp, ','); // Obter Service
        anetwork.setService(temp);
        networks.push_back(anetwork);
    }
    return networks;
}

vector<Station> loadStations(){
    Station astation;
    vector<Station> stations;

    ifstream station;
    station.open("stations.csv");

    string line;
    getline(station, line); // Passar á frente a primeira linha

    while(getline(station, line)){

        string temp;
        stringstream input(line);

        getline(input, temp, ','); // Obter Name
        astation.setName(temp);
        getline(input, temp, ','); // Obter District
        astation.setDistrict(temp);
        getline(input, temp, ','); // Obter Municipality
        astation.setMunicipality(temp);
        getline(input, temp, ','); // Obter Township
        astation.setTownship(temp);
        getline(input, temp, ','); // Obter Line
        astation.setLine(temp);
        stations.push_back(astation);
    }
    return stations;
}




