#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "classes.h" //классы растение, погода и т. д. для работы программы
#include <qtimer.h>
#include <math.h>
#include <QMouseEvent>

QTimer *timer; // таймер для работы модели (рост растений и смена погоды)
QTimer *human_tick; // таймер для работы моделей - людей (их перемещение и взаимодействие)
Forest forest; //объект - лес
Weather weather; //объект - погода
Forester forester; //объект - лесник
Invaders invaders; //объект - чужаки
QLabel *house_img; //объект - label с картинкой домика лесника

int num_info=-1; //номер растения/ячейки почвы для инфо
int type_of_info=-1; //тип вывода инфо (-1 - никакое, 0 - ячейка почвы, 1 - трава, 2 - куст, 3 - дерево)
int all_time=0; //общее время работы программы (кол-во тиков)
int all_plants_died=0; //кол-во растений, которые завяли и погибли
int f_house_img=0; //флаг вывода картинки дома лесника
int forester_is_on=0; //флаг "включения" лесника (иначе он не выводится на экран)
int f_pause_human=0; //если флаг отмечен, то ранее была включена пауза для модели людей
int time_for_new_poacher=0; //отсчёт времени до появления нового браконьера (если их меньше, чем 2)
int f_speed_start=0; //флаг быстрого запуска

struct plant_sort //структура для сортировки растений (их упорядочиванию по высоте или агрессивности)
{
    int num;
    int type;
    int radius;
    int height;
    int agressiv;
};

QPixmap *sun; //объект с картинкой солнца
QPixmap *cloud; //объект с картинкой облака
QPixmap *rain; //объект с картинкой дождя
QPixmap *pgrass; //объект с картинкой Трава
QPixmap *pbush; //объект с картинкой Куст
QPixmap *ptree; //объект с картинкой Дерево
QPixmap *pgrass_selected; //объект с картинкой Трава выбранная
QPixmap *pbush_selected; //объект с картинкой Куст выбранный
QPixmap *ptree_selected; //объект с картинкой Дерево выбранное
QPixmap *pforester; //объект с картинкой Лесник
QPixmap *ppoacher1; //объект с картинкой Браконьер 1
QPixmap *ppoacher2; //объект с картинкой Браконьер 2
QPixmap *phouse; //объект с картинкой Домик в лесу (принадлежит леснику)

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    srand(time(NULL)); //автоматическая рандомизация генератора случайных чисел в зависимости от времени (чтобы всегда давал разный результат)

    sun = new QPixmap("sun.png"); //объект с картинкой солнца
    cloud = new QPixmap("cloud.png"); //объект с картинкой облака
    rain = new QPixmap("rain.png"); //объект с картинкой дождя
    pgrass = new QPixmap("grass.png"); //объект с картинкой Трава
    pbush = new QPixmap("bush.png"); //объект с картинкой Куст
    ptree = new QPixmap("tree.png"); //объект с картинкой Дерево
    pgrass_selected = new QPixmap("grass_selected.png"); //объект с картинкой Трава выбранная
    pbush_selected = new QPixmap("bush_selected.png"); //объект с картинкой Куст выбранный
    ptree_selected = new QPixmap("tree_selected.png"); //объект с картинкой Дерево выбранное
    pforester = new QPixmap("earhat.png"); //объект с картинкой Лесник
    ppoacher1 = new QPixmap("hat1.png"); //объект с картинкой Браконьер 1
    ppoacher2 = new QPixmap("hat2.png"); //объект с картинкой Браконьер 2
    phouse = new QPixmap("house.png"); //объект с картинкой Домик в лесу (принадлежит леснику)

    ui->pogoda->setPixmap(*sun); // вывести картинку в лейбл
    ui->place->setStyleSheet("background-image:url(\"dirt_grid.png\"); background-position: center;" ); // вывести земляной фон в frame

    forest.Dirt_Init(); //инициализация ячеек почвы
    weather.Weather_Init(); //инициализация погоды
    invaders.set_corners();//установить координаты для углов появления браконьеров
    forester.set_route_points(); //установить координаты для маршрута патрулирования лесника
    invaders.set_route_points(); //установить координаты для маршрута перемещения браконьеров

    Print_forest_info(); //вывести инфо о лесе
    Print_info(0, -1, 0); //очистить блок с инфо о растении
    Print_human_info(forester_is_on, 1); //вывести пустой блок с инфо о людях (так как первым передаётся 0)
    Print_weather_info(); //вывести инфо о погоде

    timer = new QTimer(); // таймер для работы модели (рост растений и смена погоды)
    timer->start(TIME_TICK); //запустить таймер с интервалом в одну секунду
    QObject::connect(timer, SIGNAL(timeout()), SLOT(Timer_tick())); //по истечении интервала работает слот

    human_tick = new QTimer(); // таймер для работы моделей - людей (их перемещение и взаимодействие)
    QObject::connect(human_tick, SIGNAL(timeout()), SLOT(Timer_human_tick())); //по истечении интервала работает слот


    QObject::connect(ui->normal_b, SIGNAL(toggled(bool)), SLOT(Normalmode(bool))); //привязать переключение радиокнопки к слоту
    QObject::connect(ui->speed_b, SIGNAL(toggled(bool)), SLOT(Speedmode(bool))); //привязать переключение радиокнопки к слоту
    QObject::connect(ui->pause_b, SIGNAL(toggled(bool)), SLOT(Pausemode(bool))); //привязать переключение радиокнопки к слоту

    QObject::connect(ui->normal_human, SIGNAL(toggled(bool)), SLOT(Normalmode_human(bool))); //привязать переключение радиокнопки к слоту
    QObject::connect(ui->pause_human, SIGNAL(toggled(bool)), SLOT(Pausemode_human(bool))); //привязать переключение радиокнопки к слоту
    QObject::connect(ui->stop_human, SIGNAL(toggled(bool)), SLOT(Stop_human(bool))); //привязать переключение радиокнопки к слоту

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

        int f_click_house=0; //флаг клика в домик
        if(x>(HOUSE_OX-RADIUS_PIC_HOUSE) && y>(HOUSE_OY-RADIUS_PIC_HOUSE) && x<(HOUSE_OX+RADIUS_PIC_HOUSE) && y<(HOUSE_OY+RADIUS_PIC_HOUSE))
        {
            f_click_house=1; //если кликнут домик, то отметить флагом и больше ничего не выполнять
        }

        if(x>0 && y>0 && x<PLACE_SIZE_X && y<PLACE_SIZE_Y && f_click_house==0) //если клик произошёл внутри площадки леса (place)
        {
            if(ui->plant_b->isChecked()==true) //если был выбран режим посадки растения
            {
                int planttype; //тип высаживаемого растения (1 - трава, 2 - куст, 3 - дерево)
                if(ui->grass_type->isChecked()==true)
                    planttype=1;
                if(ui->bush_type->isChecked()==true)
                    planttype=2;
                if(ui->tree_type->isChecked()==true)
                    planttype=3;

                forest.Add_plant(x,y,planttype); //добавить растение выбранного типа с выбранными координатами

                Show_pic(forest.get_kolvo_type(planttype)-1, planttype); //вывести изображение для добавленного растения

                Print_forest_info(); //вывести обновлённое инфо о лесе

            }
            if(ui->delete_b->isChecked()==true) //если был выбран режим удаления растения (удаляется самое верхнее растение)
            {
                int num_delete=-1; //номер искомого растения для удаления
                int type_delete=0; //тип искомого растения для удаления
                int max_height=0; //наибольшая высота растения на данный момент (удаляется самое высокое растение)
                for(int i=0, type=3, all=forest.get_kolvo_tree(); i<all; i++) //перебрать растения типа Дерево
                {
                    if(forest.Belonging_of_coordinat(i,type,x,y)==1) //если координаты клика мыши принадлежат окружности растения
                    {
                        int height_plant=forest.get_height_plant(i,type); //получить значение высоты данного растения
                        if(height_plant>max_height) //если высота данного выше ранее сохранённой
                        {
                            max_height=height_plant; //теперь макс. высота имеет новое значение
                            num_delete=i; //на данный момент удалению подлежит данное растение
                            type_delete=type; //на данный момент удалению подлежит данное растение данного типа
                        }
                    }
                }
                for(int i=0, type=2, all=forest.get_kolvo_bush(); i<all; i++) //перебрать растения типа Куст
                {
                    if(forest.Belonging_of_coordinat(i,type,x,y)==1) //если координаты клика мыши принадлежат окружности растения
                    {
                        int height_plant=forest.get_height_plant(i,type); //получить значение высоты данного растения
                        if(height_plant>max_height) //если высота данного выше ранее сохранённой
                        {
                            max_height=height_plant; //теперь макс. высота имеет новое значение
                            num_delete=i; //на данный момент удалению подлежит данное растение
                            type_delete=type; //на данный момент удалению подлежит данное растение данного типа
                        }
                    }
                }
                for(int i=0, type=1, all=forest.get_kolvo_grass(); i<all; i++) //перебрать растения типа Трава
                {
                    if(forest.Belonging_of_coordinat(i,type,x,y)==1) //если координаты клика мыши принадлежат окружности растения
                    {
                        int height_plant=forest.get_height_plant(i,type); //получить значение высоты данного растения
                        if(height_plant>max_height) //если высота данного выше ранее сохранённой
                        {
                            max_height=height_plant; //теперь макс. высота имеет новое значение
                            num_delete=i; //на данный момент удалению подлежит данное растение
                            type_delete=type; //на данный момент удалению подлежит данное растение данного типа
                        }
                    }
                }
                if(num_delete!=-1) //если найдено растение для удаления
                {
                    QLabel **img_delete=nullptr; //указатель на label с картинкой растения
                    forest.get_img(&img_delete, num_delete, type_delete); //получить адрес для объекта - label с изображением растения
                    (*img_delete)->deleteLater(); //удалить qlabel  с изображением растения

                    int f_print_changed=0; //флаг для вывода инфо о растении, выбранном ранее, но смещённом из-за удаления другого
                    if(type_delete==type_of_info && num_info>=num_delete) //проверить вывод инфо о выбранном растении (если удаляется выбранное, то переключиться на другое)
                    {
                        num_info=num_info-1;
                        if(num_info<0) //если растений больше нет, то новую инфу не выводить
                        {
                            num_info=-1;
                            type_of_info=-1;
                            Print_info(0, -1, 0); //очистить блок с инфо о растении
                        }
                        else
                            f_print_changed=1; //отметить флагом вывод

                    }
                    forest.Delete_plant(num_delete, type_delete); //удалить объект растения
                    if(f_print_changed==1) //если удаление повлияло на вывод инфо о выбранном растении, то вывести обновлённое инфо
                        Print_info(num_info, type_of_info, 0); //вывести инфо о растении, которое теперь по счёту является тем же, что и ранее удалённое

                    Print_forest_info(); //вывести обновлённое инфо о лесе
                }

            }
            if(ui->infoplant_b->isChecked()==true) //если был выбран режим инфо о растении (инфо о самом верхнем растении)
            {
                int num_info_new=-1; //новый номер растения для инфо
                int type_of_info_new=-1; //новый тип растения для вывода инфо
                int max_height=0; //наибольшая высота растения на данный момент (удаляется самое высокое растение)
                for(int i=0, type=3, all=forest.get_kolvo_tree(); i<all; i++) //перебрать растения типа Дерево
                {
                    if(forest.Belonging_of_coordinat(i,type,x,y)==1) //если координаты клика мыши принадлежат окружности растения
                    {
                        int height_plant=forest.get_height_plant(i,type); //получить значение высоты данного растения
                        if(height_plant>max_height) //если высота данного выше ранее сохранённой
                        {
                            max_height=height_plant; //теперь макс. высота имеет новое значение
                            num_info_new=i; //на данный момент выводу инфо подлежит данное растение
                            type_of_info_new=type; //на данный момент выводу инфо подлежит данное растение данного типа
                        }
                    }
                }
                for(int i=0, type=2, all=forest.get_kolvo_bush(); i<all; i++) //перебрать растения типа Куст
                {
                    if(forest.Belonging_of_coordinat(i,type,x,y)==1) //если координаты клика мыши принадлежат окружности растения
                    {
                        int height_plant=forest.get_height_plant(i,type); //получить значение высоты данного растения
                        if(height_plant>max_height) //если высота данного выше ранее сохранённой
                        {
                            max_height=height_plant; //теперь макс. высота имеет новое значение
                            num_info_new=i; //на данный момент выводу инфо подлежит данное растение
                            type_of_info_new=type; //на данный момент выводу инфо подлежит данное растение данного типа
                        }
                    }
                }
                for(int i=0, type=1, all=forest.get_kolvo_grass(); i<all; i++) //перебрать растения типа Трава
                {
                    if(forest.Belonging_of_coordinat(i,type,x,y)==1) //если координаты клика мыши принадлежат окружности растения
                    {
                        int height_plant=forest.get_height_plant(i,type); //получить значение высоты данного растения
                        if(height_plant>max_height) //если высота данного выше ранее сохранённой
                        {
                            max_height=height_plant; //теперь макс. высота имеет новое значение
                            num_info_new=i; //на данный момент выводу инфо подлежит данное растение
                            type_of_info_new=type; //на данный момент выводу инфо подлежит данное растение данного типа
                        }
                    }
                }
                if(num_info_new!=-1) //если найдено растение для вывода инфо
                {
                    num_info=num_info_new; //записать новое значение номера для вывода
                    int update_f=1; //флаг обновления названий строк
                    if(type_of_info>=1 && type_of_info<=3) //если до этого выводилась инфо о растении, то обновлять названия строк не надо
                        update_f=0;
                    type_of_info=type_of_info_new; //записать новое значение типа для вывода
                    Print_info(num_info, type_of_info, update_f); //вывести инфо в спец. блок
                }

            }
            if(ui->infodirt_b->isChecked()==true) //если был выбран режим инфо о почве
            {
                int num_cell=0; //переменная с номером ячейки почвы, на которую кликнули
                for(int i=0; i<KOLVO_DIRT; i++) //перебрать все ячейки почвы, найти искомую по координатам
                {
                    if((x>forest.get_ox_min_dirt(i)) && (y>forest.get_oy_min_dirt(i)) && x<(forest.get_ox_min_dirt(i)+DIRT_CELL_SIZE) && y<(forest.get_oy_min_dirt(i)+DIRT_CELL_SIZE)) //если координаты растения принадлежат координатам ячейки
                    {
                        num_cell=i; //найдена искомая ячейка
                        break; //остановить перебор
                    }
                }
                int update_f=1; //флаг обновления названий строк
                if(type_of_info==0) //если до этого выводилась инфо о растении, то обновлять названия строк не надо
                    update_f=0;
                num_info=num_cell; //записать новое значение номера для вывода
                type_of_info=0; //записать новое значение типа для вывода
                Print_info(num_info, type_of_info, update_f); //вывести инфо в спец. блок
            }
        }
    }
}

