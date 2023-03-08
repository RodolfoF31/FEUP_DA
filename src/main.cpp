#include "Utils/MenuMan.h"

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
    //TODO read data
    displayMainMenu();
    return 0;
}
