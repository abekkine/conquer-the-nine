#include "GameText.h"

#include "TextManager.h"
#include "GameState.h"

GameText::GameText()
{
}


GameText::~GameText()
{
}

void GameText::RegisterPlayer(Player* p)
{
	player_ = p;
}

void GameText::RegisterUniverse(Universe* u)
{
	universe_ = u;
	universe_->GetBodyLocations(bodyLocations_);
	barMax_ = bodyLocations_.back();
	bodyLocations_.pop_back();
	barMin_ = bodyLocations_.back();
	bodyLocations_.pop_back();
}

void GameText::Init(int w, int h)
{
	scrW_ = w;
	scrH_ = h;
	universe_->GetBodyLocations(bodyLocations_);
	xLeft_ = bodyLocations_.front();
	xRight_ = bodyLocations_.back();

	xSpan_ = xRight_ - xLeft_;
	xMargin_ = xSpan_ * 0.005;
}

bool GameText::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();

	if (s == GameState::gsPLAY || s == GameState::gsPAUSE)
		return false;
	else
		return true;
}

void GameText::RenderPlayerPos()
{
	double px, py;
	player_->GetPosition(px, py);
	double v = player_->GetSpeed();

	TextManager::Instance()->UseFont("ubuntu", 14);
	double xpos = Universe::GetDistanceInAU(px);
	double spd = Universe::GetSpeedInC(v);
	glColor3f(1.0, 0.5, 0.5);
	glRasterPos2i(scrW_ /2, 100);
	TextManager::Instance()->Render("SPD: %.2fc, POS: % 5.2f AU", spd, xpos);
}

void GameText::RenderNeighbors()
{
	bool inStarSystem = false;
	double px, py;
	player_->GetPosition(px, py);


	auto i = bodyLocations_.begin();
	auto ip1 = i+1;
	while (ip1 != bodyLocations_.end())
	{
		if (px > (*i) && px <= (*ip1))
		{
			inStarSystem = true;
			break;
		}
		i++;
		ip1 = i + 1;
	}

	if (!inStarSystem)
		return;

	double rightDistance = Universe::GetDistanceInAU((*ip1) - px);
	double leftDistance = Universe::GetDistanceInAU(px - (*i));

	TextManager::Instance()->UseFont("ubuntu", 14);
	glColor3f(1.0, 0.5, 0.5);
	glRasterPos2i(10, scrH_/2);
	TextManager::Instance()->Render("%.2f AU", leftDistance);

	glRasterPos2i(scrW_ - 100, scrH_/2);
	TextManager::Instance()->Render("%.2f AU", rightDistance);
}

void GameText::RenderLocationBar()
{
	int barWidth = scrW_ - 20;
	int barX = 10;
	int barY = 10;
	int barHeight = 40;

	glPushMatrix();
	glLoadIdentity();
	glTranslated(barX, barY, 0.0);

	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_LINE_LOOP);
	glVertex2i(0, 0);
	glVertex2i(barWidth, 0);
	glVertex2i(barWidth, barHeight);
	glVertex2i(0, barHeight);
	glEnd();


	double px, py;
	player_->GetPosition(px, py);

	glColor3f(0.5, 0.5, 0.5);
	int barBx;
	for (auto i = bodyLocations_.begin(); i != bodyLocations_.end(); ++i)
	{
		barBx = barWidth * ( (*i) - xLeft_ + xMargin_) / (xSpan_ + 2.0 * xMargin_);

		glLoadIdentity();
		glTranslated(barX + barBx, barY + 2, 0.0);
		glBegin(GL_LINES);
		glVertex2i(0, 0);
		glVertex2i(0, barHeight - 4);
		glEnd();
	}

	int barPx;
	barPx = barWidth * (px - xLeft_ + xMargin_) / (xSpan_ + 2.0 * xMargin_);

	glLoadIdentity();
	glTranslated(barX + barPx, barY + 2, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(0, barHeight - 4);
	glEnd();

	glPopMatrix();
}

void GameText::Render()
{
	if (StateMismatch())
		return;

	RenderPlayerPos();
	RenderNeighbors();
	RenderLocationBar();
}
