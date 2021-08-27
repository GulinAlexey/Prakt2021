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
Human::Human()
{}
Poacher::Poacher()
{}
Forester::Forester()
{}
Invaders::Invaders()
{}

void Grass::Init_rand() //трава, инициализация случайными значениями
{
    height=HEIGHT_START_GRASS; //начальная высота
    radius=RADIUS_START_GRASS; //начальный радиус кроны
    lightlove=RAND(MIN_LIGHTLOVE_GRASS, MAX_LIGHTLOVE_GRASS); //светолюбивость
    aggresiv=RAND(MIN_AGGRESIV_GRASS, MAX_AGGRESIV_GRASS); //агрессивность (скорость поглощения веществ и воды из почвы)
    wetlove=RAND(MIN_WETLOVE_GRASS, MAX_WETLOVE_GRASS); //влаголюбивость
    score_grow=SCORE_GROW_START_GRASS; //начальное кол-во очков роста
    score_grow_max=SCORE_GROW_END_GRASS; //конечное кол-во очков роста, требуемое для роста растения (затем очки обнуляются и процесс идёт заново)
    viability=VIABILITY_START_GRASS; //начальная жизнеспособность
    end_height=RAND(MIN_END_HEIGHT_GRASS, MAX_END_HEIGHT_GRASS); //конечная (макс.) высота растения
    max_radius=RAND(MIN_RADIUS_GRASS, MAX_RADIUS_GRASS); //макс. радиус кроны
    feed_norm=FEED_NORM_GRASS; //нормальное разовое питание
}

void Bush::Init_rand() //куст, инициализация случайными значениями
{
    height=HEIGHT_START_BUSH; //начальная высота
    radius=RADIUS_START_BUSH; //начальный радиус кроны
    lightlove=RAND(MIN_LIGHTLOVE_BUSH, MAX_LIGHTLOVE_BUSH); //светолюбивость
    aggresiv=RAND(MIN_AGGRESIV_BUSH, MAX_AGGRESIV_BUSH); //агрессивность (скорость поглощения веществ и воды из почвы)
    wetlove=RAND(MIN_WETLOVE_BUSH, MAX_WETLOVE_BUSH); //влаголюбивость
    score_grow=SCORE_GROW_START_BUSH; //начальное кол-во очков роста
    score_grow_max=SCORE_GROW_END_BUSH; //конечное кол-во очков роста, требуемое для роста растения (затем очки обнуляются и процесс идёт заново)
    viability=VIABILITY_START_BUSH; //начальная жизнеспособность
    end_height=RAND(MIN_END_HEIGHT_BUSH, MAX_END_HEIGHT_BUSH); //конечная (макс.) высота растения
    max_radius=RAND(MIN_RADIUS_BUSH, MAX_RADIUS_BUSH); //макс. радиус кроны
    feed_norm=FEED_NORM_BUSH; //нормальное разовое питание
}

