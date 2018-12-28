#pragma once
#include "cocos2d.h"
#include "string"
USING_NS_CC;
class HeadEquipmentLabel :public Label
{
private:
	Label* m_label;
	bool isHeadEquPropShow;
	std::string m_showText;
	Vec2 labelPosition;
public:
	Label* getLabel();
	bool getIsHeadEquPropShow();
	bool init();
	void setLabelPosition(Vec2 p);
	bool onTouchBegan(Touch *touch, Event *event);
	CREATE_FUNC(HeadEquipmentLabel);

};