#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <vector>
#include <iostream>

struct position {
    float x_pos = 0;
    float y_pos = 0;
}; 
position current = {0,0};
std::vector<position> trail;

void mainDisplay();
void displayStar();
void displayTail();
void keyboardMonitor(unsigned char, int, int);
void recordPosition(position);

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(500, 500);
    glutCreateWindow("Trails");
    glutKeyboardFunc(keyboardMonitor);
    glutDisplayFunc(mainDisplay);
    glutMainLoop();

    return 0;
}

void mainDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    displayTail();
    displayStar();

    glutSwapBuffers();
    glutPostRedisplay();
}

void displayStar(){  
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(current.x_pos + 0.0000f, current.y_pos + 0.0000f);

    // 10 perimeter vertices (outer points & inner corners)
    glVertex2f( current.x_pos + 0.0000f, current.y_pos + 0.2500f); // Top Point
    glVertex2f(current.x_pos - 0.0588f, current.y_pos + 0.0688f);
    glVertex2f(current.x_pos - 0.2378f,  current.y_pos + 0.0773f); // Upper-Left Point

    glColor3f(0.0,1.0,0.0);  
    glVertex2f(current.x_pos - 0.0951f, current.y_pos - 0.0263f);
    glVertex2f(current.x_pos - 0.1469f, current.y_pos - 0.1902f); // Bottom-Left Point
    glVertex2f(current.x_pos + 0.0000f, current.y_pos - 0.0838f); // Bottom Inner Corner
    glVertex2f(current.x_pos + 0.1469f, current.y_pos - 0.1902f); // Bottom-Right Point

    glColor3f(0.0,0.0,1.0); 
    glVertex2f(current.x_pos + 0.0951f, current.y_pos - 0.0263f);
    glVertex2f(current.x_pos + 0.2378f,  current.y_pos + 0.0773f); // Upper-Right Point
    glVertex2f(current.x_pos + 0.0588f,  current.y_pos + 0.0688f);

    // Close the loop back to the first perimeter point
    glVertex2f( current.x_pos + 0.0000f, current.y_pos + 0.2500f);
    glEnd();
};

void keyboardMonitor(unsigned char key, int x, int y){
    switch(key){
        case 'w':
            current.y_pos += 0.06f;
            recordPosition(current);
            break;
        case 'a':   
            current.x_pos -= 0.06f;
            recordPosition(current);
            break;
        case 's':
            current.y_pos -= 0.06f;
            recordPosition(current);
            break;
        case 'd':
            current.x_pos += 0.06f;
            recordPosition(current);
            break;
        case 'r':
            current.x_pos = 0;
            current.y_pos = 0;
            std::cout << "Total Vector Elements: ("<< trail.size() <<")";
            trail.clear();
        default:
            break;
    }
}

void displayTail(){
    int count = 0;
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
    for(const auto& i: trail){
        count++;
        if(count > 0 && count <= 6)
            glColor3f(1.0,0.0,0.0);
        if(count > 6 && count <= 12)
            glColor3f(0.0,1.0,0.0);            
        if(count > 12){
            count = (count <= 18) ? count : 0;
            glColor3f(0.0,0.0,1.0); 
        }     
        glVertex2f(i.x_pos, i.y_pos);
    }
    glEnd();
}

void recordPosition(position currentPosition){
    float x = currentPosition.x_pos;
    float y = currentPosition.y_pos;

    trail.push_back(currentPosition);
    std::cout << "position: ("<< x << ", " << y <<") is added" << std::endl;
}