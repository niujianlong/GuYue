

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
bool GameOptions::isOffSound = false;

bool  GameOptions::init()
{
	FileUtils::getInstance()->addSearchPath("ui/tabbarMenu");
	m_VolNode = CSLoader::createNode("ui/tabbarMenu/SetUpNode.csb");
	m_VolNode->retain();
	m_VolBtn = dynamic_cast<Button*> (m_VolNode->getChildByName("Horn"));
	m_VolBtn->retain();
	m_VolSlider = dynamic_cast<Slider*> (m_VolNode->getChildByName("Volume"));
	m_VolSlider->retain();
	m_VolSlider->setPercent(m_VolVal);
	m_VolValText = dynamic_cast<Text*> (m_VolNode->getChildByName("Volvalue"));
	m_VolValText->retain();
	m_VolValText->setText(std::to_string(m_VolVal));

	//Ìí¼ÓUIÂß¼­²¿·Ö
	m_VolBtn->addTouchEventListener(this, toucheventselector(GameOptions::volBtnCallBack));
	m_VolSlider->addEventListener(CC_CALLBACK_2(GameOptions::volSliderCallBack),this);

	return true;
}



Node* GameOptions::getNode(void)
{
	return m_VolNode;
}

void GameOptions::volBtnCallBack(Ref* sender, ui::TouchEventType touchEvent)
{
	if (ui::TouchEventType::TOUCH_EVENT_ENDED == touchEvent)
	{
		if (false == isOffSound)
		{
			m_VolBtn->loadTextureNormal("ui/tabbarMenu/button_volume_off.png");
			m_VolVal = 0;
			m_VolSlider->setPercent(0);
			m_VolValText->setText(std::to_string(m_VolVal));
			isOffSound = true;
		}
		else
		{
			m_VolBtn->loadTextureNormal("ui/tabbarMenu/button_volu.png");
			isOffSound = false;
		}
	}

}

void GameOptions::volSliderCallBack(Ref* sender, Slider::EventType touchEvent)
{
	if (ui::TouchEventType::TOUCH_EVENT_ENDED == touchEvent)
	{
		m_VolVal = static_cast<Slider*> (sender)->getPercent();
		if (0 == m_VolVal)
		{
			m_VolBtn->loadTextureNormal("ui/tabbarMenu/button_volume_off.png");
			isOffSound = true;
		}
		else
		{
			m_VolBtn->loadTextureNormal("ui/tabbarMenu/button_volu.png");
			isOffSound = false;
		}
		m_VolValText->setText(std::to_string(m_VolVal));
	}
}
void GameOptions::gameOptionsReleaseAll(void)
{
	m_VolNode->release();
	m_VolBtn->release();
	m_VolSlider->release();
	m_VolValText->release();
}