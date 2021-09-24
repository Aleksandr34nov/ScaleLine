#include "Functions.h"
#include "iostream"
#include <GL/glut.h>
#include <math.h>

using namespace std;

GLfloat pi = 3.1415926f;
GLfloat short_streak = 1.5f;
GLfloat long_streak = 2.5f;

void DrawScale(GLint num_segments, GLint num_segments_speed, GLfloat r_speed, GLfloat r, GLfloat r_scale, Point scale, GLint parts) {
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = ((2.0f / 3.0f) * pi * float(ii) / float(num_segments)) - 4.0f * pi / 3.0f;

		float x = r * cosf(theta);
		float y = r * sinf(theta);

		glVertex2f(x + scale.x, y + scale.y);
		if (ii / (num_segments / parts) <= parts / 5 || ii / (num_segments / parts) >= parts - (parts / 5)) {
			if (ii % (int)((num_segments / parts) * long_streak) == 0) {
				if ((ii / (int)((num_segments / parts) * long_streak)) % 2 == 1) {
					float xs = (r_scale - 0.015f) * cosf(theta);
					float ys = (r_scale - 0.015f) * sinf(theta);
					glVertex2f(x - xs + scale.x, y - ys + scale.y);
					glVertex2f(x + scale.x, y + scale.y);
				}
				else {
					float xs = r_scale * cosf(theta);
					float ys = r_scale * sinf(theta);
					glVertex2f(x - xs + scale.x, y - ys + scale.y);
					glVertex2f(x + scale.x, y + scale.y);
				}
			}
		}
		if (ii / (num_segments / parts) > parts / 5 && ii / (num_segments / parts) < parts - (parts / 5)) {
			if ((ii - (num_segments / parts)) % (int)((num_segments / parts) * short_streak) == 0) {
				if (ii == (int)(num_segments / 2) - ((int)((num_segments / parts) * short_streak) * 5) || ii == (int)(num_segments / 2) + ((int)((num_segments / parts) * short_streak) * 5)) {
					float xs = (r_scale - 0.015f) * cosf(theta);
					float ys = (r_scale - 0.015f) * sinf(theta);
					glVertex2f(x - xs + scale.x, y - ys + scale.y);
					glVertex2f(x + scale.x, y + scale.y);
				}
				else {
					float xs = (r_scale - 0.03f) * cosf(theta);
					float ys = (r_scale - 0.03f) * sinf(theta);
					glVertex2f(x - xs + scale.x, y - ys + scale.y);
					glVertex2f(x + scale.x, y + scale.y);
				}
				if (ii == (int)(num_segments / 2)) {
					glVertex2f(-r + scale.x, 0.0f + scale.y);
					glVertex2f(-r + 0.05f + scale.x, 0.0f + scale.y);
				}
			}
		}
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	float x = r * (-1.0f / 2.0f);
	float y = r * (-sqrt(3.0f) / 2.0f);
	float xs = r_scale * (-1.0f / 2.0f);
	float ys = r_scale * (-sqrt(3.0f) / 2.0f);
	glVertex2f(x - xs + scale.x, y - ys + scale.y);
	glVertex2f(x + scale.x, y + scale.y);
	glEnd();
	glPopMatrix();
}

void DrawWhiteSpeed(GLint num_segments_speed, GLfloat r_speed, Point white_circle, Point* white_rectangle, Point scale) {
	glPushMatrix();
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	for (int ii = 0; ii < num_segments_speed; ii++)
	{
		float theta = (-pi * float(ii) / float(num_segments_speed)) - pi / 2.0f;

		float x = r_speed * cosf(theta);
		float y = r_speed * sinf(theta);

		glVertex2f(x + white_circle.x + scale.x, y + white_circle.y + scale.y);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex2f(white_rectangle[0].x + scale.x, white_rectangle[0].y + scale.y);
	glVertex2f(white_rectangle[1].x + scale.x, white_rectangle[1].y + scale.y);
	glVertex2f(white_rectangle[2].x + scale.x, white_rectangle[2].y + scale.y);
	glVertex2f(white_rectangle[3].x + scale.x, white_rectangle[3].y + scale.y);
	glEnd();
	glPopMatrix();
}

void DrawBlueSpeed(Point* blue_rectangle, Point scale) {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_TRIANGLES);
	glVertex2f(blue_rectangle[0].x + scale.x, blue_rectangle[0].y + scale.y);
	glVertex2f(blue_rectangle[1].x + scale.x, blue_rectangle[1].y + scale.y);
	glVertex2f(blue_rectangle[2].x + scale.x, blue_rectangle[2].y + scale.y);

	glVertex2f(blue_rectangle[3].x + scale.x, blue_rectangle[3].y + scale.y);
	glVertex2f(blue_rectangle[4].x + scale.x, blue_rectangle[4].y + scale.y);
	glVertex2f(blue_rectangle[5].x + scale.x, blue_rectangle[5].y + scale.y);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();
}

void ArrowRotate(GLfloat spd, Point scale) {
	glPushMatrix();
	if (spd > 30.0f) {
		spd = 30.0f;
	}
	if (spd < -30.0f) {
		spd = -30.0f;
	}
	if (spd > 10.0f) {
		glRotatef((((spd - 10.0f) / 20.0f * ((-2.0f * pi / 15.0f)) - (pi / 5.0f)) / 0.0175f), 0, 0, 1);
	}
	if (spd < -10.0f) {
		glRotatef((((spd + 10.0f) / 20.0f * ((-2.0f * pi / 15.0f)) + (pi / 5.0f)) / 0.0175f), 0, 0, 1);
	}
	if (spd >= -10 && spd <= 10) {
		glRotatef((spd / 10.0f) * (-3.0f * pi / 15.0f) / 0.0175f, 0, 0, 1);
	}
}

void DrawWhiteArrow(Point* white_arrow, Point scale) {
	glLineWidth(2);
	glBegin(GL_TRIANGLES);
	glVertex2f(white_arrow[0].x + scale.x, white_arrow[0].y + scale.y);
	glVertex2f(white_arrow[1].x + scale.x, white_arrow[1].y + scale.y);
	glVertex2f(white_arrow[2].x + scale.x, white_arrow[2].y + scale.y);

	glVertex2f(white_arrow[3].x + scale.x, white_arrow[3].y + scale.y);
	glVertex2f(white_arrow[4].x + scale.x, white_arrow[4].y + scale.y);
	glVertex2f(white_arrow[5].x + scale.x, white_arrow[5].y + scale.y);

	glVertex2f(white_arrow[6].x + scale.x, white_arrow[6].y + scale.y);
	glVertex2f(white_arrow[7].x + scale.x, white_arrow[7].y + scale.y);
	glVertex2f(white_arrow[8].x + scale.x, white_arrow[8].y + scale.y);
	glEnd();
	glPopMatrix();
}

void DrawBlueArrow(Point* blue_arrow, Point scale) {
	glColor3f(0.0f, 1.0f, 1.0f);
	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
	glVertex2f(blue_arrow[0].x + scale.x, blue_arrow[0].y + scale.y);
	glVertex2f(blue_arrow[1].x + scale.x, blue_arrow[1].y + scale.y);
	glVertex2f(blue_arrow[2].x + scale.x, blue_arrow[2].y + scale.y);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();
}