#include "start_game.h"
#include "SelectPlaneScene.h"


USING_NS_CC;
Scene* StartGame::createScene()
{
    auto scene = Scene::create();
    auto layer = StartGame::create();
    scene->addChild(layer);
    return scene;
}

bool StartGame::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto size = Director::getInstance()->getWinSize();
        //游戏的背景
    auto spr_bg = Sprite :: create("ui/bg.png");
    spr_bg->setPosition(ccp(size.width /2, size.height/ 2));
    this->addChild(spr_bg);
    //读取xml
    auto dic = Dictionary :: createWithContentsOfFile("fonts/text.xml");
    auto str = (String*)(dic->objectForKey("title"));//游戏的标题
   
    auto title = Label::create();
    title->setString(str->getCString());
    title->setSystemFontSize(60);
    title->setColor(ccc3(174, 111, 23));
    title->setPosition(ccp(size.width / 2, size.height * 0.8));
    this->addChild(title,0);
    //创建帧动画
    auto animation= Animation::create();
    for (int i = 1;i <= 4;++i)
    {
        auto spr_name = String::createWithFormat("ui/start%d.png", i);
        animation->addSpriteFrameWithFile(spr_name->getCString());
    }
    animation->setDelayPerUnit(0.3f);
    animation->setLoops(-1);

    //创建精灵
    auto sprite = Sprite::create("ui/start1.png");
    sprite->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(sprite);
    sprite->runAction(Animate::create(animation));
    //添加开始游戏按钮
    str = (String*)(dic->objectForKey("play"));
    auto btn_label= Label:: create();
    btn_label->setString(str->getCString());
    btn_label->setSystemFontSize(30);
    /*btn_label->setWidth(100);
    btn_label->setHeight(30);*/
    auto start_menu = MenuItemLabel::create(btn_label,CC_CALLBACK_1(StartGame::start_play,this));
    
    auto menu = Menu::create(start_menu, NULL);
    menu->setPosition(ccp(size.width/ 2, size.height * 0.3));
    this->addChild(menu);

    return true;
}//开始游戏界面


void StartGame::start_play(Ref* pSender)
{
    auto a = SelectPlaneScene::create();
    //auto a = MainGame::create();
    //切换场景
    Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5,a));



}