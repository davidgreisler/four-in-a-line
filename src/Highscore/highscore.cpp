#include "highscore.h"

/**
 * @brief Highscore::Highscore
 * Standard Constructor, dummy values
 */
Highscore::Highscore()
{
    name = "test";
    win = 0;
    loss =  0;
    draw = 0;
}

/**
 * @brief Highscore::Highscore
 * Constructor
 * @param n     name of the player
 * @param w     number of wins
 * @param l     number of defeats
 * @param d     number of draws
 */
Highscore::Highscore(string n, int w, int l, int d)
{
    //argument check
    if ((n.empty()) || w < 0 || l < 0 || d < 0)
        throw invalid_argument("Highscore wrong or invalid arguments");
    name = n;
    win = w;
    loss = l;
    draw = d;
}

/**
 * @brief Highscore::getName
 * gets the name of the player
 * @return      name of the player
 */
string Highscore::getName()
{
    return name;
}

/**
 * @brief Highscore::getWin
 * gets the number of victories
 * @return      the number of victories
 */
int Highscore::getWin()
{
    return win;
}

/**
 * @brief Highscore::getLoss
 * gets the number of defeats
 * @return      the number of defeats
 */
int Highscore::getLoss()
{
    return loss;
}

/**
 * @brief Highscore::getDraw
 * gets the number of draws
 * @return      the number of draws
 */
int Highscore::getDraw()
{
    return draw;
}

/**
 * @brief Highscore::operator =
 * Copy constructor
 * @param score to be copied
 * @return a copy of the Highscore object
 */
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

/**
 * @brief Highscore::getScore
 * returns name, victories, defeats and draws as a string
 * @return name, victories, defeats and draws as a string
 */
string Highscore::getScore()
{
    stringstream s;
    s << getName() << " " << getWin() << " " << getLoss() << " " << getDraw() << "\n";
    return s.str();
}

/**
 * @brief operator <<
 * writes the Highscore data in the previosly named outputstream
 * @param output the previosly named outputstream in which shall be written
 * @param score Highscore which shall be written
 * @return output stream with the Highscore-data written inside
 */
std::ostream& operator<<(ostream& output, Highscore& score)
{
    output << score.getScore();
    return output;
}
