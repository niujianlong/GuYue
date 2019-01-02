#pragma once

//std
#include <string>

//cocos
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


using namespace std;

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;



typedef std::function<void(int)> OnTabActioveCallback;

//tab控件数据
struct STabBtnData
{
    STabBtnData()
    {
        _pTabBtn = nullptr;
        _pBtnTxt = nullptr;
        _pContentNode = nullptr;
    }
    ui::Button *_pTabBtn;        //按钮
    Text * _pBtnTxt;            //按钮文字
    Node *_pContentNode;        //对应的内容node指针
};


//选项卡控件
class TabUiControl
{
public:
    TabUiControl();
    virtual ~TabUiControl();
    //初始化tab
    bool InitTab(Node *pRootNode, int tabCount, bool bHaveContenNode = true,const char *pTabBtnName = "tabBtn", const char *pTabTxtName = "btnTxt", const char *pContentName = "tabContent");
    //tab单击事件
    void OnTabClick(Ref *pSender);
    //激活tab
    void ActiveTab(int index);
    //设置激活颜色
    void SetActiveTxtColor(const Color4B &color){ _activeTxtColor = color; }
    //设置未激活颜色
    void SetUnActiveTxtColor(const Color4B &color){ _unActiveTxtColor = color; }
    //设置选中回调
    void SetActiveCallback(OnTabActioveCallback call){ _onActiveCallback = call; }
private:
    //初始化静态数据
    static void InitDefData();
protected:
    static const int MaxTabCount=12;            //最大tab数量
    static int TabValue[MaxTabCount];            //tab 值
    int _tabCount;                                //tab数量
    int _tabMaxZorder;                            //tabMaxZorder
    STabBtnData *_pTabBtnData;                    //tab 数据
    Color4B _activeTxtColor;                    //激活tabBtn文字颜色
    Color4B _unActiveTxtColor;                    //未激活tabBtn文字颜色
    OnTabActioveCallback _onActiveCallback;        //tab被激活回调
    bool _bHaveContenNode;                        //tab是否有对应的内容节点
private:
};