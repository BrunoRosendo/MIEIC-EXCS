#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO
Game::Game()
{
}

// TODO
Game::Game(list<Kid>& l2)
{
    kids = l2;
}

// TODO
void Game::addKid(const Kid &k1)
{
    kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const
{
    list<Kid> res;
    res = kids;
    return res;
}

// TODO
string Game::write() const
{
    string res;
    for (list<Kid>::const_iterator it = kids.begin(); it != kids.end(); ++it){
        res += (*it).write() + "\n";
    }
    return res;
}

// TODO
Kid& Game::loseGame(string phrase)
{
    int num = numberOfWords(phrase);
    list<Kid>::iterator it = kids.begin();
    int n = (num-1) % kids.size();
    for (int i = 0; i < n; ++i){
        it++;
    }
    Kid *k1 = new Kid(it->getName(), it->getAge());
    return *k1;
}

// TODO
list<Kid>& Game::reverse()
{
    kids.reverse();
    return kids;
}

// TODO
list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;
    for (list<Kid>::iterator it = kids.begin(); it != kids.end(); ++it){
        if (it->getAge() > id) {
            res.push_back(*it);
            it = kids.erase(it);
            it--;
        }
    }
    return res;
}

// TODO
void Game::setKids(const list<Kid>& l1)
{
    kids = l1;
}

// TODO
bool Game::operator==(Game& g2)
{
    if (kids.size() != g2.getKids().size()) return false;
    list<Kid>::iterator it1 = kids.begin();
    list<Kid>::iterator it2 = g2.getKids().begin();
    for (int i = 0; i < kids.size(); ++i){
        if (!(*it1 == *it2)) return false;
        it1++;
        it2++;
    }
	return true;
}

// TODO
list<Kid> Game::shuffle() const
{
    list<Kid> res;
    list<Kid> temp = kids;
    int num = temp.size();
    for (int i = 0; i < num; ++i){
        int r = rand() % temp.size();
        list<Kid>::iterator it = temp.begin ();
        for (int j = 0; j < r; j++) it++;
        res.push_back(*it);
        temp.erase(it);
    }
    return res;
}
