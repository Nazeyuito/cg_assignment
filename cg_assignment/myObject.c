#include "myObject.h"

void getView(float distance, float elevation, float azimuth, float *view) {
	view[r] = distance;
	view[theta] = elevation * M_PI / 180;//x²
	view[phi] = -azimuth * M_PI / 180;//y²
}

//Stage‚Ìİ’è
void setStage(double *size, double e, Stage *stage) {
	stage->stageSize[x] = size[x]; stage->stageSize[y] = size[y]; stage->stageSize[z] = size[z];
	stage->e = e;
}
//Stage‚Ì•`Ê
void drawStage(Stage stage) {
	glPushMatrix();
	//floor
	glPushMatrix();
	glTranslatef(0, 0, -((stage.stageSize[z] / 2) + (WALL_WIDTH / 2)));//‰º‚É‰º‚°‚é
	glScalef((stage.stageSize[x] + WALL_WIDTH), (stage.stageSize[y] + WALL_WIDTH), 1.0);//‰¡‚ÉL‚°‚é
	glutSolidCube(WALL_WIDTH);//°‚ğ¶¬
	glPopMatrix();

	//side1(-x)
	glPushMatrix();
	glTranslatef(-(stage.stageSize[x] / 2), 0, 0);//‰¡‚ÉŠñ‚¹‚é
	glScalef(WALL_WIDTH, (stage.stageSize[y] + WALL_WIDTH), stage.stageSize[z]);//‘å‚«‚³‚ğŒˆ’è
	glutSolidCube(WALL_WIDTH);//•Ç‚ğ¶¬
	glPopMatrix();

	//side2(-y)
	glPushMatrix();
	glTranslatef(0, -(stage.stageSize[y] / 2), 0);//‰¡‚ÉŠñ‚¹‚é
	glScalef((stage.stageSize[x] - WALL_WIDTH), WALL_WIDTH, stage.stageSize[z]);//‘å‚«‚³‚ğŒˆ’è
	glutSolidCube(WALL_WIDTH);//•Ç‚ğ¶¬
	glPopMatrix();

	//side3(+x)
	glPushMatrix();
	glTranslatef((stage.stageSize[x] / 2), 0, 0);//‰¡‚ÉŠñ‚¹‚é
	glScalef(WALL_WIDTH, (stage.stageSize[y] + WALL_WIDTH), stage.stageSize[z]);//‘å‚«‚³‚ğŒˆ’è
	glutSolidCube(WALL_WIDTH);//•Ç‚ğ¶¬
	glPopMatrix();

	//side4(+y)
	glPushMatrix();
	glTranslatef(0, (stage.stageSize[y] / 2), 0);//‰¡‚ÉŠñ‚¹‚é
	glScalef((stage.stageSize[x] - WALL_WIDTH), WALL_WIDTH, stage.stageSize[z]);//‘å‚«‚³‚ğŒˆ’è
	glutSolidCube(WALL_WIDTH);//•Ç‚ğ¶¬
	glPopMatrix();

	glPopMatrix();
}

//ƒ{[ƒ‹
//for test
float collision(float cood, float range, int param) {
	//printf("coll");
	switch (param)
	{
	case min:
		if (cood < range)
			return range;
		else
			return cood;
		break;
	case max:
		if (cood > range)
			return range;
		else
			return cood;
		break;
	default:
		break;
	}
	return 0;
}

