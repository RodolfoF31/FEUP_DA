#include "Network.h"

Network::Network(){
    station_A = "";
    station_B = "";
    capacity = 0;
    service = "";
}

Network::Network(string station_A, string station_B, int capacity, string service){
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

void Network::setService(string s){
    service = s;
}

string Network::getStation_A(){
    return station_A;
}

string Network::getStation_B(){
    return station_B;
}

int Network::getCapacity(){
    return capacity;
}

string Network::getService(){
    return service;
}
