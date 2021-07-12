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
};
#endif // MAINWIDGET_H
