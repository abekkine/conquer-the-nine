#include "Universe.h"

#include <GLFW/glfw3.h>

#include "GameState.h"

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

void Universe::Init()
{
	// Create 100 dummy objects.
	// x E [-900.0, +900.0],
	// y E [-900.0, +900.0],
	// size E [+10.0, +50.0],
	// shade E [0.5, 1.0]
	DummyObject* obj;
	for (int i = 0; i < 100; i++)
	{
		obj = new DummyObject();
		obj->x = RandomBetween(-900.0, 900.0);
		obj->y = RandomBetween(-900.0, 900.0);
		obj->size = RandomBetween(10.0, 50.0);
		obj->shade = RandomBetween(0.5, 1.0);
		objects_.push_back(obj);
	}
}

void Universe::Render()
{
	if (StateMismatch())
		return;

	glPushMatrix();

	double s;
	double c;
	DummyContainerType::const_iterator it;
	for (it = objects_.begin(); it != objects_.end(); ++it)
	{
		s = (*it)->size;
		c = (*it)->shade;
		glLoadIdentity();
		glTranslated((*it)->x, (*it)->y, 0.0);
		glColor3d(c, c, c);
		glBegin(GL_QUADS);
		glVertex2d(-s, -s);
		glVertex2d(s, -s);
		glVertex2d(s, s);
		glVertex2d(-s, s);
		glEnd();
	}

	glPopMatrix();
}

