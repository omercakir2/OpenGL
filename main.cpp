#include <GL/glut.h>

void display() {
    // Set the background color to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // Blue background (RGBA)
    glClear(GL_COLOR_BUFFER_BIT);            // Clear the screen

    // Swap buffers (for double buffering)
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("First openGL");

    // Set the window size
    glutReshapeWindow(500, 500);  // You can adjust the size as needed

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
