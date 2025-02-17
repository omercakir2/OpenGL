#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int ASCII = -1;

void display()
{
   glClearColor(1, 0, 0, 0); // Red
   glClear(GL_COLOR_BUFFER_BIT);
   glutSwapBuffers();
}

void onKey(unsigned char key, int x, int y)
{
   if (key == 27) // 27 means esc button
   {
      exit(0);
   }
   else if ((key >= 'a' && key <= 'z') && ASCII == 1)
   {
      printf("button's ascii code is %d \n", key);
   }
   if (key == 'a')
   {
      ASCII *= -1;
   }
}
void onClick(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON)
      printf("LEFT BUTTON --");
   else if (button == GLUT_RIGHT_BUTTON)
      printf("RIGHT BUTTON --");
   if (state == GLUT_DOWN)
      printf("DOWN [%d %d]\n", x, y);
   else
      printf("UP [%d %d]\n", x, y);
}
void onSpecialKey(int key, int x, int y)
{
   switch (key)
   {
   case GLUT_KEY_UP:
      printf("UP arrow pressed.\n");
      break;
   case GLUT_KEY_DOWN:
      printf("DOWN arrow pressed.\n");
      break;
   case GLUT_KEY_LEFT:
      printf("LEFT arrow pressed.\n");
      break;
   case GLUT_KEY_RIGHT:
      printf("RIGHT arrow pressed.\n");
      break;
   }
}
int main(int argc, char *argv[])
{
   printf("Press ESC to exit the program\n");
   printf("Click on the window with left or right mouse button.\n");
   printf("Press arrow keys to be detected.\n");
   printf("IF YOU WANNA LEARN ABOUT ASCII CODES USE LETTER 'a'\n");

   // CREATING A WINDOW

   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutCreateWindow("First program!");

   // REGISTERING EVENTS
   glutDisplayFunc(display);
   glutKeyboardFunc(onKey);
   glutSpecialFunc(onSpecialKey);
   glutMouseFunc(onClick);

   // START EVENT DISPATHER FORMING A LOOP UNTIL WE EXIT
   glutMainLoop();

   return 0;
}