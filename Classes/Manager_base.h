#ifndef _MANAGER_BASE_H_
#define _MANAGER_BASE_H_

#include "cocos2d.h"
#include "Enemy_base.h"
#include "bullet.h"

USING_NS_CC;

class Managerbase
{
public:
	Managerbase();
	~Managerbase();
public:
	static Managerbase* getInstance();//创建

	static void deleteInstance();//删除



public:
	Vector<EnemyBase*> enemy_list;
	Vector<Bullet*> bullet_list;
public://管理子弹和敌机
	Vector<EnemyBase*>& getEnemyList() { return enemy_list; }
	Vector<Bullet*>& getBulletList() { return bullet_list; }
	//添加敌机
	void set_enemy_list(EnemyBase* enemy);
	//添加子弹
	void set_bullet_list(Bullet* bullet);
	//删除敌机
	void remove_enemy_list(EnemyBase* enemy);
	//删除子弹
	void remove_bullet_list(Bullet* bullet);
private:
	static Managerbase* manager_;
};
#endif
