

#include "PropColumn.h"
#include "GameScene.h"

#define GRID_WIDTH 39 //
#define GRID_HEIGHT 35
#define PROP_X 284
#define PROP_Y 74
#define COL 5 //背包格显示5列
#define ROW 7 //背包格显示7行

PropColumnMenu::PropColumnMenu()
	:m_editProp(NULL)
{
	m_propVec = new PropIconShow*[COL*ROW];
	for (unsigned int i = 0; i < COL*ROW; i++)
	{
		m_propVec[i] = NULL;
	}
	m_CurrentSlectProp = 0;
}

PropColumnMenu::~PropColumnMenu()
{
	delete[] m_propVec;
}

void PropColumnMenu::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->updatePropVecPoint();
}

bool PropColumnMenu::init()
{
	if (!Layer::init())
		return false;

	//this->setTouchEnabled(true);
	FileUtils::getInstance()->addSearchPath("ui/tabbarMenu");
	m_Node = CSLoader::createNode("ui/tabbarMenu/BackPack.csb");
	m_Node->retain();
	Sprite* bg = dynamic_cast<Sprite*>(m_Node->getChildByName("Sprite_1"));//Sprite::create("ui/prop_column.png");
	m_head = dynamic_cast<Button*>(m_Node->getChildByName("head"));
	m_EquipVec.push_back(m_head);
	m_foot = m_Node->getChildByName<Button*>("foot");
	m_EquipVec.push_back(m_foot);
	m_hand = m_Node->getChildByName<Button*>("hand");
	m_EquipVec.push_back(m_hand);
	m_body = m_Node->getChildByName<Button*>("body");
	m_EquipVec.push_back(m_body);
	//m_head ->retain();
	m_Node->setPosition(Vec2(0.0, 0.0));
#if 0
	auto pScrollView = m_Node->getChildByName<ui::ScrollView*>("ScrollView_1");
	pScrollView->setClippingType(ui::Layout::ClippingType::SCISSOR);
#endif
	this->addChild(m_Node);
	m_propColumn = LayerColor::create(ccc4(255, 255, 255, 0), GRID_WIDTH*COL, GRID_HEIGHT*ROW);
	m_propColumn->setContentSize(Size(GRID_WIDTH*COL, GRID_HEIGHT*ROW));
	m_propColumn->setPosition(Point(PROP_X, PROP_Y));
	auto propColumn_Listenner = EventListenerTouchOneByOne::create();
	propColumn_Listenner->onTouchBegan = CC_CALLBACK_2(PropColumnMenu::onTouchBegan, this);
	propColumn_Listenner->onTouchMoved = CC_CALLBACK_2(PropColumnMenu::onTouchMoved, this);
	propColumn_Listenner->onTouchEnded = CC_CALLBACK_2(PropColumnMenu::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(propColumn_Listenner, m_propColumn);

	bg->addChild(m_propColumn);

#if 0
	ControlButton* button = ControlButton::create(Scale9Sprite::create("ui/closed_normal.png"));
	button->setBackgroundSpriteForState(Scale9Sprite::create("ui/closed_selected.png"), Control::State::HIGH_LIGHTED);
	button->setPreferredSize(Size(57, 58));
	button->setPosition(ccpSub(ccpAdd(bg->getPosition(), bg->getContentSize() / 2), button->getContentSize() / 2));
	this->addChild(button);
	button->addTargetWithActionForControlEvents(GAME_UILAYER, cccontrol_selector(GameInfoUIController::removeSmallMenuAndButton), Control::EventType::TOUCH_UP_INSIDE);
#endif // 0

	// button->setTouchPriority(0);

	for (int i = 0; i < 12; i++)
	{
		m_propVec[i] = PropIconShow::create(PropSystem::getPropInfo(i + 1));
		m_propColumn->addChild(m_propVec[i]);
	}

	return true;
}

void PropColumnMenu::updatePropVecPoint()
{
	for (unsigned int j = 0; j < ROW; j++)
	{
		for (unsigned int i = 0; i < COL; i++)
		{
			if (m_propVec[j*COL + i])
			{
				m_propVec[j*COL + i]->setPosition(Point(GRID_WIDTH * (i + 0.5f), GRID_HEIGHT * (ROW - j - 0.5f)));
			}
		}
	}
}

Rect PropColumnMenu::getPropRect(int i)
{
	Rect rect;
	int x = i % COL;
	int y = i / COL;
	rect.origin = Point(GRID_WIDTH * x, GRID_HEIGHT * (ROW - y - 1));
	rect.origin = m_propColumn->convertToWorldSpace(rect.origin);
	rect.size = Size(GRID_WIDTH, GRID_HEIGHT);
	return rect;
}

Point PropColumnMenu::getPropPoint(int i)
{
	int x = i % COL;
	int y = i / COL;
	return Point(GRID_WIDTH * (x + 0.5f), GRID_HEIGHT * (ROW - y - 0.5f));
}

void PropColumnMenu::propHoming(int i)
{
	if (i < COL*ROW && m_propVec[i])
	{
		Point point = this->getPropPoint(i);
		m_propVec[i]->setPosition(point);
	}
}

void PropColumnMenu::swapProp(int a, int b)
{
	if (a < COL*ROW && b < COL*ROW)
	{
		PropIconShow* tmp = m_propVec[a];
		m_propVec[a] = m_propVec[b];
		m_propVec[b] = tmp;
	}

	this->propHoming(a);
	this->propHoming(b);
}

//void PropColumnMenu::registerWithTouchDispatcher()
//{
//    CCTouchDispatcher* touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
//	touchDispatcher->addTargetedDelegate(this, 0, true);
//}

bool PropColumnMenu::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	log("PropColumnMenu::onTouchBegan");
	Point point = pTouch->getLocation();

	Rect rect = Rect::ZERO;
	rect.origin = m_propColumn->convertToWorldSpace(Point::ZERO);
	rect.size = m_propColumn->getContentSize();

	if (!rect.containsPoint(point))
		return false;

	for (int i = 0; i < COL*ROW; i++)
	{
		if (m_propVec[i] && this->getPropRect(i).containsPoint(point))
		{
			m_propVec[i]->setVisible(false);
			m_editProp = PropIconShow::create(m_propVec[i]->getPropInfo());
			m_editProp->setPosition(point);
			GAME_UILAYER->addChild(m_editProp);
			m_editProp->setTag(i);
			m_editProp->setOpacity(127);
			m_CurrentSlectProp = i;
			break;
		}
	}

	if (m_editProp == NULL)
		return false;

	return true;
}

