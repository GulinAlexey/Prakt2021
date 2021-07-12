#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "classes.h" //классы растение, погода и т. д. для работы программы
#include <qtimer.h>
#include <QMouseEvent>

#define TIME_TICK 1000 //время интервала таймера в миллисекундах
#define PLACE_X_MIN 20 //координата оx верхнего левого угла площадки леса
#define PLACE_Y_MIN 20 //координата оy верхнего левого угла площадки леса
#define PLACE_SIZE_X 800 //размер площадки леса по горизонтали
#define PLACE_SIZE_Y 600 //размер площадки леса по вертикали

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
        int x = (cursor().pos().x())- (this->geometry().x())- PLACE_X_MIN; //координата х мыши относительно place (площадка леса)
        int y = cursor().pos().y()- (this->geometry().y())- PLACE_Y_MIN; //координата у мыши относительно place (площадка леса)
        if(x>0 && y>0 && x<PLACE_SIZE_X && y<PLACE_SIZE_Y) //если клик произошёл внутри площадки леса (place)
        {
            ui->label->setText(QString::number(x)); //вывести координату х (временная строка)
            ui->label_2->setText(QString::number(y)); //вывести координату y (временная строка)
        }
    }
}

void MainWidget::Timer_tick() //слот интервала таймера
{
}
