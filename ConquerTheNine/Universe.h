#ifndef UNIVERSE_H_
#define UNIVERSE_H_

#include <random>
#include <vector>

#include "DisplayObjectInterface.h"

class Universe : public DisplayObjectInterface
{
private:
	std::default_random_engine generator_;
	struct Body {
		double x, y;
		double radius;
		double color[3];
	};
	typedef std::vector<Body*> BodyContainerType;
	BodyContainerType starSystem_;

public:
	static double distanceUnit_;
	static double radiusUnit_;
	static double distanceFactor_;
	static double radiusFactor_;
	static double speedLimit_;

public:
	Universe();
	~Universe();

	virtual bool KeyEvent(int key, int scancode, int action, int mods) { return false; }
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init(int w, int h);
	virtual bool StateMismatch();
	void GetBodyLocations(std::vector<double>& locations);

	static double GetDistanceInAU(double d);
	static double GetSpeedInC(double v);

private:
	double RandomBetween(double min, double max);
	void RenderDisk(double r, double step=0.1);
	void RenderBody(Body* pBody);
};

#endif // UNIVERSE_H_
