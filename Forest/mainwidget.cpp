#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "classes.h" //классы растение, погода и т. д. для работы программы
#include <qtimer.h>
#include <QMouseEvent>

#define TIME_TICK 1000 //время интервала таймера в миллисекундах

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    srand(time(NULL)); //автоматическая рандомизация генератора случайных чисел в зависимости от времени (чтобы всегда давал разный результат)
    QPixmap sun = QPixmap("sun.png"); //объект с картинкой солнца
    QPixmap cloud = QPixmap("cloud.png"); //объект с картинкой облака
    QPixmap rain = QPixmap("rain.png"); //объект с картинкой дождя
    ui->pogoda->setPixmap(sun); // вывести картинку в лейбл
    ui->place->setStyleSheet("background-image:url(\"dirt_grid.png\"); background-position: center;" ); // вывести земляной фон в frame

    QTimer *timer = new QTimer(); // таймер для работы модели
    timer->start(TIME_TICK); //запустить таймер с интервалом в одну секунду
    QObject::connect(timer, SIGNAL(timeout()), SLOT(Timer_tick())); //по истечении интервала работает слот
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mousePressEvent(QMouseEvent*e) //событие нажатия кнопки мыши внутри окна
{
    if(e->button()==Qt::LeftButton) //если нажата левая кнопка мыши
    {
        int x = cursor().pos().x();
        int y = cursor().pos().y();
        ui->label->setText(QString::number(x));
        ui->label_2->setText(QString::number(y));
    }
}

void MainWidget::Timer_tick() //слот интервала таймера
{
}
