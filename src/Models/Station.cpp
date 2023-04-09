#include "Station.h"

/**
 * @brief
 * Default Constructor
 */

Station::Station() = default;

/**
 * @brief Constructor
 * @param name
 * @param district
 * @param municipality
 * @param township
 * @param line
 */

Station::Station(string name, string district, string municipality, string township, string line){
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

/**
 * @brief Station name setter
 * @param s
 */

void Station::setName(string s){
    name = s;
}

/**
 * @brief District setter
 * @param s
 */

void Station::setDistrict(string s){
    district = s;
}

/**
 * @brief Municipality setter
 * @param s
 */

void Station::setMunicipality(string s){
    municipality = s;
}

/**
 * @brief Township setter
 * @param s
 */

void Station::setTownship(string s) {
    township = s;
}

/**
 * @brief Line setter
 * @param s
 */

void Station::setLine(string s){
    line = s;
}

/**
 * @brief Station name getter
 * @return string
 */

string Station::getName() const{
    return name;
}

/**
 * @brief District getter
 * @return string
 */

string Station::getDistrict() const {
    return district;
}

/**
 * @brief Line getter
 * @return string
 */

const string& Station::getLine() const{
    return line;
}

/**
 * @brief Municipality getter
 * @return string
 */

string Station::getMunicipality() const {
    return municipality;
}

/**
 * @brief Township getter
 * @return string
 */

string Station::getTownship(){
    return township;
}
