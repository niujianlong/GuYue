

#include "GameTabBarMenu.h"
#include "GameScene.h"
#include "SkillTableView.h"
#include "PropColumn.h"
#include "GameOptions.h"
#include "RoleInfo.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


#define WINSIZE Director::getInstance()->getWinSize()

bool GameTabBarMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }
	FileUtils::getInstance()->addSearchPath("ui/tabbarMenu");
	auto p_Layer = CSLoader::createNode("ui/tabbarMenu/TabBarMenu.csb");
	Layer_listener = EventListenerTouchOneByOne::create();
	Layer_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { log("p_Layer of TabBarMenu touch began"); return true; };
	Layer_listener->setSwallowTouches(false);//不向下传递触摸 add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Layer_listener, p_Layer);//这里必须是m_pBg，改成this照样会向下传递
#if 0  //无法解决代码创建的ControlButton的Scale问题遂放弃 改成静态获取
	auto m_pBg = dynamic_cast<Sprite*> (p_Layer->getChildByName("options_1"));
	//把关闭按钮放在最上层
	ControlButton* button = ControlButton::create(Scale9Sprite::create("ui/closed_normal.png"));
	button->setBackgroundSpriteForState(Scale9Sprite::create("ui/closed_selected.png"), Control::State::HIGH_LIGHTED);
	button->setPreferredSize(Size(60, 60));
	button->setScaleX(0.8569);
	button->setScaleY(0.75625);
	auto Vec2Test = ccpSub(m_pBg->getContentSize(), button->getContentSize() / 2);
	button->setPosition(Vec2Test);
	m_pBg->addChild(button);
	auto Vec2Anc = m_pBg->getAnchorPoint();
	auto Vec2AncAbs = m_pBg->getAnchorPointInPoints();
	//Director::getInstance()->getRunningScene()->addChild(button,0xffff);

	button->addTargetWithActionForControlEvents(GAME_UILAYER,
		cccontrol_selector(GameInfoUIController::removeBigMenuAndButton),
		Control::EventType::TOUCH_UP_INSIDE);
#endif
	auto button_Close = dynamic_cast<Button*> (p_Layer->getChildByName("Button_Close"));
	button_Close->addTouchEventListener(this, toucheventselector(GameTabBarMenu::btnCloseCallBack));
    //Layout* widget = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("ui/tabbarMenu/tabbarMenu.json"));
	auto pNode0_RoleInfo = dynamic_cast<Node*> (p_Layer->getChildByName("Node_0"));
	m_RoleInfo = RoleInfo::create();
	//m_RoleInfo->retain();//这个还不能去掉，去掉会出错
	m_RoleInfo->getNode()->setPosition(Vec2(0, 0));//Point(WINSIZE.width / 2, (WINSIZE.height + 80) / 2));
	//m_RoleInfo->setZOrder(0xffff);
	pNode0_RoleInfo->addChild(m_RoleInfo->getNode());


	//加入设置界面的显示
	auto pNode4_Setting = dynamic_cast<Node*> (p_Layer->getChildByName("Node_4"));
	m_GameOptions = GameOptions::create();
	m_GameOptions->retain();//这里为什么要加这个，因为我要改变里面button的图片
	m_GameOptions->getNode()->setPosition(Vec2(0.0, 0.0));
	pNode4_Setting->addChild(m_GameOptions->getNode());


	//加入背包的显示
	auto pNode1_BackPack = dynamic_cast<Node*> (p_Layer->getChildByName("Node_1"));
	PropColumnMenu* backPackLayer = PropColumnMenu::create();
	backPackLayer->retain();
	backPackLayer->setPosition(Vec2(0.0,0.0));
	pNode1_BackPack->addChild(backPackLayer);

	


    if (p_Layer)
    {
        //widget->setTouchEnabled(true);
        this->addChild(p_Layer);
		//this->addChild(m_RoleInfo);
    }
	m_TabUiControl = new TabUiControl();
	m_TabUiControl->InitTab(p_Layer, 5, true, "Button_", "Text_", "Node_");
	m_TabUiControl->ActiveTab(0);
	//Director::getInstance()->getRunningScene()->addChild(m_RoleInfo->getNode(),0xffff);
