

#ifndef __mir9__GameTabBarMenu__
#define __mir9__GameTabBarMenu__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/cocosgui.h"
#include "cocostudio/cocostudio.h"
#include "RoleInfo.h"
#include "TabUiControl.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
class GameTabBarMenu: public Layer {
    
	CC_SYNTHESIZE_READONLY(RoleInfo*, m_RoleInfo, RoleInfo);
public:
    
    CREATE_FUNC(GameTabBarMenu);
    
    bool init();
    
    void hideGameTabBarMenu();
    
    void showGameTabBarMenu();
public:
    //Control::State::NORMAL
    //Control::EventType controlEvent
    void showRoleInfo(Ref* sender = NULL, Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
    
    void showBackPack(Ref* sender = NULL, Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
    
    void showSkillInfo(Ref* sender = NULL, Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
    
    void showStrengthen(Ref* sender = NULL, Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
    
    void showMakeFriends(Ref* sender = NULL, Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
    
    void showDestiny(Ref* sender = NULL, Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
    
    void showMall(Ref* sender = NULL, Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
    
    void showCanon(Ref* sender = NULL,Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
    
    void showSetUp(Ref* sender = NULL, Control::EventType controlEvent= Control::EventType::TOUCH_UP_INSIDE);
	void btnCloseCallBack(Ref* sender = NULL, ui::TouchEventType touchEvent = ui::TouchEventType::TOUCH_EVENT_BEGAN);

private:
	TabUiControl* m_TabUiControl;

};


#endif /* defined(__mir9__GameTabBarMenu__) */
