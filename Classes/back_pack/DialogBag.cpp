#include "DialogBag.h"

bool DialogBag::init()
{
    Layer::init();

    //初始化字段
    slider_bar_min_pos_y = 0;
    slider_bar_area = 0;

    //csb文件位于KouDaiCE D:\temp\ui2\KouDaiCE
    auto dialog = CSLoader::createNode("DialogBag.csb");
    bindingNode(dialog);
    this->addChild(dialog); 

    return true;
}
void DialogBag::bindingNode(cocos2d::Node* dialog)
{
    //按钮
    btn_close = (Button*)dialog->getChildByName("Button_3");
    btn_back = (Button*)dialog->getChildByName("Button_1");

    btn_close->addTouchEventListener(CC_CALLBACK_2(DialogBag::onBtnCallback, this));
    btn_back->addTouchEventListener(CC_CALLBACK_2(DialogBag::onBtnCallback, this));

    bg_capacity_label = (Text*)dialog->getChildByName("Text_1_0");

    //滚动层
    sv = (ScrollView*)dialog->getChildByName("ScrollView_1");
    sv->addEventListener(CC_CALLBACK_2(DialogBag::onSVCallback, this));
    sv->addTouchEventListener(CC_CALLBACK_2(DialogBag::onSVTouch, this));

    //滑块
    slider_base = (ImageView*)dialog->getChildByName("Image_1");
    slider_bar = (ImageView*)slider_base->getChildByName("Image_2");
}


void DialogBag::setupDialogBag(DialogBagModel* model)
{

    CC_SAFE_DELETE(model_);
    model_ = model;

    //设置背包容量的文字---------------------------------------------------------------
    int capacity = model_->capacity_limit;
    int size = model_->item_list.size();
    bg_capacity_label->setString(StringUtils::format("%d/%d", size, capacity));


    //根据item的数量动态设置其在背包中的位置,已经滚动区域的大小------------------------
    int width = 792;//滚动层的宽
    int height = 352;//滚动层的高
    int padding = 6;//只是为了对坐标，并不是真正的内边距

    int count_per_row = 6;//每行的个数

    float row_width = 127+padding;//127是图片btn_daojudibang.png
    float column_heigth = height / 2;

    //因为空格子也要显示
    int max = (capacity > size) ? capacity : size;

    //计算列数
    float total_column = ((max - 1) / count_per_row + 1);

    //计算内容区的高度
    int container_hight = total_column*column_heigth;
    container_hight = (container_hight > height) ? container_hight : height;

    sv->setInnerContainerSize(Size(width, container_hight));

    //更新item-------------------------------------------------------------------------
    int old_item_list_size = item_list.size();//默认为0

    //如果有多余的Item，删除多余的item
    if (old_item_list_size>max)
    {
        for (int idx = old_item_list_size; idx < max;idx--)//倒着删
        {
            auto item = item_list.at(idx-1);
            item->removeFromParent();
            item_list.popBack();
        }
    }

    //更新或者创建item
    for (int idx = 0; idx < max; idx++)
    {
        int row = idx % count_per_row;
        int column = idx / count_per_row;

        NodeBagItem* item;
        if (old_item_list_size>idx)
        {
            //复用这个item
            item = item_list.at(idx);
        }
        else{
            //不够就创建
            item = NodeBagItem::create();
            sv->addChild(item);
            item_list.pushBack(item);
        }

        if (idx < size)
        {
            NodeBagItemModel data = model_->item_list[idx];
            item->setupNodeBagItem(data);
        }
        else if (idx < capacity) //空格子
        {
            NodeBagItemModel data;
            data.createGridNothing();
            item->setupNodeBagItem(data);
        }

        //计算并设置位置
        int x = padding/2 + row_width * row;
        int y = padding / 2 + container_hight - (column + 1)*(column_heigth);
        item->setPosition(x, y);

    }

    //计算滑块的大小和位置-------------------------------------------------------------
    float slider_orign_height = slider_base->getContentSize().height;
    float slider_bar_height = slider_orign_height*(2.0 / total_column);
    slider_bar->setContentSize(Size(11, slider_bar_height));

    this->slider_bar_min_pos_y = slider_bar_height;
    this->slider_bar_area = slider_orign_height - slider_bar_height;

    if (slider_bar->getPositionY() < slider_bar_min_pos_y)
    {
        slider_bar->setPositionY(slider_bar_min_pos_y);
    }
}

//ScrollView滚动事件的回调
void DialogBag::onSVCallback(Ref*, ScrollView::EventType type)
{
    if (type == ScrollView::EventType::SCROLLING)
    {
        //根据InnerContainer的滚动更新滑块的位置
        float current_pos = -sv->getInnerContainer()->getPositionY();
        float pos_area = sv->getInnerContainerSize().height - sv->getContentSize().height;

        //由于ScrollView开启了回弹效果，所以他的位置会超出范围，所以需要修正
        if (current_pos<0)
        {
            current_pos = 0;
        }
        else if (current_pos>pos_area){
            current_pos = pos_area;
        }

        float percent = current_pos / pos_area;

        //设置滑块的位置
        if (slider_bar_area != 0)
        {
            slider_bar->setPositionY(slider_bar_min_pos_y + slider_bar_area*percent);
        }

    }
}

//ScrollView触摸事件的回调
void DialogBag::onSVTouch(Ref *object, Widget::TouchEventType type)
{
    //由于按钮的点击事件会屏蔽ScrollView的滚动事件。即点击在按钮上的时候是不能拖动滚动层的。
    //所以背包中的item并不是button。而是自己实现的点击判定
    //处理背包中item的点击，模拟按钮的点击效果。
    if (type == Widget::TouchEventType::ENDED)
    {
        auto pos = sv->getTouchEndPosition();
        CCLOG("ended x = %f , y = %f", pos.x, pos.y);

        auto pos_began = sv->getTouchBeganPosition();

        float dis = pos.distance(pos_began);

        for (auto item : item_list)
        {
            auto btn = item->getBtn();
            btn->loadTexture("bag/btn_daojudibang.png");//设置所有item为非选中状态

            if (dis < 10 && btn->hitTest(pos)){//如果移动距离小于10，判断为1次点击操作
                CCLOG("on click item : sno = %lld , id = %d", item->get_sno(), item->get_id());
                onItemClick(item->get_sno(), item->get_id());
            }
        }

    }
    if (type == Widget::TouchEventType::BEGAN)
    {
        auto pos = sv->getTouchBeganPosition();
        CCLOG("began x = %f , y = %f", pos.x, pos.y);

        for (auto item : item_list)
        {
            auto btn = item->getBtn();
            if (btn->hitTest(pos))
            {
                //设置点中的item为点中状态
                btn->loadTexture("bag/pressed_daojudibang.png");
            }
        }

    }
    if (type==Widget::TouchEventType::MOVED)
    {
        auto pos = sv->getTouchMovePosition();
        CCLOG("moved x = %f , y = %f", pos.x, pos.y);
    }
}
