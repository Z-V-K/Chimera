#pragma once

#include "../Impl/Common/Common.h"
#include "../Framework/Spells/SpellDataResource/SpellDataResource.h"
#include "../Framework/Spells/SpellDataScript/SpellDataScript.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class SpellData final
{
public:
	std::string get_spell_name() const;
	SpellDataResource* get_spell_data_resource() const;
	SpellDataScript* get_spell_data_script() const;

	// ========== EXPORTED ==========
	uint32_t get_hash() const;
	std::vector<std::string> mSpellTags() const;
	std::vector<float> mDataValues_BaseDamage() const;
	std::vector<float> cooldownTime() const;
	float delayCastOffsetPercent() const;
	float delayTotalTimePercent() const;
	std::vector<int> mMaxAmmo() const;
	std::vector<float> mAmmoRechargeTime() const;
	float mTurnSpeedScalar() const;
	std::vector<float> castRange() const;
	std::vector<float> castRangeDisplayOverride() const;
	std::vector<float> castRadius() const;
	float castConeDistance() const;
	float mMissileSpec_mMissileWidth() const;
	int castType() const;
	float castFrame() const;
	float missileSpeed() const;
	float mLineWidth() const;

	EXPORT_FUNC(std::string, get_spell_name, (SpellData* obj), ());
	EXPORT_FUNC(uint32_t, get_hash, (SpellData* obj), ());
	EXPORT_FUNC(std::vector<std::string>, mSpellTags, (SpellData* obj), ());
	EXPORT_FUNC(std::vector<float>, mDataValues_BaseDamage, (SpellData* obj), ());
	EXPORT_FUNC(std::vector<float>, cooldownTime, (SpellData* obj), ());
	EXPORT_FUNC(float, delayCastOffsetPercent, (SpellData* obj), ());
	EXPORT_FUNC(float, delayTotalTimePercent, (SpellData* obj), ());
	EXPORT_FUNC(std::vector<int>, mMaxAmmo, (SpellData* obj), ());
	EXPORT_FUNC(std::vector<float>, mAmmoRechargeTime, (SpellData* obj), ());
	EXPORT_FUNC(float, mTurnSpeedScalar, (SpellData* obj), ());
	EXPORT_FUNC(std::vector<float>, castRange, (SpellData* obj), ());
	EXPORT_FUNC(std::vector<float>, castRangeDisplayOverride, (SpellData* obj), ());
	EXPORT_FUNC(std::vector<float>, castRadius, (SpellData* obj), ());
	EXPORT_FUNC(float, castConeDistance, (SpellData* obj), ());
	EXPORT_FUNC(float, mMissileSpec_mMissileWidth, (SpellData* obj), ());
	EXPORT_FUNC(int, castType, (SpellData* obj), ());
	EXPORT_FUNC(float, castFrame, (SpellData* obj), ());
	EXPORT_FUNC(float, missileSpeed, (SpellData* obj), ());
	EXPORT_FUNC(float, mLineWidth, (SpellData* obj), ());
};

#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif