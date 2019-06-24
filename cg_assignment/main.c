#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "myObject.h"
#include "myUtility.h"

#define KEY_ESC 27
#define TICK	1.0e-3						/* 1msec�̃T���v�����O�^�C�� */

//���_�ݒ�p�p�����[�^
float distance = 50.0;
float twist = 0.0;
float elevation = 0.0;
float azimuth = 0.0;
//���_�̐ݒ�
void polarview() {
	glTranslatef(0.0, 0.0, -distance);
	glRotatef(-elevation, 1.0, 0.0, 0.0);//x���ɑ΂���p�x
	glRotatef(-twist, 0.0, 0.0, 1.0);//z���ɑ΂���p�x
	glRotatef(-azimuth, 0.0, 1.0, 0.0);//y���ɑ΂���p�x
}

//���_�p���̏�����
void resetview() {
	distance = 50.0;
	twist = 0.0;
	elevation = 0.0;
	azimuth = 0;
}

int xBegin, yBegin;
int mButton;


void setShade(float *diffuse, float *specular, float *ambient, float shininess) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess); 
}

Stage stage;
flatWall wall;
Ball ball;
flatWall wall;

void setWalls() {
	float s_cood[] = { -10.0,0.0,0.0 };
	float e_cood[] = { 10.0,0.0,0.0 };
	float e = 1.0;
	setFlatWall(s_cood, e_cood, e, &wall);
}

void setWorld() {
	float stageSize[] = { 20.0,20.0,2.0 };
	float startCood[] = { 0.0,0.0,0.0 };
	float startSpeed[] = { 0.0,0.0,0.0 };

	setStage(stageSize, 0.6, &stage);
	setWalls();
	setBall(startCood, 1.0, 1.0, startSpeed, startCood, &ball);
}

void resetWorld() {
	setWorld();
}

void drawWorld() {
	float view[] = { 0.0,0.0,0.0 };
	getView(distance, elevation, azimuth, view);
	drawStage(stage);
	drawFlatWall(wall);
	for (int i = 0; i < 30; i++) {
		updateBall(view, &ball, stage);
	}
	drawBall(ball);
}

void display(void)
{
	float diffuse[] = { 0.0,0.5,1.0,1.0 };
	float specular[] = { 0.8,0.8,0.8,1.0 };
	float ambient[] = { 0.1,0.1,0.1,1.0 };
	float shininess = 128.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	polarview(20.0, 0.0, 0.0, 0.0);//���_
	glEnable(GL_DEPTH_TEST);

	setShade(diffuse, specular, ambient, shininess);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	//���m��u����
	drawWorld();

	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glPopMatrix();

	glutSwapBuffers();
}


void idle(void) {
	glutPostRedisplay();
}

void myKbd(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'R':
		resetview();
		resetWorld();
		break;
	case KEY_ESC:
		exit(0);
	}
	glutPostRedisplay();
}

void mySkey(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_F1:
		break;
	}
	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			mButton = button;
			break;
		case GLUT_RIGHT_BUTTON:
			mButton = button;
			break;
		}
		xBegin = x;
		yBegin = y;
	}
}

float viewRange(float min, float max, float target, float addition) {
	if (min < (target + addition) && (target + addition) < max)
		return target + addition;
	else
		return target;
}

void myViewMotion(int mx, int my, int button) {
	int xDisp, yDisp;
	xDisp = mx - xBegin;
	yDisp = my - yBegin;

	switch (mButton)
	{
	case GLUT_LEFT_BUTTON:
		azimuth = viewRange(-45.0, 45.0, azimuth, (float)xDisp / 2.0);
		elevation = viewRange(-45.0, 45.0, elevation, (float)yDisp / 2.0);
		break;
	case GLUT_RIGHT_BUTTON:
		distance += (float)yDisp / 40.0;
		break;
	}
}

void myMotion(int mx, int my) {

	myViewMotion(mx, my, mButton);

	xBegin = mx;
	yBegin = my;
	glutPostRedisplay();
}

void myInit(char *progname)
{
	int width = 600, height = 600;
	float aspect = (float)width / (float)height;
	int setWindowX = (glutGet(GLUT_SCREEN_WIDTH) / 2) - (width / 2);
	int setWindowY = (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (height / 2);
	glutInitWindowPosition(setWindowX, setWindowY);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutKeyboardFunc(myKbd);
	glutSpecialFunc(mySkey);

	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, aspect, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHT0);

	setWorld();
}

void myReshape(int width, int height) {
	float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, aspect, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int value)						/* �^�C�}�p�@�R�[���o�b�N�֐� */
{
	if (value == 1) {							/* �ԍ��P�̃^�C�}�� */
		glutTimerFunc(30, timer, 1);			/* �^�C�}�̍ċN�� */
		glutPostRedisplay();				/* �\�� */
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutTimerFunc(30, timer, 1);
	glutIdleFunc(idle);
	glutMainLoop();
	return(0);
}
