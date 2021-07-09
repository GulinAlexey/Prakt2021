#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QPixmap sun = QPixmap("sun.png"); //объект с картинкой
    ui->pogoda->setPixmap(sun); // вывести картинку в лейбл
}

MainWidget::~MainWidget()
{
    delete ui;
}

