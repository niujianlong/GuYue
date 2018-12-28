#ifndef __mir9__RoleInfo__
#define __mir9__RoleInfo__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RoleInfo: public Node
{
private:
	RoleInfo();
	Node* m_pNode;//pointer of load from csb
    Sprite* m_pBg;//背景option的精灵
	Sprite* m_RolePic;//人物图片
	Sprite* m_HeadEquipment;//头部装备
	Sprite* m_HandEquipment;//hand equipment
	Sprite* m_BodyEquipment; //
	Sprite* m_FootEquipment;

public:
	bool init();
	Node* getNode();
	Sprite* getHeadEquipment();
    CREATE_FUNC(RoleInfo);
    
    //void onEnterTransitionDidFinish();
};

#endif /* defined(__mir9__RoleInfo__) */