void MainWidget::Timer_tick() //слот интервала таймера для растений и погоды
{
    all_time=all_time+1; //получить новое значение общего времени

    ui->all_time_text->setText("Всего времени прошло (в тиках): "+QString::number(all_time)); //вывести на экран

    if(f_house_img==0) //если картинка домика ещё не выведена
    {
        Show_pic(1,6); //вывести картинку домика лесника
        f_house_img=1; //отметить флагом
    }

    weather.set_time_status(weather.get_time_status()+1); //увеличить кол-во времени текущей погоды
    if(weather.get_time_status()==TIME_STATUS_END) //если время типа погоды закончилось, случайно выбрать один из двух других
    {
        int randm=RAND(0,1); //случайное число 0 или 1
        switch(weather.get_f_status()) //случайно установить другой статус погоды
        {
        case F_SUN:
            switch(randm)
            {
            case 0:
                weather.set_f_status(F_CLOUD);
                break;
            case 1:
                weather.set_f_status(F_RAIN);
                break;
            }
            break;
        case F_CLOUD:
            switch(randm)
            {
            case 0:
                weather.set_f_status(F_SUN);
                break;
            case 1:
                weather.set_f_status(F_RAIN);
                break;
            }
            break;
        case F_RAIN:
            switch(randm)
            {
            case 0:
                weather.set_f_status(F_SUN);
                break;
            case 1:
                weather.set_f_status(F_CLOUD);
                break;
            }
            break;
        }
        weather.set_time_status(0); //начать отсчёт для текущего типа погоды заново
    }

    switch(weather.get_f_status()) //изменить яркость солнца и кол-во осадков в зависимости от погоды
    {
    case F_SUN:
        ui->pogoda->setPixmap(*sun); //вывести картинку погоды
        weather.set_sunshine(RAND((SUNSHINE_SUN-SUNSHINE_SUN_RANGE), (SUNSHINE_SUN+SUNSHINE_SUN_RANGE))); //яркость солнца случайно меняется каждый тик в своём диапазоне
        weather.set_rainfall_tick(RAINFALL_TICK_SUN);
        break;
    case F_CLOUD:
        ui->pogoda->setPixmap(*cloud); //вывести картинку погоды
        weather.set_sunshine(RAND((SUNSHINE_CLOUD-SUNSHINE_CLOUD_RANGE), (SUNSHINE_CLOUD+SUNSHINE_CLOUD_RANGE))); //яркость солнца случайно меняется каждый тик в своём диапазоне
        weather.set_rainfall_tick(RAND((RAINFALL_TICK_CLOUD-RAINFALL_TICK_CLOUD_RANGE), (RAINFALL_TICK_CLOUD+RAINFALL_TICK_CLOUD_RANGE))); //небольшое кол-во осадков в виде росы
        break;
    case F_RAIN:
        ui->pogoda->setPixmap(*rain); //вывести картинку погоды
        weather.set_sunshine(RAND((SUNSHINE_RAIN-SUNSHINE_RAIN_RANGE), (SUNSHINE_RAIN+SUNSHINE_RAIN_RANGE))); //яркость солнца случайно меняется каждый тик в своём диапазоне
        weather.set_rainfall_tick(RAND((RAINFALL_TICK_RAIN-RAINFALL_TICK_RAIN_RANGE), (RAINFALL_TICK_RAIN+RAINFALL_TICK_RAIN_RANGE))); //кол-во осадков случайно меняется каждый тик в своём диапазоне
        break;
    }

    for(int i=0, kolvo=forest.get_kolvo_dirt(), rainf=weather.get_rainfall_tick(); i<kolvo; i++) //перебрать ячейки почвы
    {
        forest.set_wet_dirt(i, (forest.get_wet_dirt(i)+rainf)); //почва получает влагу
        if(weather.get_f_status()==F_SUN) //если сейчас солнечно
        {
            forest.set_wet_dirt(i, (forest.get_wet_dirt(i)-DRY_TICK_SUN)); //влага испаряется с почвы
        }
        forest.set_fertility_now_dirt(i, forest.get_fertility_dirt(i)); //установить питание на одно растение за цикл питания (может быть изменено, в отличии от основной плодородности)
    }

    plant_sort *plants; //структура для сортировки растений (их упорядочиванию по высоте или агрессивности)

    int all_plants=forest.get_kolvo_grass()+forest.get_kolvo_bush()+forest.get_kolvo_tree(); //кол-во растений всех видов
    plants = new plant_sort[all_plants]; //структура для сортировки

    for(int type=1, j=0; type<=3; type++) //заполнить структуру информацией о всех растениях
    {
        for(int i=0, kolvo=forest.get_kolvo_type(type); i<kolvo; i++)
        {
            plants[j].num=i;
            plants[j].type=type;
            plants[j].radius=forest.get_radius_plant(i, type);
            plants[j].height=forest.get_height_plant(i, type);
            plants[j].agressiv=forest.get_aggresiv_plant(i, type);
            j++;
        }
    }

    for(int k=1; k<all_plants; k++) //метод пузырька
        {
            for(int i=0; i<all_plants-k; i++)
            {
                if(plants[i].agressiv < plants[i+1].agressiv) //сортировка по убыванию агрессивности
                { //ПЕРЕСТАВИТЬ ЗНАЧЕНИЯ
                    plant_sort vsp;
                    vsp=plants[i];
                    plants[i]=plants[i+1];
                    plants[i+1]=vsp;
                }
            }
        }

    for(int i=0; i<all_plants; i++) //перебрать все растения, получающие питание
    {
        int num = plants[i].num; //номер растения
        int type = plants[i].type; //тип растения
        int num_dirt = forest.get_num_dirt_plant(num, type); //номер ячейки почвы с растением
        int wet = forest.get_wet_dirt(num_dirt); //получаемая влажность
        int sun = weather.get_sunshine(); //получаемый солнечный свет (пока без учёта наложения растений)
        int f_died=0; //флаг гибели растения (устанавливается, если у растения заканчивается жизнеспособность

        int remain_wet = wet - forest.get_wet_dirt(num_dirt); //остаток влаги после растения

        if(remain_wet >= 0) //растение получило достаточно влаги
        {
            forest.set_score_grow_plant(num, type, forest.get_score_grow_plant(num, type)+1); //увеличить кол-во очков роста на 1
            double viability = forest.get_viability_plant(num, type); //жизнеспособность растения
            if(viability<1.0)
            {
                forest.set_viability_plant(num, type, viability+0.05); //увеличить жизнеспособность растения, если она была неполной
                if(forest.get_viability_plant(num, type)>1.0)
                {
                    forest.set_viability_plant(num, type, 1.0); //если после увеличения жизнеспособности она стала больше, чем 1, то приравнять к 1 (это максимум)
                }
            }
        }
        else //растение получило недостаточно влаги
        {
            forest.set_wet_dirt(num_dirt, wet-abs(remain_wet)); //если влаги не хватило, то растение забирает больше влаги из почвы (остальным меньше достанется)
            if(forest.get_wet_dirt(num_dirt)<0) //если в почве нет столько влаги, сколько нужно растению
            {
                forest.set_wet_dirt(num_dirt, 0); //обнулить влагу в почве (иначе отрицательна)
                double viability = forest.get_viability_plant(num, type); //жизнеспособность растения
                if(viability==1.0 || viability==0.9)
                {
                    forest.set_viability_plant(num, type, 0.8); //уменьшить жизнеспособность растения, если она была близка к нормальной
                }
            }
            else //если теперь растению хватило влаги (оно забрало у остальных)
            {
                forest.set_score_grow_plant(num, type, forest.get_score_grow_plant(num, type)+1); //увеличить кол-во очков роста на 1
            }
        }

        double sun_received; //полученное кол-во солнечного света с учётом более высоких растений
        double square_sun_shielded=0; //площадь исходного растения, которая была закрыта от солнца более высоким
        for (int k=0; k<all_plants; k++) //перебрать все растения
        {
            if(plants[k].height>plants[i].height) //если высота текущего растения выше исходного
            {
                double new_square_sun_shielded=0; //площадь исходного растения, которая была закрыта от солнца данным растением
                int ox1 = forest.get_x_plant(num, type); // координата ox центра окружности 1 (исходной)
                int oy1 = forest.get_y_plant(num, type); // координата oy центра окружности 1 (исходной)
                int ox2 = forest.get_x_plant(plants[k].num, plants[k].type); // координата ox центра окружности 2 (более высокого растения)
                int oy2 = forest.get_y_plant(plants[k].num, plants[k].type); // координата oy центра окружности 2 (более высокого растения)
                int dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между центрами двух окружностей
                if(dist<(plants[i].radius+plants[k].radius)) //если окружности пересекаются
                {
                    if(dist<(plants[k].radius-plants[i].radius)) //если исходное растение полностью находится внутри радиуса более высокого
                    {
                        new_square_sun_shielded = M_PI*plants[i].radius*plants[i].radius; // S = pi * r^2,  закрытая площадь = площадь всего более низкого растения
                    }
                    else
                    {
                        if(dist<(plants[i].radius-plants[k].radius)) //если более высокое растение полностью находится внутри радиуса исходного
                        {
                            new_square_sun_shielded = M_PI*plants[k].radius*plants[k].radius; // S = pi * r^2,  закрытая площадь = площадь всего более высокого растения
                        }
                        else //если окружности частично пересекаются, то вычислять площадь пересечения по формулам
                        {
                            int r1 = plants[i].radius; //радиус 1-го круга для использования в формулах
                            int r2 = plants[k].radius; //радиус 2-го круга для использования в формулах
                            int f1 = 2 * acos((r1*r1 - r2*r2 + dist*dist) / (2 * r1 * dist));
                            int f2 = 2 * acos((r2*r2 - r1*r1 + dist*dist) / (2 * r2 * dist));
                            int s1 = (r1*r1 * (f1 - sin(f1))) / 2;
                            int s2 = (r2*r2 * (f2 - sin(f2))) / 2;

                             new_square_sun_shielded = s1 + s2; //получить искомое значеие площади пересечения
                        }
                    }
                }

                if(new_square_sun_shielded > square_sun_shielded) //если данное растение закрывает исходное сильнее предыдущего, то изменить значение перекрытой площади на новое
                {
                    square_sun_shielded=new_square_sun_shielded;
                }
            }

        }
        double square = M_PI*plants[i].radius*plants[i].radius; //площадь круга данного растения
        sun_received = sun * (1-(square_sun_shielded/square)); //растение получает солн. свет с учётом закрытой площади
        if(sun_received!=0) //если растение получило хоть немного солн. света
        {
            int f_lightlove = forest.get_lightlove_plant(num, type); //флаг светолюбивости растения (любит свет или полутень)
            double percent_receipt = sun_received/sun; //процент полученного растения света от начального значения (солнце не в тени)
            int f_add=0; //флаг, что растение получило нужный солнечный свет
            if(f_lightlove==TYPE_LOVE_BRIGHT) //если растение любит яркий свет
            {
                if(percent_receipt>=0.9) //если растение получило достаточно света
                {
                    f_add=1;
                }
            }
            if(f_lightlove==TYPE_LOVE_SHADOW) //если растение любит полутень
            {
                if(percent_receipt>=0.3 && percent_receipt<0.8) //если растение получило нужное кол-во света
                {
                    f_add=1;
                }
            }

            if(f_add==1) //если растение получило нужное кол-во света
            {
                if(f_lightlove==TYPE_LOVE_BRIGHT && weather.get_f_status()==F_SUN) //солнцелюбивое растение растёт только в солнечную погоду
                {
                    forest.set_score_grow_plant(num, type, forest.get_score_grow_plant(num, type)+1); //увеличить кол-во очков роста на 1
                }
                if(f_lightlove==TYPE_LOVE_SHADOW) //тенелюбивое растение
                {
                    if(weather.get_f_status()==F_SUN || weather.get_f_status()==F_CLOUD) //тенелюбивое растение растёт только в солнечную или облачную погоду
                    {
                        forest.set_score_grow_plant(num, type, forest.get_score_grow_plant(num, type)+1); //увеличить кол-во очков роста на 1
                    }
                }
                double viability = forest.get_viability_plant(num, type); //жизнеспособность растения
                if(viability<1.0)
                {
                    forest.set_viability_plant(num, type, viability+0.05); //увеличить жизнеспособность растения, если она была неполной
                    if(forest.get_viability_plant(num, type)>1.0)
                    {
                        forest.set_viability_plant(num, type, 1.0); //если после увеличения жизнеспособности она стала больше, чем 1, то приравнять к 1 (это максимум)
                    }
                }
            }
            else //если растение получило мало/слишком_много света
            {
                double viability = forest.get_viability_plant(num, type); //жизнеспособность растения
                if(viability==1.0 || viability==0.9)
                {
                    forest.set_viability_plant(num, type, 0.8); //уменьшить жизнеспособность растения, если она была близка к нормальной
                }
                if(viability==0.8)
                {
                    forest.set_viability_plant(num, type, 0.7); //уменьшить жизнеспособность растения, если она была близка к нормальной
                }
            }

        }
        else //если растение не получило солн. света вовсе
        {
            double viability = forest.get_viability_plant(num, type); //жизнеспособность растения
            forest.set_viability_plant(num, type, viability-0.25); //уменьшить жизнеспособность растения, так как без света оно не может
            if(forest.get_viability_plant(num, type)<=0)
            {
                f_died=1; //отметить флагом, если растение совсем зачахло (оно погибнет)
            }

        }

        if(f_died==1) //если растение умирает без света
        {
            forest.set_fertility_dirt(num_dirt, forest.get_fertility_dirt(num_dirt)+ADD_FERT_IF_DIED_PLANT); //увеличить плодородность ячейки почвы, так как на ней зачахло растение (стало удобрением)
            forest.set_fertility_now_dirt(num_dirt, forest.get_fertility_now_dirt(num_dirt)+ADD_FERT_IF_DIED_PLANT); //увеличить плодородность ячейки почвы, так как на ней зачахло растение (стало удобрением)
            Remove_plant_and_resort(i, &plants, &all_plants); //удалить это растение (в том числе из списка сортировки)
            i=i-1; //перейти к сл. растению (но его порядок уменьшился, поэтому i--)
        }
        else //если растение не зачахло
        {
            int feed = forest.get_fertility_now_dirt(num_dirt); //получаемое питание из почвы
            int remain_feed = feed - forest.get_feed_norm_plant(num, type); //остаток от питания после растения
            if (remain_feed >= 0) //растение получило достаточно питания
            {
                forest.set_score_grow_plant(num, type, forest.get_score_grow_plant(num, type)+1); //увеличить кол-во очков роста на 1
                double viability = forest.get_viability_plant(num, type); //жизнеспособность растения
                if(viability<1.0)
                {
                    forest.set_viability_plant(num, type, viability+0.025); //увеличить жизнеспособность растения, если она была неполной
                    if(forest.get_viability_plant(num, type)>1.0)
                    {
                        forest.set_viability_plant(num, type, 1.0); //если после увеличения жизнеспособности она стала больше, чем 1, то приравнять к 1 (это максимум)
                    }
                }

            }
            else //растение получило недостаточно питания
            {
                forest.set_fertility_now_dirt(num_dirt, feed-abs(remain_feed)); //если питания не хватило, то растение забирает больше питания из почвы (остальным меньше достанется)
                if(forest.get_fertility_now_dirt(num_dirt)<0) //если в почве нет столько питания, сколько нужно растению
                {
                    forest.set_fertility_now_dirt(num_dirt, 0); //обнулить питание в почве (иначе отрицательно) (но только для данного цикла питания)
                    double viability = forest.get_viability_plant(num, type); //жизнеспособность растения
                    forest.set_viability_plant(num, type, viability-0.15); //уменьшить жизнеспособность растения
                    if(forest.get_viability_plant(num, type)<=0)
                    {
                        f_died=1; //отметить флагом, если растение совсем зачахло (оно погибнет)
                    }
                }
                else //если теперь растению хватило питания (оно забрало у остальных)
                {
                    forest.set_score_grow_plant(num, type, forest.get_score_grow_plant(num, type)+1); //увеличить кол-во очков роста на 1
                }
            }
            if(f_died==1) //если растение умирает без питания
            {
                forest.set_fertility_dirt(num_dirt, forest.get_fertility_dirt(num_dirt)+ADD_FERT_IF_DIED_PLANT); //увеличить плодородность ячейки почвы, так как на ней зачахло растение (стало удобрением)
                forest.set_fertility_now_dirt(num_dirt, forest.get_fertility_now_dirt(num_dirt)+ADD_FERT_IF_DIED_PLANT); //увеличить плодородность ячейки почвы, так как на ней зачахло растение (стало удобрением)
                Remove_plant_and_resort(i, &plants, &all_plants); //удалить это растение (в том числе из списка сортировки)
                i=i-1; //перейти к сл. растению (но его порядок уменьшился, поэтому i--)
            }
            else //если растение не зачахло
            {
                if(forest.get_score_grow_plant(num, type) >= forest.get_score_grow_max_plant(num, type)) //если растение набрало макс. кол-во очков для дальнейшего роста
                {
                    forest.set_score_grow_plant(num, type, forest.get_score_grow_plant(num, type)-forest.get_score_grow_max_plant(num, type)); //списать с растения очки роста взамен на рост в высоту и ширину
                    int grow_height=0, grow_radius=0; //переменные с величиной роста в высоту и в радиусе растения
                    switch (type) //отличаются в зависимости от типа растения
                    {
                    case 1: //трава
                        grow_height=GROW_GRASS_HEIGHT;
                        grow_radius=GROW_GRASS_RADIUS;
                        break;
                    case 2: //куст
                        grow_height=GROW_BUSH_HEIGHT;
                        grow_radius=GROW_BUSH_RADIUS;
                        break;
                    case 3: //дерево
                        grow_height=GROW_TREE_HEIGHT;
                        grow_radius=GROW_TREE_RADIUS;
                        break;
                    }
                    forest.set_height_plant(num, type, (forest.get_height_plant(num, type)+grow_height)); //вырасти в высоту
                    forest.set_radius_plant(num, type, (forest.get_radius_plant(num, type)+grow_radius)); //вырасти в радиусе

                    if(forest.get_height_plant(num, type) > forest.get_end_height_plant(num, type)) //если растение достигло своей макс. высоты
                    {
                        forest.set_height_plant(num, type, forest.get_end_height_plant(num, type)); //то оставить значение высоты равным макс. значению
                    }
                    if(forest.get_radius_plant(num, type) > forest.get_max_radius_plant(num, type)) //если растение достигло своего макс. радиуса
                    {
                        forest.set_radius_plant(num, type, forest.get_max_radius_plant(num, type)); //то оставить значение радиуса равным макс. значению
                    }
                }
            }


        }
    } //конец цикла питания


    Print_forest_info(); //вывести инфо о лесе
    Print_weather_info(); //вывести инфо о погоде
    if(type_of_info!=-1)
        Print_info(num_info, type_of_info, 0); //вывести инфо в спец. блок

    for(int k=1; k<all_plants; k++) //метод пузырька
        {
            for(int i=0; i<all_plants-k; i++)
            {
                if(plants[i].height > plants[i+1].height) //сортировка по возрастанию высоты
                { //ПЕРЕСТАВИТЬ ЗНАЧЕНИЯ
                    plant_sort vsp;
                    vsp=plants[i];
                    plants[i]=plants[i+1];
                    plants[i+1]=vsp;
                }
            }
        }

    for(int i=0; i<all_plants; i++) //перебрать все растения. Вывести картинки для них на экран (с учётом высоты)
    {
        QLabel **old_img=nullptr; //указатель на label со старой картинкой
        forest.get_img(&old_img, plants[i].num, plants[i].type); //получить адрес для объекта - label со старым изображением
        (*old_img)->deleteLater(); //удалить qlabel со старым изображением

        Show_pic(plants[i].num, plants[i].type); //вывести новые картинки растений (Сначала более низкие. Верхние на них наслаиваются)
    }

    house_img->deleteLater(); //удалить qlabel со старым изображением домика лесника
    Show_pic(1,6); //вывести картинку домика лесника (отобразится поверх всех растений)

    delete[] plants; //очистить память от структуры сортировки

    if(forester_is_on==1) //если включена модель людей, то обновить их картинки, чтобы они располагались выше деревьев
    {
        for(int i=0, kolvo=invaders.get_kolvo_poacher(); i<kolvo; i++) //обновить картинки браконьеров
        {
            QLabel **old_img=nullptr; //указатель на label со старой картинкой
            invaders.get_img(&old_img, i); //получить адрес для объекта - label со старым изображением браконьера
            (*old_img)->deleteLater(); //удалить qlabel со старым изображением

            Show_pic(i, TYPE_POACHER); //вывести новую картинку на экран
        }

        /*Обновить картинку лесника*/
        QLabel **old_img=nullptr; //указатель на label со старой картинкой
        forester.get_img(&old_img); //получить адрес для объекта - label со старым изображением лесника
        (*old_img)->deleteLater(); //удалить qlabel со старым изображением

        Show_pic(1, TYPE_FORESTER); //вывести новую картинку на экран
    }
}

