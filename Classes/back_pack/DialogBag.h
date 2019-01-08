#ifndef DialogBag_h__
#define DialogBag_h__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

#include <vector>
#include <string>
#include "NodeBagItem.h"
#include "DialogBagModel.h"

//背包界面
class DialogBag : public Layer{
public:
    //创建界面
    CREATE_FUNC(DialogBag);

    //界面初始化
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();

    //设置界面显示内容
    void setupDialogBag(DialogBagModel* model);

    //绑定cocos文件到程序控件
    void bindingNode(cocos2d::Node* dialog);

    void onBtnCallback(Ref *object, Widget::TouchEventType type);

    //ScrollView滚动事件的回调
    void onSVCallback(Ref*, ui::ScrollView::EventType type);

    //ScrollView触摸事件的回调
    void onSVTouch(Ref *object, Widget::TouchEventType type);

    //背包中某一个item被点击
    void onItemClick(int sno, int id);

    //该函数响应背包内容更新的事件
    void doUpdateViewEvent(EventCustom* event);

    virtual ~DialogBag();
    DialogBag();
private:

    Button* btn_close;//关闭按钮
    Button* btn_back;//返回按钮

    ui::ScrollView* sv;//滚动层

    ImageView* slider_base;//滑块底部
    ImageView* slider_bar;//滑块

    Text* bg_capacity_label;//显示背包容量的文字

    Vector<NodeBagItem*> item_list;//背包item的列表
private:
    float slider_bar_min_pos_y;//用于控制滑块的位置
    float slider_bar_area;//滑块y轴可移动的距离的范围

    DialogBagModel* model_;
    EventListenerCustom* bag_updateEventListener;//用于监听背包内容更新
};

#endif // DialogBag_h__