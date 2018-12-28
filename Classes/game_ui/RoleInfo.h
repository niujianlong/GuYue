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
    Sprite* m_pBg;//����option�ľ���
	Sprite* m_RolePic;//����ͼƬ
	Sprite* m_HeadEquipment;//ͷ��װ��
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
