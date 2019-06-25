#include "myObject.h"

void getView(float distance, float elevation, float azimuth, float *view) {
	view[r] = distance;
	view[theta] = elevation * M_PI / 180;//x��
	view[phi] = -azimuth * M_PI / 180;//y��
}

//Stage�̐ݒ�
void setStage(float *size, float e, Stage *stage) {
	stage->stageSize[x] = size[x]; stage->stageSize[y] = size[y]; stage->stageSize[z] = size[z];
	stage->e = e;
}
//Stage��a
void drawStage(Stage stage) {
	glPushMatrix();
	//floor
	glPushMatrix();
	glTranslatef(0, 0, -((stage.stageSize[z] / 2) + (WALL_WIDTH / 2)));//���ɉ�����
	glScalef((stage.stageSize[x] + WALL_WIDTH), (stage.stageSize[y] + WALL_WIDTH), 1.0);//���ɍL����
	glutSolidCube(WALL_WIDTH);//���𐶐�
	glPopMatrix();

	//side1(-x)
	glPushMatrix();
	glTranslatef(-(stage.stageSize[x] / 2), 0, 0);//���Ɋ񂹂�
	glScalef(WALL_WIDTH, (stage.stageSize[y] + WALL_WIDTH), stage.stageSize[z]);//�傫��������
	glutSolidCube(WALL_WIDTH);//�ǂ𐶐�
	glPopMatrix();

	//side2(-y)
	glPushMatrix();
	glTranslatef(0, -(stage.stageSize[y] / 2), 0);//���Ɋ񂹂�
	glScalef((stage.stageSize[x] - WALL_WIDTH), WALL_WIDTH, stage.stageSize[z]);//�傫��������
	glutSolidCube(WALL_WIDTH);//�ǂ𐶐�
	glPopMatrix();

	//side3(+x)
	glPushMatrix();
	glTranslatef((stage.stageSize[x] / 2), 0, 0);//���Ɋ񂹂�
	glScalef(WALL_WIDTH, (stage.stageSize[y] + WALL_WIDTH), stage.stageSize[z]);//�傫��������
	glutSolidCube(WALL_WIDTH);//�ǂ𐶐�
	glPopMatrix();

	//side4(+y)
	glPushMatrix();
	glTranslatef(0, (stage.stageSize[y] / 2), 0);//���Ɋ񂹂�
	glScalef((stage.stageSize[x] - WALL_WIDTH), WALL_WIDTH, stage.stageSize[z]);//�傫��������
	glutSolidCube(WALL_WIDTH);//�ǂ𐶐�
	glPopMatrix();

	glPopMatrix();
}

//�{�[��
//for test
float collision(float cood, float range, int param, flatWall wall) {
	return 0.0;
}

//for reflection
float refSpeed(float b_cood, float b_speed, float *range, float e){
	if ((b_cood + b_speed) < range[min]) {
		//printf("min : %3f %3f %3f", b_cood, b_speed, range[min]);
		 return -b_speed * e;
	}
	else if ((b_cood + b_speed) > range[max]) {
		return -b_speed * e;
	}
	else {
		return b_speed;
	}
	return 0.0;
}

float refCood(float b_cood, float b_speed, float *range, float e){
	if ((b_cood + b_speed) < range[min]) {
		//printf("min : %3f %3f %3f", b_cood, b_speed, range[min]);
		return range[min] - (b_speed*e);
	}
	else if ((b_cood + b_speed) > range[max]) {
		return range[max] - (b_speed*e);
	}
	else {
		return b_cood + b_speed;
	}
	return 0.0;
}