void Tree::Init_rand() //дерево, инициализация случайными значениями
{
    height=HEIGHT_START_TREE; //начальная высота
    radius=RADIUS_START_TREE; //начальный радиус кроны
    lightlove=RAND(MIN_LIGHTLOVE_TREE, MAX_LIGHTLOVE_TREE); //светолюбивость
    aggresiv=RAND(MIN_AGGRESIV_TREE, MAX_AGGRESIV_TREE); //агрессивность (скорость поглощения веществ и воды из почвы)
    wetlove=RAND(MIN_WETLOVE_TREE, MAX_WETLOVE_TREE); //влаголюбивость
    score_grow=SCORE_GROW_START_TREE; //начальное кол-во очков роста
    score_grow_max=SCORE_GROW_END_TREE; //конечное кол-во очков роста, требуемое для роста растения (затем очки обнуляются и процесс идёт заново)
    viability=VIABILITY_START_TREE; //начальная жизнеспособность
    end_height=RAND(MIN_END_HEIGHT_TREE, MAX_END_HEIGHT_TREE); //конечная (макс.) высота растения
    max_radius=RAND(MIN_RADIUS_TREE, MAX_RADIUS_TREE); //макс. радиус кроны
    feed_norm=FEED_NORM_TREE; //нормальное разовое питание
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
int Forest::get_kolvo_dirt()
{
    return kolvo_dirt;
}

int Forest::get_kolvo_type(int type) //вернуть кол-во объектов выбранного типа (0 - ячейка почвы, 1 - трава, 2 - куст, 3 - дерево)
{
    switch(type)
    {
    case 0: //земля
        return kolvo_dirt;
        break;
    case 1: //трава
        return kolvo_grass;
        break;
    case 2: //куст
        return kolvo_bush;
        break;
    case 3: //дерево
        return kolvo_tree;
        break;
    default:
        return 0;
        break;
    }

}


int Forest::get_ox_min_dirt(int num) //получить поле "ox_min" выбранной ячейки почвы
{
    return dirt[num].ox_min; //получить искомое значение поля
}
int Forest::get_oy_min_dirt(int num) //получить поле "oy_min" выбранной ячейки почвы
{
    return dirt[num].oy_min; //получить искомое значение поля
}

int Forest::get_fertility_dirt(int num) //получить поле "fertility" выбранной ячейки почвы
{
    return dirt[num].fertility; //получить искомое значение поля
}

int Forest::get_fertility_now_dirt(int num) //получить поле "fertility_now" выбранной ячейки почвы
{
    return dirt[num].fertility_now; //получить искомое значение поля
}
int Forest::get_effectiv_dirt(int num) //получить поле "effectiv" выбранной ячейки почвы
{
    return dirt[num].effectiv; //получить искомое значение поля
}
int Forest::get_wet_dirt(int num) //получить поле "wet" выбранной ячейки почвы
{
    return dirt[num].wet; //получить искомое значение поля
}

void Forest::set_wet_dirt(int num, int inp) //установить значение поля "wet" выбранной ячейки почвы
{
    dirt[num].wet=inp;
}

void Forest::set_fertility_dirt(int num, int inp) //установить значение поля "fertility" выбранной ячейки почвы
{
    dirt[num].fertility=inp;
}
void Forest::set_fertility_now_dirt(int num, int inp) //установить значение поля "fertility_now" выбранной ячейки почвы
{
    dirt[num].fertility_now=inp;
}
int Forest::get_x_plant(int num, int type) //получить поле "x" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].ox; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].ox; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].ox; //получить искомое значение поля
    }
}
int Forest::get_y_plant(int num, int type) //получить поле "y" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].oy; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].oy; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].oy; //получить искомое значение поля
    }
}
int Forest::get_radius_plant(int num, int type) //получить поле "radius" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].radius; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].radius; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].radius; //получить искомое значение поля
    }
}

int Forest::get_height_plant(int num, int type) //получить поле "height" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].height; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].height; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].height; //получить искомое значение поля
    }
}

int Forest::get_num_dirt_plant(int num, int type) //получить поле "num_dirt" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].num_dirt; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].num_dirt; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].num_dirt; //получить искомое значение поля
    }
}
int Forest::get_lightlove_plant(int num, int type) //получить поле "lightlove" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].lightlove; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].lightlove; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].lightlove; //получить искомое значение поля
    }
}
int Forest::get_aggresiv_plant(int num, int type) //получить поле "aggresiv" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].aggresiv; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].aggresiv; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].aggresiv; //получить искомое значение поля
    }
}
int Forest::get_wetlove_plant(int num, int type) //получить поле "wetlove" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].wetlove; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].wetlove; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].wetlove; //получить искомое значение поля
    }
}
int Forest::get_score_grow_plant(int num, int type) //получить поле "score_grow" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].score_grow; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].score_grow; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].score_grow; //получить искомое значение поля
    }
}
int Forest::get_score_grow_max_plant(int num, int type) //получить поле "score_grow_max" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].score_grow_max; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].score_grow_max; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].score_grow_max; //получить искомое значение поля
    }
}
double Forest::get_viability_plant(int num, int type) //получить поле "viability" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].viability; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].viability; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].viability; //получить искомое значение поля
    }
}
int Forest::get_end_height_plant(int num, int type) //получить поле "end_height" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].end_height; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].end_height; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].end_height; //получить искомое значение поля
    }
}
int Forest::get_max_radius_plant(int num, int type) //получить поле "max_radius" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].max_radius; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].max_radius; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].max_radius; //получить искомое значение поля
    }
}

int Forest::get_feed_norm_plant(int num, int type) //получить поле "feed_norm" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        return grass[num].feed_norm; //получить искомое значение поля
    }
    if(type==2) //куст
    {
        return bush[num].feed_norm; //получить искомое значение поля
    }
    if(type==3) //дерево
    {
       return tree[num].feed_norm; //получить искомое значение поля
    }
}

int Forest::get_cutting_degree_tree(int num) //получить поле "cutting_degree" дерева
{
    return tree[num].cutting_degree; //получить искомое значение поля
}

