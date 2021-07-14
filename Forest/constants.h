#ifndef CONSTANTS_H
#define CONSTANTS_H

//макрос нахождения случайного числа в заданном диапазоне
#define RAND(min,max) rand()%(max-min+1)+min

/*ЗНАЧЕНИЯ ДЛЯ classes*/
#define KOLVO_DIRT 12 // кол-во ячеек почвы
#define DIRT_CELL_SIZE 200 //длина ребра одной ячейки почвы (квадратной)
#define KOLVO_CELL_X 4 //кол-во ячеек почвы по горизонтали
#define KOLVO_CELL_Y 3 //кол-во ячеек почвы по вертикали

/*ЗНАЧЕНИЯ ДЛЯ mainwidget*/
#define TIME_TICK 1000 //время интервала таймера в миллисекундах
#define SPEED_TICK 333 //время ускоренного интервала таймера в миллисекундах

#define PLACE_X_MIN 20 //координата оx верхнего левого угла площадки леса
#define PLACE_Y_MIN 20 //координата оy верхнего левого угла площадки леса
#define PLACE_SIZE_X 800 //размер площадки леса по горизонтали
#define PLACE_SIZE_Y 600 //размер площадки леса по вертикали

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Grass - трава*/
#define HEIGHT_START_GRASS 1
#define RADIUS_START_GRASS 5
#define MIN_
#define MAX_
#define SCORE_GROW_START_GRASS 0
#define VIABILITY_START_GRASS 1
#define MIN_RADIUS_GRASS 5
#define MAX_RADIUS_GRASS 200

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Bush - куст*/
#define MIN_
#define MAX_

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Grass - дерево*/

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Dirt_cell - ячейка почвы*/
#define MIN_FERTILITY 5
#define MAX_FERTILITY 30
#define EFFECTIV_START_DIRT 1
#define MIN_WET_START_DIRT 0
#define MAX_WET_START_DIRT 5

/*ДИАПАЗОНЫ ЗНАЧЕНИЙ ДЛЯ Weather - погода*/

#endif // CONSTANTS_H
