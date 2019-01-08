#include “NodeBagItem.h”
static const std::string text1 = “\xE7\xA9\xBA”;//空

bool NodeBagItem::init() 
{ 
Node::init();

Node* node = CSLoader::createNode("NodeBagItem.csb");

this->addChild(node);

btn = (ImageView*)node->getChildByName("Image_2");

auto center_x = btn->getContentSize().width / 2;
auto center_y = btn->getContentSize().height / 2;

grid = NodeBagGrid::create();
btn->addChild(grid);

grid->setPosition(Vec2(center_x, center_y + 20));

auto position_y_name = 20;

name_label = (Text*)node->getChildByName("Text_1");

isSelected_sp = Sprite::create("bag/img_xuanzhong.png");
isSelected_sp->setPosition(center_x, center_y);

this->addChild(isSelected_sp);

setSelected(false);

sp_debris = (Sprite*)node->getChildByName("img_flag_suipian_1");
already_use = (Sprite*)node->getChildByName("img_yizhuangbei_2");

return true;
}

void NodeBagItem::setupNodeBagItem(NodeBagItemModel model) 
{

view_model = model;

grid->setupNodeBagGrid(model.gridModel);

if (model.name != "")
{
    name_label->setString(model.name);
}
else{
    name_label->setString(text1);
}

sp_debris->setVisible(model.is_suipian);
already_use->setVisible(model.yi_zhuang_bei);

}

void NodeBagItem::setSelected(bool isSelected) 
{ 
this->isSelected_ = isSelected;

isSelected_sp->setVisible(isSelected);
1
}

int64_t NodeBagItem::get_sno() 
{ 
return view_model.sno; 
}

int NodeBagItem::get_id() 
{ 
int id = view_model.gridModel.icon_id;

//肮脏的代码，由于碎片的icon_id是合成后的装备的icon_id。
//所以添加了一个多余的字段，用于获取其原始id
if (view_model.is_suipian == true)
{
    id = view_model.debris_id;
}

return id;

}
