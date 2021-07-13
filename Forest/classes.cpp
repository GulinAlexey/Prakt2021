#include "classes.h"

Plant::Plant()
{}
Dirt_cell::Dirt_cell()
{}
Forest::Forest()
{}
Grass::Grass()
{}
Bush::Bush()
{}
Tree::Tree()
{}
Weather::Weather()
{}

void Grass::Init_rand() //трава, инициализация случайными значениями
{
    height=1; //начальная высота
    //radius=; //начальный радиус кроны
    //lightlove=; //светолюбивость
    //aggresiv=; //агрессивность (скорость поглощения веществ и воды из почвы)
    //wetlove=; //влаголюбивость
    score_grow=0; //начальное кол-во очков роста
    viability=1; //начальная жизнеспособность
    //max_height=; //макс. высота растения
    //max_radius=; //макс. радиус кроны
}

void Bush::Init_rand() //куст, инициализация случайными значениями
{
}

void Tree::Init_rand() //дерево, инициализация случайными значениями
{
}

void Plant::Change_OXY(int ox_new, int oy_new) //установка новых координат
{
    ox=ox_new;
    oy=oy_new;
}


/*методы получения и установления полей объекта класса Лес*/
int Forest::get_kolvo_grass()
{
    return kolvo_grass;
}
int Forest::get_kolvo_bush()
{
    return kolvo_bush;
}
int Forest::get_kolvo_tree()
{
    return kolvo_tree;
}

void Forest::Find_dirt_for_plant(int num, int type) //найти номер ячейки почвы для растения (координаты уже записаны в поля растения) (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    int x, y; //координаты растения, для которого нужно найти номер ячейки почвы
    int num_cell; //искомый номер ячейки
    if(type==1) //трава
    {
        x=grass[num].ox; //получить координаты растения, для которого нужно найти номер ячейки почвы
        y=grass[num].oy;
    }
    if(type==2) //куст
    {
        x=bush[num].ox; //получить координаты растения, для которого нужно найти номер ячейки почвы
        y=bush[num].oy;
    }
    if(type==3) //дерево
    {
        x=tree[num].ox; //получить координаты растения, для которого нужно найти номер ячейки почвы
        y=tree[num].oy;
    }
    for(int i=0; i<KOLVO_DIRT; i++) //перебрать все ячейки почвы
    {
        if(x>dirt[i].ox_min && y>dirt[i].oy_min && x<(dirt[i].ox_min+DIRT_CELL_SIZE) && y<(dirt[i].oy_min+DIRT_CELL_SIZE)) //если координаты растения принадлежат координатам ячейки
        {
            num_cell=i; //найдена искомая ячейка
            break; //остановить перебор
        }
    }
    if(type==1) //трава
    {
        grass[num].num_dirt=num_cell; //записать в поле объекта растения номер его ячейки
    }
    if(type==2) //куст
    {
        bush[num].num_dirt=num_cell; //записать в поле объекта растения номер его ячейки
    }
    if(type==3) //дерево
    {
        tree[num].num_dirt=num_cell; //записать в поле объекта растения номер его ячейки
    }
}

void Forest::Dirt_Init() //инициализация ячеек почвы
{
    int num=0; //номер ячейки почвы
    for(int i=0, cell_y=0; i<KOLVO_CELL_Y; i++) //перебор по вертикали
    {
        for(int j=0, cell_x=0; j<KOLVO_CELL_X; j++) //перебор по горизонтали
        {
            dirt[num].ox_min=cell_x; //записать значение ox верхнего левого угла ячейки
            dirt[num].oy_min=cell_y; //записать значение oy верхнего левого угла ячейки
            num++; //перейти к сл. ячейке
            cell_x+=DIRT_CELL_SIZE; //перейти к координате ox следующего верхнего левого угла

        }
        cell_y+=DIRT_CELL_SIZE; //перейти к координате oy следующего верхнего левого угла
    }
}

