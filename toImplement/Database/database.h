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

private:
    void initialize();
    int playerExists(QString);
    void insertHighscore(QString name, int result);
    void updateHighscore(QString name, int result);
};

#endif // DATABASE_H
