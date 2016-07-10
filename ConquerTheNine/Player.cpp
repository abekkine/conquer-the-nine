#include "Player.h"

#include <GLFW/glfw3.h>

#include "GameState.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();
	if (s == GameState::gsPLAY)
		return false;
	else
		return true;
}

void Player::KeyEvent(int key, int scancode, int action, int mods)
{
	if (StateMismatch())
		return;

	switch (key)
	{
	case GLFW_KEY_UP:
		if (action != GLFW_RELEASE)
			vy_ = 1.0;
		else
			vy_ = 0.0;
		break;
	case GLFW_KEY_DOWN:
		if (action != GLFW_RELEASE)
			vy_ = -1.0;
		else
			vy_ = 0.0;
		break;
	case GLFW_KEY_LEFT:
		if (action != GLFW_RELEASE)
			vx_ = -1.0;
		else
			vx_ = 0.0;
		break;
	case GLFW_KEY_RIGHT:
		if (action != GLFW_RELEASE)
			vx_ = 1.0;
		else
			vx_ = 0.0;
		break;
	}
}

void Player::Render()
{
	if (StateMismatch())
		return;

	x_ += vx_;
	y_ += vy_;

	// Update viewport;
	viewport_->left = x_ - vpHalfWidth_;
	viewport_->right = x_ + vpHalfWidth_;
	viewport_->top = y_ + vpHalfHeight_;
	viewport_->bottom = y_ - vpHalfHeight_;

	double s = 2.5;

	glPushMatrix();
	glLoadIdentity();
	glTranslated(x_, y_, 0.0);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2d(-s, -s);
	glVertex2d(-s, s);
	glVertex2d(s, s);
	glVertex2d(s, -s);
	glEnd();

	glPopMatrix();
}

void Player::Init()
{
	x_ = 0.0;
	y_ = 0.0;
	vx_ = 0.0;
	vy_ = 0.0;
}

void Player::RegisterViewport(Display::Viewport* vp)
{
	viewport_ = vp;
	vpHalfWidth_ = vp->right - vp->left;
	vpHalfHeight_ = vp->top - vp->bottom;
}