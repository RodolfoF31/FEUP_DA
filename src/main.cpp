#include <limits>
#include "Utils/MenuMan.h"
#include "Utils/FileMan.h"
#include "Models/Graph.h"

Graph graph;

void displayMainMenu(){
    while (true){
        int choice = MenuMan::createMenu("\nSelect what you pretend to do: ", {"Find shortest path","Find maximum number of trains","Exit"});
        string source, destination;
        int max_trains;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1:
                cout << "\nEnter the source station name: ";
                getline(cin, source);
                cout << "\nEnter the destination station name: ";
                getline(cin, destination);
                graph.dijkstra(source, destination);
                break;
            case 2:
                cout << "\nEnter the source station name: ";
                getline(cin, source);
                cout << "\nEnter the destination station name: ";
                getline(cin, destination);
                max_trains = graph.maxFlow(source, destination);
                if (max_trains != -1) cout << "\nMaximum number of trains that can simultaneously travel: " << max_trains << endl;
                break;
            case 3:
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
