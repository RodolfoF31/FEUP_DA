#ifndef PROJETODA_FILEMAN_H
#define PROJETODA_FILEMAN_H

#include <string>
#include <vector>
#include <iostream>
#include "../Models/Network.h"
#include "../Models/Station.h"

using namespace std;

class FileMan {
public:
        static vector<Network> loadNetworks();
        static vector<Station> loadStations();
};


#endif //PROJETODA_FILEMAN_H
