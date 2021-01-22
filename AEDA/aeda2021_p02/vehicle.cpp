#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y) {
    brand = b;
    month = m;
    year = y;
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::getMonth() const {
    return month;
}

string Vehicle::getBrand() const {
    return brand;
}

int Vehicle::info() const {
    cout << "Brand: " << brand << endl << "Month: " << month << endl << "Year: " << year << endl;
    return 3;
}


bool Vehicle::operator<(const Vehicle &v) const {
    if (this->year < v.getYear()) return true;
    if (this-> year > v.getYear()) return false;
    if (this->month < v.getMonth()) return true;
    return false;
}




MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl) : Vehicle(b, m, y) {
    fuel = f;
    cylinder = cyl;
}

string MotorVehicle::getFuel() const {
    return fuel;
}

int MotorVehicle::info() const {
    Vehicle::info();
    cout << "Fuel: " << fuel << " Cylinder: " << cylinder << endl;
    return 5;
}

int MotorVehicle::info(ostream &o) const {
    o << "Brand: " << brand << endl << "Month: " << month << endl << "Year: " << year << endl;
    o << "Fuel: " << fuel << " Cylinder: " << cylinder << endl;
    return 5;
}

float MotorVehicle::calculateTax() const {
    if (fuel == "gas"){
        if (cylinder <= 1000){
            if (year > 1995) return 14.56;
            else return 8.10;
        }
        else if (cylinder <= 1300){
            if (year > 1995) return 29.06;
            else return 14.56;
        }
        else if (cylinder <= 1750){
            if (year > 1995) return 45.15;
            else return 22.65;
        }
        else if (cylinder <= 2600) {
            if (year > 1995) return 113.98;
            else return 54.89;
        }
        else if (cylinder <= 3500){
            if (year > 1995) return 181.17;
            else return 87.13;
        }
        else{
            if (year > 1995) return 320.89;
            else return 148.13;
        }
    }
    else{
        if (cylinder <= 1500){
            if (year > 1995) return 14.56;
            else return 8.10;
        }
        else if (cylinder <= 2000){
            if (year > 1995) return 29.06;
            else return 14.56;
        }
        else if (cylinder <= 3000){
            if (year > 1995) return 45.15;
            else return 22.65;
        }
        else{
            if (year > 1995) return 113.98;
            else return 54.89;
        }
    }
}





Car::Car(string b, int m, int y, string f, int cyl) : MotorVehicle(b, m, y, f, cyl){}

int Car::info() const {
    return MotorVehicle::info();
}

int Car::info(ostream &o) const {
    return MotorVehicle::info(o);
}







Truck::Truck(string b, int m, int y, string f, int cyl, int ml) : MotorVehicle(b, m, y, f, cyl) {
    maximumLoad = ml;
}

int Truck::info() const {
    MotorVehicle::info();
    cout << "Max Load: " << maximumLoad << endl;
    return 6;
}

int Truck::info(ostream &o) const {
    MotorVehicle::info(o);
    o << "Max Load: " << maximumLoad << endl;
    return 6;
}






Bicycle::Bicycle(string b, int m, int y, string t) : Vehicle(b, m, y) {
    type = t;
}

int Bicycle::info() const {
    Vehicle::info();
    cout << "Type: " << type << endl;
    return 4;
}

int Bicycle::info(ostream &o) const {
    o << "Brand: " << brand << endl << "Month: " << month << endl << "Year: " << year << endl << "Type: " << type << endl;
    return 4;
}

float Bicycle::calculateTax() const {
    return 0;
}