// PURPOSE: control and manage UI input, send values to visual display

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sort.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    makeConnections();
    stateChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Sort Buttons
void MainWindow::onBubbleSortBtnClicked()
{
    qDebug() << "Bubble Sort Clicked!"; 
    cout << "Num of Elements: " << ui->nElements->value() << endl;

    Sort cSort(0, ui->nElements->value());
    cSort.bubbleSort();

    emit ui->visual->doSort(1);
    emit stateChanged(1);
}

// Media Buttons
void MainWindow::onPlayPauseBtnClicked(bool checked)
{
    // change icon
    if(checked)
    {
        ui->playPauseBtn->setIcon(QIcon(":icons/play_arrow_black_24dp.svg"));
        qDebug() << "Pause! --CHECKED ON--";
    }
    else
    {
        ui->playPauseBtn->setIcon(QIcon(":icons/pause_black_24dp.svg"));
        qDebug() << "Play! --CHECKED OFF--";
    }
    ui->visual->toggleTimer();
}

// Settings
void MainWindow::onSliderValueChanged(int n)
{
    ui->elementsLabel->setText("Number of Elements: " + QString::number(n));
    // change number of input
    ui->visual->setNumElements(n);
    stateChanged(0);
}

// Speed Menu Options
void MainWindow::spd1()
{
    ui->visual->setSpeed(51);
    ui->speedLabel->setText("x1");
    qDebug() << "Speed set to 1!";
}

void MainWindow::spd2()
{
    ui->visual->setSpeed(25);
    ui->speedLabel->setText("x2");
    qDebug() << "Speed set to 2!";
}

void MainWindow::spd3()
{
    ui->visual->setSpeed(17);
    ui->speedLabel->setText("x3");
    qDebug() << "Speed set to 3!";
}

void MainWindow::makeConnections()
{
    // Sorting Buttons
    connect(ui->BubbleSortBtn,    &QPushButton::clicked, this, &MainWindow::onBubbleSortBtnClicked);

    // Media Buttons
    connect(ui->playPauseBtn, &QPushButton::clicked, this, &MainWindow::onPlayPauseBtnClicked);

    QMenu *menu = new QMenu;
    QAction *a1 = menu->addAction("x1");
    QAction *a2 = menu->addAction("x2");
    QAction *a3 = menu->addAction("x3");

    ui->speedCycleBtn->setMenu(menu);

    connect(a1, &QAction::triggered, this, &MainWindow::spd1);
    connect(a2, &QAction::triggered, this, &MainWindow::spd2);
    connect(a3, &QAction::triggered, this, &MainWindow::spd3);

    // Settings Buttons
    connect(ui->nElements, &QSlider::valueChanged, this, &MainWindow::onSliderValueChanged);

    // Signals
    connect(this, &MainWindow::stateChanged, this, &MainWindow::toggleButtonsEnable);
    connect(ui->visual, &VisualizerWidget::sortFinished, this, &MainWindow::toggleButtonsEnable);
}

void MainWindow::toggleButtonsEnable(int state)
{
    // Sort State: positive number
    if(state)
    {
        ui->playPauseBtn->setEnabled(true);
        ui->BubbleSortBtn->setEnabled(false);
    }

    // Default State: 0
    else {
        ui->playPauseBtn->setIcon(QIcon(":icons/pause_black_24dp.svg"));
        ui->playPauseBtn->setChecked(false);
        ui->playPauseBtn->setEnabled(false);

        ui->BubbleSortBtn->setEnabled(true);
    }
}