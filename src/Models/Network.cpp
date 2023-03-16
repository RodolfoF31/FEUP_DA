#include "Network.h"

Network::Network(){
    station_A = "";
    station_B = "";
    capacity = "";
    service = "";
}

Network::Network(string Station_A, string Station_B, int Capacity, string Service){
    this->station_A = Station_A;
    this->station_B = Station_B;
    this->capacity = Capacity;
    this->service = Service;
}

void Network::setStation_A(string s){
    station_A = s;
}

void Network::setStation_B(string s){
    station_A = s;
}

void Network::setCapacity(string s){
    capacity = s;
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

string Network::getCapacity(){
    return capacity;
}

string Network::getService(){
    return service;
}
