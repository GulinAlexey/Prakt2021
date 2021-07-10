#ifndef CLASSES_H
#define CLASSES_H

class Plant // класс Растение
{
private:
    int ox, oy; //координаты
    int height; //высота
    int radius; //радиус кроны
    int lightlove; //светолюбивость
public:
    Plant();
};

class Forest // класс Лес
{
public:
    Forest();
};

#endif // CLASSES_H
