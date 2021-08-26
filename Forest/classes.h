#ifndef CLASSES_H
#define CLASSES_H

#include <qlabel.h>
#include "constants.h"

class Forest; //объявление класса
class Invaders; //объявление класса

class Plant // класс Растение
{
protected:
    int ox=0, oy=0; //координаты центра растения
    int num_dirt=0; //номер ячейки почвы, на которой находится
    int height; //высота
    int radius; //радиус кроны
    int lightlove; //светолюбивость
    int aggresiv; //агрессивность (скорость поглощения веществ и воды из почвы)
    int wetlove; //влаголюбивость
    int feed_norm; //нормальное разовое потребление питания
    int score_grow; //текущее кол-во очков роста (при достижении максимума увеличивается высота и радиус, а данный показатель вновь обнуляется)
    int score_grow_max; //макс кол-во очков роста, требуемое для роста растения
    double viability; //жизнеспособность (при уменьшении до нулевого значения растение умирает)

    int end_height; //конечная (макс.) высота растения (случайно генерируется при посадке, значение зависит от типа растения)
    int max_radius; //макс. радиус кроны (случайно генерируется при посадке, значение зависит от типа растения)

    QLabel *img; //указатель на label с изображением растения
public:
    Plant();
    void Change_OXY(int ox_new, int oy_new); //установка новых координат

    friend class Forest; //дружественный класс, имеет доступ ко всем полям данного
};

class Grass : public Plant //класс Трава
{
public:
    Grass();
    void Init_rand(); //инициализация случайными значениями
};

class Bush : public Plant //класс Куст
{
public:
    Bush();
    void Init_rand(); //инициализация случайными значениями
};

class Tree : public Plant //класс Дерево
{
private:
    int cutting_degree=0; //степень срубленности дерева
public:
    Tree();
    void Init_rand(); //инициализация случайными значениями

    friend class Forest; //дружественный класс, имеет доступ ко всем полям данного
};

class Dirt_cell //класс ячейки почвы
{
private:
    int ox_min, oy_min; //координаты верхнего левого угла ячейки
    int fertility; // плодородность почвы
    int effectiv; // эффективность плодородности (изначально 1, при истощении/насыщении изменяется)
    int wet; //влажность
public:
    Dirt_cell();

    friend class Forest; //дружественный класс, имеет доступ ко всем полям данного
};

class Forest // класс Лес
{
private:
    Dirt_cell dirt[KOLVO_DIRT]; //массив с ячейками почвы
    Grass* grass; //указатель на массив объектов Трава
    Bush* bush; //указатель на массив объектов Куст
    Tree* tree; //указатель на массив объектов Дерево

    int kolvo_dirt = KOLVO_DIRT; //кол-во ячеек почвы
    int kolvo_grass=0; //кол-во объектов травы
    int kolvo_bush=0; //кол-во кустов
    int kolvo_tree=0;  //кол-во деревьев

public:
    Forest();
    void Add_plant(int x, int y, int type); //добавить растение (тип: 1 - трава, 2 - куст, 3 - дерево)
    void Delete_plant(int num, int type); //удалить растение (тип: 1 - трава, 2 - куст, 3 - дерево)
    void get_img(QLabel*** png, int num, int type); //вернуть указатель на изображение выбранного растения
    void Dirt_Init(); //инициализация ячеек почвы
    void Find_dirt_for_plant(int num, int type); //найти номер ячейки почвы для растения (координаты уже записаны в поля растения) (тип: 1 - трава, 2 - куст, 3 - дерево)
    int Belonging_of_coordinat(int num, int type, int x, int y); //проверка, что координаты x и y принадлежат окружности растения (возвращает 1, если верно и 0, если неверно)



