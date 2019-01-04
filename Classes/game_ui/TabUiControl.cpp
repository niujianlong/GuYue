#include "TabUiControl.h"


int TabUiControl::TabValue[MaxTabCount];

TabUiControl::TabUiControl() 
:_activeTxtColor(241, 255, 223, 255), _unActiveTxtColor(182, 167, 166, 255)
{
    InitDefData();


    _tabMaxZorder = 0;
    _tabCount = 0;
    _pTabBtnData = nullptr;
    _onActiveCallback = nullptr;
    _bHaveContenNode = false;

    
}

TabUiControl::~TabUiControl()
{

    CC_SAFE_DELETE_ARRAY(_pTabBtnData);
}
void TabUiControl::InitDefData()
{
    static bool BInitOk = false;
    if (!BInitOk)
    {
        for (int i = 0; i < MaxTabCount; i++)
        {
            TabValue[i] = i;
        }

        BInitOk = true;
    }

}

bool TabUiControl::InitTab(Node *pRootNode, int tabCount, bool bHaveContenNode, const char *pTabBtnName, const char *pTabTxtName, const char *pContentName)
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(!pTabBtnName || !pTabTxtName || !pRootNode || !pContentName);
        CC_BREAK_IF(tabCount > MaxTabCount || tabCount <= 0);

        
        //分配tab 数据
        _pTabBtnData = new STabBtnData[tabCount];
        _tabCount = tabCount;
        _bHaveContenNode = bHaveContenNode;

        //临时变量
        ui::Button *pTempBtn = nullptr;
        Text *pTempTxt = nullptr;
        Node *pNode = nullptr;
        char tc[128] = { 0 };
        int i = 0;
        Widget::ccWidgetClickCallback callback = CC_CALLBACK_1(TabUiControl::OnTabClick, this);

        for (i = 0; i < tabCount; i++)
        {
            //内容节点指针
            if (bHaveContenNode)
            {
                sprintf(tc, "%s%d", pContentName, i);
                //pNode = StudioUiBase::FindUiChildNode(pRootNode, tc);
				pNode = dynamic_cast<Node*> (pRootNode->getChildByName(tc));
                CC_BREAK_IF(!pNode);
                _pTabBtnData[i]._pContentNode = pNode;
            }


            //tabBtn
            sprintf(tc, "%s%d", pTabBtnName, i);
            //pNode = StudioUiBase::FindUiChildNode(pRootNode, tc);
			pNode = dynamic_cast<Button*> (pRootNode->getChildByName(tc));
            pTempBtn = dynamic_cast<ui::Button*>(pNode);
            CC_BREAK_IF(!pTempBtn);
            //btnTxt
			sprintf(tc, "%s%d", pTabTxtName, i);
            //pNode = StudioUiBase::FindUiChildNode(pTempBtn, pTabTxtName);
			pNode = dynamic_cast<Text*> (pRootNode->getChildByName(tc));
            pTempTxt = dynamic_cast<Text*>(pNode);
            CC_BREAK_IF(!pTempTxt);
            //tab 值
            pTempBtn->setUserData(&(TabValue[i]));
            //事件
            pTempBtn->addClickEventListener(callback);
            //保存
            _pTabBtnData[i]._pTabBtn = pTempBtn;
            _pTabBtnData[i]._pBtnTxt = pTempTxt;

        }
        CC_BREAK_IF(i != tabCount);

        //获取最大的zorder-----------
        int zoreder = 0;
        _tabMaxZorder = 0;
        for (i = 0; i < tabCount; i++)
        {
            zoreder = _pTabBtnData[i]._pTabBtn->getLocalZOrder();
            if (zoreder>_tabMaxZorder)
                _tabMaxZorder = zoreder;
        }

        ret = true;
    } while (0);

    return ret;
}

void TabUiControl::ActiveTab(int index)
{
    if (index >= 0 && index < _tabCount)
    {
        int zorder = _tabMaxZorder;

        //选中设置
        _pTabBtnData[index]._pTabBtn->setLocalZOrder(_tabMaxZorder);
		//_pTabBtnData[index]._pTabBtn->loadTextureNormal("ui/tabbarMenu/anxia.png");

        _pTabBtnData[index]._pTabBtn->setBright(true);

		_pTabBtnData[index]._pBtnTxt->setLocalZOrder(_tabMaxZorder + 1);
        _pTabBtnData[index]._pBtnTxt->setTextColor(_activeTxtColor);

        //内容可见性
        if (_bHaveContenNode)
            _pTabBtnData[index]._pContentNode->setVisible(true);
		switch (index) 
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		
		}



        //左边的tab
        for (int i = index - 1; i >= 0; i--)
        {
            //未选中设置
#if 0
            zorder--;
            _pTabBtnData[i]._pTabBtn->setLocalZOrder(zorder);
            _pTabBtnData[i]._pTabBtn->setBright(false);
			//_pTabBtnData[i]._pTabBtn->setLocalZOrder(zorder);

			//_pTabBtnData[i]._pTabBtn->loadTextureNormal("ui/tabbarMenu/notSelected.png");
#endif
			//这个setBright(false)精髓就是把按钮的状态设置成disable状态，让他显示禁用状态的图片
			//这样就实现了Tab页的效果，你可以跟到代码里看到这个false确实在设置button的 onPressStateChangedToDisabled();
			_pTabBtnData[i]._pTabBtn->setBright(false);
            _pTabBtnData[i]._pBtnTxt->setTextColor(_unActiveTxtColor);

            //内容可见性
			if (_bHaveContenNode)
			{
				_pTabBtnData[i]._pContentNode->setVisible(false);
			}
                
        }

        //右边的tab
        for (int i = index + 1; i < _tabCount; i++)
        {
            //未选中设置
#if 0
			zorder--;
			_pTabBtnData[i]._pTabBtn->setLocalZOrder(zorder);
			//_pTabBtnData[i]._pTabBtn->setBright(false);
			//_pTabBtnData[i]._pTabBtn->setLocalZOrder(zorder);

			//_pTabBtnData[i]._pTabBtn->loadTextureNormal("ui/tabbarMenu/notSelected.png");  
#endif // 0
			_pTabBtnData[i]._pTabBtn->setBright(false);
			_pTabBtnData[i]._pBtnTxt->setTextColor(_unActiveTxtColor);

            //内容可见性
            if (_bHaveContenNode)
                _pTabBtnData[i]._pContentNode->setVisible(false);
        }


        //回调
        if (_onActiveCallback)
        {
            _onActiveCallback(index);
        }

    }
}

void TabUiControl::OnTabClick(Ref *pSender)
{
    do 
    {
        ui::Button *pBtn = dynamic_cast<ui::Button*>(pSender);
        CC_BREAK_IF(!pBtn);
        void *pUserData = pBtn->getUserData();
        CC_BREAK_IF(!pUserData);
        int *pValue = (int*)(pUserData);
        //激活tab
        ActiveTab(*pValue);


    } while (0);
}