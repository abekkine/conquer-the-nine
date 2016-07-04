#include "Display.h"

Display* Display::instance_ = 0;

Display::Display()
{
}

Display* Display::Instance()
{
	if (instance_ == 0)
	{
		instance_ = new Display();
	}

	return instance_;
}

Display::~Display()
{
}
