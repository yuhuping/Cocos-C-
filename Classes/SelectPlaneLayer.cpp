#include "SelectPlaneLayer.h"



int page_node = 0;
int cur_page_node;
Point touch_down_point_;
Point touch_up_point_;
Point touch_cur_point_;
float size_x, size_y;
int SHORTEST_SLIDE_LENGTH = 0;
Scene* SelectPlaneLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectPlaneLayer::create();
	scene->addChild(layer);
	return scene;
}

bool SelectPlaneLayer::init()
{
	if (!Layer::init())
		return false;
	/*page_node = 1;*/
	//创建监视器
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SelectPlaneLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SelectPlaneLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SelectPlaneLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	size_x = Director::getInstance()->getWinSize().width;
	size_y = Director::getInstance()->getWinSize().height;

	/*cur_page_node = 1;*/
	return true;
}

void SelectPlaneLayer::goToCurrNode()
{
	//滑动效果
	this->runAction(MoveTo::create(0.4f, Point(-cur_page_node * size_x, 0)));
}

void SelectPlaneLayer::addNode(Node* level)
{
	if (level) {
		level->setContentSize(Size(size_x, size_y));
		level->setPosition(Point(size_x * page_node, 0));
		this->addChild(level);//记录添加几个飞机界面
		page_node++;
		log("page_node-%d",page_node);
	}
}

bool SelectPlaneLayer::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	touch_down_point_ = touch->getLocation();//最开始点击的位置touch_down_point_
	touch_cur_point_ = touch_down_point_;
	return true;
}

void SelectPlaneLayer::onTouchMoved(Touch* touch, Event* event)
{
	Point touchPoint = touch->getLocation();
	auto currX = this->getPositionX() + touchPoint.x - touch_up_point_.x;
	Point pos_point = Point(currX, getPositionY());

	touch_cur_point_ = touchPoint;
}

void SelectPlaneLayer::onTouchEnded(Touch* touch, Event* event)
{
	touch_up_point_ = touch->getLocation();

	//坐标差
	auto dis = touch_up_point_.getDistance(touch_down_point_);

	if (dis >= SHORTEST_SLIDE_LENGTH)
	{
		if (touch_down_point_.x > touch_up_point_.x)
		{
			//记录当前页
			++cur_page_node;
			if (page_node - 1 < cur_page_node)
				cur_page_node = page_node - 1;
		}
		else if (touch_down_point_.x < touch_up_point_.x)
		{
			//记录当前页
			--cur_page_node;
			if (cur_page_node < 0)
				cur_page_node = 0;
		}
		//播放滚动界面
		goToCurrNode();
	}
}

