#include "barsort.h"
#include <iostream>

BarSort::BarSort(int n, QOpenGLShaderProgram *prgm)
{
    numBarsBS = n;
    program = prgm;
    initBars();
}

BarSort::~BarSort()
{
    VAO.destroy();
    VBO.destroy();
}

void BarSort::initBars()
{
    initializeOpenGLFunctions();

    // Create Buffers
    VAO.create();
    VBO.create();

    VBO.setUsagePattern(QOpenGLBuffer::DynamicDraw); // set once draw many times

    // Add VAO to VBO to active objects
    VAO.bind();
    VBO.bind();

    // Make space to put vertex data in the buffer
    VBO.allocate(sizeof(GLfloat) * (MAXVERTICES + MAXCOLORS));

    // Make the Shader Program the active object
    program->bind();

    // Activate the variable from the vertex shader
    program->enableAttributeArray("position");
    makeArray();

    VAO.release();
    VBO.release();
}

void BarSort::makeArray()
{
    // Make random numbers from 0 - 100
    std::random_device rand;
    std::mt19937 mt(rand());
    std::uniform_int_distribution dist(0, 100);

    int temp;
    /*======================== ARRAY DATA ========================*/
    for(int i = 0; i < numBarsBS; i++)
    {
        temp = dist(mt);
        arr[i] = temp;
    }
}

void BarSort::setNumBars(int n)
{
    numBarsBS = n;
    iTime = 0;
    jTime = numBarsBS - 1;
    makeArray();
}

int BarSort::getNumBars() const
{
    return numBarsBS;
}

void BarSort::drawRect(GLuint index, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    // Make vertices of one Rectangle
    GLfloat vertices[] = {
        (GLfloat)((index * 2.0 / numBarsBS) - 1),       -1.0,                          0.0,
        (GLfloat)(((index + 1) * 2.0 / numBarsBS) - 1), -1.0,                          0.0,
        (GLfloat)(((index + 1) * 2.0 / numBarsBS) - 1), (GLfloat)((height * 0.02) -1), 0.0,
        (GLfloat)((index * 2.0 / numBarsBS) - 1),       (GLfloat)((height * 0.02) -1), 0.0
    };

    // Add VAO to VBO to active objects
    VAO.bind();
    VBO.bind();

    // Put vertex data in the buffer
    // VBO.write(index * sizeof(vertices), vertices, sizeof(vertices));
    VBO.write(0, vertices, sizeof(vertices));

    /*======================= SHADER PROGRAM =======================*/
    // Make the Shader Program the active object
    program->bind();

    // Put the vertices into the position variable
    // Input: Attribute variable, type of elements in variable, *values (0 = nullptr), # of bytes b/tw vertices
    program->setAttributeArray("position", GL_FLOAT, 0, 3);
    program->setAttributeValue("color", r, g, b, a);    // yellow

    glDrawArrays(GL_QUADS, 0, 4);
    glFlush();
}

int BarSort::increment(int code)
{
    switch (code)
    {
    // Bubble Sort
    case 1:
        if(iTime > numBarsBS)
        {
            iTime = 0;
            jTime = numBarsBS - 1;
        }
        else { 
            // && jTime - 1 != 0 && jTime - 1 != iTime
            // jTime - 1 > iTime
            if(jTime > iTime && jTime - 1 != 0 && jTime - 1 != iTime)
            {
                jTime--;
            }
            else {
                iTime++;
                jTime = numBarsBS - 1;
            }
        }
        break;
    
    default:
        break;
    }
    
    return iTime;
}


void BarSort::drawBars()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0; i < numBarsBS; i++)
    {
        drawRect(i, arr[i], 0.55, 0.50, 0.75, 1.00); // purple
    }
    std::cout << "Draw Purple Bars" << std::endl;
}

// Set up per frame
void BarSort::bubbleSort()
{
     std::cout << "Draw Bubble Sort" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Step 1: Add purple bars to Buffer
    for(int i = 0; i < numBarsBS; i++)
    {
        drawRect(i, arr[i], 0.55, 0.50, 0.75, 1.00); // purple
    }

    if(iTime < numBarsBS)
    {
        // Step 2: Add yellow bars to Buffer
        drawRect(iTime, arr[iTime], 0.50, 0.50, 0.00, 1.00);    // yellow
        drawRect(jTime, arr[jTime], 0.50, 0.50, 0.00, 1.00);
        
        // Step 4: If need to be swapped, Rewrite yellow bars to blue bars
        if(arr[jTime] < arr[jTime - 1])
        {
            // swap

            drawRect(jTime, arr[jTime], 0.00, 0.00, 1.00, 1.00);        // blue
            drawRect(jTime - 1, arr[jTime - 1], 0.00, 0.00, 1.00, 1.00);

            int temp = arr[jTime];
            arr[jTime] = arr[jTime-1];
            arr[jTime-1] = temp;
        }
    }
}