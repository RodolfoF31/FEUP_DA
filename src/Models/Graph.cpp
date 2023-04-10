#include "Graph.h"
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>
#include <climits>

Graph::Graph() = default;

/**
 * @brief Adds a station to the stations vector
 * @note Time-Complexity -> O(1)
 * @param station A station
 */

void Graph::addStation(const Station &station) {
    stations[station.getName()] = station;
}

/**
 * @brief Adds a network to the network vector
 * @note Time-Complexity -> O(1)
 * @param network A network
 */

void Graph::addNetwork(const Network &network) {
    stationNetworks[network.getStation_A()].push_back(network);
    stationNetworks[network.getStation_B()].push_back(network);

    initialCapacities[network.getStation_A()][network.getStation_B()] = network.getCapacity();
    initialCapacities[network.getStation_B()][network.getStation_A()] = network.getCapacity();
}

/**
 * @brief Gets all the adjacent stations of a certain station
 * @note Time-Complexity -> O(n) being n the size of the vector
 * @param stationName name of the station
 * @return vector of adjacent stations
 */

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

/**
 * @brief Gets the capacity of the network between two stations
 * @note Time-Complexity -> O(n) being n the size of the vector
 * @param station_A name of station A
 * @param station_B name of station B
 * @return capacity of the network
 */

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