void Forest::set_score_grow_plant(int num, int type, int inp) //установить значение поля "score_grow" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        grass[num].score_grow=inp;
    }
    if(type==2) //куст
    {
        bush[num].score_grow=inp;
    }
    if(type==3) //дерево
    {
       tree[num].score_grow=inp;
    }
}
void Forest::set_height_plant(int num, int type, int inp) //получить поле "height" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        grass[num].height=inp;
    }
    if(type==2) //куст
    {
        bush[num].height=inp;
    }
    if(type==3) //дерево
    {
       tree[num].height=inp;
    }
}
void Forest::set_radius_plant(int num, int type, int inp) //получить поле "radius" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        grass[num].radius=inp;
    }
    if(type==2) //куст
    {
        bush[num].radius=inp;
    }
    if(type==3) //дерево
    {
       tree[num].radius=inp;
    }
}
void Forest::set_viability_plant(int num, int type, double inp) //получить поле "viability" растения (тип: 1 - трава, 2 - куст, 3 - дерево)
{
    if(type==1) //трава
    {
        grass[num].viability=inp;
    }
    if(type==2) //куст
    {
        bush[num].viability=inp;
    }
    if(type==3) //дерево
    {
       tree[num].viability=inp;
    }
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

int Forest::Belonging_of_coordinat(int num, int type, int x_search, int y_search) //проверка, что координаты x и y принадлежат окружности растения (возвращает 1, если верно и 0, если неверно)
{
    if(type==1) //трава
    {
        int x_plant=grass[num].ox; //ox центра растения
        int y_plant=grass[num].oy; //oy центра растения
        int radius_plant=grass[num].radius; //радиус растения
        if((pow(x_search-x_plant, 2) + pow(y_search-y_plant, 2))<=(radius_plant*radius_plant)) //проверка, принадлежат ли проверемые координаты окружности растения
            return 1; //если верно
        else
            return 0; //если неверно
    }
    if(type==2) //куст
    {
        int x_plant=bush[num].ox; //ox центра растения
        int y_plant=bush[num].oy; //oy центра растения
        int radius_plant=bush[num].radius; //радиус растения
        if((pow(x_search-x_plant, 2) + pow(y_search-y_plant, 2))<=(radius_plant*radius_plant)) //проверка, принадлежат ли проверемые координаты окружности растения
            return 1; //если верно
        else
            return 0; //если неверно
    }
    if(type==3) //дерево
    {
        int x_plant=tree[num].ox; //ox центра растения
        int y_plant=tree[num].oy; //oy центра растения
        int radius_plant=tree[num].radius; //радиус растения
        if((pow(x_search-x_plant, 2) + pow(y_search-y_plant, 2))<=(radius_plant*radius_plant)) //проверка, принадлежат ли проверемые координаты окружности растения
            return 1; //если верно
        else
            return 0; //если неверно
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
    for(int i=0; i<KOLVO_DIRT; i++) //перебрать все ячейки
    {
        dirt[i].fertility=RAND(MIN_FERTILITY, MAX_FERTILITY); // плодородность ячейки почвы
        dirt[i].fertility_now=dirt[i].fertility; //плодородность ячейки почвы для текущего растения в цикле поглощений
        dirt[i].effectiv=EFFECTIV_START_DIRT; // эффективность плодородности
        dirt[i].wet=RAND(MIN_WET_START_DIRT, MAX_WET_START_DIRT); //влажность
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
            if(i!=num)
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
            if(i!=num)
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
            if(i!=num)
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

void Forest::get_img(QLabel*** png, int num, int type) //получить указатель на изображение выбранного растения
{
    if(type==1)
       (*png)=&grass[num].img;
    if(type==2)
       (*png)=&bush[num].img;
    if(type==3)
       (*png)=&tree[num].img;
}

void Weather::Weather_Init() //инициализация погоды
{
    sunshine=SUNSHINE_SUN;
    f_status=F_STATUS_START;
    rainfall_tick=RAINFALL_TICK_SUN;
    time_status=TIME_STATUS_START;
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
void Weather::set_rainfall_tick(int inp)
{
    rainfall_tick=inp;
}
int Weather::get_rainfall_tick()
{
    return rainfall_tick;
}
void Weather::set_time_status(int inp)
{
    time_status=inp;
}
int Weather::get_time_status()
{
    return time_status;
}

void Forester::Init() //инициализация
{
    ox=HOUSE_OX;
    oy=HOUSE_OY;
    speed=SPEED_FORESTER;
    tired=TIRED_HUMAN_START;
    view_radius=VIEW_RADIUS_FORESTER;
}

void Poacher::Init() //инициализация
{
    speed=RAND(MIN_SPEED_POACHER, MAX_SPEED_POACHER);
    tired=TIRED_HUMAN_START;
    view_radius=RAND(MIN_VIEW_RADIUS_POACHER, MAX_VIEW_RADIUS_POACHER);
    cutting_speed=RAND(MIN_CUTTING_SPEED_POACHER, MAX_CUTTING_SPEED_POACHER);
}

void Forester::get_img(QLabel*** png) //вернуть указатель на изображение лесника
{
    (*png)=&img;
}

int Forester::get_ox() //получить поле "ox"
{
    return ox;
}
int Forester::get_oy() //получить поле "oy"
{
    return oy;
}

int Forester::get_speed() //получить поле "speed"
{
    return speed;
}
int Forester::get_target_ox() //получить поле "target_ox"
{
    return target_ox;
}
int Forester::get_target_oy() //получить поле "target_oy"
{
    return target_oy;
}
int Forester::get_tired() //получить поле "tired"
{
    return tired;
}
int Forester::get_view_radius() //получить поле "view_radius"
{
    return view_radius;
}

int Forester::get_target_type() //получить поле "target_type"
{
    return target_type;
}

void Forester::set_ox(int inp) //установить поле "ox"
{
    ox=inp;
}
void Forester::set_oy(int inp) //установить поле "oy"
{
    oy=inp;
}
void Forester::set_speed(int inp) //установить поле "speed"
{
    speed=inp;
}
void Forester::set_target_ox(int inp) //установить поле "target_ox"
{
    target_ox=inp;
}
void Forester::set_target_oy(int inp) //установить поле "target_oy"
{
    target_oy=inp;
}
void Forester::set_tired(int inp) //установить поле "tired"
{
    tired=inp;
}

void Forester::set_target_type(int inp) //установить поле "target_type"
{
    target_type=inp;
}

int Invaders::get_ox(int num) //получить поле "ox" выбранного браконьера
{
    return poachers[num].ox;
}
int Invaders::get_oy(int num) //получить поле "oy" выбранного браконьера
{
    return poachers[num].oy;
}

int Invaders::get_speed(int num) //получить поле "speed" выбранного браконьера
{
    return poachers[num].speed;
}
int Invaders::get_target_ox(int num) //получить поле "target_ox" выбранного браконьера
{
    return poachers[num].target_ox;
}
int Invaders::get_target_oy(int num) //получить поле "target_oy" выбранного браконьера
{
    return poachers[num].target_oy;
}
int Invaders::get_tired(int num) //получить поле "tired" выбранного браконьера
{
    return poachers[num].tired;
}
int Invaders::get_view_radius(int num) //получить поле "view_radius" выбранного браконьера
{
    return poachers[num].view_radius;
}
int Invaders::get_cutting_speed(int num) //получить поле "cutting_speed" выбранного браконьера
{
    return poachers[num].cutting_speed;
}

int Invaders::get_target_type(int num) //получить поле "target_type" выбранного браконьера
{
    return poachers[num].target_type;
}

void Invaders::set_ox(int num, int inp) //установить поле "ox" выбранного браконьера
{
    poachers[num].ox=inp;
}
void Invaders::set_oy(int num, int inp) //установить поле "oy" выбранного браконьера
{
    poachers[num].oy=inp;
}
void Invaders::set_speed(int num, int inp) //установить поле "speed" выбранного браконьера
{
    poachers[num].speed=inp;
}
void Invaders::set_target_ox(int num, int inp) //установить поле "target_ox" выбранного браконьера
{
    poachers[num].target_ox=inp;
}
void Invaders::set_target_oy(int num, int inp) //установить поле "target_oy" выбранного браконьера
{
    poachers[num].target_oy=inp;
}
void Invaders::set_tired(int num, int inp) //установить поле "tired" выбранного браконьера
{
    poachers[num].tired=inp;
}
void Invaders::set_view_radius(int num, int inp) //установить поле "view_radius" выбранного браконьера
{
    poachers[num].view_radius=inp;
}
void Invaders::set_cutting_speed(int num, int inp) //установить поле "cutting_speed" выбранного браконьера
{
    poachers[num].cutting_speed=inp;
}
void Invaders::set_target_type(int num, int inp) //установить поле "target_type" выбранного браконьера
{
    poachers[num].target_type=inp;
}

void Invaders::get_img(QLabel*** png, int num) //вернуть указатель на изображение выбранного браконьера
{
    (*png)=&poachers[num].img;
}

int Invaders::get_kolvo_poacher() //получить кол-во браконьеров
{
    return kolvo_poacher;
}

void Invaders::Add_invader(int x, int y) //добавить чужака
{
    int kolvo = kolvo_poacher; //старое кол-во браконьеров
    Poacher* poachers_old = poachers; //указатель на старый массив браконьеров
    Poacher* poachers_change = new Poacher[kolvo+1]; //указатель на новый массив браконьеров

    int i; //счётчик перебора всех объектов массива
    for(i=0; i<kolvo; i++)
        poachers_change[i]=poachers_old[i]; //перенести значения в новый массив
    poachers_change[i].Init(); //инициализация
    poachers_change[i].ox = x; //установить координату x
    poachers_change[i].oy = y; //установить координату y
    delete[] poachers_old; //очистить память от старого массива

    poachers = poachers_change; //теперь указатель указывает на новый массив
    kolvo_poacher++; //увеличить значение кол-ва объектов в массиве на 1
}

void Invaders::Delete_invader(int num) //удалить чужака
{
    int kolvo = kolvo_poacher; //старое кол-во браконьеров
    Poacher* poachers_old = poachers; //указатель на старый массив браконьеров
    Poacher* poachers_change = new Poacher[kolvo+1]; //указатель на новый массив браконьеров

    for(int i=0, j=0; i<kolvo; i++)
    {
        if(i!=num)
        {
            poachers_change[j]=poachers_old[i]; //перенести значения в новый массив
            j++;
        }
    }

    delete[] poachers_old; //очистить память от старого массива

    poachers = poachers_change; //теперь указатель указывает на новый массив
    kolvo_poacher--; //уменьшить значение кол-ва объектов в массиве на 1
}

void Invaders::set_corners() //установить координаты для углов появления браконьеров
{
    corners[0][X_CORNER]=0;
    corners[0][Y_CORNER]=0;

    corners[1][X_CORNER]=PLACE_SIZE_X;
    corners[1][Y_CORNER]=0;

    corners[2][X_CORNER]=0;
    corners[2][Y_CORNER]=PLACE_SIZE_Y;

}

int Invaders::get_corner(int num, int coord) //получить значение координаты одного из углов
{
    return corners[num][coord];
}

void Forester::set_route_points() //установить координаты для маршрута патрулирования лесника
{
    route_points[0][X_CORNER]=700;
    route_points[0][Y_CORNER]=500;

    route_points[1][X_CORNER]=700;
    route_points[1][Y_CORNER]=100;

    route_points[2][X_CORNER]=500;
    route_points[2][Y_CORNER]=100;

    route_points[3][X_CORNER]=500;
    route_points[3][Y_CORNER]=500;

    route_points[4][X_CORNER]=300;
    route_points[4][Y_CORNER]=500;

    route_points[5][X_CORNER]=300;
    route_points[5][Y_CORNER]=100;

    route_points[6][X_CORNER]=100;
    route_points[6][Y_CORNER]=100;

    route_points[7][X_CORNER]=100;
    route_points[7][Y_CORNER]=500;
}

void Invaders::set_route_points() //установить координаты для маршрута перемещения браконьеров
{
    route_points[0][X_CORNER]=100;
    route_points[0][Y_CORNER]=100;

    route_points[1][X_CORNER]=100;
    route_points[1][Y_CORNER]=500;

    route_points[2][X_CORNER]=300;
    route_points[2][Y_CORNER]=500;

    route_points[3][X_CORNER]=300;
    route_points[3][Y_CORNER]=100;

    route_points[4][X_CORNER]=500;
    route_points[4][Y_CORNER]=100;

    route_points[5][X_CORNER]=500;
    route_points[5][Y_CORNER]=500;

    route_points[6][X_CORNER]=700;
    route_points[6][Y_CORNER]=350;

    route_points[7][X_CORNER]=700;
    route_points[7][Y_CORNER]=100;
}

int Forester::get_route_points(int num, int coord) //получить координаты точки маршрута лесника (coord - x или y)
{
    return route_points[num][coord];
}

int Invaders::get_route_points(int num, int coord) //получить координату точки маршрута перемещения браконьеров (coord - x или y)
{
    return route_points[num][coord];
}
