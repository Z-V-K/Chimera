#include "../pch.h"
#include "SpellData.h"

#define ASSERT_NULL(val) if (!val) return { };

SpellDataResource* SpellData::get_spell_data_resource() const
{
	return RVA_CAST_THIS(SpellDataResource*, Structures::SpellData::SpellDataResource);
}

SpellDataScript* SpellData::get_spell_data_script() const
{
	return RVA_CAST_THIS(SpellDataScript*, Structures::SpellData::SpellDataScript);
}

std::string SpellData::get_spell_name() const
{
	return RVA_CAST_THIS(std::string, Structures::SpellData::SpellName);
}

uint32_t SpellData::get_hash() const
{
	const auto spell_data_script = get_spell_data_script();

	if (!spell_data_script)
		return 0x0;

	return spell_data_script->get_hash();
}

std::vector<std::string> SpellData::mSpellTags() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->mSpellTags();
}

std::vector<float> SpellData::mDataValues_BaseDamage() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->mDataValues_BaseDamage();
}

std::vector<float> SpellData::cooldownTime() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->cooldownTime();
}

float SpellData::delayCastOffsetPercent() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->delayCastOffsetPercent();
}

float SpellData::delayTotalTimePercent() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->delayTotalTimePercent();
}

std::vector<int> SpellData::mMaxAmmo() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->mMaxAmmo();
}

std::vector<float> SpellData::mAmmoRechargeTime() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->mAmmoRechargeTime();
}

float SpellData::mTurnSpeedScalar() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->mTurnSpeedScalar();
}

std::vector<float> SpellData::castRange() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->castRange();
}

std::vector<float> SpellData::castRangeDisplayOverride() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->castRangeDisplayOverride();
}

std::vector<float> SpellData::castRadius() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->castRadius();
}

float SpellData::castConeDistance() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->castConeDistance();
}

float SpellData::mMissileSpec_mMissileWidth() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->mMissileSpec_mMissileWidth();
}

int SpellData::castType() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->castType();
}

float SpellData::castFrame() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->castFrame();
}

float SpellData::missileSpeed() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->missileSpeed();
}

float SpellData::mLineWidth() const
{
	const auto spell_resource = get_spell_data_resource();

	ASSERT_NULL(spell_resource)

	return get_spell_data_resource()->mLineWidth();
}