//Ball�̏����ݒ�
void setBall(float *cood, float diag, float mass, float *speed, float*nxtcood, Ball *ball) {
	ball->b_cood[x] = cood[x]; ball->b_cood[y] = cood[y]; ball->b_cood[z] = cood[z];
	ball->b_diag = diag;
	ball->b_mass = mass;
	ball->b_speed[x] = speed[x]; ball->b_speed[y] = speed[y]; ball->b_speed[z] = speed[z];
	ball->b_nxtcood[x] = nxtcood[x]; ball->b_nxtcood[y] = nxtcood[y]; ball->b_nxtcood[z] = nxtcood[z];
}
//Ball�̑J��
void updateBall(float *view, Ball *ball, Stage stage) {
	//�{�[���̓�����͈͂̐ݒ�
	float xRange = (stage.stageSize[x] / 2) - WALL_WIDTH / 2 - ball->b_diag;
	float yRange = (stage.stageSize[y] / 2) - WALL_WIDTH / 2 - ball->b_diag;
	float range[3][2] = { {-xRange,xRange},{-yRange,yRange},{0.0,0.0} };
	//printf("view : %3f, %3f, %3f : ", view[r], view[theta], view[phi]);
	//���x�̌���
	ball->b_speed[x] += G * sin(view[phi]) * 0.00001;
	ball->b_speed[y] += G * sin(view[theta]) * 0.00001;
	ball->b_speed[z] = 0.0;
	//printf("speed : %3f, %3f, %3f\t", ball->b_speed[x], ball->b_speed[y], ball->b_speed[z]);

	for (int i = 0; i < 3; i++) {
		ball->b_nxtcood[i] = refCood(ball->b_cood[i], ball->b_speed[i], range[i], stage.e);
		ball->b_speed[i] = refSpeed(ball->b_cood[i], ball->b_speed[i], range[i], stage.e);
	}

	ball->b_cood[x] = ball->b_nxtcood[x]; ball->b_cood[y] = ball->b_nxtcood[y]; ball->b_cood[z] = ball->b_nxtcood[z];
	//printf("cood : %3f, %3f, %3f", ball->b_cood[x], ball->b_cood[y], ball->b_cood[z]);

	//printf("\n");
}
//Ball�̕`��
void drawBall(Ball ball) {
	glPushMatrix();
	glTranslated(ball.b_cood[x], ball.b_cood[y], ball.b_cood[z]);
	glutSolidSphere(ball.b_diag, 20, 20);
	glPopMatrix();
}


//��
//Wall�̏����ݒ�
void setWall(float *s_cood, float *e_cood, float e, Wall *wall) {
	wall->w_cood[start][x] = s_cood[x];
	wall->w_cood[start][y] = s_cood[y];
	wall->w_cood[start][z] = s_cood[z];
	wall->w_cood[end][x] = e_cood[x];
	wall->w_cood[end][y] = e_cood[y];
	wall->w_cood[end][z] = e_cood[z];
	wall->e = e;
	wall->center[x] = (wall->w_cood[start][x] + wall->w_cood[end][x]) / 2;
	wall->center[y] = (wall->w_cood[start][y] + wall->w_cood[end][y]) / 2;
	wall->center[z] = (wall->w_cood[start][z] + wall->w_cood[end][z]) / 2;
}
//Wall�̑J��
void stepWall(Wall *wall) {

}
//Wall�̕`��
void drawWall(Wall wall) {
	glPushMatrix();
	glTranslatef(wall.center[x], wall.center[y], wall.center[z]);//���Ɋ񂹂�
	glScalef(0,0,0);//�傫��������
	glutSolidCube(WALL_WIDTH);//�ǂ𐶐�
	glPopMatrix();
}


//flatWall�̏����ݒ�
void setFlatWall(float *s_cood, float *e_cood, float e, flatWall *wall) {
	wall->w_cood[start][x] = s_cood[x];
	wall->w_cood[start][y] = s_cood[y];
	wall->w_cood[start][z] = s_cood[z];
	wall->w_cood[end][x] = e_cood[x];
	wall->w_cood[end][y] = e_cood[y];
	wall->w_cood[end][z] = e_cood[z];
	wall->e = e;
	wall->w_center[x] = (wall->w_cood[start][x] + wall->w_cood[end][x]) / 2;
	wall->w_center[y] = (wall->w_cood[start][y] + wall->w_cood[end][y]) / 2;
	wall->w_center[z] = (wall->w_cood[start][z] + wall->w_cood[end][z]) / 2;
	wall->w_length = dintancePoints(s_cood, e_cood, 3);
	wall->w_phi = flatPhi(s_cood, e_cood) * 180 / M_PI;
}
//flatWall�̕`��
void drawFlatWall(flatWall wall) {
	glPushMatrix();
	glTranslatef(wall.w_center[x], wall.w_center[y], wall.w_center[z]);
	//printf("center = (%3f, %3f, %3f)\t",wall.w_center[x], wall.w_center[y], wall.w_center[z]);
	glRotatef(wall.w_phi, 0.0, 0.0, 1.0);//2�_�Ǝ����Ȃ��p��ݒ肵�ĉ�](y)
	//printf("phi = %3f", wall.w_phi);
	glScalef(1.0, wall.w_length, 1.0);//���鎲�ɂ���length�����������΂�
	//printf("length  = %3f", wall.w_length);
	glutSolidCube(WALL_WIDTH);
	glPopMatrix();
	//printf("\n");
}

