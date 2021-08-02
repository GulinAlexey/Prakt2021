#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "classes.h" //классы растение, погода и т. д. для работы программы
#include <qtimer.h>
#include <QMouseEvent>

QTimer *timer; // таймер для работы модели
Forest forest; //объект - лес
Weather weather; //объект - погода

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

    forest.Dirt_Init(); //инициализация ячеек почвы

    timer = new QTimer(); // таймер для работы модели
    timer->start(TIME_TICK); //запустить таймер с интервалом в одну секунду
    QObject::connect(timer, SIGNAL(timeout()), SLOT(Timer_tick())); //по истечении интервала работает слот
    QObject::connect(ui->normal_b, SIGNAL(toggled(bool)), SLOT(Normalmode(bool))); //привязать переключение радиокнопки к слоту
    QObject::connect(ui->speed_b, SIGNAL(toggled(bool)), SLOT(Speedmode(bool))); //привязать переключение радиокнопки к слоту
    QObject::connect(ui->pause_b, SIGNAL(toggled(bool)), SLOT(Pausemode(bool))); //привязать переключение радиокнопки к слоту

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
            if(ui->plant_b->isChecked()==true) //если был выбран режим посадки растения
            {
                int planttype; //тип высаживаемого растения (1 - трава, 2 - куст, 3 - дерево)
                QLabel **new_img=nullptr; //указатель на новый label с картинкой растения
                if(ui->grass_type->isChecked()==true)
                    planttype=1;
                if(ui->bush_type->isChecked()==true)
                    planttype=2;
                if(ui->tree_type->isChecked()==true)
                    planttype=3;
                forest.Add_plant(x,y,planttype); //добавить растение выбранного типа с выбранными координатами

                if(ui->grass_type->isChecked()==true)
                {
                    forest.get_img(new_img, forest.get_kolvo_grass()-1, planttype); //получить адрес для объекта - label с изображением растения
                    int x_plant, y_plant, radius_plant; //координаты x, y и радиус растения
                    int x_png, y_png, w_png, h_png; //координаты x, y изображения растения и его ширина, высота
                    x_plant=forest.get_x_plant(forest.get_kolvo_grass()-1, planttype); //получить значение поля растения
                    y_plant=forest.get_y_plant(forest.get_kolvo_grass()-1, planttype); //получить значение поля растения
                    radius_plant=forest.get_radius_plant(forest.get_kolvo_grass()-1, planttype); //получить значение поля растения
                    x_png = x_plant - radius_plant; //получить координату x верхнего левого угла изображения растения
                    y_png = y_plant + radius_plant; //получить координату y верхнего левого угла изображения растения
                    w_png = h_png = radius_plant*2; // получить ширину и высоту изображения
                    *new_img = new QLabel(""); //создать новый label для картинки данного растения
                    (*new_img)->setGeometry(x_png,y_png,w_png,h_png); //указать размеры картинки и её положение

                }
                if(ui->bush_type->isChecked()==true)
                {
                    forest.get_img(new_img, forest.get_kolvo_bush()-1, planttype); //получить адрес для объекта - label с изображением растения
                    *new_img = new QLabel(""); //создать новый label для картинки данного растения
                }
                if(ui->tree_type->isChecked()==true)
                {
                    forest.get_img(new_img, forest.get_kolvo_tree()-1, planttype); //получить адрес для объекта - label с изображением растения
                    *new_img = new QLabel(""); //создать новый label для картинки данного растения
                }

            }
            if(ui->delete_b->isChecked()==true) //если был выбран режим удаления растения
            {

            }
            if(ui->infoplant_b->isChecked()==true) //если был выбран режим инфо о растении
            {
                //ui->label->setText(QString::number(x)); //вывести координату х (временная строка)
                //ui->label_2->setText(QString::number(y)); //вывести координату y (временная строка)
            }
            if(ui->infodirt_b->isChecked()==true) //если был выбран режим инфо о почве
            {

            }
        }
    }
}

void MainWidget::Timer_tick() //слот интервала таймера
{
}

void MainWidget::Normalmode(bool value) //слот при переключении в нормальный режим времени
{
    if(value==true)
    {
        timer->start(TIME_TICK); //запустить таймер с интервалом в одну секунду
    }
}

void MainWidget::Speedmode(bool value) //слот при переключении в ускоренный режим времени
{
    if(value==true)
    {
        timer->start(SPEED_TICK); //запустить таймер с интервалом в треть секунды
    }
}

void MainWidget::Pausemode(bool value) //слот при переключении в режим времени - паузу
{
    if(value==true)
    {
        timer->stop(); //остановить таймер
    }
}
