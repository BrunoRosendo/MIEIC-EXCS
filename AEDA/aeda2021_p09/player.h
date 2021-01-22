#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

//TODO
struct betHash
{
	int operator() (const Bet& b) const
	{
		int v = 0;
		tabHInt nums = b.getNumbers();
		for (tabHInt::const_iterator it = nums.begin(); it != nums.end(); it++)
		    v = 37*v + *it;
		return v;
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
	    if (b1.getNumbers().size() != b2.getNumbers().size()) return false;
	    tabHInt nums1 = b1.getNumbers();
        for (tabHInt::const_iterator it = nums1.begin(); it != nums1.end(); it++){
            if (!b2.contains(*it)) return false;
        }
		return true;
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player
{
	tabHBet bets;
	string name;
public:
	Player(string nm="anonymous") { name=nm; }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 
