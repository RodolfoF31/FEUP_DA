#include "Network.h"

/**
 * @brief Default constructor
 */

Network::Network()= default;

/**
 * @brief Constructor
 * @param station_A
 * @param station_B
 * @param capacity
 * @param service
 */

Network::Network(string station_A, string station_B, int capacity, ServiceType service){
    this->station_A = station_A;
    this->station_B = station_B;
    this->capacity = capacity;
    this->service = service;
}

/**
 * @brief Station_A setter
 * @param s
 */

void Network::setStation_A(string s){
    station_A = s;
}

/**
 * @brief Station_B setter
 * @param s
 */

void Network::setStation_B(string s){
    station_B = s;
}

/**
 * @brief Capacity setter
 * @param s
 */

void Network::setCapacity(int c){
    capacity = c;
}

/**
 * @brief Service setter
 * @param s
 */

void Network::setService(ServiceType s){
    service = s;
}

/**
 * @brief Station_A getter
 * @return string
 */

string Network::getStation_A() const{
    return station_A;
}

/**
 * @brief Station_B getter
 * @return string
 */

string Network::getStation_B() const{
    return station_B;
}

/**
 * @brief Capacity getter
 * @return int
 */

int Network::getCapacity() const{
    return capacity;
}

/**
 * @brief Service getter
 * @return ServiceType
 */

ServiceType Network::getService() const{
    return service;
}
