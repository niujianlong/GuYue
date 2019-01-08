#ifndef NodeBagItem_h__
#define NodeBagItem_h__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "NodeBagGrid.h"
#include "NodeBagItemModel.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

//背包中的物品item（长方形），包含NodeBagGrid以及一些额外信息(名字，是否已装备等)
class NodeBagItem : public Node{
public:
    CREATE_FUNC(NodeBagItem);
    virtual bool init();

    void setupNodeBagItem(NodeBagItemModel model);

    void setSelected(bool isSelected);
    bool isSelected(){ return isSelected_; }

    ImageView* getBtn(){ return btn; }

    int64_t get_sno();
    int get_id();

private:
    ImageView* btn;
    NodeBagGrid* grid;
    Text* name_label;
    bool isSelected_;
    Sprite* isSelected_sp;

    Sprite* sp_debris;
    Sprite* already_use;
private:
    NodeBagItemModel view_model;
};

#endif // NodeBagItem_h__
