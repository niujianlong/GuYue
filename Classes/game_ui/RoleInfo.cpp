#include "RoleInfo.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
RoleInfo::RoleInfo() :
	m_pNode(NULL),//pointer of load from csb
	m_pBg(NULL),//背景option的精灵
	m_RolePic(NULL),//人物图片
	m_HeadEquipment(NULL),//头部装备
	m_HandEquipment(NULL),//hand equipment
	m_BodyEquipment(NULL), //
	m_FootEquipment(NULL)
{}
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
	button->setPosition(ccpSub(ccpAdd(m_pBg->getPosition(), m_pBg->getContentSize()), button->getContentSize() / 2));
	m_pBg->addChild(button);

	button->addTargetWithActionForControlEvents(GAME_UILAYER,
		cccontrol_selector(GameInfoUIController::removeBigMenuAndButton),
		Control::EventType::TOUCH_UP_INSIDE);


	//  button->setTouchPriority(0);
}
#endif
Rect HeadEquaera;
bool  RoleInfo::init()
{
	FileUtils::getInstance()->addSearchPath("ui/roleInfo");
	m_pNode = CSLoader::createNode("ui/roleInfo/RoleInfoPanel.csb");
	m_pNode->retain();
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
#if 1
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { log("m_pBg touch began %d", cishu++); return true; };
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->setSwallowTouches(true);//不向下传递触摸 add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_pBg);//这里必须是m_pBg，改成this照样会向下传递
#endif
	m_RolePic = dynamic_cast<Sprite*> (m_pNode->getChildByName("RoleInfo_2"));
	//添加触控消息
	auto Role_listener = EventListenerTouchOneByOne::create();
	Role_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { log("m_RolePic touch began %d", cishu++); return true; };
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Role_listener->setSwallowTouches(true);//不向下传递触摸 add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Role_listener, m_RolePic);

	m_HeadEquipment = dynamic_cast<Sprite*> (m_pNode->getChildByName("head_3"));
	HeadEquaera = m_HeadEquipment->getBoundingBox();
	//添加触控消息
	static bool isHeadEquPropShow = false;
	auto Head_listener = EventListenerTouchOneByOne::create();
	Head_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_HeadEquipment touch began %d", cishu++);
		auto pos = m_pNode->convertTouchToNodeSpace(touch);
		if (HeadEquaera.containsPoint(pos))
		{
			Label* labTem = Label::create("Poor Head Equipment!", "fonts/FZKATJW.ttf", 10);
			if (isHeadEquPropShow == false) {//getHeadEquipment()->getBoundingBox().containsPoint(touch->getLocation())) {//判断触摸点是否在目标的范围内
				labTem->setAnchorPoint(Vec2(0.0, 0.0));
				labTem->setPosition(touch->getLocation());
				labTem->setColor(Color3B::YELLOW);
				labTem->enableOutline(Color4B(124, 66, 24, 255), 2);
				Director::getInstance()->getRunningScene()->addChild(labTem, 0, 0xff19);
				isHeadEquPropShow = true;
				return true;
			}
			else
			{
				//既然labTem是一个临时变量，我这里不能通过这个指针来消除label，这里改用tag来消除
				Director::getInstance()->getRunningScene()->removeChildByTag(0xff19);
				isHeadEquPropShow = false;
				return true;
			}
		}
		else
		{
			return false;
		}

	};
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Head_listener->setSwallowTouches(true);//不向下传递触摸 add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Head_listener, m_HeadEquipment);

	return true;
}
Node* RoleInfo::getNode()
{
	return m_pNode;
}

Sprite* RoleInfo::getHeadEquipment()
{
	return m_HeadEquipment;
}