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

//箱
typedef struct Stage {
	float stageSize[3];
	float e;
}Stage;
//Stageの設定
void setStage(float *size, float e, Stage *stage);
//Stageの描写
void drawStage(Stage stage);

typedef struct flatWall {
	float w_cood[2][3];
	float e;
	float w_center[3];
	float w_length;
	float w_phi;
}flatWall;
//flatWallの初期設定
void setFlatWall(float *s_cood, float *e_cood, float e, flatWall *wall);
//flatWallの描画
void drawFlatWall(flatWall wall);

//ボール
typedef struct Ball {
	float b_cood[3];//ボールの座標
	float b_diag;//ボールの半径
	float b_mass;//ボールの質量
	float b_speed[3];//ボールの速度
	float b_nxtcood[3];//ボールの遷移後の座標
}Ball;

//for test
float collision(float cood, float range, int param, flatWall wall);

//for reflection
float refSpeed(float b_cood, float b_speed, float *range, float e);
float refCood(float b_cood, float b_speed, float *range, float e);
//Ballの初期設定
void setBall(float *cood, float diag, float mass, float *speed, float *nxtcood, Ball *ball);
//Ballの遷移
void updateBall(float *view, Ball *ball, Stage stage);
//Ballの描画
void drawBall(Ball ball);


//壁
typedef struct Wall {
	float w_cood[2][3];
	float e;
	float center[3];
	float length[3];
}Wall;
//Wallの初期設定
void setWall(float *s_cood, float *e_cood,float e, Wall *wall);
//Wallの遷移
void stepWall(Wall *wall);
//Wallの描画
void drawWall(Wall wall);



