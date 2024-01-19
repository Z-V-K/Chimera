#pragma once

#include "../Impl/Common/Common.h"

class SpellDataResource final
{
public:
	std::vector<std::string> mSpellTags();
	uintptr_t mDataValues();
	std::vector<float> mDataValues_BaseDamage();
	std::vector<float> cooldownTime();
	float delayCastOffsetPercent();
	float delayTotalTimePercent();
	std::vector<int> mMaxAmmo();
	std::vector<float> mAmmoRechargeTime();
	float mTurnSpeedScalar();
	std::vector<float> castRange();
	std::vector<float> castRangeDisplayOverride();
	std::vector<float> castRadius();
	float castConeDistance();
	uintptr_t mMissileSpec();
	float mMissileSpec_mMissileWidth();
	int castType();
	float castFrame();
	float missileSpeed();
	float mLineWidth();
};