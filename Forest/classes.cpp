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

void Grass::Init_rand() //трава, инициализация случайными значениями
{
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


void Forest::Add_plant(int x, int y, int type)//добавить растение
{
    if(type==1) //трава
    {
        int kolvo = kolvo_grass; //старое кол-во растений данного типа
        Grass* plants_old = grass; //указатель на старый массив растений данного типа
        Grass* plants_change = new Grass[kolvo+1]; //указатель на новый массив растений данного типа

        for(int i=0; i<kolvo; i++)
            plants_change[i]=plants_old[i]; //перенести значения в новый массив
        plants_change[i].Init_rand(); //инициализация случайных значений
        plants_change[i].Change_OXY(x, y); //установить координаты растения
        delete[] plants_old; //очистить память от старого массива

        grass = plants_change; //теперь указатель указывает на новый массив
        kolvo_grass++; //увеличить значение кол-ва объектов в массиве на 1
    }
    if(type==2) //куст
    {
        int kolvo = kolvo_bush; //старое кол-во растений данного типа
        Bush* plants_old = bush; //указатель на старый массив растений данного типа
        Bush* plants_change = new Bush[kolvo+1]; //указатель на новый массив растений данного типа

        for(int i=0; i<kolvo; i++)
            plants_change[i]=plants_old[i];
        plants_change[i].Init_rand(); //инициализация случайных значений
        plants_change[i].Change_OXY(x, y); //установить координаты растения
        delete[] plants_old; //очистить память от старого массива

        bush = plants_change; //теперь указатель указывает на новый массив
        kolvo_bush++; //увеличить значение кол-ва объектов в массиве на 1
    }
    if(type==3) //дерево
    {
        int kolvo = kolvo_tree; //старое кол-во растений данного типа
        Tree* plants_old = tree; //указатель на старый массив растений данного типа
        Tree* plants_change = new Tree[kolvo+1]; //указатель на новый массив растений данного типа

        for(int i=0; i<kolvo; i++)
            plants_change[i]=plants_old[i];
        plants_change[i].Init_rand(); //инициализация случайных значений
        plants_change[i].Change_OXY(x, y); //установить координаты растения
        delete[] plants_old; //очистить память от старого массива

        tree = plants_change; //теперь указатель указывает на новый массив
        kolvo_tree++; //увеличить значение кол-ва объектов в массиве на 1
    }
}
void Forest::Delete_plant(int num, int type) //удалить растение с выбранным номером и выбранного типа
{
    if(type==1) //трава
    {
        int kolvo = kolvo_grass; //старое кол-во растений данного типа
        Grass* plants_old = grass; //указатель на старый массив растений данного типа
        Grass* plants_change = new Grass[kolvo-1]; //указатель на новый массив растений данного типа

        for(int i=0, int j=0; i<kolvo; i++)
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

        for(int i=0, int j=0; i<kolvo; i++)
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

        for(int i=0, int j=0; i<kolvo; i++)
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

Weather::Weather()
{

}
