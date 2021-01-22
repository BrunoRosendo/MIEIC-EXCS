#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


//TODO
bool Bet::contains(unsigned num) const
{
	return numbers.find(num) != numbers.end();
}

//TODO
void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    int i = 0;
    while (numbers.size() < n) {
        numbers.insert(values.at(i));
        i++;
    }
}

//TODO
unsigned Bet::countRights(const tabHInt& draw) const
{
	unsigned sum = 0;
	for (unordered_set<unsigned>::const_iterator it = draw.begin(); it != draw.end(); ++it){
	    if (numbers.find(*it) != numbers.end()) sum++;
	}
	return sum;
}
