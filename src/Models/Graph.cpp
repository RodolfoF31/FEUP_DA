#include "Graph.h"
#include <queue>
#include <limits>
#include <iostream>

Graph::Graph() {}

void Graph::addStation(const Station &station) {
    stations[station.getName()] = station;
}

void Graph::addNetwork(const Network &network) {
    stationNetworks[network.getStation_A()].push_back(network);
    stationNetworks[network.getStation_B()].push_back(network);
}

vector<Station> Graph::getAdjacentStations(const string &stationName) const {
    vector<Station> adjacentStations;
    if(stationNetworks.count(stationName) > 0){
        for(const Network& network : stationNetworks.at(stationName)){
            string adjacentStationName = (network.getStation_A() == stationName) ? network.getStation_B() : network.getStation_A();
            adjacentStations.push_back(stations.at(adjacentStationName));
        }
    }
    return adjacentStations;
}

int Graph::getNetworkCapacity(const string &station_A, const string &station_B) const {
    if(stationNetworks.count(station_A) > 0){
        for(const Network& network : stationNetworks.at(station_A)){
            if(network.getStation_A() == station_B || network.getStation_B() == station_B){
                return network.getCapacity();
            }
        }
    }
    return -1;
}

ServiceType Graph::getNetworkService(const string &station_A, const string &station_B) const {
    if(stationNetworks.count(station_A) > 0){
        for (const Network& network: stationNetworks.at(station_A)) {
            if(network.getStation_A() == station_B || network.getStation_B() == station_B){
                return network.getService();
            }
        }
    }
    return ServiceType::NO_SERVICE; // change?
}

struct Node {
    string stationName;
    int distance;

    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

void Graph::dijkstra(const string& source, const string& destination) {
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;
    priority_queue<Node> queue;

    for (const auto& station : stations) {
        distances[station.first] = numeric_limits<int>::max();
    }

    distances[source] = 0;
    queue.push({source, 0});

    while (!queue.empty()) {
        Node current = queue.top();
        queue.pop();

        if (current.stationName == destination) {
            break;
        }

        for (const Station& adjacentStation : getAdjacentStations(current.stationName)) {
            int newDistance = distances[current.stationName] + getNetworkCapacity(current.stationName, adjacentStation.getName());

            if (newDistance < distances[adjacentStation.getName()]) {
                distances[adjacentStation.getName()] = newDistance;
                previous[adjacentStation.getName()] = current.stationName;
                queue.push({adjacentStation.getName(), newDistance});
            }
        }
    }

    if (previous.count(destination) > 0) {
        cout << "Shortest path: ";
        string currentNode = destination;

        while (currentNode != source) {
            cout << currentNode << " <- ";
            currentNode = previous[currentNode];
        }

        cout << source << endl;
        cout << "Total distance: " << distances[destination] << endl;
    } else {
        cout << "No path found from " << source << " to " << destination << endl;
    }
}