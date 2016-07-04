#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display
{
private:
	static Display* instance_;
	Display();
public:
	static Display* Instance();
	~Display();

private:
	// Static callback methods, and their processor methods.
};

#endif // DISPLAY_H_