#if 0
    Button* roleInfoBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButton_role"));
    if (roleInfoBtn)
    {
         roleInfoBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showRoleInfo));
        
    }

    Button* backPackBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButton_backPack"));
    if (backPackBtn)
    {
      
        backPackBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showBackPack));
    }

    Button* skillBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButton_skill"));
    if (skillBtn)
    {
        
        skillBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showSkillInfo));
    }

    Button* strengthenBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButton_strengthen"));
    if (strengthenBtn)
    {
      
        strengthenBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showStrengthen));
    }

    Button* makeFriendsBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButton_makeFriends"));
    if (makeFriendsBtn)
    {
        makeFriendsBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showMakeFriends));
    }

    Button* destinyBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButton_destiny"));
    if (destinyBtn)
    {
        destinyBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showDestiny));
    }

    Button* mallBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButton_mall"));
    if (mallBtn)
    {
        mallBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showMall));
    }

    Button* canonBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButton_canon"));
    if (canonBtn)
    {
        canonBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showCanon));
    }

    Button* setUpBtn = dynamic_cast<Button*>(ui::Helper::seekWidgetByName(widget,"TextButtonsetUp"));
    if (setUpBtn)
    {
        setUpBtn->addTouchEventListener(this, toucheventselector(GameTabBarMenu::showSetUp));
    }
#endif
	
    return true;
}

void GameTabBarMenu::showRoleInfo(Ref* sender , Control::EventType controlEvent)
{
	m_RoleInfo = RoleInfo::create();
	m_RoleInfo->retain();//这个还不能去掉，去掉会出错
	//Node* m_pNode = CSLoader::createNode("ui/roleInfo/RoleInfoPanel.csb");
	GAME_UILAYER->addBigMenu(m_RoleInfo->getNode());
}

void GameTabBarMenu::showBackPack(Ref* sender , Control::EventType controlEvent)
{
    PropColumnMenu* layer= PropColumnMenu::create();
    GAME_UILAYER->addSmallMenu(layer);
    GAME_UILAYER->getOperationMenu()->joinEditState();
}

void GameTabBarMenu::showSkillInfo(Ref* sender , Control::EventType controlEvent)
{
    SkillTableView* layer = SkillTableView::create();
    GAME_UILAYER->addSmallMenu(layer);
    GAME_UILAYER->getOperationMenu()->joinEditState();
}

void GameTabBarMenu::showStrengthen(Ref* sender , Control::EventType controlEvent)
{
    
}

void GameTabBarMenu::showMakeFriends(Ref* sender , Control::EventType controlEvent)
{
    
}

void GameTabBarMenu::showDestiny(Ref* sender , Control::EventType controlEvent)
{
    
}

void GameTabBarMenu::showMall(Ref* sender , Control::EventType controlEvent)
{
    
}

void GameTabBarMenu::showCanon(Ref* sender , Control::EventType controlEvent)
{
    
}

void GameTabBarMenu::showSetUp(Ref* sender , Control::EventType controlEvent)
{
    GameOptions* layer = GameOptions::create();
    GAME_UILAYER->addBigMenu(layer);
}

void GameTabBarMenu::hideGameTabBarMenu()
{
    this->stopAllActions();
    Size winSize = Director::getInstance()->getWinSize();
    MoveTo* moveTo = MoveTo::create(0.3f, Point(0, -winSize.height));
    EaseSineOut* easeBack = EaseSineOut::create(moveTo);
    this->runAction(easeBack);
}

void GameTabBarMenu::showGameTabBarMenu()
{
    this->stopAllActions();
    Size winSize = Director::getInstance()->getWinSize();
    MoveTo* moveTo = MoveTo::create(0.3f, Point(winSize.width-960, 0));
    EaseSineOut* easeBack = EaseSineOut::create(moveTo);
    this->runAction(easeBack);
}
void GameTabBarMenu::btnCloseCallBack(Ref* sender, ui::TouchEventType touchEvent )
{
	if (ui::TouchEventType::TOUCH_EVENT_BEGAN == touchEvent)
	{
		GAME_UILAYER->hideTabBarMenuCall();
		//m_GameOptions->release(); 不能在这里进行，需要在游戏整体结束的时候进行析构，否则你再次打开的时候会引起崩溃
	}
}