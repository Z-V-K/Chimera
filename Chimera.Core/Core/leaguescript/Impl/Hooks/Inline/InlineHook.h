#pragma once

namespace InlineHook
{
	struct hash_struct {
		char pad1[0x68];
		uint64_t hash[4];
	};

	struct section_hash
	{
		uint64_t og_hash[4];
		hash_struct* hash_ptr;

		section_hash() = default;

		section_hash(hash_struct* hash) : hash_ptr(hash)
		{
			for (int i = 0; i < 4; i++)
			{
				og_hash[i] = hash_ptr->hash[i];
			} 
		}

		void restore_hash()
		{
			for (int i = 0; i < 4; i++)
			{
				hash_ptr->hash[i] = og_hash[i];
			}
		}

		void bypass_hash()
		{
			for (int i = 0; i < 4; i++)
			{
				hash_ptr->hash[i] = 0x0;
			}
		}
	};

	inline std::unordered_map<uintptr_t, section_hash> hashes = { };

	void initialize();
	void remove(uintptr_t og_page_addr, uintptr_t og_addr, const std::vector<byte>& og_bytes);

	uintptr_t hook(void* target, void* detour, size_t size, std::vector<byte>* og_bytes, uintptr_t* og_page_addr);

	void load_hashes();
	void replace_hash(uintptr_t func_address, uintptr_t* og_page_addr);

	bool get_shadow_module(std::uintptr_t& base_address);
	uintptr_t get_addr_from_shadow_module(uintptr_t addr);
}