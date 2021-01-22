#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

bool InfoCard::operator==(const InfoCard& c) const {
    return this->name == c.name;
}

bool InfoCard::operator<(const InfoCard &c) const {
    if (this->frequency == c.frequency){
        return this->name < c.name;
    }
    else return this->frequency > c.frequency;
}

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}

// TODO
int CarPark::clientPosition(const string & name) const
{
    InfoCard search;
    search.name = name;
    return sequentialSearch(clients, search);
}

// TODO
unsigned CarPark::getFrequency(const string &name) const
{
    int pos = clientPosition(name);
    if (pos == -1) throw ClientDoesNotExist(name);
    return clients.at(pos).frequency;
}

// TODO: to modify
bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    info.frequency = 0;
    clients.push_back(info);
    return true;
}

// TODO: to modify
bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

// TODO: to modify
bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    clients[pos].frequency++;
    freePlaces--;
    return true;
}

// TODO: to modify
bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


// TODO
InfoCard CarPark::getClientAtPos(unsigned p) const
{
    InfoCard info;
    if (p > clients.size() - 1) throw PositionDoesNotExist(p);
    else info = clients.at(p);
    return info;
}

// TODO
void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

// TODO
void CarPark::sortClientsByName() //bubble sort
{
    for (int j = clients.size() - 1; j > 0; j--){
        bool end = true;
        for (int i = 0; i < j; i++){
            if (clients.at(i+1).name < clients.at(i).name){
                swap(clients[i], clients[i+1]);
                end = false;
            }
        }
        if (end) return;
    }
}

// TODO
vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    vector<string> names;
    sortClientsByFrequency();
    for (vector<InfoCard>::iterator it = clients.begin(); it < clients.end(); ++it){
        if ((*it).frequency >= f1 && (*it).frequency <= f2) names.push_back((*it).name);
    }
    return names;
}


// TODO
ostream & operator<<(ostream & os, const CarPark & cp)
{
    vector<InfoCard> copia = cp.getClients();
    for (vector<InfoCard>::iterator it = copia.begin(); it < copia.end(); ++it){
        os << (*it).name << endl;
        if ((*it).present) os << "This client is present on the park" << endl;
        else os << "This client is not present on the park" << endl;
        os << "The client has been on the park " << (*it).frequency << " times" << endl << endl;
    }
    return os;
}

/**
PERGUNTA 2
a) Temporal- n^2
   Spatial- Constant (1)
b) Temporal- log(n)
   Spatial- constant (1)
*/