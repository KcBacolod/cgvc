#include <GL/freeglut.h>

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    //Body of the house
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.5, 0.5); //top-left
        glVertex2f(0.5, 0.5); //top-right
        glVertex2f(0.5, -0.5); //bottom-right
        glVertex2f(-0.5, -0.5); //bottom-left
    glEnd();

    //roof
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);        
        glVertex2f(0.0, 1.0); 
    glEnd();

    //fences
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(9.0);
    glBegin(GL_LINES);
        glVertex2f(0.55, -0.1);
        glVertex2f(0.55, -0.5); 
        glVertex2f(-0.55, -0.1);
        glVertex2f(-0.55, -0.5);
        glVertex2f(0.45, -0.1);
        glVertex2f(0.45, -0.5); 
        glVertex2f(-0.45, -0.1);
        glVertex2f(-0.45, -0.5);
        glVertex2f(0.35, -0.1);
        glVertex2f(0.35, -0.5); 
        glVertex2f(-0.35, -0.1);
        glVertex2f(-0.35, -0.5);
    glEnd();

    //door
    glColor3f(0.15, 0.75, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.2, 0.25); 
        glVertex2f(0.2, 0.25); 
        glVertex2f(0.2, -0.5); //bottom-right
        glVertex2f(-0.2, -0.5); //bottom-left
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutCreateWindow("House");
    glutDisplayFunc(display);
    glutMainLoop();

}