#include <limits>
#include "Utils/MenuMan.h"
#include "Utils/FileMan.h"
#include "Models/Graph.h"

Graph graph;

void displayReliabilityMenu(){
    int choice = MenuMan::createMenu("\nSelect what you pretend to do: ",{"Maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity","Report on the stations that are the most affected by each segment failure"});
    int num, maxTrains;
    string line, source, destination;
    Graph graph1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean input buffer
    switch (choice) {
        case 1:
            cout << "\nWhat is the line affected: " << endl;
            getline(cin, line);

            cout << "\nWhat is the number of trains that got affected: " << endl;
            cin >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean input buffer

            graph1 = Graph::createReducedGraph(graph, line, num);

            cout << "\nEnter the source station name: " << endl;
            getline(cin, source);

            cout << "\nEnter the destination station name: ";
            getline(cin, destination);

            maxTrains = graph1.maxFlow(source, destination);

            if (maxTrains != -1) cout << "\nMaximum number of trains that can simultaneously travel with the reduced connectivity is: " << maxTrains << endl;
            break;
        case 2:
            //TODO T4.2
            break;
        default:
            cout << "\nPlease, select a valid option!" << endl;
            displayReliabilityMenu();
            break;
    }
}

void displayTopTransportation(){
    int choice = MenuMan::createMenu("\nSelect what you pretend to do: ",{"Municipalities","Districts"});
    int k;
    switch (choice) {
        case 1:
            cout << "\nEnter the number of municipalities with the highest transportation needs: ";
            cin >> k;
            cout << "\nThe top " << k << " municipalities with the highest transportation needs are: \n";
            graph.topTransportationNeedsDistrict(k);
            break;
        case 2:
            cout << "\nEnter the number of districts with the highest transportation needs: ";
            cin >> k;
            cout << "\nThe top " << k << " districts with the highest transportation needs are: \n";
            graph.topTransportationNeedsMunicipality(k);
            break;
        default:
            cout << "\nPlease, select a valid option!" << endl;
            displayTopTransportation();
            break;
    }
}

/**
 * @brief Function used to display the menu with all the options
 */

void displayMainMenu(){
    while (true){
        int choice = MenuMan::createMenu("\nSelect what you pretend to do: ", {"Find shortest path between 2 stations","Find maximum number of trains between 2 stations","Find station pairs with highest max flow","Top-k municipalities and districts, regarding transportation needs","Find the maximum number of trains that can simultaneously arrive at a given station","Reliability and Sensitivity to Line Failures","Exit"});
        string source, destination, maxTrainStation;
        int max_trains;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean input buffer
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
                graph.findMostTrainsRequired();
                break;
            case 4:
                displayTopTransportation();
                break;
            case 5:
                cout << "\nEnter the source station name: ";
                getline(cin, maxTrainStation);
                cout << "\nThe maximum number of trains that can simultaneously arrive at the station " << maxTrainStation << " is " << graph.maxNumOfTrainsArrivingAt(maxTrainStation) << "!\n";
                break;
            case 6:
                displayReliabilityMenu();
                break;
            case 7:
                return;
            default:
                cout << "\nPlease, select a valid option!" << endl;
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
