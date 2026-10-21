#ifndef	ENEMY_H
#define	ENEMY_H
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class EnemyBase :public Sprite {

public:
	EnemyBase();
	~EnemyBase();
public:
	static cocos2d::Sprite* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(EnemyBase);

	void onEnterTransitionDidFinish();
	void onExit();
	virtual void update(float delta);
public:
	void initEnemy(int index=1);
	void enemy_death();
	int enemy_index;
	void remove_enemy();

	//µÐ»úÑªÁ¿
	void set_hp(int hp);
	int get_hp() { return enemy_hp; }
	int enemy_hp;
	bool is_death;
};
#endif