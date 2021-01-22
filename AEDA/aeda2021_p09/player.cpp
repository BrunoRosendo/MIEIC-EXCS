#include "player.h"

//TODO
void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

//TODO
unsigned Player::betsInNumber(unsigned num) const
{
    unsigned sum = 0;
	for (tabHBet::const_iterator it = bets.begin(); it != bets.end(); ++it){
	        if ((*it).contains(num)) sum++;
	}
	return sum;
}

//TODO
tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
    for (tabHBet::const_iterator it = bets.begin(); it != bets.end(); ++it){
        unsigned sum = 0;
        for (tabHInt::const_iterator it2 = draw.begin(); it2 != draw.end(); ++it2)
            if ((*it).contains(*it2)) sum++;
        if (sum > 3) res.insert(*it);
    }
    return res;
}
