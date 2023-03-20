#include "Utils/MenuMan.h"
#include "Utils/FileMan.h"
#include "Models/Graph.h"

Graph graph;

string source, destination; // change placement

void displayMainMenu(){
    while (true){
        int choice = MenuMan::createMenu("\nSelect what you pretend to do: ", {"Find shortest path","Exit"});
        switch (choice) {
            case 1:
                cout << "Enter the source station name: ";
                cin >> source;
                cout << "Enter the destination station name: ";
                cin >> destination;
                graph.dijkstra(source, destination);
                break;
            case 2:
                return;
            default:
                cout << "Please, select a valid option!" << endl;
        }
    }
}

int main() {
    vector<Station> stations = FileMan::loadStations("../dataset/stations.csv");
    vector<Network> networks = FileMan::loadNetworks("../dataset/network.csv");

    for(const Station& station : stations) graph.addStation(station);
    for(const Network& network : networks) graph.addNetwork(network);


    displayMainMenu();
    return 0;
}
