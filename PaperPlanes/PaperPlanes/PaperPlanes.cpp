#pragma warning (disable:4996)     // (or others, depending on the system in use)
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <GL/glut.h>
#include <Windows.h>

#define WHITE_A 1.0,1.0,1.0,1.0

#define	PINK_AMBIENT				1.0,0.5,0.5,1.0
#define	PINK_DIFFUSE				1.0,0.5,0.5,1.0
#define	PINK_SPECULAR				1.0,0.5,0.5,1.0
#define	PINK_SHININESS				30.0
#define	BLACK_AMBIENT				0,0,0,1.0
#define	BLACK_DIFFUSE				0,0,0,1.0
#define	BLACK_SPECULAR				0,0,0,1.0
#define	BLACK_SHININESS				0

#define M_PI 3.14159

using namespace std;

void introscreen();

bool folding = false;
bool unfolding = true;
bool moving = false;
bool finish = false;
int fold1, fold2, fold3, fold4, fold5, fold6, fold7, fold8 = 0;
int step = 1;
float Size = 1.2;
float all, all2, all3, all4, turn, Move = 0;
//int wrong = 1;

// WCS volume limit
float Left = -3.0;
float Right = 3.0;
float bottom = -3.0;
float top = 3.0;
float znear = -100;
float zfar = 100;

// RCS for window  limit
int win_width = 640;
int win_height = 480;
float win_position_x = 0;
float win_position_y = 0;

// mouse position start
float xstart = 0;
float ystart = 0;

//void material() {
//	float mat_ambient[] = { GOLD_AMBIENT };
//	float mat_diffuse[] = { GOLD_DIFFUSE };
//	float mat_specular[] = { GOLD_SPECULAR };
//	float mat_shininess = GOLD_SHININESS;
//	/* define material proerties for front face of all polygons */
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
//}

//void material2() {
//	float mat_ambient[] = { JADE_AMBIENT };
//	float mat_diffuse[] = { JADE_DIFFUSE };
//	float mat_specular[] = { JADE_SPECULAR };
//	float mat_shininess = JADE_SHININESS;
//
//	/* define material proerties for front face of all polygons */
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
//}

void material() {
	float mat_ambient[] = { PINK_AMBIENT };
	float mat_diffuse[] = { PINK_DIFFUSE };
	float mat_specular[] = { PINK_SPECULAR };
	float mat_shininess = PINK_SHININESS;
	/* define material proerties for front face of all polygons */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void material1() {
	float mat_ambient[] = { BLACK_AMBIENT };
	float mat_diffuse[] = { BLACK_DIFFUSE };
	float mat_specular[] = { BLACK_SPECULAR };
	float mat_shininess = BLACK_SHININESS;
	/* define material proerties for front face of all polygons */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void setLightPos() {
	GLfloat light0_pos[4] = { 0.9F, 0.9F, 2.5F, 1.0F };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
}


void lighting() {
	float light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	setLightPos();
}


void userSettings(void) {
	lighting();
	//material();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
}

void motion(int x, int y) {
	float aspect = (float)640 / 480;
	//glRotatef(all2, ((x - xstart)*Right / (float)win_width)/5, ((win_height - y - ystart)*top / (float)win_height)/5, 0);
	//all3 = x*Right/(float)win_width+x;
	//all2 = y*top/(float)win_height+y;
	all2 = ((y*aspect) / 2) + 50;
	all3 = ((x*aspect) / 2) - 170;
	all4 = 1;
	xstart = x;
	ystart = win_height - y;
	//printf("motion x=%3.3f, y=%3.3f\n", xstart, ystart);
	printf("motion x=%3.3f, y=%3.3f\n", all2, all3);
	glutPostRedisplay();
}


void init(void) {
	glClearColor(WHITE_A);                 // Set display-window color to white.

	glMatrixMode(GL_PROJECTION);           // Set projection parameters.
	glLoadIdentity();
	glOrtho(Left, Right, bottom, top, znear, zfar);
}


void poly1() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, 0, 0);
	glVertex3f(-1, -0.2, 0);
	glEnd();
}

void poly2() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, -0.2, 0);
	glVertex3f(-1, -0.42, 0);
	glEnd();
}

void poly3() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, -0.42, 0);
	glVertex3f(-1, -0.675, 0);
	glEnd();
}

void poly4() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, -0.675, 0);
	glVertex3f(-1, -1, 0);
	glEnd();
}

void poly5() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(-1, -1.48, 0);
	glEnd();
}

void poly6() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, -1.48, 0);
	glVertex3f(-1, -2.4, 0);
	glEnd();
}

void poly7() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, -2.4, 0);
	glVertex3f(-1, -2.855, 0);
	glVertex3f(-0.57, -2.855, 0);
	glEnd();
}

