#pragma once

namespace Enums{
	enum class CollisionFlags : unsigned int
	{
		None = 0,
		Grass = 0x1,
		Wall = 0x2,
		Building = 0x46,
		Prop = 0x80,
		GlobalVision = 0x100
	};
}