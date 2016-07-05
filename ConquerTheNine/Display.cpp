#include "Display.h"

#include <iostream>

Display* Display::instance_ = 0;

Display::Display()
{
	std::cout << "Display::Display()" << std::endl;
}

Display* Display::Instance()
{
	std::cout << "Display::Instance()" << std::endl;
	if (instance_ == 0)
	{
		instance_ = new Display();
	}

	return instance_;
}

Display::~Display()
{
	std::cout << "Display::~Display()" << std::endl;
}
