#include "Universe.h"

#include <GLFW/glfw3.h>

#include "GameState.h"

// in AU, 3.2 in light minutes.
double Universe::distanceUnit_ = 0.4;
// in kilometers
double Universe::radiusUnit_ = 500.0;
double Universe::distanceFactor_ = 7500.0;
double Universe::radiusFactor_ = 4.0;

double Universe::speedLimit_ = 0.0;

Universe::Universe()
{
}

Universe::~Universe()
{
}

bool Universe::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();
	if (s == GameState::gsPLAY || s == GameState::gsPAUSE)
		return false;
	else
		return true;
}

double Universe::RandomBetween(double min, double max)
{
	std::uniform_real_distribution<double> dist(min, max);

	return dist(generator_);
}

void Universe::Init(int w, int h)
{
	struct {
		double x, y, r;
		double c[3];
	} filler[] = {
		{ -2.5, 0.0,   13.0, {0.0, 0.0, 1.0}},
		{  0.0, 0.0, 1400.0, {1.0, 1.0, 0.0}},
		{  1.0, 0.0,    5.0, {1.0, 1.0, 1.0}},
		{  2.0, 0.0,   12.0, {1.0, 1.0, 1.0}},
		{  4.0, 0.0,    7.0, {1.0, 1.0, 1.0}},
		{  7.0, 0.0,    1.0, {1.0, 1.0, 1.0}},
		{ 13.0, 0.0,  140.0, {1.0, 1.0, 1.0}},
		{ 24.0, 0.0,  116.0, {1.0, 1.0, 1.0}},
		{ 48.0, 0.0,   51.0, {1.0, 1.0, 1.0}},
		{ 75.0, 0.0,   49.0, {1.0, 1.0, 1.0}},
		{ 99.0, 0.0,    2.5, {1.0, 1.0, 1.0}}
	};
	
	Universe::speedLimit_ = Universe::distanceFactor_ * 0.0021 / Universe::distanceUnit_;

	Body* obj;

	for (int i = 0; i < 11; i++)
	{
		obj = new Body();
		obj->x = filler[i].x * Universe::distanceFactor_;
		obj->y = -filler[i].r * Universe::radiusFactor_; //filler[i].y;
		obj->radius = filler[i].r * Universe::radiusFactor_;
		obj->color[0] = filler[i].c[0];
		obj->color[1] = filler[i].c[1];
		obj->color[2] = filler[i].c[2];
		starSystem_.push_back(obj);
	}
}

void Universe::GetBodyLocations(std::vector<double>& locations)
{
	double x;
	double xMin = 1e100;
	double xMax = -1e100;
	for (auto i = starSystem_.begin(); i != starSystem_.end(); ++i)
	{
		x = (*i)->x;
		if (x < xMin) xMin = x;
		if (x > xMax) xMax = x;
		locations.push_back(x);
	}
	locations.push_back(xMin);
	locations.push_back(xMax);
}

void Universe::RenderDisk(double r, double step)
{
	glBegin(GL_TRIANGLE_FAN);
	//glBegin(GL_LINE_LOOP);
	glVertex2d(0.0, 0.0);
	for (double a = 0.0; a < 6.28318 + step; a += step)
	{
		glVertex2d(r * cos(a), r * sin(a));
	}
	glEnd();
}

void Universe::RenderBody(Body* pBody)
{
	glLoadIdentity();
	glTranslated(pBody->x, pBody->y, 0.0);
	glRotated(90.0, 0.0, 0.0, 1.0);
	glColor3dv(pBody->color);
	RenderDisk(pBody->radius, 0.01);
}

void Universe::Render()
{
	if (StateMismatch())
		return;

	glPushMatrix();

	double radius;
	BodyContainerType::const_iterator it;
	Body* iBody;
	for (it = starSystem_.begin(); it != starSystem_.end(); ++it)
	{
		iBody = *it;
		RenderBody(iBody);
	}

	glPopMatrix();
}

double Universe::GetDistanceInAU(double d)
{
	return d * Universe::distanceUnit_ / Universe::distanceFactor_;
}

double Universe::GetSpeedInC(double v)
{
	return v / Universe::speedLimit_;
}

