#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "classes.h" //классы растение, погода и т. д. для работы программы
#include <qtimer.h>
#include <QMouseEvent>

QTimer *timer; // таймер для работы модели
Forest forest; //объект - лес
Weather weather; //объект - погода
Forester forester; //объект - лесник
Invaders invaders; //объект - чужаки

int num_info=-1; //номер растения/ячейки почвы для инфо
int type_of_info=-1; //тип вывода инфо (-1 - никакое, 0 - ячейка почвы, 1 - трава, 2 - куст, 3 - дерево)
int all_time=0; //общее время работы программы (кол-во тиков)

QPixmap *sun; //объект с картинкой солнца
QPixmap *cloud; //объект с картинкой облака
QPixmap *rain; //объект с картинкой дождя
QPixmap *pgrass; //объект с картинкой Трава
QPixmap *pgrass_selected; //объект с картинкой Трава выбранная
QPixmap *pbush; //объект с картинкой Куст
QPixmap *pbush_selected; //объект с картинкой Куст выбранный
QPixmap *ptree; //объект с картинкой Дерево
QPixmap *ptree_selected; //объект с картинкой Дерево выбранное

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
    pgrass_selected = new QPixmap("grass_selected.png"); //объект с картинкой Трава выбранная
    pbush = new QPixmap("bush.png"); //объект с картинкой Куст
    pbush_selected = new QPixmap("bush_selected.png"); //объект с картинкой Куст выбранный
    ptree = new QPixmap("tree.png"); //объект с картинкой Дерево
    ptree_selected = new QPixmap("tree_selected.png"); //объект с картинкой Дерево выбранное

    ui->pogoda->setPixmap(*sun); // вывести картинку в лейбл
    ui->place->setStyleSheet("background-image:url(\"dirt_grid.png\"); background-position: center;" ); // вывести земляной фон в frame

    forest.Dirt_Init(); //инициализация ячеек почвы
    weather.Weather_Init(); //инициализация погоды

    Print_forest_info(); //вывести инфо о лесе
    Print_info(0, -1, 0); //очистить блок с инфо о растении
    Print_weather_info(); //вывести инфо о погоде

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

