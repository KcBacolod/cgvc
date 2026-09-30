#include <GL/freeglut.h>

void triangle();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutCreateWindow("VertexArray");
    glutDisplayFunc(triangle);
    glutMainLoop();
}

void triangle(){
    GLfloat trianglevertex[] = {
        0.0f, .75f, 0.0f,
        -0.75,0.0f,0.0f,
        0.75,0.0f,0.0f,
    };

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, trianglevertex);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
}