#include <GL/freeglut.h>
#include <GL/glut.h>
#include<iostream>
#include <random>
#include <vector>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<float> windowWidth(-0.95, 0.95);
const GLfloat triangleVertices[] = {
        0.00f,  0.10f,  // Top
        -0.08f, -0.08f,  // Bottom-Left
        0.08f, -0.08f   // Bottom-Right
    };
const GLfloat squareVertices[] = {
        -0.08f,  0.08f,  // Top-Left
        -0.08f, -0.08f,  // Bottom-Left
        0.08f, -0.08f,  // Bottom-Right
        0.08f,  0.08f   // Top-Right
    };
const GLfloat starVertices[] = {
        0.000f,  0.000f, // center
        0.000f,  0.100f,   // Outer 1 (Top)
        -0.024f,  0.031f,   // Inner 1
        -0.095f,  0.031f,   // Outer 2
        -0.038f, -0.012f,   // Inner 2
        -0.059f, -0.081f,   // Outer 3
        0.000f, -0.038f,   // Inner 3 (Center Bottom)
        0.059f, -0.081f,   // Outer 4
        0.038f, -0.012f,   // Inner 4
        0.095f,  0.031f,   // Outer 5
        0.024f,  0.031f,   // Inner 5
        0.000f,  0.100f // close loop
    };
enum ShapeType{
    SHAPE_TRIANGLE,
    SHAPE_SQUARE,
    SHAPE_STAR,
    COUNT
};
GLfloat playerSprite[] ={
    // Left Wing
     0.00f, -0.70f,  // Top tip
    -0.08f, -0.83f,  // Bottom-left
     0.00f, -0.78f,  // Inner notch

     // Right Wing
     0.00f, -0.700f,  // Top tip
     0.00f, -0.78f,  // Inner notch
     0.08f, -0.83f   // Bottom-right
};
float addPlayerSpeed = 0.0f;
struct playerState{
    float red   = 0.0f;
    float green = 1.0f;
    float blue  = 0.0f;
    float posX, posY = 0.0f;
    float speed = 0.04f + addPlayerSpeed;
    int score = 0;
    int lives = 3;
}; playerState player1;
float addObjSpeed = 0.00f;
struct fallingObject{
    uniform_real_distribution<float> speedRange{0.008f, 0.02f};
    float x = 0.0f;
    float y = 1.1f;
    float baseSpeed = 0.01f;
    float speed = 0.01f;
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
    int colorId = 1;
    ShapeType shape = ShapeType::SHAPE_SQUARE;

    void reset(float startingY = 1.1f) {
        // Keep the whole object inside the left and right edges.
        x = windowWidth(gen);
        y = startingY;

        baseSpeed = speedRange(gen);
        speed = baseSpeed + addObjSpeed;
        // new color
        colorId = (rand() % 3) + 1; // 1 = red; 2 = green; 3 = blue;
        switch (colorId){
            case 1:
                red = 1.0f;
                green = 0.0f;
                blue = 0.0f;
                break;
            case 2:
                red = 0.0f;
                green = 1.0f;
                blue = 0.0f;
                break;
            case 3:
                red = 0.0f;
                green = 0.0f;
                blue = 1.0f;
                break;
        }
        // new shape
        uniform_int_distribution<int> shapeDist(0, static_cast<int>(COUNT) - 1);
        shape = static_cast<ShapeType>(shapeDist(gen));

    }

    void update() {
        y -= speed;

        // Recycle the object after it has moved below the screen.
        if (y < -1.1f) {
            reset();
        }
    }

    void draw() const {
        glPushMatrix(); 
        glTranslatef(x, y, 0.0f);   

        glColor3f(red, green, blue);

        glEnableClientState(GL_VERTEX_ARRAY);
        
        switch (shape) {
        case SHAPE_TRIANGLE:
            glVertexPointer(2, GL_FLOAT, 0, triangleVertices);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            break;

        case SHAPE_SQUARE:
            glVertexPointer(2, GL_FLOAT, 0, squareVertices);
            glDrawArrays(GL_QUADS, 0, 4);
            break;

        case SHAPE_STAR:
            glVertexPointer(2, GL_FLOAT, 0, starVertices);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
            break;

        case COUNT:
            break;
        }
        glDisableClientState(GL_VERTEX_ARRAY);
        glPopMatrix();
    }
};
constexpr int OBJECT_COUNT = 2;
vector<fallingObject> objects(OBJECT_COUNT);

void mainDisplay();
void drawText();
void playerHud();
void player();
void movementTimer(int);
void speedTimer(int);
bool checkCollision(const fallingObject&);
bool checkColor(const fallingObject&);
void keyboard(unsigned char key, int x, int y);
void restart();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // glutInitWindowSize(1280,720);
    glutCreateWindow("Cosmic Dodger");
    glutFullScreen();
    glutDisplayFunc(mainDisplay);
    glutTimerFunc(0, movementTimer, 0);
    glutTimerFunc(2000, speedTimer, 0);
    glutKeyboardFunc(keyboard);
    for (int i = 0; i < OBJECT_COUNT; i++)
    // Start each object at a different height.
    objects[i].reset(1.1f + i * 0.6f); 

    glutMainLoop();
}

