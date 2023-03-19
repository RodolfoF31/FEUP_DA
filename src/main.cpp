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
    vector<Network> networks = FileMan::loadNetworks();
    vector<Station> stations = FileMan::loadStations();
    displayMainMenu();
    return 0;
}
