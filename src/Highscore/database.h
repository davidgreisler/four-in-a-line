#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <QtSql>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "highscore.h"

using namespace std;
/**
 * @brief The Database class
 * This class serves as simple access to the local Highscore Database.
 * Once an object of this class is created, the local SQlite Database "DB.db3" will be created, if its not already there.
 * Afterwards player data can be inserted updated or selected. In case the data shall be cleared just delete the the database file "DB.db3"
 */
class Database : public QObject
{
private:
    QSqlDatabase db;
    int counter;

public:
    Database();
    ~Database();
    void insertHighscore(QString name1, QString name2, int result);
    vector <Highscore> getHighscoreData();
    Highscore getHighscoreData(QString name);
    bool dbExists();
    void clearHighscore();

private:
    void initialize();
    int playerExists(QString);
    void insertHighscore(QString name, int result);
    void updateHighscore(QString name, int result);
};

#endif // DATABASE_H
