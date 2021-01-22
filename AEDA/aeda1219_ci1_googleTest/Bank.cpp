/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>
#include <set>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    double sum = 0;
	for (int i = 0; i < accounts.size(); ++i){
	    if ( accounts.at(i)->getCodH() == cod1){
            sum+= accounts.at(i)->getWithdraw();
	    }
	}
	return sum;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for (int i = 0; i < bankOfficers.size(); ++i){
	    if (bankOfficers.at(i).getName() == name){
	        for (auto account : bankOfficers.at(i).getAccounts()) res.push_back(account);
	        bankOfficers.erase(bankOfficers.begin() + i);
	    }
	}
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    for (int i = 0; i < bankOfficers.size(); ++i){
        if (bankOfficers.at(i).getName() == name){
            bankOfficers.at(i).addAccount(ac);
            return bankOfficers.at(i);
        }
    }
    throw NoBankOfficerException(name);
}


// a alterar

bool compareAccounts(Account* a1, Account* a2){
    if (a1->getBalance() < a2->getBalance()) return true;
    if (a1->getBalance() > a2->getBalance()) return false;
    return a1->getCodIBAN() < a2->getCodIBAN();
}

void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), compareAccounts);
}

NoBankOfficerException::NoBankOfficerException(string name) {
    this->name = name;
}

string NoBankOfficerException::getName() const {
    return name;
}