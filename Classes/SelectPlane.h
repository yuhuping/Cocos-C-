#include "cocos2d.h"
USING_NS_CC;
class SelectPlane :public Node {
public:
	//初始化选择飞机页面I
	bool initLevelPage(int page);
	static SelectPlane* create(int page);
	void GotoMain(Ref* pSender);
	CREATE_FUNC(SelectPlane);
	
public:
	
};