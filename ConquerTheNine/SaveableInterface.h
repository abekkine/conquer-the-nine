#ifndef SAVEABLE_INTERFACE_H_
#define SAVEABLE_INTERFACE_H_

#include <fstream>

class SaveableInterface
{
public:
	virtual void Save(std::fstream& s) = 0;
	virtual void Load(std::fstream& s) = 0;
};

#endif // SAVEABLE_INTERFACE_H_
