#pragma once
#include "Point.h"
#include "iostream"
#include <GL/glut.h>
#include <math.h>
#include "string"

void DrawScale(GLint, GLint, GLfloat, GLfloat, GLfloat, Point, GLint);
void DrawWhiteSpeed(GLint, GLfloat, Point, Point*, Point);
void DrawBlueSpeed(Point*, Point);
void ArrowRotate(GLfloat, Point);
void DrawWhiteArrow(Point*, Point);
void DrawBlueArrow(Point*, Point);
void Draw(void);
void Visibility(int);
void timf(int);
void Reshape(int, int);