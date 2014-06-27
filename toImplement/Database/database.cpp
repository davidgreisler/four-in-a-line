#include "database.h"

Database::Database()
{
   db = QSqlDatabase::addDatabase("QSQLITE");
   //db.addDatabase("QSQLITE");
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

Database::~Database()
{
    QString conName = db.connectionName();
    delete &db;
    QSqlDatabase::removeDatabase(conName);
}

/**
 *creates the database and inserts insert an empty players table for names, wins, losses, and draws
 */
void Database::initialize()
{
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("DB.db3"); //QDir::homePath() + QDir::separator() + "DB.db3");
    //cout << QDir::homePath().toStdString() << QDir::separator() << "DB.db3";
    if (db.open())
    {
       QSqlQuery query = QSqlQuery(db);
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
    //QString conName = db.connectionName();
    db.close();
}

void Database::insertHighscore(QString name1, QString name2, int result)
{
    //argument check
    if (name1 == 0 || name2 ==  0 || result < 0 || result > 2)
        throw invalid_argument("falsche Argumente");
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
            //nicht erreichbar
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
  selects content of the highscore table
  @return Highscore Vector with player data
 */
vector <Highscore> Database::getHighscoreData()
{
    vector <Highscore> results;
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("DB.db3");
    if(db.open())
    {
        //select highscore
        QSqlQuery query(db);
        if (query.exec("SELECT name, won, draw, loss FROM players;"))
        {
            std::cout << "players selected." <<endl;
            while(query.next())
            {
                /*std::cout << query.value(0).toString().toStdString() <<endl;
                std::cout << query.value(1).toInt() << endl;
                std::cout << query.value(2).toInt() << endl;
                std::cout << query.value(3).toInt() << endl;*/
                results.push_back(Highscore(query.value(0).toString().toStdString(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt()));

            }
        }
        else
        {
            qDebug() << "error while recalling game." << query.lastError();
        }
    }
    //QString conName = db.connectionName();
    db.close();
    //delete &db;
    //QSqlDatabase::removeDatabase(conName);
    return results;
}

/**
 * @brief Database::getHighscoreData
 * @param name
 * @return
 */
Highscore Database::getHighscoreData(QString name)
{
    Highscore results;
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("DB.db3");
    if(db.open())
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
                /*std::cout << query.value(0).toString().toStdString() <<endl;
                std::cout << query.value(1).toInt() << endl;
                std::cout << query.value(2).toInt() << endl;
                std::cout << query.value(3).toInt() << endl;*/
                results = Highscore(query.value(0).toString().toStdString(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt());
            }
        }
        else
        {
            qDebug() << "error while recalling game." << query.lastError();
        }
    }
    //QString conName = db.connectionName();
    db.close();
    //delete &db;
    //QSqlDatabase::removeDatabase(conName);
    return results;
}

/**
checks whether database exists already or not.
@return bool-value whether database exists (true) already or not (false).
*/
bool Database::dbExists()
{
    ifstream pruefer("DB.db3");
    return pruefer;
}

/**
 * @brief Database::playerExists
 * @param name
 * @return
 */
int Database::playerExists(QString name)
{
    //argument check
    if (name == 0)
        throw invalid_argument("falsche Argumente");
    //open database
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("DB.db3");
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
    //delete &db;
    //QSqlDatabase::removeDatabase(conName);
    return xists;
}

void Database::insertHighscore(QString name, int result)
{
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("DB.db3");
    if(db.open())
    {
        QSqlQuery query = QSqlQuery(db);
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
    //QString conName = db.connectionName();
    db.close();
    //delete &db;
   //QSqlDatabase::removeDatabase(conName);
}


/** --------------------------------------------funktioniert noch nicht bekomme "Parameter count mismatch"
 * @brief Database::updateHighscore
 * @param name
 * @param result
 */
void Database::updateHighscore(QString name, int result)
{
    Highscore oldData = getHighscoreData(name);
    cout << oldData.getScore();
    QSqlQuery query = QSqlQuery(db);
    if (db.open())
    {
        qDebug() << "versuche Update";
        int win = (result == 1) ? oldData.getWin() + 1 : oldData.getWin();
        int loss = (result == 0) ? oldData.getLoss() + 1 : oldData.getLoss();
        int draw = (result == 2) ? oldData.getDraw() + 1 : oldData.getDraw();
        stringstream str;
        str << "UPDATE players SET won = " << win << ", loss = " << loss << ", draw = " << draw << "  WHERE name = '" << name.toStdString() << '\'' <<';';
        qDebug() << "vor ausführung";
        string s = str.str();
        cout << s << endl;
        QString queryString = QString::fromStdString(s);
        db.exec(queryString);/*)
        {
            qDebug() << "Highscore updated.";
        }
        else
        {
            qDebug() << "error while updating player " << name  << "."  << query.lastError();
        }*/
    }
    //QString conName = db.connectionName();
    db.close();
    //delete &db;
   //QSqlDatabase::removeDatabase(conName);
}


