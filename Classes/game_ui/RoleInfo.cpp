#include "RoleInfo.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "FontChina.h"
RoleInfo::RoleInfo() :
	m_pNode(NULL),//pointer of load from csb
	m_pBg(NULL),//����option�ľ���
	m_RolePic(NULL),//����ͼƬ
	m_HeadEquipment(NULL),//ͷ��װ��
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
	m_pNode->retain();
	/*//����addBigMenuʱ������Node��������Ļ���ĵ�λ��
	��������Ҫǿ�а�Node��ê���00���ó�0.5���ҰѺ���ê������Ϊfalse
	�����Ļ����Node�Ϳ�����ʾ����Ļ���ĵ�λ��*/
	//m_pNode->ignoreAnchorPointForPosition(false);
	//m_pNode->setAnchorPoint(Vec2(0.5, 0.5));
	static int cishu = 0;
#if 0
	m_pBg = dynamic_cast<Sprite*> (m_pNode->getChildByName("options_1"));
	m_pBg->retain();
	
	//��Ӵ�����Ϣ
	auto Bg_listener = EventListenerTouchOneByOne::create();
	Bg_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { log("m_pBg touch began %d", cishu++); return true; };
	/*������ò���ȥ����������ڵ�Ŀ�ľ��ǰ��ϲ�û�д���Ĵ�����������д������Ҳ����´��ݸ���ͼ
	���½�ɫ���ƶ�*/
	//Bg_listener->setSwallowTouches(true);//�����´��ݴ��� add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Bg_listener, m_pBg);//���������m_pBg���ĳ�this���������´���
#endif
	m_RolePic = dynamic_cast<Sprite*> (m_pNode->getChildByName("RoleInfo_2"));
	m_RolePic->retain();
	//��Ӵ�����Ϣ
	auto Role_listener = EventListenerTouchOneByOne::create();
	Role_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { log("m_RolePic touch began %d", cishu++); return true; };
	//Role_listener->setSwallowTouches(true);//�����´��ݴ��� add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Role_listener, m_RolePic);

	m_HeadEquipment = dynamic_cast<Sprite*> (m_pNode->getChildByName("head_3"));
	m_HeadEquipment->retain();
	//��Ӵ�����Ϣ
	static bool isHeadEquPropShow = false;
	auto Head_listener = EventListenerTouchOneByOne::create();
	Head_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_HeadEquipment touch began %d", cishu++);
		Rect HeadEquaera = m_HeadEquipment->getBoundingBox();  //(0,0,0,0);
		auto pos = m_pNode->convertTouchToNodeSpace(touch);
		if (HeadEquaera.containsPoint(pos))
		{
			Label* labTem = Label::create(FontChina::G2U("����һ����ͨ��ͷ��"), "fonts/FZKATJW.ttf", 20);
			if (isHeadEquPropShow == false) {//getHeadEquipment()->getBoundingBox().containsPoint(touch->getLocation())) {//�жϴ������Ƿ���Ŀ��ķ�Χ��
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
				//��ȻlabTem��һ����ʱ�����������ﲻ��ͨ�����ָ��������label���������tag������
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
	//Head_listener->setSwallowTouches(true);//�����´��ݴ��� add by njl
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Head_listener, m_HeadEquipment);

	m_HandEquipment = dynamic_cast<Sprite*> (m_pNode->getChildByName("hand_4"));
	m_HandEquipment->retain();
	auto Hand_listener = EventListenerTouchOneByOne::create();
	Hand_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_HandEquipment touch began %d", cishu++);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Hand_listener, m_HandEquipment);


	m_BodyEquipment = dynamic_cast<Sprite*> (m_pNode->getChildByName("body_5"));
	m_BodyEquipment->retain();
	auto Body_listener = EventListenerTouchOneByOne::create();
	Body_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_BodyEquipment touch began %d", cishu++);
		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Body_listener, m_BodyEquipment);


	m_FootEquipment = dynamic_cast<Sprite*> (m_pNode->getChildByName("foot_6"));
	m_FootEquipment->retain();
	auto Foot_listener = EventListenerTouchOneByOne::create();
	Foot_listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {
		log("m_FootEquipment touch began %d", cishu++);
		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Foot_listener, m_FootEquipment);

#if 0
	//�ѹرհ�ť�������ϲ�
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


void RoleInfo::roleInfoReleaseAll()
{
	this->m_BodyEquipment->release();
	this->m_FootEquipment->release();
	this->m_HandEquipment->release();
	this->m_HeadEquipment->release();
	this->m_RolePic->release();
	this->m_pBg->release();
	this->m_pNode->release();
	this->release();
}