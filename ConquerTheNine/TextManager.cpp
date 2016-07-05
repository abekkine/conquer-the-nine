#include "TextManager.h"

#include "Exception.h"

TextManager* TextManager::instance_ = 0;

TextManager* TextManager::Instance()
{
	if (instance_ == 0)
	{
		instance_ = new TextManager();
	}

	return instance_;
}

TextManager::TextManager()
{
}

TextManager::~TextManager()
{
}

void TextManager::Init()
{
	font_ = new FTGLPixmapFont("C:/Source/Fonts/AlegreyaSans/AlegreyaSans-Regular.ttf");

	if (font_->Error())
	{
		throw Exception("FTGL font unable to load!");
	}
}

void TextManager::Render(std::string message)
{
	font_->FaceSize(40);
	font_->Render(message.c_str());
}