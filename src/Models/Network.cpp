#include "Network.h"

Network::Network()= default;

Network::Network(string station_A, string station_B, int capacity, ServiceType service){
    this->station_A = station_A;
    this->station_B = station_B;
    this->capacity = capacity;
    this->service = service;
}

void Network::setStation_A(string s){
    station_A = s;
}

void Network::setStation_B(string s){
    station_B = s;
}

void Network::setCapacity(int c){
    capacity = c;
}

void Network::setService(ServiceType s){
    service = s;
}

string Network::getStation_A() const{
    return station_A;
}

string Network::getStation_B() const{
    return station_B;
}

int Network::getCapacity() const{
    return capacity;
}

ServiceType Network::getService() const{
    return service;
}
