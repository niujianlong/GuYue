#ifndef DialogBagModel_h__
#define DialogBagModel_h__

#include <vector>
#include <string>
#include <stdint.h>
#include "NodeBagItemModel.h"

//背包界面的model
struct DialogBagModel
{
    //背包列表
    std::vector<NodeBagItemModel> item_list;

    //背包上限
    int capacity_limit;

    //创建测试数据
    void createTestData(){

        capacity_limit = 90;

        for (int i = 0; i < 20; i++)
        {
            NodeBagItemModel a;
            a.gridModel.grid_bg_color = i % 5 + 1;
            a.gridModel.icon_id = 10001 + i;
            a.gridModel.level = i+1;
            a.gridModel.type = NodeBagGridModel::Equip;
            a.name = "zhuang bei";
            item_list.push_back(a);
        }

    }

    //从模型层获取数据
    void crateFromModel();

};

#endif // DialogBagModel_h__