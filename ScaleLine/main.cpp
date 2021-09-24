#include "Functions.h"
#include "iostream"
#include <GL/glut.h>
#include <math.h>
#include "stb_easy_font.h"

using namespace std;

int WindW, WindH;
GLfloat speed = 10.0f;
GLfloat real_speed = -10.0f;
GLfloat delta_real_speed = 0.2f;
GLfloat delta_speed = 0.1f;
GLint max_speed = 30;
GLint min_speed = -30;
Point scale;

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	WindW = width;
	WindH = height;
}

void printNumScale() {
	glPushMatrix();
	glScalef(0.01, -0.01, 1);
	string str_0 = to_string(0);
	string str_5 = to_string(5);
	string str_10 = to_string(10);
	string str_30 = to_string(30);
	char* cstr_0 = &str_0[0];
	char* cstr_5 = &str_5[0];
	char* cstr_10 = &str_10[0];
	char* cstr_30 = &str_30[0];
	print_string(-43 + scale.x * 100, -3.5 - scale.y * 100, cstr_0, 1, 1, 1);
	print_string(-41 + scale.x * 100, 8.5 - scale.y * 100, cstr_5, 1, 1, 1);
	print_string(-41 + scale.x * 100, -15.5 - scale.y * 100, cstr_5, 1, 1, 1);
	print_string(-35 + scale.x * 100, 17.5 - scale.y * 100, cstr_10, 1, 1, 1);
	print_string(-35 + scale.x * 100, -24.5 - scale.y * 100, cstr_10, 1, 1, 1);
	print_string(-23 + scale.x * 100, 28.5 - scale.y * 100, cstr_30, 1, 1, 1);
	print_string(-23 + scale.x * 100, -35.5 - scale.y * 100, cstr_30, 1, 1, 1);
	glPopMatrix();
}

void printWhiteSpeed(GLfloat spd) {
	glPushMatrix();
	glScalef(0.01, -0.01, 1);
	if (spd >= 0.0f && spd < 1.0f) {
		spd = 1.0f;
	}
	if (spd <= 0.0f && spd > -1.0f) {
		spd = -1.0f;
	}
	string str = to_string((GLint)spd);
	char* cstr = &str[0];
	print_string(-15 + scale.x * 100, -3.5 - scale.y * 100, cstr, 1, 1, 1);
	glPopMatrix();
}

void printBlueSpeed(GLfloat spd) {
	glPushMatrix();
	glScalef(0.01, -0.01, 1);
	GLint fut_out = 0;
	GLfloat fut = spd * 196.85f;
	GLint div = fut / 50;
	GLint ost = (GLint)fut % 50;
	if (ost >= 25 || spd <= -25) {
		fut_out = div * 50 + 50;
	}
	else {
		fut_out = div * 50;
	}
	string str = to_string(fut_out) + " fpm";
	char* cstr = &str[0];
	print_string(-49 + scale.x * 100, -53.5 - scale.y * 100, cstr, 0, 1, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

void Draw(void)
{
	GLint parts = 50;
	scale = { 0.0f, 0.0f };
	Point white_circle = { -0.15f, 0.0f };
	Point white_rectangle[] = { -0.15f, 0.05f, 0.035f, 0.05f, 0.035f, -0.05f, -0.15f, -0.05f };
	Point blue_rectangle[] = { -0.5f,  0.55f, 0.05f, 0.55f, 0.05f, 0.45f, -0.5f, 0.55f, 0.05f,  0.45f, -0.5f, 0.45f };
	Point white_arrow[] = { -0.43f, 0.02f, -0.3f, 0.02f, -0.3f, -0.02f, -0.43f, 0.02f, -0.3f, -0.02f,
				-0.43f, -0.02f, -0.5f, 0.0f, -0.43f, -0.02f, -0.43f, 0.02f };
	Point blue_arrow[] = { -0.43f, -0.029f, -0.5f, 0.0f, -0.43f, 0.029f };
	GLint num_segments = 100000;
	GLint num_segments_speed = 10000;
	GLfloat r_speed = 0.05f;
	GLint num_seg = 0;
	GLfloat r = 0.5f;
	GLfloat r_scale = 0.05f;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawScale(num_segments, num_segments_speed, r_speed, r, r_scale, scale, parts);
	DrawWhiteSpeed(num_segments_speed, r_speed, white_circle, white_rectangle, scale);
	DrawBlueSpeed(blue_rectangle, scale);

	ArrowRotate(real_speed,scale);
	DrawWhiteArrow(white_arrow, scale);

	ArrowRotate(speed, scale);
	DrawBlueArrow(blue_arrow, scale);

	printNumScale();
	printWhiteSpeed(real_speed);
	printBlueSpeed(real_speed);

	glFlush();
	glutSwapBuffers();
}

void Visibility(int state)
{
	if (state == GLUT_NOT_VISIBLE) cout << "Window not visible!\n";
	if (state == GLUT_VISIBLE) cout << "Window visible!\n";
}

void timf(int value)
{
	glutPostRedisplay();
	if (real_speed >= max_speed) {
		delta_real_speed = -0.2f;
	}
	if (real_speed <= min_speed) {
		delta_real_speed = 0.2f;
	}
	real_speed = real_speed + delta_real_speed;
	if (speed >= max_speed) {
		delta_speed = -0.1f;
	}
	if (speed <= min_speed) {
		delta_speed = 0.1f;
	}
	speed = speed + delta_speed;
	glutTimerFunc(50, timf, 0);
}

int main(int argc, char* argv[])
{
    WindW = 750;
    WindH = 750;

    glutInit(&argc, argv);
    glutInitWindowSize(WindW, WindH);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    (void)glutCreateWindow("Scale");

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    glutTimerFunc(50, timf, 0); //40ms - 25 fps
    glutVisibilityFunc(Visibility);
    glClearColor(0, 0, 0, 0);

    glutMainLoop();

    return 0;
}