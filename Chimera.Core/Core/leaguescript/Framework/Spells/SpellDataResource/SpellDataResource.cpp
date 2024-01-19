#include "../pch.h"
#include "SpellDataResource.h"

#include "../../../Impl/Common/Utils.h"
#include "../Framework/Containers/RiotString.h"

std::vector<std::string> SpellDataResource::mSpellTags()
{
	std::vector<std::string> spellTags{ };

	uint8_t spellTagsArrayLength = RVA_CAST_THIS(uint8_t, Structures::SpellDataResource::mSpellTagsArrayLength);

	if (spellTagsArrayLength == 0)
		return spellTags;

	uint64_t spellTagsArray = RVA_CAST_THIS(uint64_t, Structures::SpellDataResource::mSpellTagsArray);

	spellTags.reserve(spellTagsArrayLength);
	for (int i = 0; i < spellTagsArrayLength; i++)
	{
		std::string str = reinterpret_cast<LolString*>((uintptr_t) spellTagsArray + i * 0x10)->GetPtr();
		spellTags.push_back(str);
	}

	return spellTags;
}

uintptr_t SpellDataResource::mDataValues()
{
	uintptr_t* pDataValues = RVA_CAST_THIS_REF(uintptr_t*, Structures::SpellDataResource::mDataValues);

	return pDataValues ? *pDataValues : (uintptr_t) nullptr;
}

std::vector<float> SpellDataResource::mDataValues_BaseDamage()
{
	std::vector<float> ret{ };

	uintptr_t pDataValues = mDataValues();

	if (!pDataValues)
		return ret;

	uintptr_t baseOffset = (uintptr_t)pDataValues + (uintptr_t)Structures::SpellDataResource::mDataValues_BaseDamage;

	ret.reserve(7);
	for (int i = 0; i < 7; i++)
	{
		ret.push_back(*reinterpret_cast<float*>((uintptr_t)baseOffset + i * 0x4));
	}

	return ret;
}

std::vector<float> SpellDataResource::cooldownTime()
{
	std::vector<float> ret{ };

	uintptr_t baseOffset = (uintptr_t)this + (uintptr_t)Structures::SpellDataResource::cooldownTime;

	ret.reserve(7);
	for (int i = 0; i < 7; i++)
	{
		ret.push_back(*reinterpret_cast<float*>((uintptr_t) baseOffset + i * 0x4));
	}

	return ret;
}

float SpellDataResource::delayCastOffsetPercent()
{
	return RVA_CAST_THIS(float, Structures::SpellDataResource::delayCastOffsetPercent);
}

float SpellDataResource::delayTotalTimePercent()
{
	return RVA_CAST_THIS(float, Structures::SpellDataResource::delayTotalTimePercent);
}

std::vector<int> SpellDataResource::mMaxAmmo()
{
	std::vector<int> ret{ };

	uintptr_t baseOffset = (uintptr_t)this + (uintptr_t)Structures::SpellDataResource::mMaxAmmo;

	ret.reserve(7);
	for (int i = 0; i < 7; i++)
	{
		ret.push_back(*reinterpret_cast<int*>((uintptr_t)baseOffset + i * 0x4));
	}

	return ret;
}

std::vector<float> SpellDataResource::mAmmoRechargeTime()
{
	std::vector<float> ret{ };

	uintptr_t baseOffset = (uintptr_t)this + (uintptr_t)Structures::SpellDataResource::mAmmoRechargeTime;

	ret.reserve(7);
	for (int i = 0; i < 7; i++)
	{
		ret.push_back(*reinterpret_cast<float*>((uintptr_t)baseOffset + i * 0x4));
	}

	return ret;
}

float SpellDataResource::mTurnSpeedScalar()
{
	return RVA_CAST_THIS(float, Structures::SpellDataResource::mTurnSpeedScalar);
}

std::vector<float> SpellDataResource::castRange()
{
	std::vector<float> ret{ };

	uintptr_t baseOffset = (uintptr_t)this + (uintptr_t)Structures::SpellDataResource::castRange;

	ret.reserve(7);
	for (size_t i = 0; i < 7; i++)
	{
		ret.push_back(*reinterpret_cast<float*>(baseOffset + i * 0x4));
	}

	return ret;
}

std::vector<float> SpellDataResource::castRangeDisplayOverride()
{
	std::vector<float> ret{ };

	uintptr_t baseOffset = (uintptr_t)this + (uintptr_t)Structures::SpellDataResource::castRangeDisplayOverride;

	ret.reserve(7);
	for (int i = 0; i < 7; i++)
	{
		ret.push_back(*reinterpret_cast<float*>((uintptr_t)baseOffset + i * 0x4));
	}

	return ret;
}

std::vector<float> SpellDataResource::castRadius()
{
	std::vector<float> ret{ };

	uintptr_t baseOffset = (uintptr_t)this + (uintptr_t)Structures::SpellDataResource::castRadius;

	ret.reserve(7);
	for (int i = 0; i < 7; i++)
	{
		ret.push_back(*reinterpret_cast<float*>((uintptr_t)baseOffset + i * 0x4));
	}

	return ret;
}

float SpellDataResource::castConeDistance()
{
	return RVA_CAST_THIS(float, Structures::SpellDataResource::castConeDistance);
}

uintptr_t SpellDataResource::mMissileSpec()
{
	uintptr_t* pDataValues = RVA_CAST_THIS_REF(uintptr_t*, Structures::SpellDataResource::mMissileSpec); 
	return pDataValues ? *pDataValues : (uintptr_t) nullptr;
}

float SpellDataResource::mMissileSpec_mMissileWidth()
{
	uintptr_t missileSpec = mMissileSpec();

	if (!missileSpec)
		return 0.f;

	return *reinterpret_cast<float*>((uintptr_t)missileSpec + (uintptr_t)Structures::SpellDataResource::mMissileSpel_mMissileWidth);
}

int SpellDataResource::castType()
{
	return RVA_CAST_THIS(int, Structures::SpellDataResource::castType);
}

float SpellDataResource::castFrame()
{
	return RVA_CAST_THIS(float, Structures::SpellDataResource::castFrame);
}

float SpellDataResource::missileSpeed()
{
	return RVA_CAST_THIS(float, Structures::SpellDataResource::missileSpeed);
}

float SpellDataResource::mLineWidth()
{
	return RVA_CAST_THIS(float, Structures::SpellDataResource::mLineWidth);
}