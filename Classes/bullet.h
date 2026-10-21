#ifndef	BULLET_H
#define	BULLET_H


#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Bullet : public Sprite {

public:
	Bullet() ;
	~Bullet();

public:
	static cocos2d::Sprite* createScene();
	virtual bool init();
	CREATE_FUNC(Bullet);

	void onEnterTransitionDidFinish();
	void onExit();
	virtual void update(float delta);

	void initBullet(char* bullent_name);


};
#endif