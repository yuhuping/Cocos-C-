#include "Enemy_base.h"
#include "Manager_base.h"
#include "main_game.h"
#include "GamOver.h"
USING_NS_CC;
Sprite* EnemyBase::createScene()
{
	return EnemyBase::create();
}

void EnemyBase::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void EnemyBase::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

//update实现敌机向下滚动
void EnemyBase::update(float delta)
{
	//判断is_death是否死了，则不移动了
	if (is_death) return;

	//没死继续执行
	auto point = this->getPositionY() - 5;
	this->setPositionY(point);
	if (point < -this->getContentSize().height) {
		this->removeFromParentAndCleanup(true);
		remove_enemy();
	}

}

//设置敌机在屏幕顶层，x坐标随机生成
void EnemyBase::initEnemy(int index)
{
	
	enemy_hp = index;
	auto name_str = String::createWithFormat("plane/enemy%d.png", index);
	/*auto name_str = Sprite::create(String::createWithFormat("plane/enemy%d.png", index)->getCString());*/
	/*this->create(name_str->getCString());
	this->initWithSpriteFrame(Sprite::create(String::createWithFormat("plane/enemy%d.png", index)->getCString()));*/
	this->initWithFile(name_str->getCString());
	Size size = Director::getInstance()->getWinSize();
	//s随机敌机坐标
	Point pos = ccp(CCRANDOM_0_1() * (size.width - this->getContentSize().width) + this->getContentSize().width / 2, size.height - this->getContentSize().height / 2);
	this->setPosition(pos);
	this->scheduleUpdate();
}

void EnemyBase::enemy_death()
{
	is_death = true;
	auto animation = Animation::create();
	for (int i = 1;i <= 4;++i) {
		auto enemy_name = String::createWithFormat("plane/b%d.png", i);//爆炸的三张图片
		animation->addSpriteFrameWithFile(enemy_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);
	this->runAction(Sequence::create(Animate::create(animation), 
		RemoveSelf::create(),CallFunc::create(CC_CALLBACK_0(EnemyBase::remove_enemy,this)),NULL) );

}

void EnemyBase::remove_enemy()
{
	Managerbase::getInstance()->remove_enemy_list(this);
}

void EnemyBase::set_hp(int hp)
{
	enemy_hp = hp;
}

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

bool EnemyBase::init()
{
	is_death = false;
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void EnemyBase::menuCloseCallback(cocos2d::Ref* pSender)
{
}
