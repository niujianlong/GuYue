#ifndef NodeBagGrid_h__
#define NodeBagGrid_h__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;



struct NodeBagGridModel
{
    enum ItemType
    {
        Equip,//装备，需要显示等级，
        Other,//包括道具、宝箱和钥匙，需要显示数量
    };

    ItemType type;//物品的类型
    int icon_id;//道具的id，id和图片资源一一对应
    int level;//如果是装备，显示等级
    int grid_bg_color;//装备的稀有度通过框框的背景色表示
    //bool has_jiahao;
    bool is_max_level;//装备有等级上限，满级会显示max标志
    int num;//其他类型的物品需要显示数量
};


//物品节点（正方形的格子），对应一件道具或装备
class NodeBagGrid : public Node{
public:
    CREATE_FUNC(NodeBagGrid);
    virtual bool init();
    void setupNodeBagGrid(NodeBagGridModel model);

protected:
    //Sprite* btn_jia;
    ImageView* btn;
    Sprite* equip_icon;
    Sprite* lv_flag;
    TextAtlas* lable_level;
    Sprite* lv_max_flag;
};

#endif // NodeBagGrid_h__
