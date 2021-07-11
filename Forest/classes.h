#ifndef CLASSES_H
#define CLASSES_H

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
public:
    Plant();
    //метод случайных начальных значений для каждого растения свой

    //дружественные функции (эти функции имеют доступ к полям Plant)
    // friend void Add_plant(int x, int y, int type);
};

class Grass : public Plant //класс Трава
{

};

class Bush : public Plant //класс Куст
{

};

class Tree : public Plant //класс Дерево
{

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
public:
    Forest();
    void Add_plant(int x, int y, int type); //добавить растение
    void Delete_plant(int num, int type); //удалить растение
};

class Weather //класс Погода
{
private:
    int sunshine; // уровень яркости солнца
    int f_rain; //флаг дождя (=1, если идёт дождь, иначе =0)
public:
    Weather();
};


#endif // CLASSES_H