void poly8() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-0.57, -2.855, 0);
	glVertex3f(0, -2.855, 0);
	glEnd();
}

void poly9() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -2.855, 0);
	glVertex3f(0.57, -2.855, 0);
	glEnd();
}

void poly10() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0.57, -2.855, 0);
	glVertex3f(1, -2.855, 0);
	glVertex3f(1, -2.4, 0);
	glEnd();
}

void poly11() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1, -2.4, 0);
	glVertex3f(1, -1.48, 0);
	glEnd();
}

void poly12() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1, -1.48, 0);
	glVertex3f(1, -1, 0);
	glEnd();
}

void poly13() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(1, -0.675, 0);
	glEnd();
}

void poly14() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1, -0.675, 0);
	glVertex3f(1, -0.42, 0);
	glEnd();
}

void poly15() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1, -0.42, 0);
	glVertex3f(1, -0.2, 0);
	glEnd();
}

void poly16() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1, -0.2, 0);
	glVertex3f(1, 0, 0);
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	material1();
	introscreen();
	glScalef(Size, Size, Size);
	glTranslatef(-0.7, 1.5, 0);
	glTranslatef(0, -1.4275, 0);
	glRotatef(all3, 0, 1, 0);
	glRotatef(all2, 1, 0, 0);
	glRotatef(all4, 0, 0, 1);
	glRotatef(turn, 0, 0, 1);
	glTranslatef(0, 1.4275, 0);
	glTranslatef(0, Move, 0);

	material();
	glPushMatrix();
	glRotatef(fold5, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0);
	glRotatef(fold1, 1, 1, 0);
	glTranslatef(0.5, 0.5, 0);
	poly1();
	glPushMatrix();
	glTranslatef(-0.5, -0.1, 0);
	glRotatef(fold7, 1, 0.2, 0);
	glTranslatef(0.5, 0.1, 0);
	poly2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5, -0.21, 0);
	glRotatef(fold3, 1, 0.42, 0);
	glTranslatef(0.5, 0.21, 0);
	poly4();
	glPushMatrix();
	glTranslatef(-0.5, -0.3375, 0);
	glRotatef(fold7, 1, 0.675, 0);
	glTranslatef(0.5, 0.3375, 0);
	poly3();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5, -1.2, 0);
	glRotatef(fold3, 1, 2.4, 0);
	glTranslatef(0.5, 1.2, 0);
	poly5();
	glPushMatrix();
	glTranslatef(-0.5, -0.74, 0);
	glRotatef(fold7, 1, 1.48, 0);
	glTranslatef(0.5, 0.74, 0);
	poly6();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.285, -1.4275, 0);
	glRotatef(fold7, 0.57, 2.855, 0);
	glTranslatef(0.285, 1.4275, 0);
	poly7();
	glPopMatrix();
	poly8();
	glPopMatrix();

	glPushMatrix();
	glRotatef(fold6, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0.5, -0.5, 0);
	glRotatef(fold2, -1, 1, 0);
	glTranslatef(-0.5, 0.5, 0);
	poly16();
	glPushMatrix();
	glTranslatef(0.5, -0.1, 0);
	glRotatef(fold8, -1, 0.2, 0);
	glTranslatef(-0.5, 0.1, 0);
	poly15();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5, -0.21, 0);
	glRotatef(fold4, -1, 0.42, 0);
	glTranslatef(-0.5, 0.21, 0);
	poly13();
	glPushMatrix();
	glTranslatef(0.5, -0.3375, 0);
	glRotatef(fold8, -1, 0.675, 0);
	glTranslatef(-0.5, 0.3375, 0);
	poly14();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5, -1.2, 0);
	glRotatef(fold4, -1, 2.4, 0);
	glTranslatef(-0.5, 1.2, 0);
	poly12();
	glPushMatrix();
	glTranslatef(0.5, -0.74, 0);
	glRotatef(fold8, -1, 1.48, 0);
	glTranslatef(-0.5, 0.74, 0);
	poly11();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.285, -1.4275, 0);
	glRotatef(fold8, -0.57, 2.855, 0);
	glTranslatef(-0.285, 1.4275, 0);
	poly10();
	glPopMatrix();
	poly9();
	glPopMatrix();
	glPopMatrix();

	glFlush();     // Process all OpenGL routines as quickly as possible.
	glutSwapBuffers();
	glMatrixMode(GL_PROJECTION);
}

