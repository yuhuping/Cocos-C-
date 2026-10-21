#include "SelectPlaneScene.h"
#include "SelectPlaneLayer.h"
#include "SelectPlane.h"
USING_NS_CC;
SelectPlaneScene* SelectPlaneScene::instance_ = nullptr;
//SelectPlaneScene* SelectPlaneScene::getInstance()
//{
//	
//	if (instance_ == NULL) {
//		instance_ = new SelectPlaneScene();
//	}
//	return instance_;
//}
Scene* SelectPlaneScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectPlaneScene::create();
	scene->addChild(layer);
	return scene;
}
//以下为单例模式设置



bool SelectPlaneScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	instance_ = this;
	Size size = Director::getInstance()->getWinSize();
	//滑动界面
	SelectPlaneLayer* scrollView = SelectPlaneLayer::create();
	
	//关卡1-3
	for (int i = 1;i <= 3;++i) {
		// 添加飞机界面
		auto page = SelectPlane::create(i);
		page->setTag(i);
		scrollView->addNode(page);
	}

	//背景
	Sprite* spritebg = Sprite::create("ui/bg_select.png");
	spritebg->setPosition(Point(size.width / 2, size.height / 2));
	addChild(spritebg);
	this->addChild(scrollView);

	return true;
}
