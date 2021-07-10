#ifndef CLASSES_H
#define CLASSES_H

class Plant // класс Растение
{
private:
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

class Forest // класс Лес
{
public:
    Forest();
    void Add_plant(int x, int y, int type); //добавить растение
    void Delete_plant(int num, int type); //удалить растение
};

#endif // CLASSES_H
