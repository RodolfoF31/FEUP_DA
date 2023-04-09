#ifndef PROJETODA_STATION_H
#define PROJETODA_STATION_H

#include <string>

using namespace std;

class Station {
private:

    string name;
    string district;
    string municipality;
    string township;
    string line;

public:

    Station();
    Station(string name, string district, string municipality, string township, string line);
    void setName(string s);
    void setDistrict(string s);
    void setMunicipality(string s);
    void setTownship(string s);
    void setLine(string s);
    string getName() const;
    string getDistrict() const;
    string getMunicipality() const;
    string getTownship();
    const string& getLine() const;
};


#endif //PROJETODA_STATION_H
