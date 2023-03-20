#include "Utils/MenuMan.h"
#include "Utils/FileMan.h"

void displayMainMenu(){
    while (true){
        int choice = MenuMan::createMenu("Select what you pretend to do: ", {"","Exit"});
        switch (choice) {
            case 1:
                //TODO
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
    vector<Network> networks = FileMan::loadNetworks("../dataset/network.csv"); // stations.csv has an invalid capacity value somewhere
    /*for(Network network: networks) cout << network.getCapacity();*/ 
    displayMainMenu();
    return 0;
}
