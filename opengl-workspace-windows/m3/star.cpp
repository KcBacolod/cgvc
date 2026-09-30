#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

void drawStar() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    
        // Center vertex (anchor for triangle fan)
        glVertex2f(0.0000f, 0.0000f);

        // 10 perimeter vertices (outer points & inner corners)
        glVertex2f( 0.0000f,  0.2500f); // Top Point
        glVertex2f(-0.0588f,  0.0688f);
        glVertex2f(-0.2378f,  0.0773f); // Upper-Left Point
        glVertex2f(-0.0951f, -0.0263f);
        glVertex2f(-0.1469f, -0.1902f); // Bottom-Left Point
        glVertex2f( 0.0000f, -0.0838f); // Bottom Inner Corner
        glVertex2f( 0.1469f, -0.1902f); // Bottom-Right Point
        glVertex2f( 0.0951f, -0.0263f);
        glVertex2f( 0.2378f,  0.0773f); // Upper-Right Point
        glVertex2f( 0.0588f,  0.0688f);

        // Close the loop back to the first perimeter point
        glVertex2f( 0.0000f,  0.2500f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutCreateWindow("Star");
    glutDisplayFunc(drawStar);
    glutMainLoop();

    return 0;
}