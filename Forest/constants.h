#ifndef CONSTANTS_H
#define CONSTANTS_H

//макрос нахождения случайного числа в заданном диапазоне
#define RAND(min,max) (rand()%(max-min+1)+min)

/*ЗНАЧЕНИЯ ДЛЯ classes*/
#define KOLVO_DIRT 12 // кол-во ячеек почвы

#define DIRT_CELL_SIZE 200 //длина ребра одной ячейки почвы (квадратной)
#define KOLVO_CELL_X 4 //кол-во ячеек почвы по горизонтали
#define KOLVO_CELL_Y 3 //кол-во ячеек почвы по вертикали

#define GROW_GRASS_HEIGHT 1 //кол-во единиц, на которые вырастает трава за раз по высоте
#define GROW_GRASS_RADIUS 5 //кол-во единиц, на которые вырастает трава за раз в радиусе

#define GROW_BUSH_HEIGHT 4 //кол-во единиц, на которые вырастает куст за раз по высоте
#define GROW_BUSH_RADIUS 3 //кол-во единиц, на которые вырастает куст за раз в радиусе

#define GROW_TREE_HEIGHT 14 //кол-во единиц, на которые вырастает дерево за раз по высоте
#define GROW_TREE_RADIUS 3 //кол-во единиц, на которые вырастает дерево за раз в радиусе

#define SCORE_GROW_START 0 //начальное кол-во очков роста

/*ЗНАЧЕНИЯ ДЛЯ mainwidget*/
#define TIME_TICK 1000 //время интервала таймера в миллисекундах
#define SPEED_TICK 100 //время ускоренного интервала таймера в миллисекундах

#define TIME_HUMAN_TICK 500 //время интервала таймера для людей в миллисекундах

#define TIME_FOR_NEW_POACHER_MAX 20 //время появления нового браконьера в тиках таймера людей

#define PLACE_X_MIN 20 //координата оx верхнего левого угла площадки леса
#define PLACE_Y_MIN 20 //координата оy верхнего левого угла площадки леса
#define PLACE_SIZE_X 800 //размер площадки леса по горизонтали
#define PLACE_SIZE_Y 600 //размер площадки леса по вертикали

#define RADIUS_PIC_HUMAN 20 //радиус картинки человека (радиус круга или половина длины стороны квадрата)

#define HOUSE_OX 715 //координата ox центра дома лесника
#define HOUSE_OY 515 //координата oy центра дома лесника
#define RADIUS_PIC_HOUSE 60 //радиус картинки дома лесника (половина длины стороны квадрата)

#define TYPE_TREE 3 //номер типа - дерево
#define TYPE_FORESTER 4 //номер лесника при выводе картинки
#define TYPE_POACHER 5 //номер лесника при выводе картинки

#define DIST_ACTION_FORESTER (RADIUS_PIC_HUMAN+RADIUS_PIC_HUMAN)  //дальность, с которой лесник может поймать браконьера
#define DIST_ACTION_POACHER (RADIUS_PIC_HUMAN+(RADIUS_START_TREE/2)) //дальность, с которой браконьер может рубить дерево

#define TARGET_HOUSE 1 //номер цели человека - дом лесника
#define TARGET_POACHER 2 //номер цели человека - браконьер
#define TARGET_TREE 3 //номер цели человека - дерево
#define TARGET_CORNER_ESCAPE 4 //номер цели - угол для побега (браконьера от лесника)
#define TARGET_ROUTE 5 //номер цели - следующая точка маршрута патрулирования (исследования)

#define TARGET_FIND_FORESTER 1 //тип, передаваемый функции Find_target() при поиске цели леснику
#define TARGET_FIND_POACHER 2 //тип, передаваемый функции Find_target() при поиске цели браконьеру

#define KOLVO_ROUTE_POINTS 8 //кол-во точек маршрута (лесника и браконьеров)

#define F_PLUS 0 //значение для флага при вычислении разницы между координатами
#define F_MINUS 1 //значение для флага при вычислении разницы между координатами

#define TYPE_LOVE_BRIGHT 1 //тип светолюбивости - яркое солнце
#define TYPE_LOVE_SHADOW 2 //тип светолюбивости - полутень

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Grass - трава*/
#define HEIGHT_START_GRASS 1

#define MIN_END_HEIGHT_GRASS 10
#define MAX_END_HEIGHT_GRASS 15

#define RADIUS_START_GRASS 22

#define MIN_RADIUS_GRASS 100
#define MAX_RADIUS_GRASS 180

#define MIN_LIGHTLOVE_GRASS 1
#define MAX_LIGHTLOVE_GRASS 2

#define MIN_AGGRESIV_GRASS 10
#define MAX_AGGRESIV_GRASS 40

#define MIN_WETLOVE_GRASS 30
#define MAX_WETLOVE_GRASS 50

#define FEED_NORM_GRASS_MIN 40
#define FEED_NORM_GRASS_MAX 100

#define SCORE_GROW_START_GRASS 0
#define SCORE_GROW_END_GRASS 12

