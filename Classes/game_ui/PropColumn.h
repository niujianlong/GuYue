

#ifndef __mir9__PropColumn__
#define __mir9__PropColumn__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "PropIconShow.h"
#include <vector>
USING_NS_CC;
USING_NS_CC_EXT;

class EquipMentBtnInfo {
public:
	ui::Button* btn;
	int EquipmentType;
	bool haveEquiped;
};

class PropColumnMenu: public Layer {
    
    LayerColor* m_propColumn;
    
    PropIconShow** m_propVec;
    
    PropIconShow* m_editProp;
private:
	Node* m_Node;
	ui::Button* m_head;
	ui::Button* m_foot;
	ui::Button* m_hand;
	ui::Button* m_body;
	std::vector<EquipMentBtnInfo*> m_EquipVec;
	int m_CurrentSlectProp;
	int m_PreSlectProp;

public:
    
    PropColumnMenu();
    
    ~PropColumnMenu();
    
    CREATE_FUNC(PropColumnMenu);
    
    bool init();
    
    void onEnterTransitionDidFinish();
    
protected:
    
   // void registerWithTouchDispatcher(void);
    
    bool onTouchBegan(Touch *pTouch, Event *pEvent);
    
    void onTouchMoved(Touch *pTouch, Event *pEvent);
    
	void onTouchEnded(Touch *pTouch, Event *pEvent);
    
    void updatePropVecPoint();
    
    Rect getPropRect(int i);
    
    Point getPropPoint(int i);
    
    void propHoming(int i);
    
    void swapProp(int a, int b);
};

#endif /* defined(__mir9__PropColumn__) */
