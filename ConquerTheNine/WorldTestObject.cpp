#include "WorldTestObject.h"

#include <math.h>
#include <GLFW/glfw3.h>

WorldTestObject::WorldTestObject()
{
}

WorldTestObject::~WorldTestObject()
{
}

void WorldTestObject::Init()
{
	a = 0.0;
}

void WorldTestObject::RenderToWorld()
{
	double s;

	glLoadIdentity();
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glRotated(a, 0.0, 0.0, 1.0);
	a += 1.0;
	s = 0.46 + 0.04*sin(12.0* a * 3.14159 / 180.0);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2d(-s, -s);
	glVertex2d(s, -s);
	glVertex2d(s, s);
	glVertex2d(-s, s);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2d(-0.5, -0.5);
	glVertex2d(0.5, -0.5);
	glVertex2d(0.5, 0.5);
	glVertex2d(-0.5, 0.5);
	glEnd();

	glPopMatrix();
}