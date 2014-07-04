#include "highscore.h"

Highscore::Highscore()
{
    name = "test";
    win = 0;
    loss =  0;
    draw = 0;
}

Highscore::Highscore(string n, int w, int l, int d)
{
    //argument check
    if ((n.empty()) || w < 0 || l < 0 || d < 0)
        throw invalid_argument("Highscore falsche oder unvollständige Argumente");
    name = n;
    win = w;
    loss = l;
    draw = d;
}

string Highscore::getName()
{
    return name;
}

int Highscore::getWin()
{
    return win;
}

int Highscore::getLoss()
{
    return loss;
}

int Highscore::getDraw()
{
    return draw;
}

Highscore& Highscore::operator=(const Highscore& score)
{
    if (this != &score)
    {
        name = score.name;
        win = score.win;
        loss = score.loss;
        draw = score.draw;
    }
    return *this;
}

string Highscore::getScore()
{
    stringstream wandler;
    wandler << getName() << " " << getWin() << " " << getLoss() << " " << getDraw() << "\n";
    return wandler.str();
}

std::ostream& operator<<(ostream& ausgabe, Highscore& score)
{
    ausgabe << score.getScore();
    return ausgabe;
}
