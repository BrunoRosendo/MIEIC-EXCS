#include "fleet.h"
#include <string>
#include <algorithm>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *vl) {
    vehicles.push_back(vl);
}

int Fleet::numVehicles() const {
    return vehicles.size();
}

int Fleet::lowestYear() const {
    if (vehicles.size() == 0) return 0;
    int y = vehicles[0]->getYear();
    for (size_t i = 1; i < vehicles.size(); ++i){
        if (vehicles[i]->getYear() < y) y = vehicles[i]->getYear();
    }
    return y;
}


ostream & operator<<(ostream & o, const Fleet & f){
    for (size_t i = 0; i < f.vehicles.size(); ++i){
        f.vehicles[i]->info(o);
    }
    return o;
}

vector<Vehicle *> Fleet::operator()(int yearM) const {
    vector<Vehicle*> v;
    for (size_t i = 0; i < vehicles.size(); ++i){
        if (vehicles.at(i)->getYear() == yearM) v.push_back(vehicles.at(i));
    }
    return v;
}

float Fleet::totalTax() const {
    float total = 0;
    for (int i = 0; i < vehicles.size(); ++i){
        total += vehicles.at(i)->calculateTax();
    }
    return total;
}


unsigned Fleet::removeOldVehicles(int y1) {
    unsigned start = vehicles.size();
    vehicles.erase(remove_if(vehicles.begin(), vehicles.end(), [y1] (const Vehicle* v) {return v->getYear() <= y1;}), vehicles.end());
    return start - vehicles.size();
}