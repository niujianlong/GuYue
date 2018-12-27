#include "RoleInfo.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

#if 0
void RoleInfo::onEnterTransitionDidFinish()
{
    CCNode::onEnterTransitionDidFinish();
    
    m_pBg = Sprite::create("ui/options.png");
    m_pBg->setPosition(Vec2::ZERO);
    this->addChild(m_pBg, -1);
    
    ControlButton* button = ControlButton::create(Scale9Sprite::create("ui/closed_normal.png"));
    button->setBackgroundSpriteForState(Scale9Sprite::create("ui/closed_selected.png"), Control::State::HIGH_LIGHTED);
    button->setPreferredSize(Size(57, 58));
    button->setPosition(ccpSub(ccpAdd(m_pBg->getPosition(), m_pBg->getContentSize()), button->getContentSize()/2));
    m_pBg->addChild(button);
    
    button->addTargetWithActionForControlEvents(GAME_UILAYER,
                                                cccontrol_selector(GameInfoUIController::removeBigMenuAndButton),
                                                Control::EventType::TOUCH_UP_INSIDE );
    
    
  //  button->setTouchPriority(0);
}
#endif
bool  RoleInfo::init()
{
	FileUtils::getInstance()->addSearchPath("ui/roleInfo");
	m_pNode = CSLoader::createNode("ui/roleInfo/RoleInfoPanel.csb");
	/*//由于addBigMenu时候把这个Node放在了屏幕中心的位置
	所以这里要强行把Node的锚点从00设置成0.5并且把忽略锚点设置为false
	这样的话这个Node就可以显示在屏幕中心的位置*/
	m_pNode->ignoreAnchorPointForPosition(false); 
	m_pNode->setAnchorPoint(Vec2(0.5, 0.5));

	m_pBg = dynamic_cast<Sprite*> (m_pNode->getChildByName("options_1"));
	ControlButton* button = ControlButton::create(Scale9Sprite::create("ui/closed_normal.png"));
	button->setBackgroundSpriteForState(Scale9Sprite::create("ui/closed_selected.png"), Control::State::HIGH_LIGHTED);
	button->setPreferredSize(Size(57, 58));
	button->setPosition(ccpSub(ccpAdd(m_pBg->getPosition(), m_pBg->getContentSize()), button->getContentSize() / 2));
	m_pBg->addChild(button);

	button->addTargetWithActionForControlEvents(GAME_UILAYER,
		cccontrol_selector(GameInfoUIController::removeBigMenuAndButton),
		Control::EventType::TOUCH_UP_INSIDE);

	//添加触控消息
	static int cishu = 0;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { log("RoleInfo touch began %d", cishu++); return true; };
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->setSwallowTouches(true);//不向下传递触摸 add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_pBg);

	return true;
}
Node* RoleInfo::getNode()
{
	return m_pNode;
}