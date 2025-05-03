/*
OMER CAKIR
22302695
CTIS164-003 (SECTION 3)
My second game using GLUT library
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265358
#define D2R 0.01745329252 // degree to radian
#define WIN_W 800
#define WIN_H 600
#define BALLOON_COUNT 5
#define RADIUS 35


bool Started = false;

float balloonX[BALLOON_COUNT];
float balloonY[BALLOON_COUNT];

float aimX = 130, aimY = WIN_H / 2;
float r[BALLOON_COUNT], g[BALLOON_COUNT], b[BALLOON_COUNT];
bool hasCrossedLine[BALLOON_COUNT] = { false };
float distances[BALLOON_COUNT] = { 0 };
int missedBalloonCount = 0;

float remainingTime = 20;
int totalBalloons = 0;
int poppedBalloons = 0;
int lastPoints = 0;
int totalPoints = 0;

float knifeX;
float knifeY;
float throwSpeed = 18;
float balloonSpeed = 4.f;
bool Timer = false;
bool up = false, down = false;
bool fire = false;

float aimSpeed = 20.f;

void vprint(int x, int y, void* font, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
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

void drawBackGround() {
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.0, 0.1);
	glVertex2f(0, WIN_H);
	glVertex2f(WIN_W, WIN_H);

	glColor3f(0.95, 0.75, 0.1);
	glVertex2f(WIN_W, 0);
	glVertex2f(0, 0);
	glEnd();
}

void drawScoreBoard() {
	drawRectangle(0, 0, 130, WIN_H, 0, 0, 0);
	drawRectangle(0, WIN_H - 40, WIN_W, 40, 0.2f, 0.2f, 0.2f);
}

void drawBalloon(int x, int y, double r, double g, double b) {
	drawLine(x, y, x, y - RADIUS * 2);

	glColor3f(r, g, b);
	circle(x, y, RADIUS);

	glColor3f(r + 0.5, g + 0.5, b + 0.5);
	circle(x + 5, y + 5, RADIUS / 2);

}
void drawBalloon2(float x, float y, double r, double g, double b) {

	glColor3f(0.2f, 0.2f, 0.2f);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 10; ++i) {
		float dx = sin(i * 0.6f) * 3;
		float dy = -i * 5;
		glVertex2f(x + dx, y + dy - 20);
	}


	glEnd();

	glColor3f(r, g, b);

	circle(x, y, RADIUS);


	glColor4f(1, 1, 1, 0.3f);
	circle(x - 6, y + 6, RADIUS / 2);


}


void drawKnife(float x, float y) {
	float bladeLength = 50;
	float bladeHeight = 6;
	float handleLength = 25;
	float handleHeight = 10;
	glColor3f(0.8f, 0.8f, 0.85f);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + bladeLength, y + bladeHeight / 2);
	glVertex2f(x + bladeLength, y - bladeHeight / 2);
	glVertex2f(x, y);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(x + bladeLength, y + bladeHeight / 2);
	glVertex2f(x + bladeLength + 8, y);
	glVertex2f(x + bladeLength, y - bladeHeight / 2);
	glEnd();

	glColor3f(0.4f, 0.2f, 0.1f);
	glBegin(GL_POLYGON);
	glVertex2f(x - handleLength + 25, y + handleHeight / 2);
	glVertex2f(x + 25, y + handleHeight / 2);
	glVertex2f(x + 25, y - handleHeight / 2);
	glVertex2f(x - handleLength + 25, y - handleHeight / 2);
	glEnd();

	glColor3f(0.4f, 0.2f, 0.1f);
	glBegin(GL_POLYGON);
	glVertex2f(x + 20, y + handleHeight + 10 / 2);
	glVertex2f(x + 25, y + handleHeight + 10 / 2);
	glVertex2f(x + 25, y - handleHeight - 10 / 2);
	glVertex2f(x + 20, y - handleHeight - 10 / 2);
	glEnd();
}


void drawHand(float x, float y, float scale) {
	glColor3f(1, 0.8, 0.6);

	circle(x, y + 4, 25 * scale);


	float fingerDistance = 15 * scale;
	for (int i = -2; i <= 2; i++) {
		circle(x + i * fingerDistance, y + 35 * scale, 8 * scale);
	}


	circle(x - 30 * scale, y + 10 * scale, 8 * scale);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawBackGround();
	drawScoreBoard();
	drawKnife(aimX, aimY);
	drawHand(aimX + 5, aimY - 10, 0.5f);
	drawKnife(knifeX, knifeY);
	if (Timer) {
		if (fire) {

			knifeY -= throwSpeed / 6;
			knifeX += throwSpeed;
		}
		else {

			knifeY = aimY;
		}
	}

	if (remainingTime > 0) {
		for (int i = 0; i < BALLOON_COUNT; i++) {
			drawBalloon2(balloonX[i], balloonY[i], r[i], g[i], b[i]);
		}
	}
	else {
		for (int i = 0; i < BALLOON_COUNT; i++) {
			balloonX[i] = rand() % (WIN_W - 300) + 350;
			balloonY[i] = -rand() % WIN_H - 100;
			drawBalloon2(balloonX[i], balloonY[i], r[i], g[i], b[i]);
		}
	}
	drawScoreBoard();

	glColor3f(1, 1, 1);
	if (!Started) {
		vprint(WIN_W / 2 - 400 / 2 + 10 - 30, WIN_H - 20, GLUT_BITMAP_9_BY_15, "Press F1 to start a new game.");
	}
	else {
		if (!Timer) {

			vprint(WIN_W / 2 - 400 / 2 + 10 - 30, WIN_H - 20, GLUT_BITMAP_9_BY_15, "Press F1 to resume the game.");
		}
		else {

			vprint(10, WIN_H - 20, GLUT_BITMAP_9_BY_15, "<Spacebar> FIRE,<F1> Pause/Restart, UP-DOWN(or W and S) to adjust aim, <ESC> to exit");
		}
	}
	vprint(20, WIN_H - 80, GLUT_BITMAP_9_BY_15, "REMAINING");
	vprint(20, WIN_H - 95, GLUT_BITMAP_9_BY_15, "TIME");
	if (remainingTime > 10) {
		glColor3f(0, 1, 0);
	}
	else {
		glColor3f(1, 0, 0);
	}
	vprint(20, WIN_H - 120, GLUT_BITMAP_HELVETICA_18, "%.2f", remainingTime);

	glColor3f(1, 1, 1);


	vprint(20, WIN_H - 180, GLUT_BITMAP_9_BY_15, "TOTAL");
	vprint(20, WIN_H - 195, GLUT_BITMAP_9_BY_15, "BALLOONS");
	vprint(20, WIN_H - 220, GLUT_BITMAP_HELVETICA_18, "%d", totalBalloons);


	vprint(20, WIN_H - 280, GLUT_BITMAP_9_BY_15, "POPPED");
	vprint(20, WIN_H - 295, GLUT_BITMAP_9_BY_15, "BALLOONS");
	vprint(20, WIN_H - 320, GLUT_BITMAP_HELVETICA_18, "%d", poppedBalloons);


	vprint(20, WIN_H - 380, GLUT_BITMAP_9_BY_15, "LAST");
	vprint(20, WIN_H - 395, GLUT_BITMAP_9_BY_15, "POINTS");
	vprint(20, WIN_H - 420, GLUT_BITMAP_HELVETICA_18, "%d", lastPoints);


	vprint(20, WIN_H - 480, GLUT_BITMAP_9_BY_15, "TOTAL");
	vprint(20, WIN_H - 495, GLUT_BITMAP_9_BY_15, "POINTS");
	glColor3f(0, 1, 0);
	vprint(20, WIN_H - 520, GLUT_BITMAP_HELVETICA_18, "%d", totalPoints);


	if (remainingTime == 0) {
		Started = false;
		glColor3f(0, 0, 0);
		vprint(WIN_W / 2, WIN_H - 235, GLUT_BITMAP_HELVETICA_18, "THE GAME");
		vprint(WIN_W / 2 + 35, WIN_H - 250, GLUT_BITMAP_HELVETICA_18, "IS");
		vprint(WIN_W / 2 + 35 / 2, WIN_H - 265, GLUT_BITMAP_HELVETICA_18, "OVER!");
	}

	glutSwapBuffers();
}

void onTimer(int value)
{

	if (knifeX > WIN_W) {
		fire = false;
		knifeX = aimX;
	}
	if (remainingTime < 0) {
		Timer = !Timer;
		remainingTime = 0;
	}
	if (Timer) {
		if (aimY > 40 && aimY < WIN_H - 100) {

			if (up) {
				aimY += aimSpeed;
				up = !up;
			}
			else if (down) {
				aimY -= aimSpeed;
				down = !down;
			}
		}
		else {
			if (aimY <= 40) {

				aimY += 1;
				printf("if\n");
			}
			else {

				printf("else\n");
				aimY -= 1;
			}
		}

		remainingTime -= 1.f / 60.f;
		for (int i = 0; i < BALLOON_COUNT; i++) {
			distances[i] = sqrtf(pow(knifeX + 50 - balloonX[i], 2) + pow(knifeY - balloonY[i], 2));
			if (distances[i] < RADIUS) {
				lastPoints = knifeX * 3 / 100;
				totalPoints += lastPoints;
				poppedBalloons += 1;
			}
			if (balloonY[i] < WIN_H && distances[i] > RADIUS) {
				balloonY[i] += balloonSpeed;
				if (hasCrossedLine[i] == false && balloonY[i] > -50) {
					hasCrossedLine[i] = true;
					totalBalloons += 1;

				}
			}
			else {
				balloonX[i] = rand() % (WIN_W / 2) + WIN_W / 2 - RADIUS;
				balloonY[i] = -20;
				r[i] = rand() % 159 * 0.01;
				g[i] = rand() % 159 * 0.01;
				b[i] = rand() % 159 * 0.01;
				hasCrossedLine[i] = false;
			}
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
	else if (key == ' ')
	{
		if (Timer) {
			fire = true;

		}
	}
	glutPostRedisplay();
}

void onSpecialKeyDown(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		if (!Started) {
			Started = true;
			remainingTime = 20;
			totalBalloons = 0;
			poppedBalloons = 0;
			lastPoints = 0;
			totalPoints = 0;
		}
		Timer = !Timer;

	}
	else if (key == GLUT_KEY_UP) {
		up = !up;
	}
	else if (key == GLUT_KEY_DOWN) {
		down = !down;

	}
}

void onClick(int button, int stat, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
		// Placeholder for future interaction
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	srand(time(NULL));

	for (int i = 0; i < BALLOON_COUNT; i++) {
		balloonX[i] = rand() % (WIN_W / 2) + WIN_W / 2 - RADIUS;
		balloonY[i] = -(rand() % 300) - 100;
		r[i] = rand() % 159 * 0.01;
		g[i] = rand() % 159 * 0.01;
		b[i] = rand() % 159 * 0.01;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("Omer Cakir's Hit The Balloons Game");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);
	glutTimerFunc(16, onTimer, 0);

	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);
	glutMouseFunc(onClick);

	glutMainLoop();
	return 0;
}
