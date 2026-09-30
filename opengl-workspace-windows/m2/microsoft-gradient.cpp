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
    glBegin(GL_QUAD_STRIP);
    
    glColor3f(1, 0, 0);
    glVertex2f(-1.0f, 1.0f);

    glColor3f(0, 1, 0);
    glVertex2f(1.0f, 1.0f);

    glColor3f(0, 0, 1);
    glVertex2f(-1.0f, -1.0f);

    glColor3f(1, 1, 0);
    glVertex2f(1.0f, -1.0f);

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