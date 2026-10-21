#include "GamOver.h"
#include "start_game.h"
USING_NS_CC;
Scene* GameOver::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}

bool GameOver::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
    auto size = Director::getInstance()->getWinSize();

    auto spr_bg = Sprite::create("ui/bg.png");
    spr_bg-> setPosition(ccp(size.width/2,size.height/2));
    this->addChild(spr_bg);

	//-------------------------------------------设置分数------------------------------//
	auto label_score = Label::create();
	label_score->setString(((String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(40);
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(size.width/2-label_score->getContentSize().width/2+5, size.height/2+40));
	this->addChild(label_score);
	auto label_score_num_ = Label::create();

	label_score_num_->setSystemFontSize(30);
	label_score_num_->setAnchorPoint(ccp(0, 0.5));
	label_score_num_->setPosition(ccp(label_score->getPositionX()+ label_score->getContentSize().width, size.height / 2+40));
	this->addChild(label_score_num_);
	//最高分
	auto label_best_score = Label::create();
	label_best_score->setString(((String*)(dictionary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(40);
	label_best_score->setAnchorPoint(ccp(0.5, 0.5));
	label_best_score->setPosition(ccp(size.width / 2-label_best_score->getContentSize().width / 2 + 5, size.height / 2 -20));
	this->addChild(label_best_score);

	auto label_best_score_num_ = Label::create();

	label_best_score_num_->setSystemFontSize(30);
	label_best_score_num_->setAnchorPoint(ccp(0, 0.5));
	label_best_score_num_->setPosition(ccp(label_best_score->getPositionX()+ label_best_score->getContentSize().width , size.height / 2 -20));
	this->addChild(label_best_score_num_);

	//获取最高分
	auto score_win = UserDefault::getInstance()->getIntegerForKey("beast_score");
	auto score = UserDefault::getInstance()->getIntegerForKey("score");

	label_best_score_num_->setString(String::createWithFormat("%d", score_win)->getCString());
	label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
	auto btn_label = Label::create();
	btn_label->setString(((String*)(dictionary->objectForKey("back_menu")))->getCString());
	btn_label->setSystemFontSize(40);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(GameOver::menu_play, this));
	//添加返回主页menu
	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(size.width/2,size.height/2-200));
	this->addChild(menu);
}

void GameOver::menu_play(Ref* ref)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, StartGame::create()));
}
