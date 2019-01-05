

#ifndef __mir9__GameOptions__
#define __mir9__GameOptions__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/UIButton.h"
#include "ui/UISlider.h"
#include "ui/UIText.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class GameOptions: public Node
{
private:
    Node* m_VolNode;
	Button* m_VolBtn;
	Slider* m_VolSlider;
	Text*  m_VolValText; 
	int m_VolVal = 10;
	static bool isOffSound;
public:
	bool init(void);
    CREATE_FUNC(GameOptions);
	Node* getNode(void);
	void gameOptionsReleaseAll(void);
private:
	void volBtnCallBack(Ref* sender = NULL, ui::TouchEventType touchEvent = ui::TouchEventType::TOUCH_EVENT_BEGAN);
	void volSliderCallBack(Ref* sender = NULL, Slider::EventType touchEvent = Slider::EventType::ON_PERCENTAGE_CHANGED);
	int getVolValue(void);

    //void onEnterTransitionDidFinish();
};

#endif /* defined(__mir9__GameOptions__) */