void renderbitmap(float x, float y, void *font, char *string) {
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void introscreen() {
	glColor3f(0, 0, 0);
	char buf[100] = { 0 };
	sprintf_s(buf, "PAPER PLANE control guide");
	renderbitmap(1.3, 1.3, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "Fold & Unfold: press 'Spacebar'");
	renderbitmap(1.3, 0.9, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "Rotate: press 'Left Click' & drag");
	renderbitmap(1.3, 0.7, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "Throw: press '1'");
	renderbitmap(1.3, 0.5, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "Reset Object: press '0'");
	renderbitmap(1.3, 0.1, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "Zoom in: press '+'");
	renderbitmap(1.3, -0.3, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "Zoom out: press '-'");
	renderbitmap(1.3, -0.5, GLUT_BITMAP_HELVETICA_12, buf);
}


void reshape(int w, int h) {
	float aspect = (float)w / h; //aspect>1 = w>h , aspect<1 = w<h
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (aspect >= 1.0) {
		glOrtho(Left*aspect, Right*aspect, bottom, top, znear, zfar);
	}
	else {
		glOrtho(Left, Right, bottom / aspect, top / aspect, znear, zfar);
	}
	glutPostRedisplay();
}

void keyboard(unsigned char c, int w, int h) {
	switch (c) {
	case '0':
		Size = 1.2;
		fold1 = 0;
		fold2 = 0;
		fold3 = 0;
		fold4 = 0;
		fold5 = 0;
		fold6 = 0;
		fold7 = 0;
		fold8 = 0;
		Move = 0;
		all = 0;
		all2 = 0;
		all3 = 0;
		moving = false;
		folding = false;
		unfolding = true;
		finish = false;
		step = 1;
		break;
	case '1':
		if (!moving && finish)
			moving = true;
		else
			moving = false;
		break;
	case '+':
		if (Size < 1.8)
			Size += 0.1;
		break;
	case '-':
		if (Size > 0.8)
			Size -= 0.1;
		break;
	case ' ':
		if (unfolding) {
			folding = true;
			unfolding = false;
		}
		else {
			folding = false;
			unfolding = true;
		}
		break;
	}
	glutPostRedisplay();
}


void idle() {
	if (folding) {
		if (fold1 < 179 && step == 1)
		{
			fold1++;
			if (fold1 == 179)
				step = 2;
		}
		if (fold2 > -178 && step == 2)
		{
			fold2--;
			if (fold2 == -178)
				step = 3;
		}
		if (fold3 < 179 && step == 3)
		{
			fold3++;
			if (fold3 == 179)
				step = 4;
		}
		if (fold4 > -179 && step == 4)
		{
			fold4--;
			if (fold4 == -179)
				step = 5;
		}
		if (fold5 < 80 && step == 5)
		{
			fold5++;
			if (fold5 == 80)
				step = 6;
		}
		if (fold6 > -80 && step == 5)
		{
			fold6--;
			if (fold6 == -80)
				step = 6;
		}
		if (fold7 > -90 && step == 6)
		{
			fold7--;
			if (fold7 == -90)
				step = 7;
		}
		if (fold8 < 90 && step == 7)
		{
			fold8++;
			if (fold8 == 90)
				finish = true;
		}
	}
	if (unfolding) {
		finish = false;
		if (fold8 > 0 && step == 7)
		{
			fold8--;
			if (fold8 == 0)
				step = 6;
		}
		if (fold7 < 0 && step == 6)
		{
			fold7++;
			if (fold7 == 0)
				step = 5;
		}
		if (fold6 < 0 && step == 5)
		{
			fold6++;
			if (fold6 == 0)
				step = 4;
		}
		if (fold5 > 0 && step == 5)
		{
			fold5--;
			if (fold5 == 0)
				step = 4;
		}
		if (fold4 < 0 && step == 4)
		{
			fold4++;
			if (fold4 == 0)
				step = 3;
		}
		if (fold3 > 0 && step == 3)
		{
			fold3--;
			if (fold3 == 0)
				step = 2;
		}
		if (fold2 < 0 && step == 2)
		{
			fold2++;
			if (fold2 == 0)
				step = 1;
		}
		if (fold1 > 0 && step == 1)
			fold1--;
	}
	if (moving && finish) {
		Move += 0.009;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	// initializing routine
	FreeConsole();
	glutInit(&argc, argv);                              // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);        // Set display mode.
	glutInitWindowPosition(win_position_x, win_position_y); //Set top-left display-window position.
	glutInitWindowSize(win_width, win_height); // Set display-window width and height.
	glutCreateWindow("365 Days of Paper Airplanes");     // Create display window.
	glEnable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//user initialization routine
	userSettings();
	init();															// user initializing routine
	glutMotionFunc(motion);
	//callback register function
	glutDisplayFunc(display);					// Send graphics to display window.
												//glutMouseFunc(mouse);								// callback for mouse button and position
												//glDepthFunc(GL_LESS);

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutIdleFunc(idle);
	glutMainLoop();										// Loop over registered function
														// Display everything and wait.
}

