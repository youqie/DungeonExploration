#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chooselevel.h"
#include <QSound>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool ismusic;

    //绘图事件
    void paintEvent(QPaintEvent *);

    ChooseLevel * chooselevel;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
