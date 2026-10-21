#pragma once
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
class SelectPlaneLayer : public Layer
{
private:
	
public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(SelectPlaneLayer);
	void SelectPlaneLayer::goToCurrNode();
	void SelectPlaneLayer::addNode(Node* level);
	bool onTouchBegan(Touch* touch, Event* event);
	void SelectPlaneLayer::onTouchMoved(Touch* touch, Event* event);
	void SelectPlaneLayer::onTouchEnded(Touch* touch, Event* event);

};