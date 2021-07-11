#ifndef CLASSES_H
#define CLASSES_H

#include <qlabel.h>

#define KOLVO_DIRT 12 // кол-во ячеек почвы

class Plant // класс Растение
{
protected:
    int ox, oy; //координаты
    int num_dirt; //номер ячейки почвы, на которой находится
    int height; //высота
    int radius; //радиус кроны
    int lightlove; //светолюбивость
    int aggresiv; //агрессивность (скорость поглощения веществ и воды из почвы)
    int wetlove; //влаголюбивость
    int score_grow; //текущее кол-во очков роста (при достижении максимума увеличивается высота и радиус, а данный показатель вновь обнуляется)
    int viability; //жизнеспособность (при уменьшении до нулевого значения растение умирает)
    QLabel *img; //указатель на label с изображением растения
public:
    Plant();
    void Change_OXY(int ox_new, int oy_new); //установка новых координат

    //дружественные функции (эти функции имеют доступ к полям Plant)
    // friend void Add_plant(int x, int y, int type);
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
    int ox_max, oy_max; //координаты нижнего правого угла ячейки
    int fertility; // плодородность почвы
    int effectiv; // эффективность плодородности (изначально 1, при истощении/насыщении изменяется)
    int wet; //влажность
public:
    Dirt_cell();
};

class Forest // класс Лес
{
private:
    Dirt_cell dirt[KOLVO_DIRT]; //массив с ячейками почвы
    Grass* grass; //указатель на массив объектов Трава
    Bush* bush; //указатель на массив объектов Куст
    Tree* tree; //указатель на массив объектов Дерево

    int kolvo_dirt = KOLVO_DIRT; //кол-во ячеек почвы
    int kolvo_grass; //кол-во объектов травы
    int kolvo_bush; //кол-во кустов
    int kolvo_tree;  //кол-во деревьев

public:
    Forest();
    void Add_plant(int x, int y, int type); //добавить растение (тип: 1 - трава, 2 - куст, 3 - дерево)
    void Delete_plant(int num, int type); //удалить растение (тип: 1 - трава, 2 - куст, 3 - дерево)
};

class Weather //класс Погода
{
private:
    int sunshine; // уровень яркости солнца
    int f_status; //флаг текущей погоды (0 - солнечно, 1 - облачно, 2 - дождь)
    int time_status; // время текущего состояния (при достижении 10 тиков обнуляется. Затем дождь/солнечность/облачность заканчивается или начинается (с некоторой вероятностью начала определённой погоды))
public:
    Weather();
};


#endif // CLASSES_H