void MainWidget::Timer_human_tick() //слот интервала таймера для людей
{
    if(invaders.get_kolvo_poacher()<MAX_KOLVO_POACHER) //если кол-во браконьеров меньше максимального
    {
        time_for_new_poacher=time_for_new_poacher+1; //увеличить счётчик появления нового браконьера
    }
    else //если браконьеров достаточно
    {
        time_for_new_poacher=0; //обнулить счётчик
    }
    if(time_for_new_poacher==TIME_FOR_NEW_POACHER_MAX) //если пришло время добавить
    {
        Add_invader(); //добавить браконьера и вывести его картинку на экран
        time_for_new_poacher=0; //обнулить счётчик
    }

    int old_target = forester.get_target_type();
    int old_target_ox = forester.get_target_ox();
    int old_target_oy = forester.get_target_oy();

    int kolvo_steps = forester.get_speed(); //получить кол-во шагов на один тик таймера
    int ox_human = forester.get_ox();
    int oy_human = forester.get_oy();

    Find_target(1, TARGET_FIND_FORESTER); //найти цель для лесника

    if(forester.get_target_type()==TARGET_ROUTE && old_target==TARGET_ROUTE) //если человек до этого шёл по маршруту, и не увидел ничего нового, то продолжить идти по маршруту
    {
        if(ox_human==old_target_ox && oy_human==old_target_oy) //если человек уже достиг точки маршрута, то пойти к сл. точке
        {
            ;
        }
        else //иначе продолжить путь к "старой" точке маршрута
        {
            forester.set_target_type(old_target);
            forester.set_target_ox(old_target_ox);
            forester.set_target_oy(old_target_oy);
        }
    }

    int ox_target = forester.get_target_ox();
    int oy_target = forester.get_target_oy();
    int target = forester.get_target_type();

    int f_ox, f_oy; //флаги разницы между координатами человека и цели (разный флаг в зависимости от знака разницы координат)
    if((ox_human-ox_target)<=0) //если разница между координатами отрицательная
    {
        f_ox=F_PLUS; //то шаги нужно будет прибавлять к координатам человека
    }
    else
    {
        f_ox=F_MINUS; //иначе нужно будет вычитать шаги из координат человека
    }
    if((oy_human-oy_target)<=0) //если разница между координатами отрицательная
    {
        f_oy=F_PLUS; //то шаги нужно будет прибавлять к координатам человека
    }
    else
    {
        f_oy=F_MINUS; //иначе нужно будет вычитать шаги из координат человека
    }

    if(abs(ox_human - ox_target) <= abs(oy_human - oy_human)) //если передвигаться по оси ox будет ближе, чем по oy, то сначала двигаться по ox
    {
        while(ox_human!=ox_target && kolvo_steps!=0) //человек идёт к цели по оси, пока эта координата не совпадёт или не закончатся шаги
        {
            if(f_ox==F_PLUS)
            {
                ox_human = ox_human+1;
            }
            else
            {
                ox_human = ox_human-1;
            }
            kolvo_steps = kolvo_steps-1;
        }

        while(oy_human!=oy_target && kolvo_steps!=0) //человек идёт к цели по оси, пока эта координата не совпадёт или не закончатся шаги
        {
            if(f_oy==F_PLUS)
            {
                oy_human = oy_human+1;
            }
            else
            {
                oy_human = oy_human-1;
            }
            kolvo_steps = kolvo_steps-1;
        }
    }
    else //иначе двигаться наоборот (сначала по oy)
    {
        while(oy_human!=oy_target && kolvo_steps!=0) //человек идёт к цели по оси, пока эта координата не совпадёт или не закончатся шаги
        {
            if(f_oy==F_PLUS)
            {
                oy_human = oy_human+1;
            }
            else
            {
                oy_human = oy_human-1;
            }
            kolvo_steps = kolvo_steps-1;
        }
        while(ox_human!=ox_target && kolvo_steps!=0) //человек идёт к цели по оси, пока эта координата не совпадёт или не закончатся шаги
        {
            if(f_ox==F_PLUS)
            {
                ox_human = ox_human+1;
            }
            else
            {
                ox_human = ox_human-1;
            }
            kolvo_steps = kolvo_steps-1;
        }
    }
    forester.set_ox(ox_human); //записать новые координаты человека (до которых он дошёл)
    forester.set_oy(oy_human); //записать новые координаты человека (до которых он дошёл)

    //совершить действие в зависимости от цели
    if(target ==TARGET_POACHER) //цель - браконьер
    {
        int ox1 = ox_human; // координата ox человека
        int oy1 = oy_human; // координата oy человека
        int ox2 = ox_target; // координата ox цели
        int oy2 = oy_target; // координата oy цели
        int dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между двумя точками

        if(dist<=DIST_ACTION_FORESTER) //если лесник находится достаточно близко к цели
        {
            for(int i=0, kolvo=invaders.get_kolvo_poacher(); i<kolvo; i++) //перебрать браконьеров
            {
                if(ox_target == invaders.get_ox(i) && oy_target == invaders.get_oy(i)) //если это искомый браконьер
                {
                    QLabel **img_delete=nullptr; //указатель на label со старой картинкой
                    invaders.get_img(&img_delete, i); //получить адрес для объекта - label с изображением браконьера
                    (*img_delete)->deleteLater(); //удалить qlabel  с изображением браконьера
                    invaders.Delete_invader(i); //этот браконьер пойман (удалён из леса)
                    break; //остановить перебор
                }
            }
        }
    }


    for(int i=0; i<invaders.get_kolvo_poacher(); i++) //перебрать браконьеров
    {
        int old_target = invaders.get_target_type(i);
        int old_target_ox = invaders.get_target_ox(i);
        int old_target_oy = invaders.get_target_oy(i);

        kolvo_steps = invaders.get_speed(i); //получить кол-во шагов на один тик таймера
        ox_human = invaders.get_ox(i);
        oy_human = invaders.get_oy(i);

        Find_target(i, TARGET_FIND_POACHER); //найти цель для браконьера

        if(invaders.get_target_type(i)==TARGET_ROUTE && old_target==TARGET_ROUTE) //если человек до этого шёл по маршруту, и не увидел ничего нового, то продолжить идти по маршруту
        {
            if(ox_human==old_target_ox && oy_human==old_target_oy) //если человек уже достиг точки маршрута, то пойти к сл. точке
            {
                ;
            }
            else //иначе продолжить путь к "старой" точке маршрута
            {
                invaders.set_target_type(i, old_target);
                invaders.set_target_ox(i, old_target_ox);
                invaders.set_target_oy(i, old_target_oy);
            }
        }


        ox_target = invaders.get_target_ox(i);
        oy_target = invaders.get_target_oy(i);
        target = invaders.get_target_type(i);

        if((ox_human-ox_target)<=0) //если разница между координатами отрицательная
        {
            f_ox=F_PLUS; //то шаги нужно будет прибавлять к координатам человека
        }
        else
        {
            f_ox=F_MINUS; //иначе нужно будет вычитать шаги из координат человека
        }
        if((oy_human-oy_target)<=0) //если разница между координатами отрицательная
        {
            f_oy=F_PLUS; //то шаги нужно будет прибавлять к координатам человека
        }
        else
        {
            f_oy=F_MINUS; //иначе нужно будет вычитать шаги из координат человека
        }

        if(abs(ox_human - ox_target) <= abs(oy_human - oy_human)) //если передвигаться по оси ox будет ближе, чем по oy, то сначала двигаться по ox
        {
            while(ox_human!=ox_target && kolvo_steps!=0) //человек идёт к цели по оси, пока эта координата не совпадёт или не закончатся шаги
            {
                if(f_ox==F_PLUS)
                {
                    ox_human = ox_human+1;
                }
                else
                {
                    ox_human = ox_human-1;
                }
                kolvo_steps = kolvo_steps-1;
            }

            while(oy_human!=oy_target && kolvo_steps!=0) //человек идёт к цели по оси, пока эта координата не совпадёт или не закончатся шаги
            {
                if(f_oy==F_PLUS)
                {
                    oy_human = oy_human+1;
                }
                else
                {
                    oy_human = oy_human-1;
                }
                kolvo_steps = kolvo_steps-1;
            }
        }
        else //иначе двигаться наоборот (сначала по oy)
        {
            while(oy_human!=oy_target && kolvo_steps!=0) //человек идёт к цели по оси, пока эта координата не совпадёт или не закончатся шаги
            {
                if(f_oy==F_PLUS)
                {
                    oy_human = oy_human+1;
                }
                else
                {
                    oy_human = oy_human-1;
                }
                kolvo_steps = kolvo_steps-1;
            }
            while(ox_human!=ox_target && kolvo_steps!=0) //человек идёт к цели по оси, пока эта координата не совпадёт или не закончатся шаги
            {
                if(f_ox==F_PLUS)
                {
                    ox_human = ox_human+1;
                }
                else
                {
                    ox_human = ox_human-1;
                }
                kolvo_steps = kolvo_steps-1;
            }
        }
        invaders.set_ox(i, ox_human); //записать новые координаты человека (до которых он дошёл)
        invaders.set_oy(i, oy_human); //записать новые координаты человека (до которых он дошёл)

        //совершить действие в зависимости от цели
        if(target==TARGET_TREE) //цель - дерево
        {
            int ox1 = ox_human; // координата ox человека
            int oy1 = oy_human; // координата oy человека
            int ox2 = ox_target; // координата ox цели
            int oy2 = oy_target; // координата oy цели
            int dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между двумя точками
            if(dist<=DIST_ACTION_POACHER) //если браконьер находится достаточно близко к цели
            {
                for(int j=0, kolvo_tree=forest.get_kolvo_tree(); j<kolvo_tree; j++)
                {
                    if(ox_target == forest.get_x_plant(j, TYPE_TREE) && oy_target == forest.get_y_plant(j, TYPE_TREE)) //если это искомое дерево
                    {
                        invaders.set_ox(i, ox_target-RADIUS_PIC_HUMAN); //браконьер встаёт с левой стороны дерева для его рубки
                        forest.set_cutting_degree_tree(j, forest.get_cutting_degree_tree(j)+1); //увеличить степень срубленности дерева на 1
                        if(forest.get_cutting_degree_tree(j)>=MAX_CUTTING) //если достигнута максимальная степень срубленности
                        {
                            QLabel **img_delete=nullptr; //указатель на label с картинкой для удаления
                            forest.get_img(&img_delete, j, TYPE_TREE); //получить адрес для объекта - label с картинкой для удаления
                            (*img_delete)->deleteLater(); //удалить qlabel с изображением

                            int f_print_changed=0; //флаг для вывода инфо о растении, выбранном ранее, но смещённом из-за удаления другого
                            if(TYPE_TREE==type_of_info && num_info>=j) //проверить вывод инфо о выбранном растении (если удаляется выбранное, то переключиться на другое)
                            {
                                num_info=num_info-1;
                                if(num_info<0) //если растений больше нет, то новую инфу не выводить
                                {
                                    num_info=-1;
                                    type_of_info=-1;
                                    Print_info(0, -1, 0); //очистить блок с инфо о растении
                                }
                                else
                                    f_print_changed=1; //отметить флагом вывод

                            }

                            forest.Delete_plant(j, TYPE_TREE); //удалить это дерево (оно срублено браконьером)

                            if(f_print_changed==1) //если удаление повлияло на вывод инфо о выбранном растении, то вывести обновлённое инфо
                                Print_info(num_info, type_of_info, 0); //вывести инфо о растении, которое теперь по счёту является тем же, что и ранее удалённое

                            Print_forest_info(); //вывести обновлённое инфо о лесе
                        }
                        break; //остановить перебор
                    }
                }
            }
        }
        if(target==TARGET_CORNER_ESCAPE) //цель - угол поля для побега
        {
            if(ox_human == ox_target || oy_human==oy_target) //если браконьер достиг края поля
            {
                QLabel **img_delete=nullptr; //указатель на label со старой картинкой
                invaders.get_img(&img_delete, i); //получить адрес для объекта - label с изображением браконьера
                (*img_delete)->deleteLater(); //удалить qlabel  с изображением браконьера
                invaders.Delete_invader(i); //удалить браконьера (он ушёл из поля леса)
                if(i==0) //если удалён первый браконьер, то следующим будет первый (i=-1 из-за i++ в конце цикла)
                    i=-1;
                if(i==1) //если удалён второй браконьер, то остановить перебор
                    break;
            }
        }
    }


    Print_human_info(forester_is_on, 0); //вывести инфо о людях (так как первым передаётся 1)
    for(int i=0, kolvo=invaders.get_kolvo_poacher(); i<kolvo; i++) //обновить картинки браконьеров
    {
        QLabel **old_img=nullptr; //указатель на label со старой картинкой
        invaders.get_img(&old_img, i); //получить адрес для объекта - label со старым изображением браконьера
        (*old_img)->deleteLater(); //удалить qlabel со старым изображением

        Show_pic(i, TYPE_POACHER); //вывести новую картинку на экран
    }

    /*Обновить картинку лесника*/
    QLabel **old_img=nullptr; //указатель на label со старой картинкой
    forester.get_img(&old_img); //получить адрес для объекта - label со старым изображением лесника
    (*old_img)->deleteLater(); //удалить qlabel со старым изображением

    Show_pic(1, TYPE_FORESTER); //вывести новую картинку на экран

    Print_forest_info(); //вывести инфо о лесе
    if(type_of_info!=-1)
        Print_info(num_info, type_of_info, 0); //вывести инфо в спец. блок

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

void MainWidget::Normalmode_human(bool value) //слот при переключении в нормальный режим времени людей
{
    if(value==true)
    {
        human_tick->start(TIME_HUMAN_TICK); //запустить таймер с интервалом в полсекунды
        if(f_pause_human==0) //если до этого не была включена пауза (то есть нужно восстановить людей на поле)
        {
            forester_is_on=1; //отметить флагом "включение" лесника
            forester.Init(); //инициализация лесника
            Show_pic(1, TYPE_FORESTER); //вывести картинку лесника на экран

            Add_invader(); //добавить браконьера и вывести его картинку на экран

            Print_human_info(forester_is_on, 1); //вывести инфо о людях (так как первым передаётся 1)
            f_pause_human=0; //отметить, что предыдущим состоянием была не пауза
        }
        else //если до этого была включена пауза, то кроме запуска таймера больше ничего не делать
        {
            f_pause_human=0; //отключить флаг предыдущего состояния - паузы
        }
    }
}
void MainWidget::Pausemode_human(bool value) //слот при переключении в режим времени - паузу для людей
{
    if(value==true)
    {
        human_tick->stop(); //остановить таймер
        f_pause_human=1; //отметить флагом, что была включена пауза
    }
}
void MainWidget::Stop_human(bool value) //слот при переключении в режим выключения работы модели людей
{
    if(value==true)
    {
        QLabel **img_delete=nullptr; //указатель на label с картинкой для удаления
        human_tick->stop(); //остановить таймер
        forester_is_on=0; //отметить флагом "выключение" лесника
        forester.get_img(&img_delete); //получить адрес для объекта - label с изображением лесника
        (*img_delete)->deleteLater(); //удалить qlabel  с изображением лесника

        while(invaders.get_kolvo_poacher()!=0) //удалить всех браконьеров
        {
            invaders.get_img(&img_delete, 0); //получить адрес для объекта - label с изображением браконьера
            (*img_delete)->deleteLater(); //удалить qlabel  с изображением браконьера
            invaders.Delete_invader(0); //удалить самого браконьера
        }
        Print_human_info(forester_is_on, 1); //вывести пустые строки (так как первым передаётся 0)
        f_pause_human=0; //отметить, что предыдущим состоянием была не пауза
    }
}

void MainWidget::Print_info(int num, int type, int f_update) //слот вывода инфо о растении/ячейке почвы (номер объекта, тип объекта (0 - ячейка почвы, 1 - трава, 2 - куст, 3 - дерево), флаг обновления (=0, если не надо обновлять названия строк, иначе =1)
{
    if(type==0) //если инфо о почве
    {
        if(f_update==1) //если нужно обновить строки
        {
            ui->info_name->setText("Инфо о ячейке почвы");
            ui->info_00->setText("NUM:");
            ui->info_0->setText("OX верхн. лев. угла:");
            ui->info_1->setText("OY верхн. лев. угла:");
            ui->info_2->setText("Плодородность:");
            ui->info_3->setText("Плодородн. сейчас:");
            ui->info_4->setText("Влажность:");
            /*Очистка лишних строк*/
            ui->info_5->setText(" ");
            ui->info_6->setText(" ");
            ui->info_7->setText(" ");
            ui->info_8->setText(" ");
            ui->info_9->setText(" ");
            ui->info_10->setText(" ");
            ui->info_11->setText(" ");
            ui->info_12->setText(" ");
            ui->info_13->setText(" ");
            ui->info_14->setText(" ");
            ui->info_15->setText(" ");
            ui->i_5->setText(" ");
            ui->i_6->setText(" ");
            ui->i_7->setText(" ");
            ui->i_8->setText(" ");
            ui->i_9->setText(" ");
            ui->i_10->setText(" ");
            ui->i_11->setText(" ");
            ui->i_12->setText(" ");
            ui->i_13->setText(" ");
            ui->i_14->setText(" ");
            ui->i_15->setText(" ");
        }
        /*Вывод инфо о почве*/
        ui->i_00->setText(QString::number(num));
        ui->i_0->setText(QString::number(forest.get_ox_min_dirt(num)));
        ui->i_1->setText(QString::number(forest.get_oy_min_dirt(num)));
        ui->i_2->setText(QString::number(forest.get_fertility_dirt(num)));
        ui->i_3->setText(QString::number(forest.get_fertility_now_dirt(num)));
        ui->i_4->setText(QString::number(forest.get_wet_dirt(num)));
    }
    if(type>=1 && type<=3) //если инфо о растении
    {
        if(f_update==1) //если нужно обновить строки
        {
            ui->info_name->setText("Инфо о растении");
            ui->info_00->setText("Type:");
            ui->info_0->setText("NUM:");
            ui->info_1->setText("OX центра:");
            ui->info_2->setText("OY центра:");
            ui->info_3->setText("NUM ячейки почвы:");
            ui->info_4->setText("Высота:");
            ui->info_5->setText("Радиус:");
            ui->info_6->setText("Светолюбивость:");
            ui->info_7->setText("Агрессивность:");
            ui->info_8->setText("Влаголюбивость:");
            ui->info_9->setText("Кол-во очков роста:");
            ui->info_10->setText("Макс. очки роста:");
            ui->info_11->setText("Жизнеспособность:");
            ui->info_12->setText("Макс. высота:");
            ui->info_13->setText("Макс. радиус:");
            ui->info_14->setText("Норма питания:");
            ui->info_15->setText("Степень срубленности:");
        }
        QString type_text; //строка с текстовым названием типа растения
        switch(type)
        {
        case 1:
            type_text="Grass";
            break;
        case 2:
            type_text="Bush";
            break;
        case 3:
            type_text="Tree";
            break;
        }
        /*Вывод инфо о растении*/
        ui->i_00->setText(type_text);
        ui->i_0->setText(QString::number(num));
        ui->i_1->setText(QString::number(forest.get_x_plant(num,type)));
        ui->i_2->setText(QString::number(forest.get_y_plant(num,type)));
        ui->i_3->setText(QString::number(forest.get_num_dirt_plant(num,type)));
        ui->i_4->setText(QString::number(forest.get_height_plant(num,type)));
        ui->i_5->setText(QString::number(forest.get_radius_plant(num,type)));
        QString lightlove_text; //строка с текстовым названием типа светолюбивости
        switch(forest.get_lightlove_plant(num,type))
        {
        case TYPE_LOVE_BRIGHT:
            lightlove_text="Bright";
            break;
        case TYPE_LOVE_SHADOW:
            lightlove_text="Shadow";
            break;
        }
        ui->i_6->setText(lightlove_text);
        ui->i_7->setText(QString::number(forest.get_aggresiv_plant(num,type)));
        ui->i_8->setText(QString::number(forest.get_wetlove_plant(num,type)));
        ui->i_9->setText(QString::number(forest.get_score_grow_plant(num,type)));
        ui->i_10->setText(QString::number(forest.get_score_grow_max_plant(num,type)));
        ui->i_11->setText(QString::number(forest.get_viability_plant(num,type)));
        ui->i_12->setText(QString::number(forest.get_end_height_plant(num,type)));
        ui->i_13->setText(QString::number(forest.get_max_radius_plant(num,type)));
        ui->i_14->setText(QString::number(forest.get_feed_norm_plant(num,type)));

        if(type==TYPE_TREE)
        {
            ui->i_15->setText(QString::number(forest.get_cutting_degree_tree(num)));
        }
        else
        {
            ui->i_15->setText(" ");
        }
    }
    if(type<0) //очистить блок с инфо
    {
        ui->info_name->setText("Инфо о растении");
        ui->info_00->setText(" ");
        ui->info_0->setText(" ");
        ui->info_1->setText(" ");
        ui->info_2->setText(" ");
        ui->info_3->setText(" ");
        ui->info_4->setText(" ");
        ui->info_5->setText(" ");
        ui->info_6->setText(" ");
        ui->info_7->setText(" ");
        ui->info_8->setText(" ");
        ui->info_9->setText(" ");
        ui->info_10->setText(" ");
        ui->info_11->setText(" ");
        ui->info_12->setText(" ");
        ui->info_13->setText(" ");
        ui->info_14->setText(" ");
        ui->info_15->setText(" ");

        ui->i_00->setText(" ");
        ui->i_0->setText(" ");
        ui->i_1->setText(" ");
        ui->i_2->setText(" ");
        ui->i_3->setText(" ");
        ui->i_4->setText(" ");
        ui->i_5->setText(" ");
        ui->i_6->setText(" ");
        ui->i_7->setText(" ");
        ui->i_8->setText(" ");
        ui->i_9->setText(" ");
        ui->i_10->setText(" ");
        ui->i_11->setText(" ");
        ui->i_12->setText(" ");
        ui->i_13->setText(" ");
        ui->i_14->setText(" ");
        ui->i_15->setText(" ");
    }
}

void MainWidget::Print_human_info(int f_output, int f_update) //слот вывода инфо о людях (если передан неотмеченный первый флаг, то просто вывести пустые строки) (флаг обновления показывает, надо ли обновлять названия столбцов)
{
    if(f_output==0 && f_update==1) //если не выводить инфо и обновить строки, то вывести пустые строки
    {
        ui->infoh_1->setText(" ");
        ui->infoh_2->setText(" ");
        ui->infoh_3->setText(" ");
        ui->infoh_4->setText(" ");
        ui->infoh_5->setText(" ");
        ui->infoh_6->setText(" ");
        ui->infoh_7->setText(" ");
        ui->infoh_8->setText(" ");
        ui->infoh_9->setText(" ");
        ui->infoh_10->setText(" ");
        ui->infoh_11->setText(" ");

        ui->f1_1->setText(" ");
        ui->f1_2->setText(" ");
        ui->f1_3->setText(" ");
        ui->f1_4->setText(" ");
        ui->f1_5->setText(" ");
        ui->f1_6->setText(" ");
        ui->f1_7->setText(" ");
        ui->f1_8->setText(" ");
        ui->f1_9->setText(" ");
        ui->f1_10->setText(" ");
        ui->f1_11->setText(" ");
    }
    if(f_output==1 && f_update==1) //вывести названия строк
    {
        ui->infoh_1->setText("OX:");
        ui->infoh_2->setText("OY:");
        ui->infoh_3->setText("Скорость:");
        ui->infoh_4->setText("OX цели:");
        ui->infoh_5->setText("OY цели:");
        ui->infoh_6->setText("Рад. обзора:");
        ui->infoh_7->setText("Скор. рубки:");
        ui->infoh_8->setText("Тип цели:");
        ui->infoh_9->setText(" ");
        ui->infoh_10->setText(" ");
        ui->infoh_11->setText(" ");
    }
    if(f_output==1) //вывести инфо о леснике
    {
        ui->f1_1->setText(QString::number(forester.get_ox()));
        ui->f1_2->setText(QString::number(forester.get_oy()));
        ui->f1_3->setText(QString::number(forester.get_speed()));
        ui->f1_4->setText(QString::number(forester.get_target_ox()));
        ui->f1_5->setText(QString::number(forester.get_target_oy()));
        ui->f1_6->setText(QString::number(forester.get_view_radius()));
        ui->f1_7->setText(" ");
        QString target_type_text; //строка с текстовым названием типа цели
        switch(forester.get_target_type())
        {
        case TARGET_HOUSE:
            target_type_text="House";
            break;
        case TARGET_POACHER:
            target_type_text="Poacher";
            break;
        case TARGET_TREE:
            target_type_text="Tree";
            break;
        case TARGET_CORNER_ESCAPE:
            target_type_text="Escape";
            break;
        case TARGET_ROUTE:
            target_type_text="Route";
            break;
        }
        ui->f1_8->setText(target_type_text);
        ui->f1_9->setText(" ");
        ui->f1_10->setText(" ");
        ui->f1_11->setText(" ");
    }
    if(invaders.get_kolvo_poacher()>=1 && f_output==1) //если есть 1 браконьер и вкл. вывод, то вывести инфо о нём
    {
        int num=0; //номер браконьера для вывода инфо
        ui->p1_1->setText(QString::number(invaders.get_ox(num)));
        ui->p1_2->setText(QString::number(invaders.get_oy(num)));
        ui->p1_3->setText(QString::number(invaders.get_speed(num)));
        ui->p1_4->setText(QString::number(invaders.get_target_ox(num)));
        ui->p1_5->setText(QString::number(invaders.get_target_oy(num)));
        ui->p1_6->setText(QString::number(invaders.get_view_radius(num)));
        ui->p1_7->setText(QString::number(invaders.get_cutting_speed(num)));
        QString target_type_text; //строка с текстовым названием типа цели
        switch(invaders.get_target_type(num))
        {
        case TARGET_HOUSE:
            target_type_text="House";
            break;
        case TARGET_POACHER:
            target_type_text="Poacher";
            break;
        case TARGET_TREE:
            target_type_text="Tree";
            break;
        case TARGET_CORNER_ESCAPE:
            target_type_text="Escape";
            break;
        case TARGET_ROUTE:
            target_type_text="Route";
            break;
        }
        ui->p1_8->setText(target_type_text);
        ui->p1_9->setText(" ");
        ui->p1_10->setText(" ");
        ui->p1_11->setText(" ");
    }
    else //вывести пустые ячейки в инфо о 1-м браконьере
    {
        ui->p1_1->setText(" ");
        ui->p1_2->setText(" ");
        ui->p1_3->setText(" ");
        ui->p1_4->setText(" ");
        ui->p1_5->setText(" ");
        ui->p1_6->setText(" ");
        ui->p1_7->setText(" ");
        ui->p1_8->setText(" ");
        ui->p1_9->setText(" ");
        ui->p1_10->setText(" ");
        ui->p1_11->setText(" ");
    }
    if(invaders.get_kolvo_poacher()>=2 && f_output==1) //если есть 2-й браконьер и вкл. вывод, то вывести инфо о нём
    {
        int num=1; //номер браконьера для вывода инфо
        ui->p2_1->setText(QString::number(invaders.get_ox(num)));
        ui->p2_2->setText(QString::number(invaders.get_oy(num)));
        ui->p2_3->setText(QString::number(invaders.get_speed(num)));
        ui->p2_4->setText(QString::number(invaders.get_target_ox(num)));
        ui->p2_5->setText(QString::number(invaders.get_target_oy(num)));
        ui->p2_6->setText(QString::number(invaders.get_view_radius(num)));
        ui->p2_7->setText(QString::number(invaders.get_cutting_speed(num)));
        QString target_type_text; //строка с текстовым названием типа цели
        switch(invaders.get_target_type(num))
        {
        case TARGET_HOUSE:
            target_type_text="House";
            break;
        case TARGET_POACHER:
            target_type_text="Poacher";
            break;
        case TARGET_TREE:
            target_type_text="Tree";
            break;
        case TARGET_CORNER_ESCAPE:
            target_type_text="Escape";
            break;
        case TARGET_ROUTE:
            target_type_text="Route";
            break;
        }
        ui->p2_8->setText(target_type_text);
        ui->p2_9->setText(" ");
        ui->p2_10->setText(" ");
        ui->p2_11->setText(" ");
    }
    else //вывести пустые ячейки в инфо о 2-м браконьере
    {
        ui->p2_1->setText(" ");
        ui->p2_2->setText(" ");
        ui->p2_3->setText(" ");
        ui->p2_4->setText(" ");
        ui->p2_5->setText(" ");
        ui->p2_6->setText(" ");
        ui->p2_7->setText(" ");
        ui->p2_8->setText(" ");
        ui->p2_9->setText(" ");
        ui->p2_10->setText(" ");
        ui->p2_11->setText(" ");
    }
}

void MainWidget::Print_weather_info() //слот вывода инфо о погоде
{
    ui->w_0->setText(QString::number(weather.get_sunshine()));
    QString f_status_text; //строка с текстовым названием типа погоды
    switch(weather.get_f_status())
    {
    case F_SUN:
        f_status_text="Sunny";
        break;
    case F_CLOUD:
        f_status_text="Cloudy";
        break;
    case F_RAIN:
        f_status_text="Rainy";
        break;
    }
    ui->w_1->setText(f_status_text);
    ui->w_2->setText(QString::number(weather.get_rainfall_tick()));
    ui->w_3->setText(QString::number(weather.get_time_status()));
}

void MainWidget::Print_forest_info() //слот вывода инфо о лесе
{
    ui->fi_0->setText(QString::number(forest.get_kolvo_dirt()));
    ui->fi_1->setText(QString::number(forest.get_kolvo_grass()));
    ui->fi_2->setText(QString::number(forest.get_kolvo_bush()));
    ui->fi_3->setText(QString::number(forest.get_kolvo_tree()));
}

void MainWidget::Show_pic(int num, int type) //слот - вывести изображение на поле (1 - трава, 2 - куст, 3 - дерево, 4 - лесник, 5 - браконьер, 6 - дом)
{
    QLabel **new_img=nullptr; //указатель на новый label с картинкой объекта

    if(type>=1 && type<=3) //растение
    {
        forest.get_img(&new_img, num, type); //получить адрес для объекта - label с изображением объекта
    }
    if(type==4) //лесник
    {
        forester.get_img(&new_img); //получить адрес для объекта - label с изображением лесника
    }
    if(type==5) //браконьер
    {
        invaders.get_img(&new_img, num); //получить адрес для объекта - label с изображением браконьера
    }
    if(type==6) //дом лесника
    {
        new_img=&house_img; //получить адрес для объекта - label с изображением дома
    }

    int x_object=0, y_object=0, radius_object=0; //координаты x, y и радиус объекта
    int x_png, y_png, w_png, h_png; //координаты x, y изображения объекта и его ширина, высота

    if(type>=1 && type<=3) //растение
    {
        x_object=forest.get_x_plant(num, type); //получить значение поля растения
        y_object=forest.get_y_plant(num, type); //получить значение поля растения
        radius_object=forest.get_radius_plant(num, type); //получить значение поля растения
    }

    if(type==4) // лесник
    {
        x_object=forester.get_ox(); //получить значение поля человека
        y_object=forester.get_oy(); //получить значение поля человека
        radius_object=RADIUS_PIC_HUMAN;
    }
    if(type==5) //браконьер
    {
        x_object=invaders.get_ox(num); //получить значение поля человека
        y_object=invaders.get_oy(num); //получить значение поля человека
        radius_object=RADIUS_PIC_HUMAN;
    }
    if(type==6) //дом лесника
    {
        x_object=HOUSE_OX;
        y_object=HOUSE_OY;
        radius_object=RADIUS_PIC_HOUSE;
    }

    x_png = x_object - radius_object; //получить координату x верхнего левого угла изображения объекта
    y_png = y_object - radius_object; //получить координату y верхнего левого угла изображения объекта
    w_png = h_png = radius_object*2; // получить ширину и высоту изображения
    (*new_img) = new QLabel(" ", ui->place); //создать новый label для картинки данного объекта
    (*new_img) ->setGeometry(x_png,y_png,w_png,h_png); //указать размеры картинки и её положение
    switch (type)
    {
    case 1: //трава
        if(num==num_info && type==type_of_info) //если сейчас для вывода инфо выбрано данное растение, вывести особую картинку с красными краями
            (*new_img) ->setPixmap(*pgrass_selected); // вывести картинку в лейбл
        else
            (*new_img) ->setPixmap(*pgrass); // вывести картинку в лейбл
        break;
    case 2: //куст
        if(num==num_info && type==type_of_info) //если сейчас для вывода инфо выбрано данное растение, вывести особую картинку с красными краями
            (*new_img) ->setPixmap(*pbush_selected); // вывести картинку в лейбл
        else
            (*new_img) ->setPixmap(*pbush); // вывести картинку в лейбл
        break;
    case 3: //дерево
        if(num==num_info && type==type_of_info) //если сейчас для вывода инфо выбрано данное растение, вывести особую картинку с красными краями
            (*new_img) ->setPixmap(*ptree_selected); // вывести картинку в лейбл
        else
            (*new_img) ->setPixmap(*ptree); // вывести картинку в лейбл
        break;
    case 4: //лесник
        (*new_img) ->setPixmap(*pforester); // вывести картинку в лейбл
        break;
    case 5: //браконьер
        if(num==0) //если первый браконьер
        {
            (*new_img) ->setPixmap(*ppoacher1); // вывести картинку в лейбл
        }
        if(num==1) //если второй браконьер
        {
            (*new_img) ->setPixmap(*ppoacher2); // вывести картинку в лейбл
        }
        break;
    case 6:
        (*new_img) ->setPixmap(*phouse); // вывести картинку в лейбл
        break;
    }
    (*new_img)->setScaledContents(true); //автомасштабирование картинки внутри qlabel
    (*new_img)->setStyleSheet("background-image:url(\"empty.png\");" ); // изменить фон на прозрачный (необходимо из-за наследования от place)
    (*new_img) ->show(); //вывести qlabel
}

void MainWidget::Add_invader() //слот добавления нового браконьера на поле в случайный из углов (кроме нижнего правого) и вывод его картинки
{
    int ox_start, oy_start; //стартовые координаты браконьера
    int rand_start= RAND(1,3); //случайное число для выбора угла (кроме угла с домиком лесника)
    ox_start = invaders.get_corner(rand_start, X_CORNER); //получить координату выбранного случайного угла
    oy_start = invaders.get_corner(rand_start, Y_CORNER); //получить координату выбранного случайного угла

    invaders.Add_invader(ox_start, oy_start); //добавить браконьера с выбранными стартовыми координатами
    Show_pic(invaders.get_kolvo_poacher()-1, TYPE_POACHER); //вывести его картинку на экран
}
void MainWidget::Find_target(int num, int type) //найти цель для человека (тип: 1 - лесник, 2 - браконьер)
{
    switch(type)
    {
    case 1: //лесник
        if(weather.get_f_status()!=F_RAIN) //если сейчас не дождь
        {
            int min_dist=-1; //расстояние до ближайшей цели
            int num_target=-1; //номер цели (номер браконьера)
            int ox1 = forester.get_ox(); // координата ox лесника
            int oy1 = forester.get_oy(); // координата oy лесника
            for(int i=0, kolvo=invaders.get_kolvo_poacher(); i<kolvo; i++)
            {
                int ox2 = invaders.get_ox(i); // координата ox текущего браконьера
                int oy2 = invaders.get_oy(i); // координата oy текущего браконьера
                int dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между двумя точками

                if(dist<=forester.get_view_radius()) //если браконьер находится внутри области видимости
                {
                    if(dist<min_dist || min_dist==-1) //если найдена ближайшая цель
                    {
                        min_dist=dist; //записать расстояние до этой цели как минимальное
                        num_target=i; //записать номер цели
                    }
                }

            }
            if(min_dist!=-1) //если в области видимости найден браконьер
            {
                forester.set_target_type(TARGET_POACHER); //цель лесника - браконьер
                forester.set_target_ox(invaders.get_ox(num_target)); //установить координаты цели - браконьер
                forester.set_target_oy(invaders.get_oy(num_target)); //установить координаты цели - браконьер

            }
            else //если в области видимости не найден браконьер
            {
                if(forester.get_target_type()==TARGET_ROUTE) //если предыдущей целью была точка маршрута, то следующей целью будет следующая точка по порядку
                {
                    num_target=-1; //номер цели (номер точки маршрута)
                    int old_target_ox = forester.get_target_ox(); //координата предыдущей точки маршрута
                    int old_target_oy = forester.get_target_oy(); //координата предыдущей точки маршрута
                    for(int i=0; i<KOLVO_ROUTE_POINTS; i++) //перебрать все точки маршрута
                    {
                        //если найдена точка маршрута с координатами, которые ранее являлись целью лесника
                        if((old_target_ox==forester.get_route_points(i, X_CORNER)) && (old_target_oy==forester.get_route_points(i, Y_CORNER)))
                        {
                            num_target=i; //записать номер старой точки маршрута
                            break; //остановить поиск
                        }
                    }
                    num_target=num_target+1; //теперь целью является следующая точка маршрута
                    if(num_target==KOLVO_ROUTE_POINTS) //если предыдущей была последняя точка маршрута
                    {
                        num_target=0; //то следующей точкой маршрута будет самая первая
                    }
                    forester.set_target_type(TARGET_ROUTE); // цель лесника - точка маршрута патрулирования
                    forester.set_target_ox(forester.get_route_points(num_target, X_CORNER)); //установить координаты цели - точка маршрута патрулирования
                    forester.set_target_oy(forester.get_route_points(num_target, Y_CORNER)); //установить координаты цели - точка маршрута патрулирования
                }
                else //иначе выбрать целью ближайшую точку маршрута
                {
                    min_dist=-1; //расстояние до ближайшей точки маршрута
                    num_target=-1; //номер цели (номер точки маршрута)
                    for(int i=0; i<KOLVO_ROUTE_POINTS; i++) //перебрать все точки маршрута
                    {
                        int ox2=forester.get_route_points(i, X_CORNER); // координата ox точки маршрута
                        int oy2=forester.get_route_points(i, Y_CORNER); // координата oy точки маршрута
                        int dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между двумя точками
                        if((dist<min_dist || min_dist==-1) && dist!=0) //если найдена ближайшая цель и её координаты не совпадают с координатами лесника
                        {
                            min_dist=dist; //записать расстояние до этой цели как минимальное
                            num_target=i; //записать номер цели
                        }
                    }
                    forester.set_target_type(TARGET_ROUTE); // цель лесника - точка маршрута патрулирования
                    forester.set_target_ox(forester.get_route_points(num_target, X_CORNER)); //установить координаты цели - точка маршрута патрулирования
                    forester.set_target_oy(forester.get_route_points(num_target, Y_CORNER)); //установить координаты цели - точка маршрута патрулирования
                }
            }
        }
        else // если сейчас дождь
        {
            forester.set_target_type(TARGET_HOUSE); //в дождь цель лесника - дом
            forester.set_target_ox(HOUSE_OX); //установить координаты цели - дом
            forester.set_target_oy(HOUSE_OY); //установить координаты цели - дом
        }
        break;
    case 2: //браконьер
        int min_dist=-1; //расстояние до лесника
        int ox1 = invaders.get_ox(num); // координата ox текущего браконьера
        int oy1 = invaders.get_oy(num); // координата oy текущего браконьера
        int ox2 = forester.get_ox(); // координата ox лесника
        int oy2 = forester.get_oy(); // координата oy лесника
        int dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между двумя точками

        if(dist<=invaders.get_view_radius(num) && weather.get_f_status()!=F_RAIN) //если лесник находится внутри области видимости и сейчас не дождь
        {
            min_dist=-1; //расстояние до ближайшей цели - угла
            int num_target=-1; //номер цели (номер угла)
            for(int i=0; i<3; i++) //перебрать доступные углы для побега
            {
                ox2=invaders.get_corner(i, X_CORNER); // координата ox угла
                oy2=invaders.get_corner(i, Y_CORNER); // координата oy угла
                dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между двумя точками
                if(dist<min_dist || min_dist==-1) //если найдена ближайшая цель
                {
                    min_dist=dist; //записать расстояние до этой цели как минимальное
                    num_target=i; //записать номер цели
                }
            }

            invaders.set_target_type(num, TARGET_CORNER_ESCAPE); //цель браконьера - угол поля для побега
            invaders.set_target_ox(num, invaders.get_corner(num_target, X_CORNER)); //установить координаты цели
            invaders.set_target_oy(num, invaders.get_corner(num_target, Y_CORNER)); //установить координаты цели
        }
        else //если лесник не находится внутри области видимости
        {
            min_dist=-1; //расстояние до ближайшей цели
            int num_target=-1; //номер цели (номер дерева)
            int max_cutting_degree=0; //наибольшая найденная степень срубленности дерева (браконьер идёт рубить уже подребленное, если оно есть)
            for(int i=0, kolvo=forest.get_kolvo_tree(); i<kolvo; i++)
            {
                ox2 = forest.get_x_plant(i, TYPE_TREE); // координата ox текущего дерева
                oy2 = forest.get_y_plant(i, TYPE_TREE); // координата oy текущего дерева
                dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между двумя точками

                if(dist<=invaders.get_view_radius(num)) //если дерево находится внутри области видимости
                {
                    if(forest.get_cutting_degree_tree(i)>=max_cutting_degree) //если найденное дерево срублено сильнее или также, как и предыдущее найденное
                    {
                        if(dist<min_dist || min_dist==-1) //если найдена ближайшая цель
                        {
                            max_cutting_degree=forest.get_cutting_degree_tree(i); //сохранить степень срубленности этого дерева
                            min_dist=dist; //записать расстояние до этой цели как минимальное
                            num_target=i; //записать номер цели
                        }
                    }
                }
            }
            if(min_dist!=-1) //если в области видимости найдено дерево
            {
                invaders.set_target_type(num, TARGET_TREE); //цель браконьера - дерево
                invaders.set_target_ox(num, forest.get_x_plant(num_target, TYPE_TREE)); //установить координаты цели - дерево
                invaders.set_target_oy(num, forest.get_y_plant(num_target, TYPE_TREE)); //установить координаты цели - дерево
            }
            else //если в области видимости не найдено дерево
            {
                if(invaders.get_target_type(num)==TARGET_ROUTE) //если предыдущей целью была точка маршрута, то следующей целью будет следующая точка по порядку
                {
                    num_target=-1; //номер цели (номер точки маршрута)
                    int old_target_ox = invaders.get_target_ox(num); //координата предыдущей точки маршрута
                    int old_target_oy = invaders.get_target_oy(num); //координата предыдущей точки маршрута
                    for(int i=0; i<KOLVO_ROUTE_POINTS; i++) //перебрать все точки маршрута
                    {
                        //если найдена точка маршрута с координатами, которые ранее являлись целью браконьера
                        if((old_target_ox==invaders.get_route_points(i, X_CORNER)) && (old_target_oy==invaders.get_route_points(i, Y_CORNER)))
                        {
                            num_target=i; //записать номер старой точки маршрута
                            break; //остановить поиск
                        }
                    }
                    num_target=num_target+1; //теперь целью является следующая точка маршрута
                    if(num_target==KOLVO_ROUTE_POINTS) //если предыдущей была последняя точка маршрута
                    {
                        num_target=0; //то следующей точкой маршрута будет самая первая
                    }
                    invaders.set_target_type(num, TARGET_ROUTE); // цель браконьера - точка маршрута исследования
                    invaders.set_target_ox(num, invaders.get_route_points(num_target, X_CORNER)); //установить координаты цели - точка маршрута исследования
                    invaders.set_target_oy(num, invaders.get_route_points(num_target, Y_CORNER)); //установить координаты цели - точка маршрута исследования
                }
                else //иначе выбрать целью ближайшую точку маршрута
                {
                    min_dist=-1; //расстояние до ближайшей точки маршрута
                    num_target=-1; //номер цели (номер точки маршрута)
                    for(int i=0; i<KOLVO_ROUTE_POINTS; i++) //перебрать все точки маршрута
                    {
                        int ox2=invaders.get_route_points(i, X_CORNER); // координата ox точки маршрута
                        int oy2=invaders.get_route_points(i, Y_CORNER); // координата oy точки маршрута
                        int dist = sqrt(((ox2-ox1)*(ox2-ox1))+((oy2-oy1)*(oy2-oy1))); //расстояние между двумя точками
                        if((dist<min_dist || min_dist==-1) && dist!=0) //если найдена ближайшая цель и её координаты не совпадают с координатами браконьера
                        {
                            min_dist=dist; //записать расстояние до этой цели как минимальное
                            num_target=i; //записать номер цели
                        }
                    }
                    invaders.set_target_type(num, TARGET_ROUTE); // цель браконьера - точка маршрута исследования
                    invaders.set_target_ox(num, invaders.get_route_points(num_target, X_CORNER)); //установить координаты цели - точка маршрута исследования
                    invaders.set_target_oy(num, invaders.get_route_points(num_target, Y_CORNER)); //установить координаты цели - точка маршрута исследования
                }
            }
        }
        break;
    }
}

void MainWidget::Remove_plant_and_resort(int num_sort, struct plant_sort **plants, int *kolvo_plants) //удалить растение (оно зачахло) и убрать запись о нём в структуре сортировки
{
    int num_delete = (*plants)->num; //номер удаляемого растения
    int type_delete = (*plants)->type; //тип удаляемого растения

    QLabel **img_delete=nullptr; //указатель на label с картинкой растения
    forest.get_img(&img_delete, num_delete, type_delete); //получить адрес для объекта - label с изображением растения
    (*img_delete)->deleteLater(); //удалить qlabel  с изображением растения

    if(type_delete==type_of_info && num_info>=num_delete) //проверить вывод инфо о выбранном растении (если удаляется выбранное, то переключиться на другое)
    {
        num_info=num_info-1;
        if(num_info<0) //если растений больше нет, то новую инфу не выводить
        {
            num_info=-1;
            type_of_info=-1;
            Print_info(0, -1, 0); //очистить блок с инфо о растении
        }

    }
    forest.Delete_plant(num_delete, type_delete); //удалить объект растения

    plant_sort *new_plants = new plant_sort[(*kolvo_plants)-1]; //новая структура сортировки

    for(int i=0, j=0; i<(*kolvo_plants); i++) //перебрать элементы структуры
    {
        if(i!=num_sort) //если это не удаляемый элемент
        {
            new_plants[j]=(*plants)[i]; //перенести значения в новый массив
            if(new_plants[j].type==type_delete && new_plants[j].num>num_delete)
            {
                new_plants[j].num = new_plants[j].num -1; //если этот элемент структуры содержит инфо о растении, которое слеовало за удаляемом в массиве, то уменьшить его порядковый номер
            }
            j++;
        }
    }

    delete[] (*plants); //очистить память от старой структуры сортировки
    (*plants) = new_plants; //сохранить обновлённую структуру

    (*kolvo_plants) = (*kolvo_plants)-1; //теперь кол-во растений меньше на 1

    all_plants_died=all_plants_died+1;
    ui->all_plants_died_text->setText("Всего растений завяли: "+QString::number(all_plants_died)); //вывести на экран
}
