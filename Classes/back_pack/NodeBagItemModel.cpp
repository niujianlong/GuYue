#include "NodeBagItemModel.h"
#include "ModelEquipment.h"
#include "ModelProp.h"

void NodeBagItemModel::createGridNothing()
{
    this->sno = 0;
    this->name = "";
    this->isSelect = false;

    this->yi_zhuang_bei = false;
    this->is_suipian = false;

    gridModel.icon_id = -1;
    gridModel.level = -1;
    gridModel.grid_bg_color = 1;
    gridModel.num = 0;
    gridModel.is_max_level = false;
}

void NodeBagItemModel::createFromEquipModel(ModelEquipment* item)
{
    this->gridModel.type = NodeBagGridModel::Equip;
    this->gridModel.grid_bg_color = item->getColor();
    this->gridModel.icon_id = item->getId();
    this->gridModel.level = item->getLevel();

    this->sno = item->getSno();
    this->name = item->getName();

    if (item->getLevelLimit() == item->getLevel())
    {
        this->gridModel.is_max_level = true;
    }
    else{
        this->gridModel.is_max_level = false;
    }

    this->yi_zhuang_bei = false;
    if (item->getEquipPartnerId() > 0)
    {
        this->yi_zhuang_bei = true;
    }

    this->is_suipian = false;
}

void NodeBagItemModel::createFromPropModel(ModelProp* item)
{
    this->gridModel.type = NodeBagGridModel::Other;
    this->gridModel.grid_bg_color = 1;
    this->gridModel.icon_id = item->getId();
    this->gridModel.level = -1;
    this->sno = 0;
    this->gridModel.num = item->getNum();
    this->name = item->getName();
    this->gridModel.is_max_level = false;

    this->yi_zhuang_bei = false;

    this->is_suipian = false;
    if (item->getType() == ModelProp::EQUIPMENT_DEBRIS)
    {
        this->is_suipian = true;
        ModelEquipmentDebrisProp* debris_item = ((ModelEquipmentDebrisProp*)item);
        this->gridModel.icon_id = debris_item->getTargetId();

        this->debris_id = item->getId();

    }
}