void PropColumnMenu::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	log("PropColumnMenu::onTouchMoved");

	Point point = pTouch->getLocation();

	m_editProp->setPosition(point);

	for (int i = 0; i < m_EquipVec.size(); ++i)
	{
		//ControlButton* btn = GAME_UILAYER->getOperationMenu()->getDrugsBtn();
		//Button* btn = dynamic_cast<Button*>(m_Node->getChildByName("head"));
		Rect rect;
		rect.origin = m_EquipVec[i]->convertToWorldSpace(Point::ZERO);
		rect.size = m_EquipVec[i]->getContentSize();
		if (rect.containsPoint(point))
		{
			//CC_BREAK_IF(m_editProp->getOpacity() == 255);
			//m_editProp->setOpacity(255);
			m_EquipVec[i]->stopAllActions();
			ScaleTo* scaleTo = ScaleTo::create(0.1f, 1.2f);
			m_EquipVec[i]->runAction(scaleTo);
		}
		else
		{
			//CC_BREAK_IF(m_editProp->getOpacity() == 127);
			m_editProp->setOpacity(127);
			m_EquipVec[i]->stopAllActions();
			ScaleTo* scaleTo = ScaleTo::create(0.1f, 1.0f);
			m_EquipVec[i]->runAction(scaleTo);
		}
	}

}

