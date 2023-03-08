#include "Utils/MenuMan.h"

void displayMainMenu(){
    while (true){
        int choice = MenuMan::createMenu("Selecione o que pretende fazer", {"Carregar Dados","Sair"});
        switch (choice) {
            case 1:
                //TODO
                break;
            case 2:
                return;
            default:
                cout << "Por favor, selecione uma opcao valida!" << endl;
        }
    }
}

int main() {
    displayMainMenu();
    return 0;
}
