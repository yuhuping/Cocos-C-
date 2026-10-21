
#include "cocos2d.h"

USING_NS_CC;

class GameOver : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(GameOver);

	void menu_play(Ref* ref);
};

