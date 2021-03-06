#include "RoleInfo.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "FontChina.h"
RoleInfo::RoleInfo() :
	m_pNode(NULL),//pointer of load from csb
	//m_pBg(NULL),//背景option的精灵
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
bool  RoleInfo::init()
{
	FileUtils::getInstance()->addSearchPath("ui/roleInfo");
	
	m_pNode = CSLoader::createNode("ui/roleInfo/RoleInfoPanel.csb");
	//m_pNode->retain();
	/*//由于addBigMenu时候把这个Node放在了屏幕中心的位置
	所以这里要强行把Node的锚点从00设置成0.5并且把忽略锚点设置为false
	这样的话这个Node就可以显示在屏幕中心的位置*/
	//m_pNode->ignoreAnchorPointForPosition(false);
	//m_pNode->setAnchorPoint(Vec2(0.5, 0.5));
	static int cishu = 0;
#if 0
	m_pBg = dynamic_cast<Sprite*> (m_pNode->getChildByName("options_1"));
	m_pBg->retain();
	
	//添加触控消息
	auto Bg_listener = EventListenerTouchOneByOne::create();
	Bg_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { log("m_pBg touch began %d", cishu++); return true; };
	/*这个设置不能去掉，这个存在的目的就是把上层没有处理的触摸在这里进行处理，并且不向下传递给地图
	导致角色的移动*/
	//Bg_listener->setSwallowTouches(true);//不向下传递触摸 add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Bg_listener, m_pBg);//这里必须是m_pBg，改成this照样会向下传递
#endif
	m_RolePic = dynamic_cast<ImageView*> (m_pNode->getChildByName("role"));
	//m_RolePic->retain();
	//添加触控消息
	m_RolePic->addTouchEventListener(this, toucheventselector(RoleInfo::roleCallBack));
#if 0
	auto Role_listener = EventListenerTouchOneByOne::create();
	Role_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { log("m_RolePic touch began %d", cishu++); return true; };
	//Role_listener->setSwallowTouches(true);//不向下传递触摸 add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Role_listener, m_RolePic);
#endif // 0


	m_HeadEquipment = dynamic_cast<ImageView*> (m_pNode->getChildByName("head"));
	//m_HeadEquipment->retain();
	//添加触控消息
	m_HeadEquipment->addTouchEventListener(this, toucheventselector(RoleInfo::headCallBack));

#if 0
	auto Head_listener = EventListenerTouchOneByOne::create();
	Head_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_HeadEquipment touch began %d", cishu++);
		Rect HeadEquaera = m_HeadEquipment->getBoundingBox();  //(0,0,0,0);
		auto pos = m_pNode->convertTouchToNodeSpace(touch);
		if (HeadEquaera.containsPoint(pos))
		{
			Label* labTem = Label::create(FontChina::G2U("这是一件普通的头盔"), "fonts/FZKATJW.ttf", 20);
			if (isHeadEquPropShow == false) {//getHeadEquipment()->getBoundingBox().containsPoint(touch->getLocation())) {//判断触摸点是否在目标的范围内
				labTem->setAnchorPoint(Vec2(0.0, 0.0));
				labTem->setPosition(touch->getLocation());
				labTem->setColor(Color3B::RED);
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
			if (isHeadEquPropShow == true)
			{
				Director::getInstance()->getRunningScene()->removeChildByTag(0xff19);
				isHeadEquPropShow = false;
			}
			return false;
		}

	};
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	//Head_listener->setSwallowTouches(true);//不向下传递触摸 add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Head_listener, m_HeadEquipment);
#endif

	m_HandEquipment = dynamic_cast<ImageView*> (m_pNode->getChildByName("hand"));
	//m_HandEquipment->retain();
	m_HandEquipment->addTouchEventListener(this, toucheventselector(RoleInfo::handCallBack));

#if 0
	auto Hand_listener = EventListenerTouchOneByOne::create();
	Hand_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_HandEquipment touch began %d", cishu++);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Hand_listener, m_HandEquipment);

#endif // 0


	m_BodyEquipment = m_pNode->getChildByName<ImageView*>("body");// dynamic_cast<ImageView*> ();
	//m_BodyEquipment->retain();
	m_BodyEquipment->addTouchEventListener(this, toucheventselector(RoleInfo::bodyCallBack));

#if 0
	auto Body_listener = EventListenerTouchOneByOne::create();
	Body_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_BodyEquipment touch began %d", cishu++);
		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Body_listener, m_BodyEquipment);

