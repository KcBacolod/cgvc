#include <gl/glut.h>
#include <gl/freeglut_ext.h>

void textSample(){
    glClear(GL_COLOR_BUFFER_BIT);

    const unsigned char str[100] = {"HSIN's TAIL"};
    glColor3d(1, 1, 1);
    glRasterPos2f(-0.05f,0.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    
    glutInitWindowPosition(0,0);
    glutCreateWindow("Hsin");
    glutFullScreen();
    glutDisplayFunc(textSample);
    glutMainLoop();

}