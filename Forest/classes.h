#ifndef CLASSES_H
#define CLASSES_H

#include <qlabel.h>
#include "constants.h"

class Forest; //объявление класса

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
public:
    Tree();
    void Init_rand(); //инициализация случайными значениями
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
    /*методы получения и установления полей объекта класса Dirt_cell*/
    int get_ox_min_dirt(int num); //получить поле "ox_min" выбранной ячейки почвы
    int get_oy_min_dirt(int num); //получить поле "oy_min" выбранной ячейки почвы
    int get_fertility_dirt(int num); //получить поле "fertility" выбранной ячейки почвы
    int get_effectiv_dirt(int num); //получить поле "effectiv" выбранной ячейки почвы
    int get_wet_dirt(int num); //получить поле "wet" выбранной ячейки почвы
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


#endif // CLASSES_H
