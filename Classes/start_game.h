
#include "cocos2d.h"
#include "main_game.h"
USING_NS_CC;

class StartGame : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void start_play(cocos2d::Ref* pSender);
	CREATE_FUNC(StartGame);

	//开始游戏按钮回调
	/*void start_play(Ref* ref);*/
};
