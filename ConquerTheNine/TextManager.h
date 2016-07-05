#ifndef TEXT_MANAGER_H_
#define TEXT_MANAGER_H_

#include <FTGL/ftgl.h>

#include <string>

class TextManager
{
private:
	static TextManager* instance_;

private:
	TextManager();
	FTGLPixmapFont* font_;

public:
	static TextManager* Instance();
	~TextManager();
	void Init();
	void Render(std::string message);
};

#endif // TEXT_MANAGER_H_


