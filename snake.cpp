#include <GL/glut.h>
#include <iostream>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(0.0, 1.0, 0.0); // Green text color
    glRasterPos2f(-0.2, 0.3); // Position the title

    // Display "Snake Game" title
    std::string title = "SNAKE GAME";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glColor3f(1.0, 1.0, 1.0); // White text for menu options
    glRasterPos2f(-0.15, 0.1);
    std::string option1 = "Press 'S' to Start";
    for (char c : option1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(-0.15, -0.1);
    std::string option2 = "Press 'Q' to Quit";
    for (char c : option2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') {
        std::cout << "Game Started!" << std::endl;
        // Here, you can add code to switch to the actual game screen
    } 
    else if (key == 'q' || key == 'Q') {
        std::cout << "Exiting..." << std::endl;
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Snake Game Menu");

    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // Set the coordinate system

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeys);

    glutMainLoop();
    return 0;
}
