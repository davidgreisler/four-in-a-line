#include "database.h"

/**
 * @brief Database::Database
 * Standard Constuctor for Database-objects
 * In case the database doesn't already exist, it will be created and initialized.
 * Furthermore row counter will be initialized
 */
Database::Database()
{
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("DB.db3"); //QDir::homePath() + QDir::separator() + "DB.db3");
   if(!dbExists())
   {
       initialize();
   }
   db.open();
   QSqlQuery query(db);
   query.exec("SELECT COUNT ID FROM players");
   if (query.next())
   {
       counter = query.value(0).toInt();
       qDebug() << "got id " << counter;
   }
}

/**
 * @brief Database::~Database
 * cuts all connection from the program to the database
 */
Database::~Database()
{
    QString conName = db.connectionName();
    delete &db;
    QSqlDatabase::removeDatabase(conName);
}

/**
 * @brief Database::initialize
 * creates the database and inserts insert an empty players table for names, wins, losses, and draws
 */
void Database::initialize()
{
    if (db.open())
    {
       QSqlQuery query(db);
       if (query.exec("CREATE TABLE players("  \
                       "ID                  INT PRIMARY KEY     NOT NULL," \
                       "name                VARCHAR(30) NOT NULL," \
                       "won                 INT NOT NULL," \
                       "draw                INT NOT NULL," \
                       "loss                INT NOT NULL);"
                      )
              )
       {
           qDebug() << "table created.";
       }
       else
       {
           qDebug() << "error while creating table." << query.lastError();
       }
    }
    else
    {
       qDebug() << "DB could not be opened.";
       qDebug() << db.lastError();
       qDebug() << QSqlDatabase::drivers();
    }
    db.close();
}

/**
 * @brief Database::insertHighscore
 * allows to insert highscore data via the parameters from a single game for both players.
 * if a player with the same name in the database already exists, the respective row will be updated.
 * @param name1 name of player 1
 * @param name2 name of player 2
 * @param result 2 = draw, 1 = player 1 wins, 0 = player 2 wins
 */
void Database::insertHighscore(QString name1, QString name2, int result)
{
    //argument check
    if (name1 == 0 || name2 ==  0 || result < 0 || result > 2)
        throw invalid_argument("invalid arguments");
    int p1 = playerExists(name1);
    int p2 = playerExists(name2);
    if (p1 == -1)
    {
        insertHighscore(name1, result);
    }
    else
    {
        updateHighscore(name1, result);
    }
    int newResult = 0;
    switch (result)
    {
        case 0:
            newResult = 1;
            break;
        case 1:
            newResult = 0;
            break;
        case 2:
            newResult = 2;
            break;
        default:
            //not reachable
            break;
    }

    if (p2 == -1)
    {
        insertHighscore(name2, newResult);
    }
    else
    {
        updateHighscore(name2, newResult);
    }
}

/**
 * @brief Database::getHighscoreData
 * selects the content from the highscore table and returns it as Highscore Vector
 * @return Highscore Vector with player data
 */
vector <Highscore> Database::getHighscoreData()
{
    vector <Highscore> results;
    if(db.open())
    {
        //select highscore
        QSqlQuery query(db);
        if (query.exec("SELECT name, won, draw, loss FROM players ORDER BY won;"))
        {
            while(query.next())
            {
                results.push_back(Highscore(query.value(0).toString().toStdString(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt()));
            }
        }
        else
        {
            qDebug() << "error while recalling game." << query.lastError();
        }
    }
    db.close();
    return results;
}

/**
 * @brief Database::getHighscoreData
 * returns Highscore data of a single player from the database
 * @param name name of the player data which is to be selected
 * @return Highscore data of a single player
 */
Highscore Database::getHighscoreData(QString name)
{
    Highscore results;
    if (db.open())
    {
        //select highscore
        QSqlQuery query(db);
        query.prepare("SELECT name, won, draw, loss FROM players WHERE name = :n;");
        query.bindValue(":n", name);
        if (query.exec())
        {
            qDebug() << "players selected.";
            while(query.next())
            {
                results = Highscore(query.value(0).toString().toStdString(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt());
            }
        }
        else
        {
            qDebug() << "error while recalling game." << query.lastError();
        }
    }
    db.close();
    return results;
}


/**
 * @brief Database::dbExists
 *  checks whether database exists already or not.
 * @return bool-value whether database exists (true) already or not (false).
 */
bool Database::dbExists()
{
    ifstream tester("DB.db3");
    return tester;
}



/**
 * @brief Database::playerExists
 *  checks whether a player exists in the database already or not.
 * @param name name of the player
 * @return -1 if it doesn't exist, else the Id of the player in the database
 */
int Database::playerExists(QString name)
{
    if (name == 0)
        throw invalid_argument("invalid arguments");
    int xists = -1;
    if (db.open())
    {
        //check if player exist
        QSqlQuery query(db);
        query.prepare("SELECT ID FROM players where name =:p1");
        query.bindValue(":p1", name);
        if (query.exec())
        {
            qDebug() << "trying selected name.";
            if (query.next())
            {
               xists = query.value(0).toInt();
               qDebug() << "name found.";
            }
        }
        else
        {
         qDebug() << "error while selecting name." << query.lastError();
        }
    }
     db.close();
    return xists;
}

/**
 * @brief Database::insertHighscore
 * inserts Highscore-data of a new player
 * @param name      player name
 * @param result    result 2 = draw, 1 = player wons, 0 = player lost
 */
void Database::insertHighscore(QString name, int result)
{
    if(db.open())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO players (id, name, won, loss, draw) VALUES (:i, :n, :w, :l, :d);");
        query.bindValue(":i", counter);
        query.bindValue(":n", name);
        query.bindValue(":w", (result == 1) ? 1 : 0);
        query.bindValue(":l", (result == 0) ? 1 : 0);
        query.bindValue(":d", (result == 2) ? 1 : 0);
        if (query.exec())
        {
            qDebug() << "Highscore inserted.";
            counter++;
        }
        else
        {
            qDebug() << "error while inserting player." << query.lastError();
        }
    }
    db.close();
}

/**
 * @brief Database::clearHighscore
 * clears the Database
 */
void Database::clearHighscore()
{
    if(db.open())
    {
        db.exec("DELETE FROM players");
    }
    db.close();
}


/**
 * @brief Database::updateHighscore
 * updates the Highscore data from a specific player
 * @param name      name of player whose data shall be updated
 * @param result    result 2 = draw, 1 = player wons, 0 = player lost
 *
 * comment: somehow I didn't manage to use the same stucture as in the other methods (query.prepare(), query.exc()).
 * Since this method is private and the name is checked before (in insertHighscore()) it will only be called with valid names. So ther should be no danger of SQL injection.
 */
void Database::updateHighscore(QString name, int result)
{
    Highscore oldData = getHighscoreData(name);
    cout << oldData.getScore();
    if (db.open())
    {
        int win = (result == 1) ? oldData.getWin() + 1 : oldData.getWin();
        int loss = (result == 0) ? oldData.getLoss() + 1 : oldData.getLoss();
        int draw = (result == 2) ? oldData.getDraw() + 1 : oldData.getDraw();
        stringstream str;
        str << "UPDATE players SET won = " << win << ", loss = " << loss << ", draw = " << draw << "  WHERE name = '" << name.toStdString() << '\'' <<';';
        string s = str.str();
        cout << s << endl;
        QString queryString = QString::fromStdString(s);
        db.exec(queryString);
    }
    db.close();
}


