#ifndef PROJETODA_NETWORK_H
#define PROJETODA_NETWORK_H

#include <string>

using namespace std;

class Network {

private:

    string station_A;
    string station_B;
    int capacity;
    string service;

public:

    Network();
    Network(string station_A, string station_B, int capacity, string service);
    void setStation_A(string s);
    void setStation_B(string s);
    void setCapacity(int c);
    void setService(string s);
    string getStation_A();
    string getStation_B();
    int getCapacity();
    string getService();

};


#endif //PROJETODA_NETWORK_H