struct Node {
    string stationName;
    int distance;

    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

/**
 * @brief Calculates the shortest path from a source station to a destination station using Dijkstra's algorithm.
 * @note Time-complexity -> O((E + V) * log (V)) (where E is the number of edges and V is the number of vertices)
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

/**
 * @brief Sets the residual capacity of a network between two stations
 * @note Time-Complexity -> O(n) being n the size of the vector
 * @param station_A name of station A
 * @param station_B name of station B
 * @param flow max flow between two stations
 */

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

/**
 * @brief Gets the residual capacity of a network between two stations
 * @note Time-Complexity -> O(n) being n the size of the vector
 * @param station_A name of station A
 * @param station_B name of station B
 * @return returns the residual capacity
 */

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

/**
 * @briefBFS function to find a path between source and destination in the graph.
 * @note Time-complexity -> O(V + E) (where V is the number of vertices and E is the number of edges)
 * @param source the starting station as a string
 * @param destination the destination station as a string
 * @param parent an unordered_map that stores the parent of each station in the path (output parameter)
 * @return true if a path between source and destination is found, false otherwise
 */

bool Graph::bfs(const string &source, const string &destination, unordered_map<string, string> &parent) {
    unordered_map<string, bool> visited;
    unordered_map<string, int> distance;
    for(const auto& station: stations){
        visited[station.first] = false;
        distance[station.first] = numeric_limits<int>::max();
    }

    queue<string> q;
    q.push(source);
    visited[source] = true;
    distance[source] = 0;
    parent[source] = ""; // set an invalid parent

    while (!q.empty()) {
        string current = q.front();
        q.pop();
        vector<Station> adjacentStations = getAdjacentStations(current);

        for (const Station& adjacentStation : adjacentStations) {
            if (!visited[adjacentStation.getName()] && getResidualCapacity(current, adjacentStation.getName()) > 0) {
                parent[adjacentStation.getName()] = current;
                visited[adjacentStation.getName()] = true;
                distance[adjacentStation.getName()] = distance[current] + 1;
                q.push(adjacentStation.getName());

                if (adjacentStation.getName() == destination) {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * @brief Computes the maximum flow between the source and destination stations in the graph
 * @note Time-complexity -> O(V * E^2) (where V is the number of vertices and E is the number of edges)
 * @param source the starting station as a string
 * @param destination the destination station as a string
 * @return the maximum flow between source and destination stations or -1 in case of an error
 */

int Graph::maxFlow(const string& source, const string& destination) { // edmon's-karp
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

/**
 * @brief Finds the maximum number of trains required to support the flow between all pairs of stations in the graph.
 * @brief It also prints the station pairs that require the maximum number of trains.
 * @note Time-complexity -> O(V^4 * E^2) (where V is the number of vertices and E is the number of edges)
 */

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

    cout << "\nMaximum trains required: " << maxTrains << endl;
    cout << "\nStation pairs:\n" << endl;
    for (const auto& pair : stationPairs) {
        cout << pair.first << " and " << pair.second << " with "<<  maxTrains << " trains" << endl;
    }
}

/**
 * @brief Calculates the maximum number of trains arriving at the specified station.
 * @note Time-complexity -> O(V^2 * E^2) (where V is the number of vertices and E is the number of edges)
 * @param station
 * @return the maximum number of trains arriving at the specified station or -1 in case of an error
 */

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

            maxNumOfTrains = max(maxNumOfTrains, flow);
        }
    }

    return maxNumOfTrains;
}

/**
 * @brief Calculates and outputs the k districts with the highest transportation needs, based on the maximum flow between pairs of stations within each district
 * @note Time-complexity -> O(V^3 * E^2) (where V is the number of vertices and E is the number of edges)
 * @param k The number of top districts to display
 */

void Graph::topTransportationNeedsDistrict(int k) {
    unordered_map<string, int> districtFlow;
    unordered_map<string, Station> remainingStations = stations;

    for (const auto& station: stations) {
        remainingStations.erase(station.first);
        for (const auto& station1: remainingStations) {
            if (station.first == station1.first) continue;
            if (station.second.getDistrict() != station1.second.getDistrict()) continue;
            districtFlow[station.second.getDistrict()] += maxFlow(station.first, station1.first);
        }
    }

    for (int i = k; i > 0; i--) {
        string maxDistrict;
        int maxD = 0;

        for (const auto& district: districtFlow) {
            if(district.second > maxD){
                maxDistrict = district.first;
                maxD = district.second;
            }
        }

        cout << k - i + 1 << "- " << maxDistrict << " with " << maxD << " trains\n";
        districtFlow.erase(maxDistrict);
    }
}

/**
 * @brief Calculates and outputs the k municipalities with the highest transportation needs, based on the maximum flow between pairs of stations within each municipality
 * @note Time-complexity -> O(V^3 * E^2) (where V is the number of vertices and E is the number of edges)
 * @param k The number of top municipalities to display
 */

void Graph::topTransportationNeedsMunicipality(int k) {
    unordered_map<string, int> municipalityFlow;
    unordered_map<string, Station> remainingStations = stations;

    for (const auto& station: stations) {
        remainingStations.erase(station.first);
        for (const auto& station1: remainingStations) {
            if (station.first == station1.first) continue;
            if (station.second.getMunicipality() != station1.second.getMunicipality()) continue;
            municipalityFlow[station.second.getMunicipality()] += maxFlow(station.first, station1.first);
        }
    }

    for (int i = k; i > 0; i--) {
        string maxMunicipality;
        int maxF = 0;

        for (const auto& municipality: municipalityFlow) {
            if(municipality.second > maxF){
                maxMunicipality = municipality.first;
                maxF = municipality.second;
            }
        }

        cout << k - i + 1 << "- " << maxMunicipality << " with " << maxF << " trains\n";
        municipalityFlow.erase(maxMunicipality);
    }
}

Graph Graph::createReducedGraph(const Graph& graph, const string& line, int num) {
    Graph reducedGraph;

    for (const auto& stationEntry : graph.stations) {
        const Station& station = stationEntry.second;
        reducedGraph.addStation(station);
    }

    for (const auto& stationEntry : graph.stations) {
        const string& stationName = stationEntry.first;
        const Station& station = stationEntry.second;

        auto stationNetworksIt = graph.stationNetworks.find(stationName);
        if (stationNetworksIt == graph.stationNetworks.end()) {
            continue;
        }

        for (const Network& network : stationNetworksIt->second) {
            string adjacentStationName = (network.getStation_A() == stationName) ? network.getStation_B() : network.getStation_A();

            auto adjStationIt = graph.stations.find(adjacentStationName);
            if (adjStationIt == graph.stations.end()) {
                continue;
            }

            const Station& adjStation = adjStationIt->second;
            int capacity = network.getCapacity();
            ServiceType service = network.getService();

            if (station.getLine() == line && adjStation.getLine() == line) {
                reducedGraph.addNetwork(Network(stationName, adjacentStationName, capacity - num, service));
            }
            else {
                reducedGraph.addNetwork(Network(stationName, adjacentStationName, capacity, service));
            }
        }
    }

    return reducedGraph;
}

int Graph::maxFlowMinCost(const string& source, const string& destination) {
    int max_flow = 0;
    int current_flow = 0;
    bool use_standard = true;

    unordered_map<string, int> distances; // maps each node to its shortest distance from the source node
    unordered_map<string, string> previous; // maps each node to its predecessor in the shortest path from the source node
    priority_queue<Node> queue;

    if (stations.count(source) == 0 ||
        stations.count(destination) == 0) { // check if source and destination are valid stations
        cout << "\nError: Invalid source or destination station" << endl;
    }

    for (const auto &station: stations) { // all distances are initialized to infinity except source node
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

        for (const Station &adjacentStation: getAdjacentStations(current.stationName)) {
            int newDistance =
                    distances[current.stationName] + getNetworkCapacity(current.stationName, adjacentStation.getName());

            if (newDistance < distances[adjacentStation.getName()]) {
                distances[adjacentStation.getName()] = newDistance;
                previous[adjacentStation.getName()] = current.stationName;
                queue.push({adjacentStation.getName(), newDistance});
            }
        }
    }

    while (bfs(source, destination, previous)) {
        int bottleneck = INT_MAX;
        for (string v = destination; v != source; v = previous[v]) {
            string u = previous[v];
            int residual_capacity;
            if (use_standard) {
                residual_capacity = getResidualCapacity(u, v);
            } else {
                residual_capacity = getResidualCapacity(v, u);
            }
            bottleneck = min(bottleneck, residual_capacity);
        }
        for (string v = destination; v != source; v = previous[v]) {
            string u = previous[v];
            if (use_standard) {
                setResidualCapacity(u, v, getResidualCapacity(u, v) - bottleneck);
                setResidualCapacity(v, u, getResidualCapacity(v, u) + bottleneck);
            } else {
                setResidualCapacity(v, u, getResidualCapacity(v, u) - bottleneck);
                setResidualCapacity(u, v, getResidualCapacity(u, v) + bottleneck);
            }
        }
        int cost = 0;
        for (string v = destination; v != source; v = previous[v]) {
            string u = previous[v];
            int distance = distances[v] - distances[u];
            if (use_standard) {
                cost += distance * bottleneck * 2;
            } else {
                cost += distance * bottleneck * 4;
            }
        }
        if (use_standard) {
            current_flow += bottleneck;
            max_flow += bottleneck;
        } else {
            max_flow += bottleneck * 2;
        }
        if (current_flow + bottleneck >= 3) {
            use_standard = !use_standard;
            current_flow = 0;
        } else {
            current_flow += bottleneck;
        }
    }

    // Calculate the total cost for the allocated trains
    int total_cost = 0;
    for (string v = destination; v != source; v = previous[v]) {
        string u = previous[v];
        int distance = distances[v] - distances[u];
        int flow = use_standard ? maxFlow(u, v) : maxFlow(v, u);
        int cost = distance * flow;
        total_cost += cost;
    }
    return max_flow;
}




