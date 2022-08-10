// PURPOSE: draw bars, animate using sorting algorithms, NOT a QObject
#pragma once

#include <QOpenGLExtraFunctions>
#include <QtOpenGL>
#include <random>

static const GLuint MAXVERTICES = 1200; // 100 rectangles, 4 vertices per rectangle, 3 floats per vertex
static const GLuint MAXBARS = 100;
static const GLuint MAXCOLORS = 1600;    // 100 rectangles, 4 vertices per rectangle, 4 floats per vertex color

class BarSort : protected QOpenGLExtraFunctions
{
public:
    BarSort(int n, QOpenGLShaderProgram *prgm);
    ~BarSort();

    void drawBars();
    void drawRect(GLuint index, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void makeArray();
    void setNumBars(int n);
    int getNumBars() const;

    void bubbleSort();
    int increment(int code);

private:
    void initBars();

    int numBarsBS = 3;
    int arr[MAXBARS];
    int iTime = 0; // iterates through bars
    int jTime = numBarsBS - 1;

    QOpenGLShaderProgram *program;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO{QOpenGLBuffer::VertexBuffer};
};