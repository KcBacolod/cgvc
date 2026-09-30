#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

void myAnimation();
void Timer(int);

float y_pos = 0.0;
int state = 0;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    
    glutCreateWindow("myAnimation");
    glutDisplayFunc(myAnimation);

    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
}

void myAnimation(){
    glClear(GL_COLOR_BUFFER_BIT);
    // glLoadIdentity();
    glBegin(GL_QUAD_STRIP);

    //left to right | top to bottom
    glVertex2f(-0.1f, y_pos + 0.1f);
    glVertex2f(-0.1f, y_pos - 0.1f);
    glVertex2f(0.1f, y_pos + 0.1f);
    glVertex2f(0.1f, y_pos - 0.1f);

    glEnd();

    glutSwapBuffers();
}

void Timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60, Timer, 0);
    switch(state){
        case 0:
            if(y_pos < 1.0f)
                y_pos += 0.05f;
            else 
                state = 1;
            break;
        case 1:
            if(y_pos > -1.0f)
                y_pos -= 0.05f;
            else 
                state = 0;
            break;            
    }
}