#endif // 0


	m_FootEquipment = dynamic_cast<ImageView*> (m_pNode->getChildByName("foot"));
	//m_FootEquipment->retain();
	m_FootEquipment->addTouchEventListener(this, toucheventselector(RoleInfo::footCallBack));

#if 0
	auto Foot_listener = EventListenerTouchOneByOne::create();
	Foot_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_FootEquipment touch began %d", cishu++);
		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Foot_listener, m_FootEquipment);

#endif // 0

#if 0
	//把关闭按钮放在最上层
	ControlButton* button = ControlButton::create(Scale9Sprite::create("ui/closed_normal.png"));
	button->setBackgroundSpriteForState(Scale9Sprite::create("ui/closed_selected.png"), Control::State::HIGH_LIGHTED);
	button->setPreferredSize(Size(57, 58));
	button->setPosition(ccpSub(ccpAdd(m_pBg->getPosition(), m_pBg->getContentSize()), button->getContentSize() / 2));
	m_pBg->addChild(button);

	button->addTargetWithActionForControlEvents(GAME_UILAYER,
		cccontrol_selector(GameInfoUIController::removeBigMenuAndButton),
		Control::EventType::TOUCH_UP_INSIDE);
#endif
	return true;
}
Node* RoleInfo::getNode()
{
	return m_pNode;
}

void RoleInfo::roleCallBack(Ref* sender, ui::TouchEventType touchEvent)
{
	log("role pic touchEvent = %d", touchEvent);
}
void RoleInfo::headCallBack(Ref* sender, ui::TouchEventType touchEvent)
{
	log("head pic touchEvent = %d", touchEvent);
	//static bool isHeadEquPropShow = false;
	if (ui::TouchEventType::TOUCH_EVENT_BEGAN == touchEvent) {//getHeadEquipment()->getBoundingBox().containsPoint(touch->getLocation())) {//判断触摸点是否在目标的范围内
		Label* labTem = Label::create(FontChina::G2U("这是一件普通的头盔"), "fonts/FZKATJW.ttf", 20);
		labTem->setAnchorPoint(Vec2(0.0, 1.0));
		auto Vec2Test = static_cast<ImageView*>(sender)->getPosition();
		//getNode()->convertToNodeSpace(m_HeadEquipment->getTouchMovePosition());
		//把这个label设置到这个ImageView的右上角
		labTem->setPosition(Vec2Test + static_cast<ImageView*>(sender)->getContentSize() / 2);//(getNode()->convertToNodeSpace(m_HeadEquipment->getTouchMovePosition()));
		labTem->setColor(Color3B::RED);
		labTem->enableOutline(Color4B(124, 66, 24, 255), 2);
		Director::getInstance()->getRunningScene()->addChild(labTem, 0, 0xff19);
		//isHeadEquPropShow = true;
		return;
	}
	if (ui::TouchEventType::TOUCH_EVENT_ENDED == touchEvent)
	{
		//既然labTem是一个临时变量，我这里不能通过这个指针来消除label，这里改用tag来消除
		Director::getInstance()->getRunningScene()->removeChildByTag(0xff19);
		//isHeadEquPropShow = false;
		return;
	}
}
void RoleInfo::handCallBack(Ref* sender, ui::TouchEventType touchEvent)
{
	log("hand pic touch = %d", touchEvent);
}
void RoleInfo::footCallBack(Ref* sender, ui::TouchEventType touchEvent)
{
	log("foot pic touch = %d", touchEvent);
}
void RoleInfo::bodyCallBack(Ref* sender, ui::TouchEventType touchEvent)
{
	log("body pic touch = %d", touchEvent);
}
void RoleInfo::roleInfoReleaseAll()
{
	this->m_BodyEquipment->release();
	this->m_FootEquipment->release();
	this->m_HandEquipment->release();
	this->m_HeadEquipment->release();
	this->m_RolePic->release();
	//this->m_pBg->release();
	this->m_pNode->release();
	this->release();
}