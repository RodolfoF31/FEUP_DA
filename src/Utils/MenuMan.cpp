#include "MenuMan.h"

/**
 * Função que vai ser invocada para criar cada menu
 * Time-complexity -> O(n)
 * @param title Título do menu
 * @param options Opções do menu
 * @return n
 */

int MenuMan::createMenu(string title, vector<string> options) {
    cout << title << endl << endl;
    for (int i = 0; i < options.size(); i++) {
        cout << i + 1 << ": " << options[i] << endl;
    }

    cout << endl << ">> ";
    int n;
    cin >> n;

    return n;
}
