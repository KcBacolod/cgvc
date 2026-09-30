#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    //background
    glColor3f(0.9, 0.9, 0.9);
    glVertex2f(3.05f, -3.05f);
    glVertex2f(-3.05f, -3.05f);
    glVertex2f(-3.05f, 3.05f);
    glVertex2f(3.05f, 3.05f);
        
    // left-upper
    glColor3f(1.0, 0, 0);
    glVertex2f(-3.05f, 0.05f);
    glVertex2f(-3.05f, 3.05f);
    glVertex2f(-0.05f, 3.05f);
    glVertex2f(-0.05f, 0.05f);
    
    // right-upper
    glColor3f(0, 1, 0);
    glVertex2f(3.05f, 0.05f);
    glVertex2f(3.05f, 3.05f);
    glVertex2f(0.05f, 3.05f);
    glVertex2f(0.05f, 0.05f);

    // left-lower
    glColor3f(0, 0, 1);
    glVertex2f(-3.05f, -0.05f);
    glVertex2f(-3.05f, -3.05f);
    glVertex2f(-0.05f, -3.05f);
    glVertex2f(-0.05f, -0.05f);
    // right-lower
    glColor3f(1, 1, 0);
    glVertex2f(3.05f, -3.05f);
    glVertex2f(0.05f, -3.05f);
    glVertex2f(3.05f, -0.05f);
    glVertex2f(0.05f, -0.05f);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}