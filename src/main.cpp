#include <limits>
#include "Utils/MenuMan.h"
#include "Utils/FileMan.h"
#include "Models/Graph.h"

Graph graph;

/**
 * @brief Function used to display the menu with all the options for the reliability part
 */

void displayReliabilityMenu(){
    int choice = MenuMan::createMenu("\nSelect what you pretend to do: ",{"Maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity","Report on the stations that are the most affected by each segment failure"});
    int num, maxTrains, k;
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

            graph1 = Graph::createSubGraph(graph, line, num);

            cout << "\nEnter the source station name: " << endl;
            getline(cin, source);

            cout << "\nEnter the destination station name: ";
            getline(cin, destination);

            maxTrains = graph1.maxFlow(source, destination);

            if (maxTrains != -1) cout << "\nMaximum number of trains that can simultaneously travel with the reduced connectivity is: " << maxTrains << endl;
            break;
        case 2: // T4.2
            cout << "\nWhat is the line affected: " << endl;
            getline(cin, line);

            cout << "\nWhat is the number of trains that got affected: " << endl;
            cin >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean input buffer

            cout << "\nEnter a number for the top-k most affected districts/municipalities to be displayed: " << endl;
            cin >> k;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean input buffer

            graph1 = Graph::createSubGraph(graph, line, num);

            cout << "\nThe top " << k << " municipalities most affected are: \n";
            graph1.topTransportationNeedsMunicipality(k);

            cout << "\nThe top " << k << " districts most affected are: \n";
            graph1.topTransportationNeedsDistrict(k);

            break;
        default:
            cout << "\nPlease, select a valid option!" << endl;
            break;
    }
}

/**
 * @brief Function used to display the menu with the options to choose if we want to do the top-k districts or municipalities
 */

void displayTopTransportation(){
    int choice;
    int k;
    Graph tmpGraph = graph;
    while (true) {
        choice = MenuMan::createMenu("\nSelect what you pretend to do: ",{"Municipalities","Districts"});
        switch (choice) {
            case 1:
                cout << "\nEnter the number of municipalities with the highest transportation needs: ";
                cin >> k;
                cout << "\nThe top " << k << " municipalities with the highest transportation needs are: \n";
                tmpGraph.topTransportationNeedsDistrict(k);
                return;
            case 2:
                cout << "\nEnter the number of districts with the highest transportation needs: ";
                cin >> k;
                cout << "\nThe top " << k << " districts with the highest transportation needs are: \n";
                tmpGraph.topTransportationNeedsMunicipality(k);
                return;
            default:
                cout << "\nPlease, select a valid option!" << endl;
                break;
        }
    }
}

/**
 * @brief Function used to display the menu with the options to choose if we want to do all the service metrics
 */

void displayServiceMetrics(){
    int max_trains;
    string source, destination, maxTrainStation;
    int choice = MenuMan::createMenu("\nSelect what you pretend to do: ", {"Find maximum number of trains between 2 stations","Find station pairs with highest max flow","Top-k municipalities and districts, regarding transportation needs","Find the maximum number of trains that can simultaneously arrive at a given station"});
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean input buffer
    switch (choice) {
        case 1:
            cout << "\nEnter the source station name: ";
            getline(cin, source);
            cout << "\nEnter the destination station name: ";
            getline(cin, destination);
            max_trains = graph.maxFlow(source, destination);
            if (max_trains != -1) cout << "\nMaximum number of trains that can simultaneously travel: " << max_trains << endl;
            break;
        case 2:
            graph.findMostTrainsRequired();
            break;
        case 3:
            displayTopTransportation();
            break;
        case 4:
            cout << "\nEnter the source station name: ";
            getline(cin, maxTrainStation);
            cout << "\nThe maximum number of trains that can simultaneously arrive at the station " << maxTrainStation << " is " << graph.maxNumOfTrainsArrivingAt(maxTrainStation) << "!\n";
            break;
        default:
            cout << "\nPlease, select a valid option!" << endl;
            break;
    }
}


/**
 * @brief Function used to display the menu with all the options
 */

void displayMainMenu(){
    while (true){
        int choice = MenuMan::createMenu("\nSelect what you pretend to do: ", {"Service Metrics","Calculate the maximum amount of trains that can simultaneously travel between two specific stations with minimum cost for the company","Reliability and sensitivity to line failures","Exit"});
        string source, destination, maxTrainStation;
        int max_trains;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean input buffer
        switch (choice) {
            case 1:
                displayServiceMetrics();
                break;
            case 2:
                cout << "\nEnter the source station name: ";
                getline(cin, source);
                cout << "\nEnter the destination station name: ";
                getline(cin, destination);
                max_trains = graph.maxFlowMinCost(source, destination);
                cout << "\nMaximum number of trains that can simultaneously travel with the minimum cost for the company: " << max_trains << endl;
                break;
            case 3:
                displayReliabilityMenu();
                break;
            case 4:
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
