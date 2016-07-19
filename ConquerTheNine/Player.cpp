#include "Player.h"

#include <GLFW/glfw3.h>

#include <iostream>

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
	if (s == GameState::gsPLAY || s == GameState::gsPAUSE)
		return false;
	else
		return true;
}

bool Player::IsPaused()
{
	return (GameState::gsPAUSE == GameState::Instance()->State());
}

bool Player::CanDispatch()
{
	return GameState::gsPLAY == GameState::Instance()->State();
}

bool Player::KeyEvent(int key, int scancode, int action, int mods)
{
	bool dispatch = false;

	if (StateMismatch())
		return dispatch;

	if (action == GLFW_PRESS && (key == GLFW_KEY_P||key == GLFW_KEY_ESCAPE))
	{
		dispatch = CanDispatch();
		GameState::Instance()->State(GameState::gsPAUSE);
	}
	else if (!IsPaused())
	{
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

	return dispatch;
}

void Player::Render()
{
	if (StateMismatch())
		return;

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

	x_ += vx_;
	y_ += vy_;

	// Update viewport;
	viewport_->cx = x_;
	viewport_->cy = y_;
}

void Player::Init(int w, int h)
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

void Player::Save(std::fstream& s)
{
	std::cout << "Saving player..." << std::endl;
	if (s.is_open())
	{
		save_.x = x_;
		save_.y = y_;
		s.write((char *)&save_, sizeof(save_));
	}
	else
	{
		std::cout << "ERR: stream is not open!" << std::endl;
	}
}

void Player::Load(std::fstream& s)
{
	std::cout << "Loading player..." << std::endl;
	if (s.is_open())
	{
		s.read((char *)&save_, sizeof(save_));

		x_ = save_.x;
		y_ = save_.y;
	}
	else
	{
		std::cout << "ERR: stream is not open!" << std::endl;
	}
}
