#ifndef CONSTANTS_H
#define CONSTANTS_H

//макрос нахождения случайного числа в заданном диапазоне
#define RAND(min,max) (rand()%(max-min+1)+min)

/*ЗНАЧЕНИЯ ДЛЯ classes*/
#define KOLVO_DIRT 12 // кол-во ячеек почвы

#define DIRT_CELL_SIZE 200 //длина ребра одной ячейки почвы (квадратной)
#define KOLVO_CELL_X 4 //кол-во ячеек почвы по горизонтали
#define KOLVO_CELL_Y 3 //кол-во ячеек почвы по вертикали

#define GROW_GRASS_HEIGHT 5
#define GROW_GRASS_RADIUS 10
#define GROW_BUSH_HEIGHT 8
#define GROW_BUSH_RADIUS 8
#define GROW_TREE_HEIGHT 12
#define GROW_TREE_RADIUS 3

#define SCORE_GROW_START 0

/*ЗНАЧЕНИЯ ДЛЯ mainwidget*/
#define TIME_TICK 1000 //время интервала таймера в миллисекундах
#define SPEED_TICK 333 //время ускоренного интервала таймера в миллисекундах

#define TIME_HUMAN_TICK 500 //время интервала таймера для людей в миллисекундах

#define TIME_FOR_NEW_POACHER_MAX 14 //время появления нового браконьера в тиках таймера людей

#define PLACE_X_MIN 20 //координата оx верхнего левого угла площадки леса
#define PLACE_Y_MIN 20 //координата оy верхнего левого угла площадки леса
#define PLACE_SIZE_X 800 //размер площадки леса по горизонтали
#define PLACE_SIZE_Y 600 //размер площадки леса по вертикали

#define RADIUS_PIC_HUMAN 15 //радиус картинки человека (радиус круга или половина длины стороны квадрата)

#define SUNSHINE_NORM_FORPLANT_RANGE 25 //диапазон +- от полученного растением солнечного света, который будет комфортен данному растению относительно его норм. значения

#define HOUSE_OX 715 //координата ox центра дома лесника
#define HOUSE_OY 515 //координата oy центра дома лесника
#define RADIUS_PIC_HOUSE 60 //радиус картинки дома лесника (половина длины стороны квадрата)

#define TYPE_TREE 3 //номер типа - дерево
#define TYPE_FORESTER 4 //номер лесника при выводе картинки
#define TYPE_POACHER 5 //номер лесника при выводе картинки

#define DIST_ACTION_HUMAN (RADIUS_PIC_HUMAN+6) //дальность действия человека (при приближении к цели на это расстояние действие совершается)

#define TARGET_HOUSE 1 //номер цели человека - дом лесника
#define TARGET_POACHER 2 //номер цели человека - браконьер
#define TARGET_TREE 3 //номер цели человека - дерево
#define TARGET_CORNER_ESCAPE 4 //номер цели - угол для побега (браконьера от лесника)
#define TARGET_ROUTE 5 //номер цели - следующая точка маршрута патрулирования (исследования)

#define KOLVO_ROUTE_POINTS 8 //кол-во точек маршрута (лесника и браконьеров)

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Grass - трава*/
#define HEIGHT_START_GRASS 1

#define RADIUS_START_GRASS 20

#define MIN_LIGHTLOVE_GRASS 1
#define MAX_LIGHTLOVE_GRASS 3

#define MIN_AGGRESIV_GRASS 1
#define MAX_AGGRESIV_GRASS 10

#define MIN_WETLOVE_GRASS 10
#define MAX_WETLOVE_GRASS 90

#define MIN_END_HEIGHT_GRASS 10
#define MAX_END_HEIGHT_GRASS 40

#define SCORE_GROW_START_GRASS 0

#define SCORE_GROW_END_GRASS 4

#define VIABILITY_START_GRASS 1

#define MIN_RADIUS_GRASS 80
#define MAX_RADIUS_GRASS 500

#define FEED_NORM_GRASS 200

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Bush - куст*/
#define HEIGHT_START_BUSH 1

#define RADIUS_START_BUSH 20

#define MIN_LIGHTLOVE_BUSH 1
#define MAX_LIGHTLOVE_BUSH 3

#define MIN_AGGRESIV_BUSH 1
#define MAX_AGGRESIV_BUSH 10

#define MIN_WETLOVE_BUSH 10
#define MAX_WETLOVE_BUSH 90

#define MIN_END_HEIGHT_BUSH 50
#define MAX_END_HEIGHT_BUSH 200

#define SCORE_GROW_START_BUSH 0

#define SCORE_GROW_END_BUSH 8

#define VIABILITY_START_BUSH 1

#define MIN_RADIUS_BUSH 50
#define MAX_RADIUS_BUSH 300

#define FEED_NORM_BUSH 250

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Tree - дерево*/
#define HEIGHT_START_TREE 1

#define RADIUS_START_TREE 20

#define MIN_LIGHTLOVE_TREE 1
#define MAX_LIGHTLOVE_TREE 3

#define MIN_AGGRESIV_TREE 1
#define MAX_AGGRESIV_TREE 10

#define MIN_WETLOVE_TREE 10
#define MAX_WETLOVE_TREE 90

#define MIN_END_HEIGHT_TREE 200
#define MAX_END_HEIGHT_TREE 4000

#define SCORE_GROW_START_TREE 0

#define SCORE_GROW_END_TREE 10

#define VIABILITY_START_TREE 1

#define MIN_RADIUS_TREE 30
#define MAX_RADIUS_TREE 200

#define FEED_NORM_TREE 350

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Dirt_cell - ячейка почвы*/
#define MIN_FERTILITY 5
#define MAX_FERTILITY 30

#define EFFECTIV_START_DIRT 1

#define MIN_WET_START_DIRT 0
#define MAX_WET_START_DIRT 5

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Weather - погода*/
#define MIN_SUNSHINE_START 30
#define MAX_SUNSHINE_START 50

#define MIN_SUNSHINE 20
#define MAX_SUNSHINE 70

#define SUNSHINE_SUN 50
#define SUNSHINE_SUN_RANGE 25

#define SUNSHINE_CLOUD 20
#define SUNSHINE_CLOUD_RANGE 15

#define SUNSHINE_RAIN 10
#define SUNSHINE_RAIN_RANGE 5

#define F_STATUS_START 0

#define F_SUN 0
#define F_CLOUD 1
#define F_RAIN 2

#define RAINFALL_TICK_SUN 0
#define RAINFALL_TICK_CLOUD 5
#define RAINFALL_TICK_RAIN 60
#define RAINFALL_TICK_RAIN_RANGE 15

#define MIN_RAINFALL_TICK 10
#define MAX_RAINFALL_TICK 100

#define TIME_STATUS_START 0
#define TIME_STATUS_END 10

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Human - человек*/
#define TIRED_HUMAN_START 0

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Forester - лесник*/
#define SPEED_FORESTER 40
#define VIEW_RADIUS_FORESTER 120


/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Poacher - браконьер*/
#define MIN_SPEED_POACHER 30
#define MAX_SPEED_POACHER 50
#define MIN_VIEW_RADIUS_POACHER 80
#define MAX_VIEW_RADIUS_POACHER 130
#define MIN_CUTTING_SPEED_POACHER 5
#define MAX_CUTTING_SPEED_POACHER 15

#define MAX_CUTTING 50

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Invaders - чужаки*/
#define X_CORNER 0 // обозначение для координаты ox в массиве corner[][_] (одна из координат данного угла)
#define Y_CORNER 1 // обозначение для координаты oy в массиве corner[][_] (одна из координат данного угла)

#endif // CONSTANTS_H
