
#include "main_game.h"
#include "Enemy_base.h"
#include "bullet.h"
#include "Manager_base.h"
#include "PlaneSupport.h"
#include "SuspandLayer.h"
#include "GamOver.h"
#include "SelectPlaneScene.h"
#include "SelectPlaneLayer.h"
USING_NS_CC;

Scene* MainGame::createScene()
{
	/*auto scene = Scene::create();
	auto layer = MainGame::create();
	scene->addChild(layer);*/
	return MainGame::create();
}

bool MainGame::init() {
	//背景1
	int plane_taye=NULL;
	plane_support = NULL;score = 0;
	if (!Scene::init())
		return false;

	Size size = Director::getInstance()->getWinSize();
	spr_bg1_ = Sprite::create("ui/bgs.png");
	spr_bg1_->setAnchorPoint(ccp(0, 0));
	spr_bg1_->setPosition(ccp(0, 0));
	this->addChild(spr_bg1_);
	//背景2
	spr_bg2_ = Sprite::create("ui/bgs.png");
	spr_bg2_->setAnchorPoint(ccp(0, 0));
	spr_bg2_->setPosition(ccp(0, spr_bg1_->getContentSize().height - 2));
	this->addChild(spr_bg2_);

	////在init中初始化飞机
	/*init_hero_plane(NULL);*/

	//添加暂停功能
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label= Label::create();
	btn_label->setString(((String*)(dictionary->objectForKey("suspend")))->getCString());
	btn_label->setSystemFontSize(30);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(MainGame::suspend, this));
		auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(size.width- btn_label->getContentSize().width / 2 - 5, size.height - 100));

	this->addChild(menu);
	//---------------------------设置分数------------------------------//
	auto label_score = Label::create();
	label_score->setString(((String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(40);
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(label_score->getContentSize().width / 2 + 10, size.height - 100));
	this->addChild(label_score);
	 label_score_num_ = Label::create();

	label_score_num_->setSystemFontSize(30);
	label_score_num_->setAnchorPoint(ccp(0, 0.5));
	label_score_num_->setPosition(ccp(label_score->getContentSize().width  + 10, size.height - 100));
	this->addChild(label_score_num_);
	//最高分
	auto label_best_score = Label::create();
	label_best_score->setString(((String*)(dictionary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(40);
	label_best_score->setAnchorPoint(ccp(0.5, 0.5));
	label_best_score->setPosition(ccp(label_best_score->getContentSize().width / 2 + 5, size.height - 200));
	this->addChild(label_best_score);

	label_best_score_num_ = Label::create();

	label_best_score_num_->setSystemFontSize(30);
	label_best_score_num_->setAnchorPoint(ccp(0, 0.5));
	label_best_score_num_->setPosition(ccp(label_best_score->getContentSize().width  + 10, size.height - 200));
	this->addChild(label_best_score_num_);

	int score_win = UserDefault::getInstance()->getIntegerForKey("beast_score");
	label_best_score_num_->setString(String::createWithFormat("%d",score_win)->getCString());
	label_score_num_->setString(String::createWithFormat("%d", score)->getCString());

	//-----------单点触摸的监听器------------
	EventListenerTouchOneByOne* m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
	//设置吞噬触摸
	m_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);
	//-----------------end--------------------


	return true;
}

void MainGame::onEnterTransitionDidFinish() {
	
	Scene::onEnterTransitionDidFinish();
	scheduleUpdate();
	this->schedule(SEL_SCHEDULE(&MainGame::add_enemy),0.3f);	//进入主界面开始创建敌机

	this->schedule(SEL_SCHEDULE(&MainGame::add_bullet),0.08f);//进入主界面开始发射子弹
	//
	this->schedule(SEL_SCHEDULE(&MainGame::is_crash));

	this->schedule(SEL_SCHEDULE(&MainGame::add_support),8.0f);
}

void MainGame::onExit() {
	unscheduleUpdate();
	Managerbase::getInstance()->deleteInstance();
	Scene::onExit();
}

bool MainGame::onTouchBegan(Touch* touch, Event* unused_event)
{
	auto point = touch->getLocation();
	auto rect = hero_player->getBoundingBox();
	if (rect.containsPoint(point)) {
		return true;
	}
	return false;
}

void MainGame::onTouchMoved(Touch* touch, Event* unused_event)
{
	auto add_point = touch->getLocation() - touch->getPreviousLocation();
	hero_player->setPosition(hero_player->getPosition() + add_point);

	//让飞机不要超过边界
	Size size = Director::getInstance()->getWinSize();
	auto hero_size = hero_player->getContentSize();
	//x方向
	if (hero_player->getPositionX() < hero_size.width / 2-10) {
		hero_player->setPositionX(hero_size.width / 2-10);
	}
	else if (hero_player->getPositionX() > size.width -hero_size.width/2+10) {
		hero_player->setPositionX(size.width - hero_size.width / 2+10);
	}
	//y方向
	if (hero_player->getPositionY() < hero_size.height / 2) {
		hero_player->setPositionY(hero_size.height / 2);
	}
	else if (hero_player->getPositionY() > size.height - hero_size.height / 2) {
		hero_player->setPositionY(size.height - hero_size.height / 2);
	}
}

//创建玩家飞机
void MainGame::init_hero_plane(int index)
{
	//plane_taye = index;//记录飞机类型
	//
	auto animation = Animation::create();
	for (int i = 0;i < 2;++i) {
		auto str_name = String::createWithFormat("plane/heros%d_%d.png", index, i + 1);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.5);
	animation->setLoops(-1);
	//创建飞机精灵
	hero_player = Sprite::create(String::createWithFormat("plane/heros%d_1.png", index)->getCString());
	
	auto size = Director::getInstance()->getWinSize();
	
	/*hero_player->setAnchorPoint(ccp(0, 0));*/
	hero_player ->setPosition(ccp(size.width / 2, size.height * 0.2));
	this->addChild(hero_player);
	hero_player->runAction(Animate::create(animation));


}

void MainGame::add_enemy(float delta)
{
	//添加敌机

	//用不同概率添加不同样的飞机
	int dex = CCRANDOM_0_1() * 9 + 1;
	if (dex > 6) {
		dex = 2;
	}
	else {
		dex = 1;
	}
	auto enemy = EnemyBase::create();
	enemy->initEnemy(dex);
	
	this->addChild(enemy);
	//添加敌机管理器
	Managerbase::getInstance()->set_enemy_list(enemy);

}

void MainGame::hero_death()
{
	UserDefault::getInstance()->setIntegerForKey("score",score);
	//最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("beast_score");
	if (score > score_win)
	{
		UserDefault::getInstance()->setIntegerForKey("beast_score",score);
	}

	hero_player->stopAllActions();
	this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));
	this->unschedule(SEL_SCHEDULE(&MainGame::is_crash));

	this->unschedule(SEL_SCHEDULE(&MainGame::add_support_bullet));//解决在超级子弹下死亡报错问题


	auto animation = Animation::create();
	for (int i = 1;i <= 4;++i) {
		auto enemy_name = String::createWithFormat("plane/hero_blowup_n%d.png", i);//爆炸的三张图片
		animation->addSpriteFrameWithFile(enemy_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);
	hero_player->runAction(Sequence::create(Animate::create(animation),
		RemoveSelf::create(), CallFunc::create(CC_CALLBACK_0(MainGame::hero_death_actionend, this)), NULL));
	
}

void MainGame::add_bullet(float a)
{
	auto bullet = Bullet::create();
	bullet->initBullet("bullet1.png");

	auto point = ccp(hero_player->getPositionX(),hero_player->getPositionY()+ hero_player->getContentSize().height/2+10);
	bullet->setPosition(point);
	this->addChild(bullet);

	//添加子弹管理器
	Managerbase::getInstance()->set_bullet_list(bullet);
}

void MainGame::is_crash(float tm)
{
	auto& enemy_list = Managerbase::getInstance()->getEnemyList();
	auto& bullet_list = Managerbase::getInstance()->getBulletList();

	for (int i = enemy_list.size() - 1;i >= 0;--i) {
		auto enemy = enemy_list.at(i);
		if (enemy->get_hp() <= 0) {
			continue;
		}
		auto enemysize = enemy->boundingBox();
		//子弹
		for (int i = bullet_list.size() - 1;i >= 0;--i)
		{
			auto bullet = bullet_list.at(i);
			if (enemysize.containsPoint(bullet->getPosition()))
			{
				enemy->set_hp(enemy->get_hp() - 1);

				bullet->removeFromParentAndCleanup(true);
				Managerbase::getInstance()->remove_bullet_list(bullet);
				if (enemy->get_hp() <= 0)
				{
					enemy->enemy_death();
					score += 10;//一个敌机加十分
					label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
			
				}
			}
		}
	}//敌机与子弹

	//玩家与敌机
	for (auto i = enemy_list.size() - 1;i >= 0;--i)
	{
		auto enemy = enemy_list.at(i);
		if (enemy->get_hp() <= 0)
		{
			continue;
		}
		auto rect = this->hero_player->getBoundingBox();
		auto point = enemy->getPosition();
		if (rect.containsPoint(point))
		{
			hero_death();
		}
	}
	//支援物资
	if (plane_support != NULL)
	{
		auto rect = hero_player->getBoundingBox();
		auto point = plane_support->getPosition();
		if (rect.containsPoint(point))
		{
			log("Boom!");
			this->schedule(SEL_SCHEDULE(&MainGame::add_support_bullet), 0.1f, 50, 0);
			this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));//停止添加普通子弹
			this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.1f,-1,5.0f);
			plane_support->setVisible(false);
			plane_support = NULL;
		}
		//移除物资
		if (plane_support != NULL && point.y < -plane_support->getContentSize().height / 2)
		{
			plane_support->removeFromParent();
			plane_support = NULL;
		}
	}
}

