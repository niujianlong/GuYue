#ifndef __mir9__RoleInfo__
#define __mir9__RoleInfo__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/UIImageView.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RoleInfo: public Node
{
private:
	RoleInfo();
	Node* m_pNode;
	ui::ImageView* m_RolePic;//人物图片
	ui::ImageView* m_HeadEquipment;//头部装备
	ui::ImageView* m_HandEquipment;//hand equipment
	ui::ImageView* m_BodyEquipment; //
	ui::ImageView* m_FootEquipment;
private:
	void roleCallBack(Ref* sender = NULL, ui::TouchEventType touchEvent = ui::TouchEventType::TOUCH_EVENT_BEGAN);
	void headCallBack(Ref* sender = NULL, ui::TouchEventType touchEvent = ui::TouchEventType::TOUCH_EVENT_BEGAN);
	void handCallBack(Ref* sender = NULL, ui::TouchEventType touchEvent = ui::TouchEventType::TOUCH_EVENT_BEGAN);
	void footCallBack(Ref* sender = NULL, ui::TouchEventType touchEvent = ui::TouchEventType::TOUCH_EVENT_BEGAN);
	void bodyCallBack(Ref* sender = NULL, ui::TouchEventType touchEvent = ui::TouchEventType::TOUCH_EVENT_BEGAN);


public:
	bool init();
	Node* getNode();
	void roleInfoReleaseAll();
    CREATE_FUNC(RoleInfo);
    
    //void onEnterTransitionDidFinish();
};

#endif /* defined(__mir9__RoleInfo__) */