    /*методы получения и установления полей объекта класса Forest*/
    int get_kolvo_grass();
    int get_kolvo_bush();
    int get_kolvo_tree();
    int get_kolvo_dirt();
    int get_kolvo_type(int type); //вернуть кол-во объектов выбранного типа (0 - ячейка почвы, 1 - трава, 2 - куст, 3 - дерево)
    /*методы получения и установления полей объекта класса Dirt_cell*/
    int get_ox_min_dirt(int num); //получить поле "ox_min" выбранной ячейки почвы
    int get_oy_min_dirt(int num); //получить поле "oy_min" выбранной ячейки почвы
    int get_fertility_dirt(int num); //получить поле "fertility" выбранной ячейки почвы
    int get_effectiv_dirt(int num); //получить поле "effectiv" выбранной ячейки почвы
    int get_wet_dirt(int num); //получить поле "wet" выбранной ячейки почвы

    void set_wet_dirt(int num, int inp); //установить значение поля "wet" выбранной ячейки почвы
    void set_fertility_dirt(int num, int inp); //установить значение поля "fertility" выбранной ячейки почвы
    /*методы получения и установления полей объекта класса Plant*/
    int get_x_plant(int num, int type); //получить поле "x" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_y_plant(int num, int type); //получить поле "y" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_num_dirt_plant(int num, int type); //получить поле "num_dirt" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_height_plant(int num, int type); //получить поле "height" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_radius_plant(int num, int type); //получить поле "radius" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_lightlove_plant(int num, int type); //получить поле "lightlove" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_aggresiv_plant(int num, int type); //получить поле "aggresiv" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_wetlove_plant(int num, int type); //получить поле "wetlove" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_score_grow_plant(int num, int type); //получить поле "score_grow" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_score_grow_max_plant(int num, int type); //получить поле "score_grow_max" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    double get_viability_plant(int num, int type); //получить поле "viability" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_end_height_plant(int num, int type); //получить поле "end_height" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_max_radius_plant(int num, int type); //получить поле "max_radius" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    int get_feed_norm_plant(int num, int type); //получить поле "feed_norm" растения (тип: 1 - трава, 2 - куст, 3 - дерево)

    int get_cutting_degree_tree(int num); //получить поле "cutting_degree" дерева

    void set_score_grow_plant(int num, int type, int inp); //установить значение поля "score_grow" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    void set_height_plant(int num, int type, int inp); //получить поле "height" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    void set_radius_plant(int num, int type, int inp); //получить поле "radius" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
    void set_viability_plant(int num, int type, double inp); //получить поле "viability" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
};

class Weather //класс Погода
{
private:
    int sunshine; // уровень яркости солнца
    int f_status; //флаг текущей погоды (0 - солнечно, 1 - облачно, 2 - дождь)
    int rainfall_tick; //кол-во осадков за один тик (при дожде)
    int time_status; // время текущего состояния (при достижении 10 тиков обнуляется. Затем дождь/солнечность/облачность заканчивается или начинается (с некоторой вероятностью начала определённой погоды))
public:
    Weather();
    void Weather_Init(); //инициализация погоды

    /*методы получения и установления полей объекта класса*/
    void set_sunshine(int inp);
    int get_sunshine();
    void set_f_status(int inp);
    int get_f_status();
    void set_rainfall_tick(int inp);
    int get_rainfall_tick();
    void set_time_status(int inp);
    int get_time_status();
};

class Human //класс Человек
{
protected:
    int ox=0, oy=0; //координаты
    int speed; //скорость (кол-во пикселей за один шаг)
    int target_ox, target_oy; //координаты цели
    int target_type=-1; //тип цели
    int tired; //усталость
    int view_radius; //радиус поля обзора

    QLabel *img; //указатель на label с изображением человека
public:
    Human();
};

class Poacher : public Human //класс Браконьер
{
private:
    int cutting_speed; //скорость рубки деревьев
public:
    Poacher();
    void Init(); //инициализация

    friend class Invaders; //дружественный класс, имеет доступ ко всем полям данного
};

