#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

//TODO
Client::Client() {
    numGifts = rand() % 5 + 1;
}

//TODO
unsigned Client::getNumGifts() const {
    return numGifts;
}


//TODO
Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime = 0;
    nextEnter = rand() % 20 + 1;
    nextLeave = 0;
    numAttendedClients = 0;
}

//TODO
unsigned Counter::getActualTime() const {
    return actualTime;
}

//TODO
unsigned Counter::getNextEnter() const {
    return nextEnter;
}

//TODO
unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

//TODO
unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

//TODO
unsigned Counter::getNextLeave() const {
    return nextLeave;
}

//TODO
Client & Counter::getNextClient() {
    if (clients.empty()) throw EmptyQueue();
    return clients.front();
}

//TODO
void Counter::enter()
{
    Client* c = new Client;
    clients.push(*c);
    nextEnter = rand() % 20 + 1;
    if (clients.size() == 1)
        nextLeave = actualTime + c->getNumGifts()*wrappingTime;
    cout << "time = " << actualTime <<"\n" << "new customer arrived with " << c->getNumGifts() << " gifts" << endl;
}

//TODO
void Counter::leave()
{
    try{
        getNextClient();
    }
    catch (EmptyQueue& e){
        cout << "Exception caught, empty queue: " << e.getMsg() << endl;
        return;
    }
    Client c = clients.front();
    clients.pop();
    nextLeave = actualTime + clients.front().getNumGifts()*wrappingTime;
    cout << "time= " << actualTime << "\n" << "costumer left with " << c.getNumGifts() << " gifts" << endl;
}

//TODO
void Counter:: nextEvent()
{
    if (nextLeave <= nextEnter) {
        leave();
        actualTime += nextLeave;
    }
    else {
        enter();
        actualTime += nextEnter;
    }
}


//TODO
ostream & operator << (ostream & out, const Counter & c2)
{
    out << "Number of attended clients: " << c2.getNumAttendedClients() << endl;
    out << "Number of clients waiting: " << c2.clients.size() << endl;
     return out;
}


