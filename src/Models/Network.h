#ifndef PROJETODA_NETWORK_H
#define PROJETODA_NETWORK_H

#include <string>

using namespace std;

enum class ServiceType {
    STANDARD,
    ALFA_PENDULAR
};

class Network {

private:

    string station_A;
    string station_B;
    int capacity;
    ServiceType service;

public:

    Network();
    Network(string station_A, string station_B, int capacity, ServiceType service);
    void setStation_A(string s);
    void setStation_B(string s);
    void setCapacity(int c);
    void setService(ServiceType s);
    string getStation_A();
    string getStation_B();
    int getCapacity();
    ServiceType getService();

};


#endif //PROJETODA_NETWORK_H
