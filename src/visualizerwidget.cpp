// PURPOSE: handle events for OpenGL visuals

#include "visualizerwidget.h"
#include "ui_visualizerwidget.h"

VisualizerWidget::VisualizerWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::VisualizerWidget)
{
    ui->setupUi(this);
    connect(this, &VisualizerWidget::doSort, this, &VisualizerWidget::setSortCode);
}

VisualizerWidget::~VisualizerWidget()
{
    delete ui;
}

void VisualizerWidget::setSortCode(int code)
{
    signal = code;
    std::cout << "Sort Code: " << signal << std::endl;
    if(signal > 0)
        timer.start(speed, this);
    else if(timer.isActive())
        timer.stop();
    update();
}

void VisualizerWidget::setNumElements(int num)
{
    // !pressed && 
    if(timer.isActive())
    {
        timer.stop();
        signal = 0;
        bars->setNumBars(num);
        numBarsVW = num;
        // timer.start(speed, this);
    }
    else
    {
        signal = 0;
        bars->setNumBars(num);
        numBarsVW = num;
    }
    update();
}

void VisualizerWidget::setSpeed(int spd)
{
    speed = spd;
    if(timer.isActive())
    {
        timer.stop();
        timer.start(speed, this);
    }
}

void VisualizerWidget::toggleTimer()
{
    if(timer.isActive())
    {
        timer.stop();
        // pressed = true;
    }
    else
    {
        timer.start(speed, this);
        // pressed = false;
    }
}

void VisualizerWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    /*========================== SHADER ==========================*/
    // Initialize Program Shader
    program = new QOpenGLShaderProgram();

    // Add shaders to program and compile 
    // Made without instantiating so don't need to delete any Shader objects
    // Order in .qrc needs to match files!
    // Need to use .qrc bc not in same parent folder
    if(!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":shaders/vertex.glsl"))
        close();
    if(!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":shaders/frag.glsl"))
        close();

    // Linking: connects in/out variables of shaders to shader program
    if(!program->link())
        close();

    if(!program->bind())
        close();

    bars = new BarSort(numBarsVW, program);
}

void VisualizerWidget::paintGL()
{
    std::cout << "Timer Active: " << timer.isActive() << std::endl;
    switch(signal)
    {
        case 1:
            bars->bubbleSort();
            break;
        default:
            bars->drawBars();
    }
}

void VisualizerWidget::resizeGL(int w, int h)
{}

void VisualizerWidget::timerEvent(QTimerEvent *event)
{
    if(bars->increment(signal) > numBarsVW)
    {
        timer.stop();
        signal = 0;
        sortFinished(0);
        std::cout << "Sort Code: " << signal << std::endl;
    }
    else
        update();
}