class Forester : public Human //класс Лесник
{
private:
    int route_points[8][2]; //массив точек маршрута патрулирования леса лесником (второй индекс - если [0], то x; если [1], то y)
public:
    Forester();
    void Init(); //инициализация

    void set_route_points(); //установить координаты для маршрута патрулирования лесника
    int get_route_points(int num, int coord); //получить координаты точки маршрута лесника (coord - x или y)

    /*методы получения и установления полей*/
    int get_ox(); //получить поле "ox"
    int get_oy(); //получить поле "oy"
    int get_speed(); //получить поле "speed"
    int get_target_ox(); //получить поле "target_ox"
    int get_target_oy(); //получить поле "target_oy"
    int get_tired(); //получить поле "tired"
    int get_view_radius(); //получить поле "view_radius"
    int get_target_type(); //получить поле "target_type"
    void get_img(QLabel*** png); //вернуть указатель на изображение лесника

    void set_ox(int inp); //установить поле "ox"
    void set_oy(int inp); //установить поле "oy"
    void set_speed(int inp); //установить поле "speed"
    void set_target_ox(int inp); //установить поле "target_ox"
    void set_target_oy(int inp); //установить поле "target_oy"
    void set_tired(int inp); //установить поле "tired"
    void set_target_type(int inp); //установить поле "target_type"
};

class Invaders //класс Чужаки (для леса)
{
private:
    Poacher* poachers; //указатель на массив объектов Браконьер
    int corners [3][2]; //массив координат углов для старта браконьеров и их побега (второй индекс - если [0], то x; если [1], то y)
    int route_points[8][2]; //массив точек маршрута исследования леса браконьером (второй индекс - если [0], то x; если [1], то y)
    int kolvo_poacher=0; //кол-во браконьеров
public:
    Invaders();
    void Add_invader(int x, int y); //добавить чужака
    void Delete_invader(int num); //удалить чужака

    /*методы получения и установления полей*/
    int get_ox(int num); //получить поле "ox" выбранного браконьера
    int get_oy(int num); //получить поле "oy" выбранного браконьера
    int get_speed(int num); //получить поле "speed" выбранного браконьера
    int get_target_ox(int num); //получить поле "target_ox" выбранного браконьера
    int get_target_oy(int num); //получить поле "target_oy" выбранного браконьера
    int get_tired(int num); //получить поле "tired" выбранного браконьера
    int get_view_radius(int num); //получить поле "view_radius" выбранного браконьера
    int get_cutting_speed(int num); //получить поле "cutting_speed" выбранного браконьера
    int get_target_type(int num); //получить поле "target_type" выбранного браконьера

    void set_ox(int num, int inp); //установить поле "ox" выбранного браконьера
    void set_oy(int num, int inp); //установить поле "oy" выбранного браконьера
    void set_speed(int num, int inp); //установить поле "speed" выбранного браконьера
    void set_target_ox(int num, int inp); //установить поле "target_ox" выбранного браконьера
    void set_target_oy(int num, int inp); //установить поле "target_oy" выбранного браконьера
    void set_tired(int num, int inp); //установить поле "tired" выбранного браконьера
    void set_view_radius(int num, int inp); //установить поле "view_radius" выбранного браконьера
    void set_cutting_speed(int num, int inp); //установить поле "cutting_speed" выбранного браконьера
    void set_target_type(int num, int inp); //установить поле "target_type" выбранного браконьера

    void set_corners(); //установить координаты для углов
    void set_route_points(); //установить координаты для маршрута перемещения браконьеров
    int get_route_points(int num, int coord); //получить координату точки маршрута перемещения браконьеров (coord - x или y)
    int get_corner(int num, int coord); //получить значение координаты одного из углов (coord - x или y)

    void get_img(QLabel*** png, int num); //вернуть указатель на изображение выбранного браконьера
    int get_kolvo_poacher(); //получить кол-во браконьеров
};

#endif // CLASSES_H