#define VIABILITY_START_GRASS 1

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Bush - куст*/
#define HEIGHT_START_BUSH 16

#define MIN_END_HEIGHT_BUSH 100
#define MAX_END_HEIGHT_BUSH 150

#define RADIUS_START_BUSH 20

#define MIN_RADIUS_BUSH 40
#define MAX_RADIUS_BUSH 55

#define MIN_LIGHTLOVE_BUSH 1
#define MAX_LIGHTLOVE_BUSH 2

#define MIN_AGGRESIV_BUSH 20
#define MAX_AGGRESIV_BUSH 50

#define MIN_WETLOVE_BUSH 50
#define MAX_WETLOVE_BUSH 100

#define FEED_NORM_BUSH_MIN 80
#define FEED_NORM_BUSH_MAX 250

#define SCORE_GROW_START_BUSH 0
#define SCORE_GROW_END_BUSH 12

#define VIABILITY_START_BUSH 1

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Tree - дерево*/
#define HEIGHT_START_TREE 17

#define MIN_END_HEIGHT_TREE 400
#define MAX_END_HEIGHT_TREE 600

#define RADIUS_START_TREE 20

#define MIN_RADIUS_TREE 50
#define MAX_RADIUS_TREE 75

#define MIN_LIGHTLOVE_TREE 1
#define MAX_LIGHTLOVE_TREE 2

#define MIN_AGGRESIV_TREE 40
#define MAX_AGGRESIV_TREE 90

#define MIN_WETLOVE_TREE 75
#define MAX_WETLOVE_TREE 350

#define FEED_NORM_TREE_MIN 300
#define FEED_NORM_TREE_MAX 470

#define SCORE_GROW_START_TREE 0
#define SCORE_GROW_END_TREE 15

#define VIABILITY_START_TREE 1

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Dirt_cell - ячейка почвы*/
#define MIN_FERTILITY 300
#define MAX_FERTILITY 400

#define ADD_FERT_IF_DIED_PLANT 10 //кол-во очков питания, которые добавляются ячейке почвы, на которой зачахло растение (оно стало удобрением)

#define MIN_WET_START_DIRT 30 //мин. начальная влажность почвы
#define MAX_WET_START_DIRT 50 //макс. начальная влажность почвы

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Weather - погода*/
#define SUNSHINE_SUN 70 //кол-во света за 1 тик в солнечную погоду
#define SUNSHINE_SUN_RANGE 25 //диапазон возможных значений (верхнее число в define является серединой)

#define SUNSHINE_CLOUD 30 //кол-во света за 1 тик в облачную погоду
#define SUNSHINE_CLOUD_RANGE 15 //диапазон возможных значений (верхнее число в define является серединой)

#define SUNSHINE_RAIN 10 //кол-во света за 1 тик в дождь
#define SUNSHINE_RAIN_RANGE 5 //диапазон возможных значений (верхнее число в define является серединой)

#define F_STATUS_START 0 //начальное значение флага погоды

#define F_SUN 0 //флаг типа погоды - солнечная
#define F_CLOUD 1 //флаг типа погоды - облачная
#define F_RAIN 2 //флаг типа погоды - дождливая

#define RAINFALL_TICK_SUN 0 //кол-во осадков за 1 тик в солнечную погоду

#define RAINFALL_TICK_CLOUD 6 //кол-во осадков за 1 тик в облачную погоду
#define RAINFALL_TICK_CLOUD_RANGE 3 //диапазон возможных значений (верхнее число в define является серединой)

#define RAINFALL_TICK_RAIN 60 //кол-во осадков за 1 тик в дождь
#define RAINFALL_TICK_RAIN_RANGE 15 //диапазон возможных значений (верхнее число в define является серединой)

#define DRY_TICK_SUN_MIN 20 //кол-во испаряемой влаги с почвы за 1 тик
#define DRY_TICK_SUN_MAX 150 //кол-во испаряемой влаги с почвы за 1 тик

#define TIME_STATUS_START 0 //начальное время текущего типа погоды
#define TIME_STATUS_END 10 //конечное время текущего типа погоды


/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Forester - лесник*/
#define SPEED_FORESTER 55
#define VIEW_RADIUS_FORESTER 400

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Poacher - браконьер*/
#define MIN_SPEED_POACHER 15
#define MAX_SPEED_POACHER 44
#define MIN_VIEW_RADIUS_POACHER 150
#define MAX_VIEW_RADIUS_POACHER 300
#define MIN_CUTTING_SPEED_POACHER 1
#define MAX_CUTTING_SPEED_POACHER 2

#define MAX_CUTTING 45 //макс. степень срубленности дерева (после неё растение срублено)
#define MAX_KOLVO_POACHER 2 //макс. кол-во браконьеров

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Invaders - чужаки*/
#define X_CORNER 0 // обозначение для координаты ox в массиве corner[][_] (одна из координат данного угла)
#define Y_CORNER 1 // обозначение для координаты oy в массиве corner[][_] (одна из координат данного угла)

#endif // CONSTANTS_H
