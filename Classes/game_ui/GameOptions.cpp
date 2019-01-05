

#include "GameOptions.h"
#include "GameScene.h"

#if 0
void GameOptions::onEnterTransitionDidFinish()
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
#endif // 0
bool  GameOptions::init()
{
	FileUtils::getInstance()->addSearchPath("ui/tabbarMenu");
	m_VolNode = CSLoader::createNode("ui/tabbarMenu/SetUpNode.csb");
	m_VolNode->retain();
	m_VolBtn = dynamic_cast<Button*> (m_VolNode->getChildByName("Horn"));
	m_VolBtn->retain();
	m_VolSlider = dynamic_cast<Slider*> (m_VolNode->getChildByName("Volume"));
	m_VolValText = dynamic_cast<Text*> (m_VolNode->getChildByName("Volvalue"));

	//Ìí¼ÓUIÂß¼­²¿·Ö
	m_VolBtn->addTouchEventListener(this, toucheventselector(GameOptions::volBtnCallBack));


	return true;
}



Node* GameOptions::getNode(void)
{
	return m_VolNode;
}

void GameOptions::volBtnCallBack(Ref* sender, ui::TouchEventType touchEvent)
{
	static bool isOffSound = false;
	if (ui::TouchEventType::TOUCH_EVENT_ENDED == touchEvent)
	{
		if (false == isOffSound)
		{
			m_VolBtn->loadTextureNormal("ui/tabbarMenu/button_volume_off.png");
			isOffSound = true;
		}
		else
		{
			m_VolBtn->loadTextureNormal("ui/tabbarMenu/button_volu.png");
			isOffSound = false;
		}
	}

}