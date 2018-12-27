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
	FileUtils::getInstance()->addSearchPath("ui\roleInfo");
	m_pNode = CSLoader::createNode("ui/roleInfo/RoleInfoPanel.csb");
	/*//����addBigMenuʱ������Node��������Ļ���ĵ�λ��
	��������Ҫǿ�а�Node��ê���00���ó�0.5���ҰѺ���ê������Ϊfalse
	�����Ļ����Node�Ϳ�����ʾ����Ļ���ĵ�λ��*/
	m_pNode->ignoreAnchorPointForPosition(false); 
	m_pNode->setAnchorPoint(Vec2(0.5, 0.5));
	return true;
}
Node* RoleInfo::getNode()
{
	return m_pNode;
}