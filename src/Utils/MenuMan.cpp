#include "MenuMan.h"

/**
 * @brief Function that will be invoked to create each menu
 * @note Time-complexity -> O(n)
 * @param title menu title
 * @param options menu options
 * @return user selection (n)
 */

int MenuMan::createMenu(const string& title, vector<string> options) {
    cout << title << endl << endl;
    for (int i = 0; i < options.size(); i++) {
        cout << i + 1 << ": " << options[i] << endl;
    }

    cout << endl << ">> ";
    int n;
    cin >> n;

    return n;
}
