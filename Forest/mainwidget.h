#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    virtual void mousePressEvent(QMouseEvent*e); //событие нажатия кнопки мыши внутри окна

private:
    Ui::MainWidget *ui;

public slots: //публичные слоты
    void Timer_tick(); //слот интервала таймера
    void Normalmode(bool value); //слот при переключении в нормальный режим времени
    void Speedmode(bool value); //слот при переключении в ускоренный режим времени
    void Pausemode(bool value); //слот при переключении в режим времени - паузу
    void Print_info(int num, int type, int f_update); //слот вывода инфо о растении/ячейке почвы (номер объекта, тип объекта (0 - ячейка почвы, 1 - трава, 2 - куст, 3 - дерево), флаг обновления (=0, если не надо обновлять названия столбцов, иначе =1)
    void Print_weather_info(); //слот вывода инфо о погоде
};
#endif // MAINWIDGET_H