void MainWidget::Timer_tick() //слот интервала таймера
{
    all_time=all_time+1; //получить новое значение общего времени
    ui->all_time_text->setText("Всего времени прошло (в тиках): "+QString::number(all_time)); //вывести на экран

    weather.set_time_status(weather.get_time_status()+1); //увеличить кол-во времени текущей погоды
    if(weather.get_time_status()==TIME_STATUS_END) //если время типа погоды закончилось, случайно выбрать один из двух других
    {
        int randm=RAND(0,1);
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

        switch(weather.get_f_status())
        {
        case F_SUN:
            weather.set_sunshine(RAND(SUNSHINE_SUN-SUNSHINE_SUN_RANGE, SUNSHINE_SUN+SUNSHINE_SUN_RANGE)); //яркость солнца случайно меняется каждый тик в своём диапазоне
            weather.set_rainfall_tick(RAINFALL_TICK_SUN);
            break;
        case F_CLOUD:
            weather.set_sunshine(RAND(SUNSHINE_CLOUD-SUNSHINE_CLOUD_RANGE, SUNSHINE_CLOUD+SUNSHINE_CLOUD_RANGE)); //яркость солнца случайно меняется каждый тик в своём диапазоне
            weather.set_rainfall_tick(RAINFALL_TICK_CLOUD); //небольшое кол-во осадков в виде росы
            break;
        case F_RAIN:
            weather.set_sunshine(RAND(SUNSHINE_RAIN-SUNSHINE_RAIN_RANGE, SUNSHINE_RAIN+SUNSHINE_RAIN_RANGE)); //яркость солнца случайно меняется каждый тик в своём диапазоне
            weather.set_rainfall_tick(RAND(RAINFALL_TICK_RAIN-RAINFALL_TICK_RAIN_RANGE, RAINFALL_TICK_RAIN+RAINFALL_TICK_RAIN_RANGE)); //кол-во осадков случайно меняется каждый тик в своём диапазоне
            break;
        }

        for(int i=0, kolvo=forest.get_kolvo_dirt(), rainf=weather.get_rainfall_tick(); i<kolvo; i++) //перебрать ячейки почвы
        {
            forest.set_wet_dirt(i, (forest.get_wet_dirt(i)+rainf)); //почва получает влагу
        }

        struct plant_sort //структура для сортировки растений (их упорядочиванию по высоте или агрессивности)
        {
            int num;
            int type;
            int height;
            int agressiv;
        } *plants;

        int all_plants=forest.get_kolvo_grass()+forest.get_kolvo_bush()+forest.get_kolvo_tree(); //кол-во растений всех видов
        plants = new plant_sort[all_plants]; //структура для сортировки

        for(int type=1, j=0; type<=3; type++) //заполнить структуру информацией о всех растениях
        {
            for(int i=0, kolvo=forest.get_kolvo_type(type); i<kolvo; i++)
            {
                plants[j].num=i;
                plants[j].type=type;
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
                        plants[i+1]=plants[i];
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

            int remain_wet = wet - forest.get_wet_dirt(num_dirt);




            int feed = forest.get_fertility_dirt(num_dirt);
            int remain_feed = feed - forest.get_feed_norm_plant(num, type);
            if (remain_feed >= 0) //растение получило достаточно питания
            {
                forest.set_fertility_dirt(num_dirt, feed+remain_feed);
                forest.set_score_grow_plant(num, type, (forest.get_score_grow_plant(num, type)+1));
                if(forest.get_score_grow_plant(num, type) == forest.get_score_grow_max_plant(num, type))
                {
                    forest.set_score_grow_plant(num, type, SCORE_GROW_START);
                    int grow_height, grow_radius;
                    switch (type)
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
                    forest.set_height_plant(num, type, (forest.get_height_plant(num, type)+grow_height));
                    forest.set_radius_plant(num, type, (forest.get_radius_plant(num, type)+grow_radius));

                }
            }
            else //растение получило недостаточно питания
            {

            }
        }

    }




    Print_forest_info(); //вывести инфо о лесе
    Print_weather_info(); //вывести инфо о погоде
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
            ui->info_3->setText("Эффектив. плодородн.:");
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
        }
        /*Вывод инфо о почве*/
        ui->i_00->setText(QString::number(num));
        ui->i_0->setText(QString::number(forest.get_ox_min_dirt(num)));
        ui->i_1->setText(QString::number(forest.get_oy_min_dirt(num)));
        ui->i_2->setText(QString::number(forest.get_fertility_dirt(num)));
        ui->i_3->setText(QString::number(forest.get_effectiv_dirt(num)));
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
        ui->i_6->setText(QString::number(forest.get_lightlove_plant(num,type)));
        ui->i_7->setText(QString::number(forest.get_aggresiv_plant(num,type)));
        ui->i_8->setText(QString::number(forest.get_wetlove_plant(num,type)));
        ui->i_9->setText(QString::number(forest.get_score_grow_plant(num,type)));
        ui->i_10->setText(QString::number(forest.get_score_grow_max_plant(num,type)));
        ui->i_11->setText(QString::number(forest.get_viability_plant(num,type)));
        ui->i_12->setText(QString::number(forest.get_end_height_plant(num,type)));
        ui->i_13->setText(QString::number(forest.get_max_radius_plant(num,type)));
        ui->i_14->setText(QString::number(forest.get_feed_norm_plant(num,type)));
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
    }
}

void MainWidget::Print_weather_info() //слот вывода инфо о погоде
{
    ui->w_0->setText(QString::number(weather.get_sunshine()));
    ui->w_1->setText(QString::number(weather.get_f_status()));
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

void MainWidget::Show_pic(int num, int type) //слот - вывести изображение растения
{
    QLabel **new_img=nullptr; //указатель на новый label с картинкой растения
    forest.get_img(&new_img, num, type); //получить адрес для объекта - label с изображением растения
    if(*new_img != nullptr) //удалить прошлую версию картинки, если она была
        (*new_img)->deleteLater();
    int x_plant, y_plant, radius_plant; //координаты x, y и радиус растения
    int x_png, y_png, w_png, h_png; //координаты x, y изображения растения и его ширина, высота
    x_plant=forest.get_x_plant(num, type); //получить значение поля растения
    y_plant=forest.get_y_plant(num, type); //получить значение поля растения
    radius_plant=forest.get_radius_plant(num, type); //получить значение поля растения
    x_png = x_plant - radius_plant; //получить координату x верхнего левого угла изображения растения
    y_png = y_plant - radius_plant; //получить координату y верхнего левого угла изображения растения
    w_png = h_png = radius_plant*2; // получить ширину и высоту изображения
    (*new_img) = new QLabel(" ", ui->place); //создать новый label для картинки данного растения
    (*new_img) ->setGeometry(x_png,y_png,w_png,h_png); //указать размеры картинки и её положение
    switch (type)
    {
    case 1:
        (*new_img) ->setPixmap(*pgrass); // вывести картинку в лейбл
        break;
    case 2:
        (*new_img) ->setPixmap(*pbush); // вывести картинку в лейбл
        break;
    case 3:
        (*new_img) ->setPixmap(*ptree); // вывести картинку в лейбл
        break;
    }
    (*new_img)->setScaledContents(true); //автомасштабирование картинки внутри qlabel
    (*new_img)->setStyleSheet("background-image:url(\"empty.png\");" ); // изменить фон на прозрачный (необходимо из-за наследования от place)
    (*new_img) ->show(); //вывести qlabel
}
