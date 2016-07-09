#ifndef DISPLAY_OBJECT_INTERFACE_H_
#define DISPLAY_OBJECT_INTERFACE_H_

class DisplayObjectInterface
{
public:
	struct Viewport {
		double left, right, bottom, top;
		Viewport() { left = bottom = -1.0; right = top = 1.0; }
	};
private:
	Viewport viewport_;
public:
	void SetViewport(double left, double right, double bottom, double top) { 
		viewport_.left = left;
		viewport_.right = right;
		viewport_.bottom = bottom;
		viewport_.top = top;
	}
	Viewport& GetViewport() { return viewport_;  }
	void PanViewport(double x, double y) {
		viewport_.left += x;
		viewport_.right += x;
		viewport_.top += y;
		viewport_.bottom += y;
	}

	virtual void KeyEvent(int key, int scancode, int action, int mods) = 0;
	virtual void MouseButtonEvent(int button, int action, int mods) = 0;
	virtual void CursorPositionEvent(double x, double y) = 0;
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual bool StateMismatch() = 0;
};

#endif // DISPLAY_OBJECT_INTERFACE_H_

