#ifndef NodeBagItemModel_h__
#define NodeBagItemModel_h__

#include <string>
#include <stdint.h>
#include "NodeBagGrid.h"

class ModelEquipment;
class ModelProp;

//背包中的item的model
struct NodeBagItemModel
{

	int64_t sno;//装备有唯一序列号，道具为0
	std::string name;
	bool is_suipian;
	bool yi_zhuang_bei;
	bool isSelect;//用于装备选择界面,理论上应该移到子类中去。

	NodeBagGridModel gridModel;

	void createGridNothing();//创建一个空的item
	void createFromEquipModel(ModelEquipment* item);//根据装备的相关数据创建界面model，从数据model填充界面model
	void createFromPropModel(ModelProp* item);//根据道具的相关数据创建界面model，从数据model填充界面model

	//肮脏的代码，由于装备碎片的icon_id是合成后的装备的icon_id，再在左上角加一个碎片的碎。
	//所以添加了一个多余的字段，用于获取其原始id
	int debris_id;
};

#endif // NodeBagItemModel_h__
