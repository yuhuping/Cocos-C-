#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

#include "cocos2d.h"
#include "PlaneSupport.h"
using namespace std;
USING_NS_CC;
class PlaneSupport;
class MainGame : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(MainGame);
	void onEnterTransitionDidFinish();
	void onExit();
	int support_index;//类型
	PlaneSupport* plane_support;
	int score;//当前分数
	Label* label_score_num_;
	Label* label_best_score_num_;
public:
	//初始化玩家飞机
	void init_hero_plane(int index);
	//开始游戏按钮回调
	Sprite* spr_bg1_;Sprite* spr_bg2_;Sprite* hero_player;
	void update(float delta);
	

	bool onTouchBegan(Touch *touch , Event *unused_event);
	void onTouchMoved(Touch* touch, Event* unused_event);

	
	void add_enemy(float delta);//添加敌机
	void hero_death();
	void add_bullet(float a);//添加子弹

	void is_crash(float tm);//判断碰撞

	void add_support(float tm);
	void add_support_bullet(float tm);
	void suspend(Ref* ref);
	void hero_death_actionend();

};
#endif __MAIN_GAME_H__