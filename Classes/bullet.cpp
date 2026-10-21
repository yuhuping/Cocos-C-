#include "bullet.h"
#include "Manager_base.h"
Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Sprite* Bullet::createScene()
{
	return Bullet::create();
}


bool Bullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}



void Bullet::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void Bullet::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

void Bullet::update(float delta)
{
	this->setPositionY(this->getPositionY() + 5);

	if (this->getPositionY() > Director::getInstance()->getWinSize().height) {
		this->removeFromParentAndCleanup(true);
		Managerbase::getInstance()->remove_bullet_list(this);
	}
}

void Bullet::initBullet(char* bullent_name)
{
	auto spr_name = String::createWithFormat("plane/%s", bullent_name);
	this->initWithFile(spr_name->getCString());
}
