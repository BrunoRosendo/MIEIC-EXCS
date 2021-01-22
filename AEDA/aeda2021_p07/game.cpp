#include "game.h"
#include <sstream>
#include <cmath>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}


//TODO
Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    int numCircles = pow(2, h+1) - 1;
    vector<Circle> circles;
    for (int i = 0; i < numCircles; ++i)
        circles.push_back(Circle(points[i], states[i]));
    vector<vector<Circle>> lines(h+1);   //reversed order
    for (int height = h; height >= 0; --height) {
        for (int i = pow(2, height) - 1; i < pow(2, height+1) - 1; ++i) {
            lines[h - height].push_back(circles.at(i));
        }
    }
    vector<BinaryTree<Circle>> treeLine;
    for (int l = 0; l < lines.size(); ++l){
        vector<BinaryTree<Circle>> newLine;
        for (int c = 0; c < lines[l].size(); ++c){
            if (l == 0) newLine.push_back(BinaryTree<Circle>(lines[l][c]));
            else newLine.push_back(BinaryTree<Circle>(lines[l][c], treeLine[2*c], treeLine[2*c+1]));
        }
        treeLine = newLine;
    }
    game = treeLine[0];
}


//TODO
string Game::writeGame()
{
	string result;
    BTItrLevel<Circle> it(game);
    while (!it.isAtEnd()){
        Circle c = it.retrieve();
        if (c.getState()) result += to_string(c.getPoints()) + "-true-" + to_string(c.getNVisits()) + "\n";
        else result += to_string(c.getPoints()) + "-false-" + to_string(c.getNVisits()) + "\n";
        it.advance();
    }
    return result;
}


//TODO
int Game::move()
{
    BTItrLevel<Circle> it(game);
    int points = 0;
    int nextCircle = 0;
    for (int n = 0; !it.isAtEnd(); ++n){
        if (n == nextCircle){
            if (it.retrieve().getState()) nextCircle = 2*n + 2;
            else nextCircle = 2*n + 1;
            it.retrieve().changeState();
            it.retrieve().increaseVisits();
            points = it.retrieve().getPoints();
        }
        it.advance();
    }
    return points;
}


//TODO
int Game::mostVisited()
{
    BTItrLevel<Circle> it(game);
    it.advance();
    int maxVisits = 0;
    while (!it.isAtEnd()){
        if (it.retrieve().getNVisits() > maxVisits) maxVisits = it.retrieve().getNVisits();
        it.advance();
    }
    return maxVisits;
}
