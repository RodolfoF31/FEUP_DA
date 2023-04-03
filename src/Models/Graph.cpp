#include "Graph.h"
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>

Graph::Graph() = default;

void Graph::addStation(const Station &station) {
    stations[station.getName()] = station;
}

void Graph::addNetwork(const Network &network) {
    stationNetworks[network.getStation_A()].push_back(network);
    stationNetworks[network.getStation_B()].push_back(network);

    initialCapacities[network.getStation_A()][network.getStation_B()] = network.getCapacity();
    initialCapacities[network.getStation_B()][network.getStation_A()] = network.getCapacity();
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

ServiceType Graph::getNetworkService(const string &station_A, const string &station_B) const { // might be useful
    if(stationNetworks.count(station_A) > 0){
        for (const Network& network: stationNetworks.at(station_A)) {
            if(network.getStation_A() == station_B || network.getStation_B() == station_B){
                return network.getService();
            }
        }
    }
    return ServiceType::NO_SERVICE; //TODO change?
}

struct Node {
    string stationName;
    int distance;

    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

/**
 * Calculates the shortest path from a source station to a destination station using Dijkstra's algorithm.
 * @param source The name of the source station.
 * @param destination The name of the destination station.
 */

void Graph::dijkstra(const string& source, const string& destination) {
    unordered_map<string, int> distances; // maps each node to its shortest distance from the source node
    unordered_map<string, string> previous; // maps each node to its predecessor in the shortest path from the source node
    priority_queue<Node> queue;

    if (stations.count(source) == 0 || stations.count(destination) == 0) { // check if source and destination are valid stations
        cout << "\nError: Invalid source or destination station" << endl;
        return;
    }

    for (const auto& station : stations) { // all distances are initialized to infinity except source node
        distances[station.first] = numeric_limits<int>::max();
    }

    distances[source] = 0;
    queue.push({source, 0});

    while (!queue.empty()) {
        Node current = queue.top();
        queue.pop();

        if (current.stationName == destination) { // loop through queue removing the node with the smallest distance from the queue, if it is the destination break
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
        cout << "\nShortest path: ";
        string currentNode = destination;

        while (currentNode != source) {
            cout << currentNode << " <- ";
            currentNode = previous[currentNode];
        }

        cout << source << endl;
        cout << "\nTotal distance: " << distances[destination] << endl;
    } else {
        cout << "\nNo path found from " << source << " to " << destination << endl;
    }
}

void Graph::setResidualCapacity(const string& station_A, const string& station_B, int flow) {
    if (stationNetworks.count(station_A) > 0) {
        for (Network& network : stationNetworks[station_A]) {
            if (network.getStation_A() == station_B || network.getStation_B() == station_B) {
                network.setCapacity(network.getCapacity() - flow);
                return;
            }
        }
    }

    stationNetworks[station_A].emplace_back(station_A, station_B, flow, ServiceType::NO_SERVICE);
}

int Graph::getResidualCapacity(const string& station_A, const string& station_B) const {
    if (stationNetworks.count(station_A) > 0) {
        for (const Network& network : stationNetworks.at(station_A)) {
            if (network.getStation_A() == station_B || network.getStation_B() == station_B) {
                return network.getCapacity();
            }
        }
    }
    return 0;
}

int Graph::bfs(const std::string &source, const std::string &destination, unordered_map<std::string, std::string> &parent) {
    unordered_map<string, bool> visited;
    for(const auto& station: stations) visited[station.first];

    queue<string> q;
    q.push(source);
    visited[source] = true;
    parent[source] = ""; // set an invalid parent

    while (!q.empty()) {
        string current = q.front();
        q.pop();
        vector<Station> adjacentStations = getAdjacentStations(current);

        for (const Station& adjacentStation : adjacentStations) {
            if (!visited[adjacentStation.getName()] && getNetworkCapacity(current, adjacentStation.getName()) > 0) {
                parent[adjacentStation.getName()] = current;
                visited[adjacentStation.getName()] = true;
                q.push(adjacentStation.getName());

                if (adjacentStation.getName() == destination) {
                    return true;
                }
            }
        }
    }

    return false;
}

int Graph::maxFlow(const string& source, const string& destination) {
    if (stations.count(source) == 0 || stations.count(destination) == 0) {
        cout << "\nError: Invalid source or destination station" << endl;
        return -1;
    }

    unordered_map<string, string> parent;
    int max_flow = 0;

    while (bfs(source, destination, parent)) {
        int aug_flow = numeric_limits<int>::max(); // infinite
        string currentNode = destination;

        // find the bottleneck capacity along the augmenting path
        while (currentNode != source) {
            string prevNode = parent[currentNode];
            aug_flow = min(aug_flow, getResidualCapacity(prevNode, currentNode));
            currentNode = prevNode;
        }

        // update the flow along the augmenting path
        currentNode = destination;
        while (currentNode != source) {
            string prevNode = parent[currentNode];
            setResidualCapacity(prevNode, currentNode, aug_flow);
            setResidualCapacity(currentNode, prevNode, -aug_flow);
            currentNode = prevNode;
        }

        // add the augmenting flow to the total flow
        max_flow += aug_flow;
    }

    return max_flow;
}

void Graph::findMostTrainsRequired() {
    int maxTrains = 0;
    vector<pair<string, string>> stationPairs;

    for (const auto& source : stations) {
        for (const auto& destination : stations) {
            if (source.first != destination.first) {
                int flow = maxFlow(source.first, destination.first);

                if (flow > maxTrains) {
                    maxTrains = flow;
                    stationPairs.clear();
                    stationPairs.emplace_back(source.first, destination.first);
                } else if (flow == maxTrains) {
                    stationPairs.emplace_back(source.first, destination.first);
                }
            }
            for (auto& stationNetwork : stationNetworks) {
                for (Network& network : stationNetwork.second) {
                    network.setCapacity(initialCapacities[network.getStation_A()][network.getStation_B()]);
                }
            }
        }
    }

    cout << "Maximum trains required: " << maxTrains << endl;
    cout << "Station pairs:" << endl;
    for (const auto& pair : stationPairs) {
        cout << pair.first << " - " << pair.second << endl;
    }
}

int Graph::maxNumOfTrainsArrivingAt(const string& station) {
    if (stations.count(station) == 0) {
        cout << "\nError: Invalid station" << endl;
        return -1;
    }

    int maxNumOfTrains = 0;
    for (const auto& source : stations) {
        if (source.first != station) {
            int flow = maxFlow(source.first, station);

            for (auto& stationNetwork : stationNetworks) {
                for (Network& network : stationNetwork.second) {
                    network.setCapacity(initialCapacities[network.getStation_A()][network.getStation_B()]);
                }
            }

            maxNumOfTrains += flow;
        }
    }

    return maxNumOfTrains;
}

void Graph::topTransportationNeeds(int k) {
    if (k <= 0) {
        cout << "\nPlease enter a number greater than 0";
        return;
    }
    // Create a map to store the total maximum flow for each municipality and district
    unordered_map<string, int> areas;

    // Loop over all pairs of stations in the graph
    for (auto it1 = stations.begin(); it1 != stations.end(); ++it1) {
        for (auto it2 = stations.begin(); it2 != stations.end(); ++it2) {
            if (it1 == it2) {
                continue;
            }
            int max_flow = maxFlow(it1->first, it2->first);
            string area1 = it1->second.getMunicipality() + "-" + it1->second.getDistrict();
            string area2 = it2->second.getMunicipality() + "-" + it2->second.getDistrict();
            if (areas.count(area1) == 0) {
                areas[area1] = 0;
            }
            if (areas.count(area2) == 0) {
                areas[area2] = 0;
            }
            areas[area1] += max_flow;
            areas[area2] += max_flow;
        }
    }

    // Create a vector of pairs to sort the areas by total maximum flow
    vector<pair<string, int>> sorted_areas;
    for (auto & area : areas) {
        sorted_areas.emplace_back(area.first, area.second);
    }
    sort(sorted_areas.begin(), sorted_areas.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    // Print the top-k areas
    for (int i = 0; i < k && i < sorted_areas.size(); ++i) {
        cout << sorted_areas[i].first << ": " << sorted_areas[i].second << endl;
    }
}


