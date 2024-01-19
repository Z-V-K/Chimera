#pragma once

#include "../Impl/Common/Common.h"
#include "../Framework/Items/ItemData/ItemData.h"

class ItemInfo final
{
public:
	ItemData* get_item_data();
	int16_t get_stacks();
	float get_price();
};