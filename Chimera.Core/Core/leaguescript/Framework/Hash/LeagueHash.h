#pragma once

constexpr std::uint32_t const league_hash(const char* str)
{
	std::uint32_t hash = 0x811C9DC5;
	std::uint32_t len = 0;

	while (str[len] != '\0')
		len++;

	for (auto i = 0u; i < len; ++i)
	{
		char current = str[i];
		char current_upper = current + 0x20;

		if (static_cast<uint8_t>(current - 0x41) > 0x19u)
			current_upper = current;

		hash = 16777619 * (hash ^ current_upper);
	}

	return hash;
}

#define hashstr(str) (std::integral_constant<std::uint32_t, league_hash(str)>::value)	