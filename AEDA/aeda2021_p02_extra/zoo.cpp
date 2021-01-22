#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
    string info;
    for (int i = 0; i < animals.size(); ++i){
        info += animals.at(i)->getInfo() + "\n";
    }
    return info;
}

bool Zoo::isYoung(string nameA) {
    for (int i = 0; i < animals.size(); ++i){
        if (animals.at(i)->getName() == nameA) return animals.at(i)->isYoung();
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    while (!isV.eof()){
        string name;
        long code;
        getline(isV, name);
        isV >> code;
        if(isV.fail()) break;
        isV.ignore(100, '\n');
        Veterinary* v = new Veterinary(name, code);
        veterinarians.push_back(v);

    }
    for (int i = 0; i < animals.size(); ++i){
        animals.at(i)->setVeterinary(veterinarians.at(i % veterinarians.size()));
    }
}

bool Zoo::removeVeterinary(string nameV) {
    for (int i = 0; i < veterinarians.size(); ++i){
        if (veterinarians.at(i)->getName() == nameV){
            for (int j = 0; j < animals.size(); ++j){
                if (animals.at(j)->getVeterinary()->getName() == nameV){
                    animals.at(j)->setVeterinary(veterinarians.at((i+1)%veterinarians.size()));
                }
            }
            delete veterinarians[i];
            veterinarians.erase(veterinarians.begin() + i);
            return true;
        }
    }
    return false;
}

bool Zoo::operator<(Zoo &zoo2) const {
    int age1 = 0, age2 = 0;
    for (int i = 0; i < animals.size(); ++i){
        age1+= animals.at(i)->getAge();
    }
    for (int i = 0; i < zoo2.numAnimals();++i){
        age2+= zoo2.animals.at(i)->getAge();   //class level access and not object level access!
    }
    return age1 < age2;
}