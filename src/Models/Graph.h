#ifndef PROJETODA_GRAPH_H
#define PROJETODA_GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Network.h"
#include "Station.h"


class Graph {
public:
    Graph();
    void addStation(const Station& station); // node
    void addNetwork(const Network& network); // edge
    vector<Station> getAdjacentStations(const string& stationName) const;
    int getNetworkCapacity(const string& station_A, const string& station_B) const;
    void dijkstra(const string& source, const string& destination);
    void setResidualCapacity(const string& station_A, const string& station_B, int flow);
    int getResidualCapacity(const string& station_A, const string& station_B) const;
    bool bfs(const string& source, const string& destination, unordered_map<string, string>& parent);
    int maxFlow(const string& source, const string& destination); // 2.1
    void findMostTrainsRequired(); // 2.2
    int maxNumOfTrainsArrivingAt(const string& station); // 2.4
    void topTransportationNeedsDistrict(int k); // 2.3
    void topTransportationNeedsMunicipality(int k); // 2.3
    static Graph createSubGraph(const Graph& graph, const string& line, int num); // 4.1
    int maxFlowMinCost(const string& source, const string& destination); // 3.1
private:
    unordered_map<string, Station> stations;
    unordered_map<string, vector<Network>> stationNetworks;
    unordered_map<string, unordered_map<string, int>> initialCapacities;
};


#endif
