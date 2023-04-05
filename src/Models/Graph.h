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
    ServiceType getNetworkService(const string& station_A, const string& station_B) const;
    void dijkstra(const string& source, const string& destination);
    void setResidualCapacity(const string& station_A, const string& station_B, int flow);
    int getResidualCapacity(const string& station_A, const string& station_B) const;
    bool bfs(const string& source, const string& destination, unordered_map<string, string>& parent);
    int maxFlow(const string& source, const string& destination);
    void findMostTrainsRequired();
    int maxNumOfTrainsArrivingAt(const string& station);
    void topTransportationNeeds(int k);
private:
    unordered_map<string, Station> stations;
    unordered_map<string, vector<Network>> stationNetworks;
    unordered_map<string, unordered_map<string, int>> initialCapacities;
};


#endif
