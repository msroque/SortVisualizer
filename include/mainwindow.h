#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "visualizerwidget.h"

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    stateChanged(int state);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBubbleSortBtnClicked();

    void onSliderValueChanged(int n);

    void onPlayPauseBtnClicked(bool checked);

    // Menu
    void spd1();
    void spd2();
    void spd3();

    void toggleButtonsEnable(int state);

private:
    void makeConnections();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
