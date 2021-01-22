#ifndef CARPARK_H_
#define CARPARK_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class InfoCard {
public:
    string name;
    bool present;
    int frequency;
    bool operator==(const InfoCard& c) const;
    bool operator<(const InfoCard& c) const;
};

class CarPark {
    unsigned freePlaces;
    const unsigned  capacity;
    vector<InfoCard> clients;
    const unsigned numMaxClients;
public:
    CarPark(unsigned cap, unsigned nMaxCli);
    unsigned getNumPlaces() const;
    unsigned getNumMaxClients() const;
    unsigned getNumOccupiedPlaces() const;
    vector<InfoCard> getClients() const;
    unsigned getNumClients() const;
    bool addClient(const string & name);
    bool removeClient(const string & name);
    bool enter(const string & name);
    bool leave(const string & name);
    int clientPosition(const string & name) const;
    friend ostream & operator<<(ostream & os, const CarPark & cp);
    unsigned getFrequency(const string &name) const;
    InfoCard getClientAtPos(unsigned p) const;
    void sortClientsByFrequency();
    void sortClientsByName();
    vector<string> clientsBetween(unsigned f1, unsigned f2);
};


class ClientDoesNotExist{
private:
    string name;
public:
    ClientDoesNotExist(string name){
        this->name = name;
    }
    string getName() const{
        return name;
    }
};

class PositionDoesNotExist{
private:
    unsigned pos;
public:
    PositionDoesNotExist(unsigned pos){
        this->pos = pos;
    }
    unsigned getPosition() const{
        return pos;
    }
};

#endif /*CARPARK_H_*/
