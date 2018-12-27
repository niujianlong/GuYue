#ifndef __mir9__RoleInfo__
#define __mir9__RoleInfo__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RoleInfo: public Node
{
    
    Sprite* m_pBg;
	Node* m_pNode;
    
public:
	bool init();
	Node* getNode();
    CREATE_FUNC(RoleInfo);
    
    //void onEnterTransitionDidFinish();
};

#endif /* defined(__mir9__RoleInfo__) */
