#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap sun = QPixmap("sun.png");
    ui->->SetPixmap(sun);
}

MainWindow::~MainWindow()
{
    delete ui;
}