void mainDisplay(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    playerHud();
    player();
    for (const auto& object : objects){
        object.draw();
    }

    glutSwapBuffers();
}

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawText(float x, float y, const int* score, const int* lives)
{   
    string fullText = "Score: " + to_string(*score) + " | Lives: " + to_string(*lives);
    glRasterPos2f(x, y);
    for (char c : fullText)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void playerHud()
{
    // Set text color to contrast dynamically with the background color
    glColor3f(1.0f, 1.0f, 1.0f);

    if(player1.lives <= 0){
        drawText(player1.posX - 0.24f, 0.0f, "GAME OVER!\nPRESS [X] TO RESTART");
        return;
    }

    drawText(-0.95f, 0.9f, &player1.score, &player1.lives);
    // Display instructions on the screen
    drawText(-0.95f, 0.8f, "=== RGB CONTROLLER ===");
    drawText(-0.95f, 0.7f, "[A]/[D] - Move Left to Right");
    drawText(-0.95f, 0.6f, "[R] - Change to RED");
    drawText(-0.95f, 0.5f, "[G] - Change to GREEN");
    drawText(-0.95f, 0.4f, "[B] - Change to BLUE");
    drawText(-0.95f, 0.3f, "[X] - Reset Program");
    drawText(-0.95f, 0.2f, "[ESC] - Exit Program");

}

void player(){
    glPushMatrix(); 
    glEnableClientState(GL_VERTEX_ARRAY);

    glTranslatef(player1.posX, player1.posY, 0.0f);

    glVertexPointer(2, GL_FLOAT, 0, playerSprite);
    glColor3f(player1.red, player1.green, player1.blue);
    glDrawArrays(GL_TRIANGLES, 0,6);

    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void movementTimer(int){
    if(player1.lives > 0){
        for (auto& object : objects){
            object.update();

            if (checkCollision(object)){
                if (checkColor(object))
                    player1.score++;
                else
                    player1.lives--;

                object.reset();
            }
        }
    } 
    glutPostRedisplay();
    glutTimerFunc(1000/60, movementTimer, 0);
}

void speedTimer(int){
    if(player1.lives > 0){
        if(addObjSpeed < 0.04)
            addObjSpeed += 0.0005;
        if(addPlayerSpeed < 0.02){
            addPlayerSpeed = 0.0005 *player1.score;
            player1.speed = 0.04f + addPlayerSpeed;
        }
        cout << player1.speed <<endl;
    }
    glutTimerFunc(2000, speedTimer, 0);
}

bool checkCollision(const fallingObject& object){
    // Player bounds and color
    float playerLeft   = player1.posX - 0.07f;
    float playerRight  = player1.posX + 0.07f;
    float playerTop    = player1.posY - 0.69f;
    float playerBottom = player1.posY - 0.82f;

    // Falling-object bounds and color
    float objectLeft   = object.x - 0.10f;
    float objectRight  = object.x + 0.10f;
    float objectTop    = object.y + 0.10f;
    float objectBottom = object.y - 0.10f;

    bool horizontalOverlap =
        playerLeft < objectRight &&
        playerRight > objectLeft;

    bool verticalOverlap =
        playerBottom < objectTop &&
        playerTop > objectBottom;


    return horizontalOverlap && verticalOverlap;
}

bool checkColor(const fallingObject& object){
    return player1.red == object.red && player1.green == object.green && player1.blue == object.blue;
}

void keyboard(unsigned char key, int, int){   
    if(player1.lives <= 0){
        if(key == 'X' || key == 'x')
            restart();
        return;
    }
    switch (key)
    {   
        case 'a':
        case 'A':
            if(player1.posX >= -0.90)
                player1.posX -= player1.speed;
            break;
        case 'd':
        case 'D':
            if(player1.posX <= 0.90)
                player1.posX += player1.speed;
            break;
        case '1':
        case 'r':
        case 'R':
            player1.red = 1.0f;
            player1.green = 0.0f;
            player1.blue = 0.0f;
            break;
        case '2': 
        case 'g':
        case 'G':
            player1.red = 0.0f;
            player1.green = 1.0f;
            player1.blue = 0.0f;
            break;
        case '3':
        case 'b':
        case 'B':
            player1.red = 0.0f;
            player1.green = 0.0f;
            player1.blue = 1.0f;
            break;
        case 'x':
        case 'X':
            restart();
            break;
        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

void restart(){
    addPlayerSpeed = 0.0f;
    addObjSpeed = 0.0f;
    player1.posX = 0.0f;
    player1.posY = 0.0f;
    player1.lives = 3;
    player1.score = 0;
    player1.red = 0.0f;
    player1.green = 1.0f;
    player1.blue = 0.0f;
    for (int i = 0; i < OBJECT_COUNT; i++){
        objects[i].reset(1.1f + i * 0.6f);
    }
    glutPostRedisplay();
}
