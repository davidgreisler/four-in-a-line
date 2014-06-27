#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;

class Highscore
{
   private:
    string name;
    int win;
    int loss;
    int draw;


public:
    Highscore();
    Highscore(string name, int win, int loss, int draw);
    Highscore& operator=(const Highscore& score);
    string getName();
    int getWin();
    int getLoss();
    int getDraw();
    string getScore();

private:

};

std::ostream& operator<<(ostream& ausgabe, const Highscore& score);

#endif // HIGHSCORE_H
