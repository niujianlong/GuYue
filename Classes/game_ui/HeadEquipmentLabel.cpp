#include "HeadEquipmentLabel.h"

bool HeadEquipmentLabel::init()
{
	labelPosition = Vec2(0.0, 0.0);
	m_showText = "Poor Head Equipment!";
	m_label = Label::create(m_showText, "fonts/FZKATJW.ttf", 15);
	m_label->setAnchorPoint(Vec2(0.0, 0.0));
	m_label->setPosition(labelPosition);
	m_label->setColor(Color3B::YELLOW);
	m_label->enableOutline(Color4B(124, 66, 24, 255), 2);
	isHeadEquPropShow = false;
	return true;
}
Label* HeadEquipmentLabel::getLabel()
{
	return m_label;
}
bool HeadEquipmentLabel::getIsHeadEquPropShow()
{
	return isHeadEquPropShow;
}
void HeadEquipmentLabel::setLabelPosition(Vec2 p)
{
	labelPosition = p;
}

bool HeadEquipmentLabel::onTouchBegan(Touch *touch, Event *event)
{
	static int cishu = 0;
	log("m_HeadEquipment touch began %d", cishu++);
	if (isHeadEquPropShow == false) {//getHeadEquipment()->getBoundingBox().containsPoint(touch->getLocation())) {//判断触摸点是否在目标的范围内
		Director::getInstance()->getRunningScene()->addChild(m_label);
		isHeadEquPropShow = true;
		return true;
	}
	else
	{
		Director::getInstance()->getRunningScene()->removeChild(m_label);
		return true;
	}
}