void MainGame::add_support(float tm)
{
	//初始比物资
	plane_support = PlaneSupport::create(); // 随机出支援物资的类型
	int index = CCRANDOM_0_1() * 2 + 1;
	support_index = index;
	plane_support->init_support(index);
	this->addChild(plane_support);
	plane_support->setTag(index);
}

void MainGame::add_support_bullet(float tm)
{
	auto bullet = Bullet::create();

	if (support_index == 2)
		bullet->initBullet("bullet_suspand2.png");
	else
		bullet->initBullet("bullet_suspand1.png");
	
	auto point = Point(hero_player->getPositionX(),hero_player->getPositionY() + hero_player->getContentSize().height / 2 + 10);

	bullet->setPosition(point);
	this->addChild(bullet);
	//将子弹添加到ManagerBase中
	Managerbase::getInstance()->set_bullet_list(bullet);
}
//暂停的实现
void MainGame::suspend(Ref* ref)
{
	unscheduleUpdate();//先把之前不用的纹理删除
	CCTextureCache::getInstance()->removeUnusedTextures();
	auto size =Director::getInstance()->getWinSize();
	auto texture = RenderTexture::create(size.width, size.height);
	texture->begin();
	//演染
	Director::getInstance()->getRunningScene()->visit();
	texture->end();
	texture->saveToFile("suspand.png", Image::Format::PNG);
	auto back = [](float dt)
	{
		auto scene = Scene::create();
		auto layer = SuspandLayer::create();
		scene->addChild(layer);
		Director::getInstance()->pushScene(scene);
	};
	auto layer = Layer::create();
	this->addChild(layer);
	auto schedules = layer->getScheduler();
	schedules->schedule(back, layer, 0.0f, 0, 0.0f, false, "screenshot");
}

void MainGame::hero_death_actionend()
{
	this->unschedule(SEL_SCHEDULE(&MainGame::add_enemy));

	Director::getInstance()->replaceScene(TransitionFadeTR::create(1,GameOver::createScene()));
}

void MainGame::update(float delta) {

	//实现背录滚动
	float y1 = spr_bg1_->getPositionY() - 3;
	float y2 = spr_bg2_->getPositionY() - 3;
	spr_bg1_->setPositionY(y1);
	spr_bg2_->setPositionY(y2);
	//判断背景图片是否超出边界
	
		if (y1 < - spr_bg1_->getContentSize().height) {
			spr_bg1_->setPositionY(spr_bg2_->getPositionY()+ spr_bg2_->getContentSize().height - 2);
		
		}
		else if(y2 < -spr_bg2_->getContentSize().height) {
			spr_bg2_->setPositionY(spr_bg1_->getPositionY() + spr_bg1_->getContentSize().height - 2);

		}

}