void Forest::Add_plant(int x, int y, int type)//добавить растение
{
    if(type==1) //трава
    {
        int kolvo = kolvo_grass; //старое кол-во растений данного типа
        Grass* plants_old = grass; //указатель на старый массив растений данного типа
        Grass* plants_change = new Grass[kolvo+1]; //указатель на новый массив растений данного типа

        int i; //счётчик перебора всех объектов массива
        for(i=0; i<kolvo; i++)
            plants_change[i]=plants_old[i]; //перенести значения в новый массив
        plants_change[i].Init_rand(); //инициализация случайных значений
        plants_change[i].Change_OXY(x, y); //установить координаты растения
        delete[] plants_old; //очистить память от старого массива

        grass = plants_change; //теперь указатель указывает на новый массив
        kolvo_grass++; //увеличить значение кол-ва объектов в массиве на 1

        Find_dirt_for_plant(kolvo_grass-1, type); //указать номер ячейки почвы для растения в его спец. поле
    }
    if(type==2) //куст
    {
        int kolvo = kolvo_bush; //старое кол-во растений данного типа
        Bush* plants_old = bush; //указатель на старый массив растений данного типа
        Bush* plants_change = new Bush[kolvo+1]; //указатель на новый массив растений данного типа

        int i; //счётчик перебора всех объектов массива
        for(i=0; i<kolvo; i++)
            plants_change[i]=plants_old[i];
        plants_change[i].Init_rand(); //инициализация случайных значений
        plants_change[i].Change_OXY(x, y); //установить координаты растения
        delete[] plants_old; //очистить память от старого массива

        bush = plants_change; //теперь указатель указывает на новый массив
        kolvo_bush++; //увеличить значение кол-ва объектов в массиве на 1

        Find_dirt_for_plant(kolvo_bush-1, type); //указать номер ячейки почвы для растения в его спец. поле
    }
    if(type==3) //дерево
    {
        int kolvo = kolvo_tree; //старое кол-во растений данного типа
        Tree* plants_old = tree; //указатель на старый массив растений данного типа
        Tree* plants_change = new Tree[kolvo+1]; //указатель на новый массив растений данного типа

        int i; //счётчик перебора всех объектов массива
        for(i=0; i<kolvo; i++)
            plants_change[i]=plants_old[i];
        plants_change[i].Init_rand(); //инициализация случайных значений
        plants_change[i].Change_OXY(x, y); //установить координаты растения
        delete[] plants_old; //очистить память от старого массива

        tree = plants_change; //теперь указатель указывает на новый массив
        kolvo_tree++; //увеличить значение кол-ва объектов в массиве на 1

        Find_dirt_for_plant(kolvo_tree-1, type); //указать номер ячейки почвы для растения в его спец. поле
    }
}
void Forest::Delete_plant(int num, int type) //удалить растение с выбранным номером и выбранного типа
{
    if(type==1) //трава
    {
        int kolvo = kolvo_grass; //старое кол-во растений данного типа
        Grass* plants_old = grass; //указатель на старый массив растений данного типа
        Grass* plants_change = new Grass[kolvo-1]; //указатель на новый массив растений данного типа

        for(int i=0, j=0; i<kolvo; i++)
        {
            if(j!=num)
            {
                plants_change[j]=plants_old[i]; //перенести значения в новый массив
                j++;
            }
        }

        delete[] plants_old; //очистить память от старого массива

        grass = plants_change; //теперь указатель указывает на новый массив
        kolvo_grass--; //уменьшить значение кол-ва объектов в массиве на 1
    }
    if(type==2) //куст
    {
        int kolvo = kolvo_bush; //старое кол-во растений данного типа
        Bush* plants_old = bush; //указатель на старый массив растений данного типа
        Bush* plants_change = new Bush[kolvo-1]; //указатель на новый массив растений данного типа

        for(int i=0, j=0; i<kolvo; i++)
        {
            if(j!=num)
            {
                plants_change[j]=plants_old[i]; //перенести значения в новый массив
                j++;
            }
        }

        delete[] plants_old; //очистить память от старого массива

        bush = plants_change; //теперь указатель указывает на новый массив
        kolvo_bush--; //уменьшить значение кол-ва объектов в массиве на 1
    }
    if(type==3) //дерево
    {
        int kolvo = kolvo_tree; //старое кол-во растений данного типа
        Tree* plants_old = tree; //указатель на старый массив растений данного типа
        Tree* plants_change = new Tree[kolvo-1]; //указатель на новый массив растений данного типа

        for(int i=0, j=0; i<kolvo; i++)
        {
            if(j!=num)
            {
                plants_change[j]=plants_old[i]; //перенести значения в новый массив
                j++;
            }
        }

        delete[] plants_old; //очистить память от старого массива

        tree = plants_change; //теперь указатель указывает на новый массив
        kolvo_tree--; //уменьшить значение кол-ва объектов в массиве на 1
    }
}

void Forest::get_img(QLabel** png, int num, int type) //получить указатель на изображение выбранного растения
{
    if(type==1)
       png=&grass[num].img;
    if(type==2)
       png=&bush[num].img;
    if(type==3)
       png=&tree[num].img;
}

/*методы получения и установления полей объекта класса Погода*/
void Weather::set_sunshine(int inp)
{
    sunshine=inp;
}
int Weather::get_sunshine()
{
    return sunshine;
}
void Weather::set_f_status(int inp)
{
    f_status=inp;
}
int Weather::get_f_status()
{
    return f_status;
}
void Weather::set_time_status(int inp)
{
    time_status=inp;
}
int Weather::get_time_status()
{
    return time_status;
}