//for reflection
void reflection(float *ref, float b_cood, float b_speed, float *range, float e) {
	if ((b_cood + b_speed) < range[min]) {
		//printf("min : %3f %3f %3f", b_cood, b_speed, range[min]);
		ref[speed] = -b_speed * e;
		ref[cood] = range[min] - (b_speed*e);
		return;
	}
	else if ((b_cood + b_speed) > range[max]) {
		//printf("max : %3f %3f %3f", b_cood, b_speed, range[max]);
		ref[speed] = -b_speed * e;
		ref[cood] = range[max] - (b_speed*e);
		return;
	}
	else {
		ref[speed] = b_speed;
		ref[cood] = b_cood + b_speed;
	}
	return;
}
//Ball‚Ì‰Šúİ’è
void setBall(double *cood, double diag, double mass, double *speed, double *nxtcood, Ball *ball) {
	ball->b_cood[x] = cood[x]; ball->b_cood[y] = cood[y]; ball->b_cood[z] = cood[z];
	ball->b_diag = diag;
	ball->b_mass = mass;
	ball->b_speed[x] = speed[x]; ball->b_speed[y] = speed[y]; ball->b_speed[z] = speed[z];
	ball->b_nxtcood[x] = nxtcood[x]; ball->b_nxtcood[y] = nxtcood[y]; ball->b_nxtcood[z] = nxtcood[z];
}
//Ball‚Ì‘JˆÚ
void updateBall(float *view, Ball *ball, Stage stage) {
	//ƒ{[ƒ‹‚Ì“®‚¯‚é”ÍˆÍ‚Ìİ’è
	float xRange = (stage.stageSize[x] / 2) - WALL_WIDTH / 2 - ball->b_diag;
	float yRange = (stage.stageSize[y] / 2) - WALL_WIDTH / 2 - ball->b_diag;
	float range[3][2] = { {-xRange,xRange},{-yRange,yRange},{0.0,0.0} };
	//printf("view : %3f, %3f, %3f : ", view[r], view[theta], view[phi]);
	//‘¬“x‚ÌŒˆ’è
	ball->b_speed[x] += G * sin(view[phi]) * 0.001;
	ball->b_speed[y] += G * sin(view[theta]) * 0.001;
	ball->b_speed[z] = 0.0;
	//printf("speed : %3f, %3f, %3f\t", ball->b_speed[x], ball->b_speed[y], ball->b_speed[z]);

	float ref[2] = { 0.0,0.0 };
	reflection(ref, ball->b_cood[x], ball->b_speed[x], range[x], stage.e);
	ball->b_nxtcood[x] = ref[cood]; ball->b_speed[x] = ref[speed];
	reflection(ref, ball->b_cood[y], ball->b_speed[y], range[y], stage.e);
	ball->b_nxtcood[y] = ref[cood]; ball->b_speed[y] = ref[speed];
	reflection(ref, ball->b_cood[z], ball->b_speed[z], range[z], stage.e);
	ball->b_nxtcood[z] = ref[cood]; ball->b_speed[z] = ref[speed];

	ball->b_cood[x] = ball->b_nxtcood[x]; ball->b_cood[y] = ball->b_nxtcood[y]; ball->b_cood[z] = ball->b_nxtcood[z];
	printf("cood : %3f, %3f, %3f", ball->b_cood[x], ball->b_cood[y], ball->b_cood[z]);

	printf("\n");
}
//Ball‚Ì•`‰æ
void drawBall(Ball ball) {
	glPushMatrix();
	glTranslated(ball.b_cood[x], ball.b_cood[y], ball.b_cood[z]);
	glutSolidSphere(ball.b_diag, 20, 20);
	glPopMatrix();
}


//•Ç
//Wall‚Ì‰Šúİ’è
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
//Wall‚Ì‘JˆÚ
void stepWall(Wall *wall) {

}
//Wall‚Ì•`‰æ
void drawWall(Wall wall) {
	glPushMatrix();
	glTranslatef(wall.center[x], wall.center[y], wall.center[z]);//‰¡‚ÉŠñ‚¹‚é
	glScalef(0,0,0);//‘å‚«‚³‚ğŒˆ’è
	glutSolidCube(WALL_WIDTH);//•Ç‚ğ¶¬
	glPopMatrix();
}


//flatWall‚Ì‰Šúİ’è
void setFlatWall(float *s_cood, float *e_cood, float e, flatWall *wall) {
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
	wall->length = dintancePoints(s_cood, e_cood, 3);
}
//flatWall‚Ì•`‰æ
void drawFlatWall(flatWall wall) {
	glPushMatrix();
	glTranslatef(wall.center[x], wall.center[x], wall.center[x]);
	glScalef(0, 0, 0);//‚ ‚é²‚É‚Â‚¢‚Älength‚¾‚¯ˆø‚«‰„‚Î‚·
	glRotatef(0.0, 0.0, 0.0, 0.0);//2“_‚Æ²‚ª‚È‚·Šp‚ğİ’è‚µ‚Ä‰ñ“]
	glutSolidCube(WALL_WIDTH);
	glPopMatrix();
}

