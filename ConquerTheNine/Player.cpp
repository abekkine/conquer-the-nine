#include "Player.h"

#include <GLFW/glfw3.h>

#include <mutex>
#include <iostream>

#include "Universe.h"
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
				fx_ *= 1.25;
			else
				fx_ = fx_;
			break;
		case GLFW_KEY_DOWN:
			if (action != GLFW_RELEASE)
				fx_ *= 0.5;
			else
				fx_ = fx_;
			break;
		case GLFW_KEY_LEFT:
			if (action != GLFW_RELEASE)
				fx_ -= 1.0;
			else
				fx_ = fx_;
			break;
		case GLFW_KEY_RIGHT:
			if (action != GLFW_RELEASE)
				fx_ += 1.0;
			else
				fx_ = fx_;
			break;
		case GLFW_KEY_A:
			fx_ = 0.0;
			fy_ = 0.0;
			break;
		case GLFW_KEY_V:
			vx_ = 0.0;
			vy_ = 0.0;
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
	glVertex2d(-s, -0.3*s);
	glVertex2d(-s, 0.3*s);
	glVertex2d(s, 0.3*s);
	glVertex2d(s, -0.3*s);
	glEnd();

	glPopMatrix();

	UpdatePhysics();

	// Update viewport;
	viewport_->cx = x_;
	viewport_->cy = y_;
}

void Player::UpdatePhysics()
{
	double deltaTime;
	curTime_ = glfwGetTime();
	deltaTime = curTime_ - prevTime_;
	prevTime_ = curTime_;

    double vInC = vx_ / Universe::speedLimit_;
    double lorentzFactor = sqrt(1.0 - vInC * vInC);
    double effectiveMass = mass_ / lorentzFactor;

	// Update
	std::mutex g;
	g.lock();
    ax_ = fx_ / effectiveMass;
	vx_ = vx_ + deltaTime * ax_;
	g.unlock();


    SetRelativisticViewport(lorentzFactor);

	x_ = x_ + deltaTime * vx_;
}

void Player::SetRelativisticViewport(double lf) {

    viewport_->widthFactor = 1.0 / lf;
}

void Player::Init(int w, int h)
{
	x_ = -18750.0;
	y_ = 0.0;
	vx_ = 0.0;
	vy_ = 0.0;
	ax_ = 0.0;
	ay_ = 0.0;
    fx_ = 0.0;
    fy_ = 0.0;
    mass_ = 1000.0;
	prevTime_ = glfwGetTime();
	curTime_ = prevTime_;
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
