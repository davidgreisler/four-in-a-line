#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Database *db;
    db = new Database();
    if (db->dbExists())
    {
        ui->label->setText("Database located");
    }
    //db->updateHighscore("Joe", 1);
    db->insertHighscore("Ben", "Joe", 2);
    vector<Highscore> result = db->getHighscoreData();
    QString ausgabe = QString::fromStdString(result.at(1).getScore());
    ui->label->setText(ausgabe);
}

MainWindow::~MainWindow()
{
    delete ui;
}
