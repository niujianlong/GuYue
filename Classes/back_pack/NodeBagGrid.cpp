#include "NodeBagGrid.h"


void NodeBagGrid::setupNodeBagGrid(NodeBagGridModel model)
{

    //如果是装备，装备的品质通过底板背景表示
    switch (model.grid_bg_color)
    {
    case 1:
        btn->loadTexture("common/img_zhuangbeikuang.png");
        break;
    case 2:
        btn->loadTexture("common/img_huang.png");
        break;
    case 3:
        btn->loadTexture("common/img_lv.png");
        break;
    case 4:
        btn->loadTexture("common/img_lang.png");
        break;
    case 5:
        btn->loadTexture("common/img_zi.png");
        break;
    default:
        break;
    }

    //默认不显示满级标识
    lv_max_flag->setVisible(false);


    if (model.icon_id != -1)//有id说明不是空格子
    {
        //设置图标icon
        auto equip_icon_path = StringUtils::format("icon/big_icon/%d.png", model.icon_id);
        equip_icon->setTexture(equip_icon_path);



        if (model.type == NodeBagGridModel::Equip)//装备
        {
            //设置等级或者满级标识
            lv_flag->setVisible(true);
            lable_level->setVisible(true);

            lable_level->setString(StringUtils::format("%d", model.level));
            lv_flag->setPosition(lable_level->getPositionX() - lable_level->getContentSize().width - 15, lable_level->getPositionY());

            lv_max_flag->setVisible(model.is_max_level);
            if (model.is_max_level)//注意：满级会设置等级文字为不可见，装备id为-1也会设置为不可见
            {
                lv_flag->setVisible(false);
                lable_level->setVisible(false);
            }
            else{
                lv_flag->setVisible(true);
                lable_level->setVisible(true);
            }
        }
        else{//道具需要显示数量
            lv_flag->setVisible(false);
            lable_level->setVisible(true);
            lable_level->setString(StringUtils::format("%d", model.num));

        }

    }
    else{//-1为空格子
        equip_icon->setTexture(nullptr);
        equip_icon->setTextureRect(Rect::ZERO);

        lv_flag->setVisible(false);
        lable_level->setVisible(false);
    }


}

bool NodeBagGrid::init()
{
    Node::init();

    btn = ImageView::create("common/img_zhuangbeikuang.png");
    this->addChild(btn);

    equip_icon = Sprite::create();
    btn->addChild(equip_icon);
    equip_icon->setPosition(Vec2(btn->getContentSize().width / 2, btn->getContentSize().height / 2));

    lv_flag = Sprite::create("bag/img_lv.png");
    btn->addChild(lv_flag);
    lv_flag->setPosition(88 + 15, 10 + 5);

    lable_level = TextAtlas::create("1234567890", "common/img_shuzi01.png", 225 / 15, 19, "+");
    btn->addChild(lable_level);
    lable_level->setPosition(Vec2(88 + 15, 10 + 5));
    lable_level->setAnchorPoint(Vec2(1, 0.5));

    lv_max_flag = Sprite::create("common/img_Max.png");
    lv_max_flag->setPosition(lable_level->getPosition());
    lv_max_flag->setAnchorPoint(Vec2(1, 0.5));
    btn->addChild(lv_max_flag);

    return true;
}