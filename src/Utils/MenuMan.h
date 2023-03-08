#ifndef PROJETODA_MENUMAN_H
#define PROJETODA_MENUMAN_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class MenuMan {
    public:
        static int createMenu(string title, vector<string> options);
};


#endif //PROJETODA_MENUMAN_H
