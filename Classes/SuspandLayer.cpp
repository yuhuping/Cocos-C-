#include "SuspandLayer.h"

USING_NS_CC;
Scene* SuspandLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = SuspandLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SuspandLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    auto size = Director::getInstance()->getWinSize();
    auto bg_name = FileUtils::getInstance()->getWritablePath() + "suspand.png";
    auto spr_bg = Sprite::create(bg_name);
    spr_bg->setPosition(Point(size.width / 2, size.height / 2));
    this->addChild(spr_bg);

    auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
    auto btn_label = Label::create();
    btn_label->setString(((String*)(dictionary->objectForKey("back_game")))->getCString());
    btn_label->setSystemFontSize(45);
    auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(SuspandLayer::back_game, this));
    auto menu = Menu::create(start_menu, NULL);
    menu->setPosition(ccp(size.width / 2 - 5, size.height/2));

    this->addChild(menu);
}

void SuspandLayer::back_game(Ref* ref)
{
    Director::getInstance()->popScene();
}
