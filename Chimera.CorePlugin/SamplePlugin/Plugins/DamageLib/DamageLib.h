#pragma once

#include "Spells/DamageChamp.h"
#include "Passives/DamagePassive.h"
#include "Items/DamageItem.h"

class DamageItemDatabase
{
public:
    DamageItem* get(InventoryItem* item)
    {
        auto it = database.find(item->get_item_id());

        if (it == database.end())
            return nullptr;

        return it->second;
    }

    void add(ItemId itemId, DamageItem* item)
    {
        database[itemId] = item;
    }

    void clear()
    {
        for (const auto& e : database)
        {
            delete e.second;
        }

        database.clear();
    }

private:
    std::unordered_map<ItemId, DamageItem*> database{ };
};

class DamagePassiveDatabase
{
public:

    std::vector<DamagePassive*> get_common_passives()
    {
        auto it = database.find(CharacterHash::Unknown);

        if (it == database.end())
            return { };

        return it->second;
    }

    DamagePassive* get(GameObject* obj)
    {
        auto it = database.find(obj->get_character_hash());

        if (it == database.end())
            return nullptr;

        return it->second.front();
    }

    void add(CharacterHash characterHash, DamagePassive* passive)
    {
        auto it = database.find(characterHash);

        if (it == database.end())
            database.insert({ characterHash, { } });

        database[characterHash].push_back(passive);
    }

    void clear()
    {
        for (const auto& e : database)
        {
            for (const auto& p : e.second)
                delete p;
        }

        database.clear();
    }

private:
    std::unordered_map<CharacterHash, std::vector<DamagePassive*>> database{ };
};

class DamageChampDatabase
{
public:
    DamageChamp* get(GameObject* obj)
    {
        auto it = database.find((CharacterHash) obj->get_character_hash());

        if (it == database.end()) 
            return nullptr;

    	for (const auto& champ : it->second)
	    {
            if (champ->src == obj)
                return champ;
	    }

        return nullptr;
    }

    void add(CharacterHash characterHash, DamageChamp* champ)
    {
        auto it = database.find(characterHash);

        if (it == database.end())
            database.insert({ characterHash, { } });

        database[characterHash].push_back(champ);
    }

    void clear()
    {
        for (const auto& e : database)
        {
	        for (const auto& p : e.second)
                delete p;
        }

        database.clear();
    }

private:
    std::unordered_map<CharacterHash, std::vector<DamageChamp*>> database{ };
};


namespace DamageLib {
    void initialize();
    void on_unload();

    DamageOutput get_spell_damage(GameObject* source, GameObject* target, SlotId spell_slot, int stage = 0, int stacks = 0);
    double calculate_damage(GameObject* source, GameObject* target, DamageType damage_type, double base_damage);
    DamageOutput get_auto_attack_damage(GameObject* source, GameObject* target, bool include_passive = true, bool include_items = true);

    DamageOutput compute_damage(GameObject* source, GameObject* target, DamageType damage_type, double damage);
    DamageOutput compute_physical_damage(GameObject* source, GameObject* target, double damage);
    DamageOutput compute_magical_damage(GameObject* source, GameObject* target, double damage);

    float get_crit_mulitplier(GameObject* source);

    inline DamageChampDatabase* hero_database = new DamageChampDatabase();
    inline DamagePassiveDatabase* passive_database = new DamagePassiveDatabase();
    inline DamageItemDatabase* item_database = new DamageItemDatabase();
};