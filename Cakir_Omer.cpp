/*
OMER CAKIR
22302695
CTIS164-003 (SECTION 3)

Additional Features:

-I have added :
1-  a feature changing the color of the car randomly with srand and rand functions(stdlib)
2-  a feaure which allows user to change the speed of both car and the clouds.
3-  a feature which allows user to change the thickness of the wooden window.
	The keys are shown on the program so that user can try and see.
4- a feature that allows user to change the state of the curtain (visible or not for both sides)
*/

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <__stdarg_va_arg.h>

#define PI 3.14159265358
#define WIN_W 800// WINDOW WIDTH
#define WIN_H 600// WINDOW HEIGHT


//Global variables
float carstart;
float carX = WIN_W / 4;	// car starting x axis
float cloudsX = WIN_W / 2;
float carSpeed = 1.5f;
float cloudSpeed = 0.5f;
float thickness = 20;
bool Timer = false;
bool left = true;//true : open , false : closed
bool right = true;
float r = 256, g = 256, b = 256;


void vprint(int x, int y, void* font, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, str[i]);
}


void drawLine(int x1, int y1, int x2, int y2) {
	glColor3ub(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
void circle(int x, int y, int r) {
	float angle;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}



void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
	glColor3f(r, g, b);
	glRectf(x, y, x + width, y + height);
}

void drawCar(float x, float y, float r, float g, float b) {



	//CAR BODY
	glColor3b(r, g, b);
	glBegin(GL_QUADS);
	glVertex2f(x - 40, y - 20);
	glVertex2f(x + 40, y - 20);
	glVertex2f(x + 40, y - 40);
	glVertex2f(x - 40, y - 40);
	glEnd();


	//Lights
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(x + 30, y - 20);
	glVertex2f(x + 40, y - 20);
	glVertex2f(x + 40, y - 24);
	glVertex2f(x + 30, y - 24);
	glEnd();


	// Draw the car roof
	glColor3b(r, g, b);
	glBegin(GL_QUADS);
	glVertex2f(x - 20, y - 10);
	glVertex2f(x + 20, y - 10);
	glVertex2f(x + 25, y - 20);
	glVertex2f(x - 25, y - 20);
	glEnd();


	//Glass
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex2f(x - 20, y - 20);
	glVertex2f(x + 20, y - 20);
	glVertex2f(x + 15, y - 13);
	glVertex2f(x - 15, y - 13);
	glEnd();

	//Glass Seperator
	drawLine(x, y - 20, x, y - 13);

	//Door handles
	drawLine(x - 15, y - 30, x - 5, y - 30);
	drawLine(x + 5, y - 30, x + 15, y - 30);

	//Wheels
	glColor3f(0, 0, 0);
	circle(x + 25, y - 40, 10);
	circle(x - 25, y - 40, 10);
	glColor3f(1, 1, 1);
	circle(x + 25, y - 40, 5);
	circle(x - 25, y - 40, 5);
	glColor3f(0, 0, 0);
	circle(x - 25, y - 40, 2);
	circle(x + 25, y - 40, 2);

}


void drawWall() {
	drawRectangle(0.0f, 0.0f, WIN_W, WIN_H, 0.8f, 0.8f, 0.8f);

	for (int i = 20;i < WIN_W; i += 40) {
		drawRectangle(i, 0, 20, WIN_H, 1.0f, 0.99f, 0.82f);
	}
}
void drawWindow() {
	float windowWidth = 400,
		windowHeight = 300;

	float windowX = (WIN_W - windowWidth) / 2,
		windowY = (WIN_H - windowHeight) / 2;

	drawRectangle(windowX, windowY, windowWidth, windowHeight, 0.6f, 0.4f, 0.2f);

	float skyX = windowX + thickness,
		skyY = windowY + thickness,
		skyWidth = windowWidth - thickness * 2,
		skyHeight = windowHeight - thickness * 2;

	float roadx = skyX,
		roady = skyY,
		roadWidth = skyWidth,
		roadHeight = skyHeight / 2;

	float grassx = roadx,
		grassy = roady,
		grassWidth = roadWidth,
		grassHeight = roadHeight / 2;

	drawRectangle(skyX, skyY, skyWidth, skyHeight, 0, 0, 0);	 //black sky
	drawRectangle(roadx, roady, roadWidth, roadHeight, 0.5f, 0.5f, 0.5f);
	drawRectangle(grassx, grassy, grassWidth, grassHeight, 0, 1, 0);
	for (int i = roadx;i < roadWidth + roadx;i += 30) {
		drawRectangle(i, roady + (roadHeight - grassHeight) + 20, 20, 5, 0, 0, 0);
	}

	float separatorWidth = 10,
		separatorHeight = skyHeight,
		seperatorx = skyX + skyWidth / 2 - separatorWidth / 2,
		seperatory = skyY;
	drawRectangle(seperatorx, seperatory, separatorWidth, separatorHeight, 0.6f, 0.4f, 0.2f);


	carstart = windowX;
}
void DrawClouds(int x, int y) {
	int r = 20;

	x = x - 100;

	glColor3f(1, 1, 1);
	circle(x, y, r);
	circle(x + r, y, r);
	circle(x + r * 2, y, r);


	glColor3f(1, 1, 1);
	circle(x + 150, y - 50, r - 7);
	circle(x + 150 + r, y - 50, r - 7);
	circle(x + 150 + r * 2, y - 50, r - 10);

	glColor3f(1, 1, 1);
	circle(x + 250, y - 27, r - 12);
	circle(x + 250 + r, y - 27, r - 5);
	circle(x + 250 + r * 2, y - 27, r - 5);

}
void drawMoon(int x, int y) {
	glColor3f(0.4f, 0.4f, 0.4f); // Koyu Gri
	circle(x, y, 21);

	glColor3f(0.8f, 0.8f, 0.8f); // Parlak Gri
	circle(x + 5, y + 5, 10);
}
void drawLabel(float x, float y, float w, float h) {
	glColor3f(1.0, 1.0, 1.0); // White fill
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); // Black border
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();

	drawLine(x, y + h, x + w / 2, y + h + 20);
	drawLine(x + w, y + h, x + w / 2, y + h + 20);

	circle(x + w / 2, y + h + 20, 7);
}
void drawMasking() {/*

	This function is for masking.
	Masking is to put another frame to make the object invisible by the user.
	I have put the wall pattern again before and after the window.
*/
//for wall masking
	for (int i = 0;i < WIN_W / 2 - WIN_W / 2 / 2; i += 40) {
		drawRectangle(i, 0, 20, WIN_H, 1.0f, 0.99f, 0.82f);
		drawRectangle(i + 20, 0, 20, WIN_H, 0.8f, 0.8f, 0.8f);
	}
	for (int i = WIN_W / 2 + WIN_W / 2 / 2;i < WIN_W; i += 40) {
		drawRectangle(i, 0, 20, WIN_H, 1.0f, 0.99f, 0.82f);
		drawRectangle(i + 20, 0, 20, WIN_H, 0.8f, 0.8f, 0.8f);
	}
	//for window wood seperators masking

	drawRectangle(WIN_W / 4, WIN_H / 4, thickness, WIN_H / 2, 0.6f, 0.4f, 0.2f);
	drawRectangle(WIN_W / 4 + WIN_W / 4 - thickness / 2, WIN_H / 4, thickness, WIN_H / 2, 0.6f, 0.4f, 0.2f);
	drawRectangle(WIN_W / 4 + WIN_W / 2 - thickness, WIN_H / 4, thickness, WIN_H / 2, 0.6f, 0.4f, 0.2f);


	glColor3b(0, 0, 0);
	circle(WIN_W / 4 + WIN_W / 4, WIN_H / 2, 7);

	glColor3f(0.8f, 0.8f, 0.8f);
	circle(WIN_W / 4 + WIN_W / 4, WIN_H / 2, 5);

}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawWall();
	drawWindow();
	drawLabel(WIN_W / 2 - 325 / 2, WIN_H - 100, 325, 50);
	drawMoon(WIN_W / 2 - 150, 387);
	DrawClouds(cloudsX, 380);
	drawCar(carX, WIN_H / 2, r, g, b);
	drawMasking();

	glColor3f(0, 0, 0);
	vprint(WIN_W / 2 - 325 / 2 + 10, WIN_H - 100 + 25, GLUT_BITMAP_9_BY_15, "Omer Cakir's View through window");


	vprint(WIN_W / 2 - 400 / 2 + 10 - 30, 130, GLUT_BITMAP_9_BY_15, "Press F1 to start the animation.");
	vprint(WIN_W / 2 - 400 / 2 + 10 - 30, 110, GLUT_BITMAP_9_BY_15, "Cloud's speed %.2f : press k(decrease)-l(increase)", cloudSpeed);
	vprint(WIN_W / 2 - 400 / 2 + 10 - 30, 90, GLUT_BITMAP_9_BY_15, "Car's speed %.2f : press n(decrease)-m(increase)", carSpeed);
	vprint(WIN_W / 2 - 400 / 2 + 10 - 30, 70, GLUT_BITMAP_9_BY_15, "Thickness of the window frame %.2f : press o(decrease)-p(increase)", thickness);
	vprint(WIN_W / 2 - 400 / 2 + 10 - 30, 50, GLUT_BITMAP_9_BY_15, "<spacebar> for stop or restart the animation");
	vprint(WIN_W / 2 - 400 / 2 + 10 - 30, 30, GLUT_BITMAP_9_BY_15, "ESC to exit the program.");
	vprint(WIN_W / 2 - 400 / 2 + 10 - 30, 10, GLUT_BITMAP_9_BY_15, "Left Click on each window to set curtain's state.");
	if (!left) {
		drawRectangle(200, 150, 200, 300, 0.36f, 0.25f, 0.20f);

	}
	if (!right) {
		drawRectangle(400, 150, 200, 300, 0.36f, 0.25f, 0.20f);

	}

	glutSwapBuffers();
}
void onTimer(int value) { //ONTIMER


	if (Timer) {
		if (carSpeed < 0) {
			carSpeed = 0;
		}
		if (cloudSpeed < 0) {
			cloudSpeed = 0;
		}
		if (thickness < 0) {
			thickness = 0;
		}
		carX += carSpeed;
		cloudsX += cloudSpeed;

		if (carX > WIN_W / 4 * 3 + 50) {
			carX = WIN_W / 4 - 50;
			r = rand() % 256;
			g = rand() % 256;
			b = rand() % 256;
		}
		if (cloudsX > WIN_W) {
			cloudsX = -1.0f;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(16, onTimer, 0);
}

void onResize(int w, int h) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glViewport(0, 0, WIN_W, WIN_H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIN_W, 0, WIN_H, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void onKeyDown(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);
	}
	else if (key == ' ') {
		Timer = !Timer;
	}
	if (carSpeed < 0) {
		carSpeed = 0;
	}
	if (cloudSpeed < 0) {
		cloudSpeed = 0;
	}
	if (thickness < 0) {
		thickness = 0;
	}
	else if (key == 'n') {
		carSpeed -= 0.5f;
	}
	else if (key == 'm') {
		carSpeed += 0.5f;
	}
	else if (key == 'k') {
		cloudSpeed -= 0.5f;
	}
	else if (key == 'l') {
		cloudSpeed += 0.5f;
	}

	else if (key == 'o') {
		thickness -= 0.5f;
	}
	else if (key == 'p') {
		thickness += 0.5f;
	}
	glutPostRedisplay();
}
void onSpecialKeyDown(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		Timer = !Timer;
	}
}
void onClick(int button, int stat, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
		if (y > 150 && y < 450) {
			if (x > 200 && x < 400) {
				left = !left;
			}
			else if (x > 400 && x < 600) {
				right = !right;
			}
		}

	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {

	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIN_W, WIN_H);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Omer Cakir Car Animation Project");


	glutDisplayFunc(display);
	glutReshapeFunc(onResize);
	glutTimerFunc(16, onTimer, 0);

	//Keyboard events
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	//Mouse events
	glutMouseFunc(onClick);

	glutMainLoop();

	return 0;
}
