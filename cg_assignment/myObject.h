#pragma once
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "myUtility.h"
#define G 9.80665				
#define M_PI 3.141592653589793238

#define WALL_WIDTH 1.0


enum cartesianCoodParam {
	x, y, z
};

enum polarCoodParam {
	r,theta,phi
};

enum rangeParam {
	min, max
};

enum reflectionParam {
	speed, cood
};

enum wallParam {
	start, end
};

void getView(float distance, float elevation, float azimuth, float *view);

//��
typedef struct Stage {
	float stageSize[3];
	float e;
}Stage;
//Stage�̐ݒ�
void setStage(float *size, float e, Stage *stage);
//Stage�̕`��
void drawStage(Stage stage);

//�{�[��
typedef struct Ball {
	float b_cood[3];//�{�[���̍��W
	float b_diag;//�{�[���̔��a
	float b_mass;//�{�[���̎���
	float b_speed[3];//�{�[���̑��x
	float b_nxtcood[3];//�{�[���̑J�ڌ�̍��W
}Ball;

//for test
float collision(float cood, float range, int param);

//for reflection
void reflection(float *ref, float b_cood, float b_speed, float *range, float e);
//Ball�̏����ݒ�
void setBall(float *cood, float diag, float mass, float *speed, float *nxtcood, Ball *ball);
//Ball�̑J��
void updateBall(float *view, Ball *ball, Stage stage);
//Ball�̕`��
void drawBall(Ball ball);


//��
typedef struct Wall {
	float w_cood[2][3];
	float e;
	float center[3];
	float length[3];
}Wall;
//Wall�̏����ݒ�
void setWall(float *s_cood, float *e_cood,float e, Wall *wall);
//Wall�̑J��
void stepWall(Wall *wall);
//Wall�̕`��
void drawWall(Wall wall);

typedef struct flatWall {
	float w_cood[2][3];
	float e;
	float w_center[3];
	float w_length;
	float w_phi;
}flatWall;
//flatWall�̏����ݒ�
void setFlatWall(float *s_cood, float *e_cood, float e, flatWall *wall);
//flatWall�̕`��
void drawFlatWall(flatWall wall);

