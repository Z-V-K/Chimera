#include "../pch.h"
#include "ItemInfo.h"

ItemData* ItemInfo::get_item_data()
{
	return RVA_CAST_THIS(ItemData*, Structures::ItemInfo::ItemData);
}

int16_t ItemInfo::get_stacks()
{
	return RVA_CAST_THIS(int16_t, Structures::ItemInfo::Stacks);
}

float ItemInfo::get_price()
{
	return RVA_CAST_THIS(float, Structures::ItemInfo::Price);
}