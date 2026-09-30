#include <GL/glut.h>
#include <iostream>

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);

    //Red Background
    glColor3f(1, 0, 0);
    glVertex2f(-1.113f, 1.166f);
    glVertex2f(-1.113f, -1.012f);
    glVertex2f(1.084f, -1.012f);
    glVertex2f(1.084f, 1.166f);

    //Black Background
    glColor3f(0, 0, 0);
    glVertex2f(-0.913f, 0.866f);
    glVertex2f(-0.913f, -0.912f);
    glVertex2f(0.884f, -0.912f);
    glVertex2f(0.884f, 0.866f);

    //Left polygon
    glColor3f(1, 0, 0);
    glVertex2f(-0.553f, 0.515f);
    glVertex2f(-0.567f, 0.087f);
    glVertex2f(-0.2f, -0.37f);
    glVertex2f(0.16f, -0.365f);

    //Right polygon
    glVertex2f(0.07f, -0.064f);
    glVertex2f(0.411f, -0.066f);
    glVertex2f(0.535f, 0.085f);
    glVertex2f(0.532f, 0.521f);

    glEnd();
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutCreateWindow("Valorant");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}