void PropColumnMenu::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	log("PropColumnMenu::onTouchEnded");

	Point point = pTouch->getLocation();

	Rect rect = Rect::ZERO;
	rect.origin = m_propColumn->convertToWorldSpace(Point::ZERO);
	rect.size = m_propColumn->getContentSize();

	if (rect.containsPoint(point))
	{
		point = m_propColumn->convertToNodeSpace(point);
		int x = (int)point.x / GRID_WIDTH;
		int y = (int)point.y / GRID_HEIGHT;
		y = ROW - y - 1;
		m_propVec[m_editProp->getTag()]->setVisible(true);
		this->swapProp(m_editProp->getTag(), y*COL + x);
	}
	else
	{
		for (int i = 0; i < m_EquipVec.size(); i++)
		{
			Rect rect;
			rect.origin = m_EquipVec[i]->convertToWorldSpace(Point::ZERO);
			rect.size = m_EquipVec[i]->getContentSize();
			if (rect.containsPoint(point))
			{
				//GAME_UILAYER->getOperationMenu()->addDrugs(2001);
				//ControlButton* btn = GAME_UILAYER->getOperationMenu()->getDrugsBtn();
				m_editProp->retain();
				m_editProp->setOpacity(255);
				GAME_UILAYER->removeChild(m_editProp, false);
				//m_editProp->removeFromParent();
				//GAME_UILAYER->removeObject(m_editProp,false);
				m_editProp->setPosition(m_EquipVec[i]->getContentSize() / 2);
				m_EquipVec[i]->stopAllActions();
				ScaleTo* scaleTo = ScaleTo::create(0.1f, 1.0f);
				m_EquipVec[i]->runAction(scaleTo);
				m_EquipVec[i]->addChild(m_editProp);
				m_editProp->release();
				break;
				//m_propVec[m_editProp->getTag()]->removeFromParent();
				//m_propVec[m_editProp->getTag()] = NULL;
			}
			else
			{
				m_editProp->setVisible(false);
				m_propVec[m_CurrentSlectProp]->setVisible(true);
			}
	
#if 0  //老的处理是放在地图上，我现在的处理是想让它回归原位。
			else
			{
				float r = CCRANDOM_0_1();
				if (r == 1)
					r = 0;

				BgMap* bgMap = GAME_SCENE->getCurrBgMap();
				MapPoint playerPosition = MapPoint(Player::sharePlayer()->getPosition());

				MapPoint point = MapPointZero;
				std::vector<MapPoint> mapVec;
				M_INT lenght = 1;
				do
				{
					mapVec = playerPosition.getMapPointVectorForDistance(lenght);
					unsigned int index = 0;
					for (; index < mapVec.size(); index++)
					{
						if (GAME_SCENE->getMapPointForProp(MapPoint(mapVec.at(index))) == NULL)
						{
							point = MapPoint(mapVec.at(index));
						}
					}

					CC_BREAK_IF(!point.equals(MapPointZero));

					lenght++;
				} while (1);


				PropIconShow* show = m_propVec[m_editProp->getTag()];
				m_propVec[m_editProp->getTag()] = NULL;
				show->setVisible(true);
				show->retain();
				show->removeFromParent();
				show->setPosition(point.getCCPointValue());
				bgMap->addChild(show, BgMap::getZOrderZero(bgMap));
				show->release();
				show->setScale(0.8f);

				GAME_SCENE->insterMapPointForProp(show, point);

				show->setOpacity(0);
				FadeIn* fadeIn = FadeIn::create(0.1f);
				JumpBy* jumpBy = JumpBy::create(0.3f, Point::ZERO, 30, 1);
				Spawn* spawn = Spawn::create(fadeIn, jumpBy, NULL);
				show->runAction(spawn);

			}
#endif
		}
	}
	//m_editProp->removeFromParent();
	//m_editProp = NULL;
}