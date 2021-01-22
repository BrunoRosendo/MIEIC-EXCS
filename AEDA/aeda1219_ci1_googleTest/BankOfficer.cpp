/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::nextid = 1;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string name) {
    this->name = name;
    id = nextid++;
}

bool BankOfficer::operator>(BankOfficer& b) const{
    if (myAccounts.size() > b.getAccounts().size()) return true;
    if (myAccounts.size() < b.getAccounts().size()) return false;
    return name > b.getName();
}

