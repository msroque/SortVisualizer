#ifndef VISUALIZERWIDGET_H
#define VISUALIZERWIDGET_H

#include "barsort.h"
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <iostream>

// speed x3 = 17ms, x2 = 25, x1 = 51
// static const int SPEED = 51;

namespace Ui {
class VisualizerWidget;
}

class VisualizerWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

signals:
    void doSort(int code);
    void sortFinished(int state);
    
public:
    explicit VisualizerWidget(QWidget *parent = nullptr);
    ~VisualizerWidget();

    void setSpeed(int spd);
    void toggleTimer();
    void setNumElements(int num);

public slots:
    void setSortCode(int code);

// Inherited from QOpenGLWidget
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void timerEvent(QTimerEvent *event) override;

private:
    Ui::VisualizerWidget *ui;
    int numBarsVW = 3;
    int speed = 51;
    int signal = 0;
    // bool pressed = false;
    QBasicTimer timer;
    BarSort *bars;
    QOpenGLShaderProgram *program;
};

#endif // VISUALIZERWIDGET_H
