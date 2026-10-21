#ifndef	_PlaneSupport_H
#define	_PlaneSupport_H
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class PlaneSupport :public Sprite {

public:
	PlaneSupport();
	~PlaneSupport();
public:
	/*static cocos2d::Sprite* createScene();*/
	virtual bool init();


	CREATE_FUNC(PlaneSupport);

	void init_support(int index);//根据index不同创建不同资源

};
#endif
