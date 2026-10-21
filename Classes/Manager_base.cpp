#include "Manager_base.h"
using namespace std;
Managerbase* Managerbase:: manager_ = nullptr;

Managerbase::Managerbase()
{
}

Managerbase::~Managerbase()
{
}


//以下为单例模式设置
Managerbase* Managerbase::getInstance()
{
	if (manager_ == NULL) {
		manager_ = new Managerbase();
	}
	return manager_;
}
void Managerbase::deleteInstance()
{
	if (manager_) {
		delete manager_;
		manager_ = NULL;
	}
}

void Managerbase::set_enemy_list(EnemyBase* enemy)
{
	enemy_list.pushBack(enemy);
}

void Managerbase::set_bullet_list(Bullet* bullet)
{
	bullet_list.pushBack(bullet);
}

void Managerbase::remove_enemy_list(EnemyBase* enemy)
{
	enemy_list.eraseObject(enemy);

}

void Managerbase::remove_bullet_list(Bullet* bullet)
{
	bullet_list.eraseObject(bullet);
}
