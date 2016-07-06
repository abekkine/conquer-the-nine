#ifndef TEXT_MANAGER_H_
#define TEXT_MANAGER_H_

#include <FTGL/ftgl.h>

#include <map>
#include <string>

class TextManager
{
private:
	static TextManager* instance_;
	FTGLPixmapFont* font_;
	FTGLPixmapFont* defaultFont_;
	typedef std::map<std::string, FTGLPixmapFont*> FontContainerType;
	FontContainerType fonts_;

private:
	TextManager();

public:
	static TextManager* Instance();
	~TextManager();
	void Init();
	void Render(std::string message);
	void UseFont(std::string label, int size);
	void AddFont(std::string label, std::string path);
};

#endif // TEXT_MANAGER_H_


