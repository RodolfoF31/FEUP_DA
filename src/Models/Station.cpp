#include "Station.h"

Station::Station() = default;

Station::Station(string name, string district, string municipality, string township, string line){
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

void Station::setName(string s){
    name = s;
}

void Station::setDistrict(string s){
    district = s;
}

void Station::setMunicipality(string s){
    municipality = s;
}

void Station::setTownship(string s) {
    township = s;
}

void Station::setLine(string s){
    line = s;
}

string Station::getName() const{
    return name;
}

string Station::getDistrict(){
    return district;
}

string Station::getLine(){
    return line;
}

string Station::getMunicipality(){
    return municipality;
}

string Station::getTownship(){
    return township;
}
