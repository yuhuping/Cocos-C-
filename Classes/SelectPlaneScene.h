#pragma once
#include <iostream>
#include "cocos2d.h"
class SelectPlaneScene :public cocos2d::Scene
{
public:
	virtual bool init();
	CREATE_FUNC(SelectPlaneScene);
	void menuCloseCallback(Ref* pSender);
	static SelectPlaneScene* getInstance();
	static cocos2d::Scene* createScene();
	static SelectPlaneScene* instance_;
private:

	

};
	
