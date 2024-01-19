#include "TargetSelector.h"


GameObject* getTargetAuto(std::vector<GameObject*> objects, DamageType damageType);
GameObject* getTargetLowestHp(const std::vector<GameObject*>& objects, DamageType damageType);
GameObject* getTargetLowestMaxHp(const std::vector<GameObject*>& objects, DamageType damageType);
GameObject* getTargetHighestHp(const std::vector<GameObject*>& objects, DamageType damageType);
GameObject* getTargetHighestMaxHp(const std::vector<GameObject*>& objects, DamageType damageType);
GameObject* getTargetClosest(const std::vector<GameObject*>& objects, DamageType damageType);
GameObject* getTargetStrictPriority(const std::vector<GameObject*>& objects, DamageType damageType);
GameObject* getTargetLeastSpells(std::vector<GameObject*> objects, DamageType damageType);
GameObject* getTargetLeastAutos(std::vector<GameObject*> objects, DamageType damageType);

std::unordered_map<CharacterHash, int8_t> defaultPriorities = {
 { CharacterHash::Aatrox, 3 },
 { CharacterHash::Ahri, 4 },
 { CharacterHash::Akali, 4 },
 { CharacterHash::Akshan, 5 },
 { CharacterHash::Alistar, 1 },
 { CharacterHash::Amumu, 2 },
 { CharacterHash::Anivia, 4 },
 { CharacterHash::Annie, 4 },
 { CharacterHash::Aphelios, 5 },
 { CharacterHash::Ashe, 5 },
 { CharacterHash::AurelionSol, 4 },
 { CharacterHash::Azir, 4 },
 { CharacterHash::Bard, 2 },
 { CharacterHash::Belveth, 2 },
 { CharacterHash::Blitzcrank, 1 },
 { CharacterHash::Brand, 4 },
 { CharacterHash::Braum, 1 },
 { CharacterHash::Briar, 3 },
 { CharacterHash::Caitlyn, 5 },
 { CharacterHash::Camille, 3 },
 { CharacterHash::Cassiopeia, 4 },
 { CharacterHash::Chogath, 3 },
 { CharacterHash::Corki, 4 },
 { CharacterHash::Darius, 3 },
 { CharacterHash::Diana, 2 },
 { CharacterHash::DrMundo, 3 },
 { CharacterHash::Draven, 5 },
 { CharacterHash::Ekko, 4 },
 { CharacterHash::Elise, 2 },
 { CharacterHash::Evelynn, 3 },
 { CharacterHash::Ezreal, 5 },
 { CharacterHash::Fiddlesticks, 2 },
 { CharacterHash::Fiora, 3 },
 { CharacterHash::Fizz, 4 },
 { CharacterHash::Galio, 3 },
 { CharacterHash::Gangplank, 3 },
 { CharacterHash::Garen, 3 },
 { CharacterHash::Gnar, 3 },
 { CharacterHash::Gragas, 2 },
 { CharacterHash::Graves, 4 },
 { CharacterHash::Gwen, 4 },
 { CharacterHash::Hecarim, 3 },
 { CharacterHash::Heimerdinger, 4 },
 { CharacterHash::Illaoi, 3 },
 { CharacterHash::Irelia, 3 },
 { CharacterHash::Ivern, 2 },
 { CharacterHash::Janna, 1 },
 { CharacterHash::JarvanIV, 2 },
 { CharacterHash::Jax, 3 },
 { CharacterHash::Jayce, 3 },
 { CharacterHash::Jhin, 5 },
 { CharacterHash::Jinx, 5 },
 { CharacterHash::Kaisa, 5 },
 { CharacterHash::Kalista, 5 },
 { CharacterHash::Karma, 1 },
 { CharacterHash::Karthus, 4 },
 { CharacterHash::Kassadin, 4 },
 { CharacterHash::Katarina, 4 },
 { CharacterHash::Kayle, 3 },
 { CharacterHash::Kayn, 2 },
 { CharacterHash::Kennen, 3 },
 { CharacterHash::Khazix, 2 },
 { CharacterHash::Kindred, 3 },
 { CharacterHash::Kled, 3 },
 { CharacterHash::KogMaw, 5 },
 { CharacterHash::KSante, 2 },
 { CharacterHash::Leblanc, 4 },
 { CharacterHash::LeeSin, 2 },
 { CharacterHash::Leona, 1 },
 { CharacterHash::Lillia, 2 },
 { CharacterHash::Lissandra, 4 },
 { CharacterHash::Lucian, 5 },
 { CharacterHash::Lulu, 1 },
 { CharacterHash::Lux, 4 },
 { CharacterHash::Malphite, 2 },
 { CharacterHash::Malzahar, 4 },
 { CharacterHash::Maokai, 2 },
 { CharacterHash::MasterYi, 3 },
 { CharacterHash::Milio, 2 },
 { CharacterHash::MissFortune, 5 },
 { CharacterHash::Mordekaiser, 3 },
 { CharacterHash::Morgana, 2 },
 { CharacterHash::Naafiri, 3 },
 { CharacterHash::Nami, 1 },
 { CharacterHash::Nasus, 3 },
 { CharacterHash::Nautilus, 1 },
 { CharacterHash::Neeko, 4 },
 { CharacterHash::Nidalee, 3 },
 { CharacterHash::Nilah, 5 },
 { CharacterHash::Nocturne, 3 },
 { CharacterHash::Nunu, 2 },
 { CharacterHash::Olaf, 3 },
 { CharacterHash::Orianna, 4 },
 { CharacterHash::Ornn, 3 },
 { CharacterHash::Pantheon, 3 },
 { CharacterHash::Poppy, 3 },
 { CharacterHash::Pyke, 2 },
 { CharacterHash::Qiyana, 3 },
 { CharacterHash::Quinn, 5 },
 { CharacterHash::Rakan, 1 },
 { CharacterHash::Rammus, 2 },
 { CharacterHash::RekSai, 2 },
 { CharacterHash::Rell, 1 },
 { CharacterHash::Renata, 1 },
 { CharacterHash::Renekton, 3 },
 { CharacterHash::Rengar, 3 },
 { CharacterHash::Riven, 3 },
 { CharacterHash::Rumble, 4 },
 { CharacterHash::Ryze, 4 },
 { CharacterHash::Samira, 5 },
 { CharacterHash::Sejuani, 2 },
 { CharacterHash::Senna, 4 },
 { CharacterHash::Seraphine, 2 },
 { CharacterHash::Sett, 3 },
 { CharacterHash::Shaco, 2 },
 { CharacterHash::Shen, 2 },
 { CharacterHash::Shyvana, 2 },
 { CharacterHash::Singed, 3 },
 { CharacterHash::Sion, 2 },
 { CharacterHash::Sivir, 5 },
 { CharacterHash::Skarner, 2 },
 { CharacterHash::Sona, 1 },
 { CharacterHash::Soraka, 1 },
 { CharacterHash::Swain, 4 },
 { CharacterHash::Sylas, 4 },
 { CharacterHash::Syndra, 4 },
 { CharacterHash::TahmKench, 2 },
 { CharacterHash::Taliyah, 4 },
 { CharacterHash::Talon, 4 },
 { CharacterHash::Taric, 1 },
 { CharacterHash::Teemo, 3 },
 { CharacterHash::Thresh, 1 },
 { CharacterHash::Tristana, 5 },
 { CharacterHash::Trundle, 2 },
 { CharacterHash::Tryndamere, 3 },
 { CharacterHash::TwistedFate, 4 },
 { CharacterHash::Twitch, 5 },
 { CharacterHash::Udyr, 2 },
 { CharacterHash::Urgot, 3 },
 { CharacterHash::Varus, 5 },
 { CharacterHash::Vayne, 5 },
 { CharacterHash::Veigar, 4 },
 { CharacterHash::Velkoz, 4 },
 { CharacterHash::Vex, 4 },
 { CharacterHash::Vi, 2 },
 { CharacterHash::Viego, 3 },
 { CharacterHash::Viktor, 4 },
 { CharacterHash::Vladimir, 4 },
 { CharacterHash::Volibear, 2 },
 { CharacterHash::Warwick, 2 },
 { CharacterHash::MonkeyKing, 3 },
 { CharacterHash::Xayah, 5 },
 { CharacterHash::Xerath, 4 },
 { CharacterHash::XinZhao, 3 },
 { CharacterHash::Yasuo, 3 },
 { CharacterHash::Yone, 3 },
 { CharacterHash::Yorick, 2 },
 { CharacterHash::Yuumi, 1 },
 { CharacterHash::Zac, 2 },
 { CharacterHash::Zed, 4 },
 { CharacterHash::Zeri, 5 },
 { CharacterHash::Ziggs, 4 },
 { CharacterHash::Zilean, 1 },
 { CharacterHash::Zoe, 4 },
 { CharacterHash::Zyra, 2 },
};

void TargetSelector::initialize()
{
    Menu::main_menu = menu_manager->create_menu("menuTS", "Target selector", ICON_FA_BULLSEYE_POINTER);
    Menu::selection_mode = Menu::main_menu->add_combo("mode", "Mode", 0, { "Auto", "Lowest Hp", "Lowest max Hp", "Highest Hp", "Highest max Hp", "Least spells", "Least autos", "Closest", "Strict priority" });

    target_selector->set_callbacks(
        &get_target,
        &get_target2,
        &get_selected_target,
        &set_selected_target
    );
}

GameObject* TargetSelector::get_target(float range, DamageType damage_type, bool ignore_invulnerability)
{
    if (forced_target && forced_target->is_valid_target(range, { }, ignore_invulnerability))
        return forced_target;

    std::vector<GameObject*> filteredList{ };

    for (const auto& obj : entities->get_heroes())
    {
        if (!obj || !obj->is_enemy() || !obj->is_valid_target(range, { }, ignore_invulnerability))
            continue;

        filteredList.push_back(obj);
    }

    return get_target2(filteredList, damage_type);
}

GameObject* TargetSelector::get_target2(const std::vector<GameObject*>& objects, DamageType damage_type)
{
    if (forced_target && std::find(objects.begin(), objects.end(), forced_target) != objects.end())
        return forced_target;

    switch ((SelectionMode)Menu::selection_mode->get_int())
    {
    case SelectionMode::Auto:
        return getTargetAuto(objects, damage_type);
    case SelectionMode::LowestHp:
        return getTargetLowestHp(objects, damage_type);
    case SelectionMode::LowestMaxHp:
        return getTargetLowestMaxHp(objects, damage_type);
    case SelectionMode::HighestHp:
        return getTargetHighestHp(objects, damage_type);
    case SelectionMode::HighestMaxHp:
        return getTargetHighestMaxHp(objects, damage_type);
    case SelectionMode::LeastSpells:
        return getTargetLeastSpells(objects, damage_type);
    case SelectionMode::LeastAutos:
        return getTargetLeastAutos(objects, damage_type);
    case SelectionMode::Closest:
        return getTargetClosest(objects, damage_type);
    case SelectionMode::StrictPriority:
        return getTargetStrictPriority(objects, damage_type);
    }

    return nullptr;
}

GameObject* TargetSelector::get_selected_target()
{
    return forced_target;
}

void TargetSelector::set_selected_target(GameObject* target)
{
    forced_target = target;
}

int get_priority(GameObject* obj)
{
    return defaultPriorities.contains(obj->get_character_hash()) ? defaultPriorities.at(obj->get_character_hash()) : 0;
}

GameObject* getTargetAuto(std::vector<GameObject*> objects, DamageType damage_type)
{
    if (objects.empty())
        return nullptr;
    
    std::sort(objects.begin(), objects.end(), [damage_type](GameObject* a1, GameObject* a2)
    {
        const auto dmg1 = dmg_lib->calculate_damage(local_player, a1, damage_type, 100.0) / (1 + a1->get_health()) * get_priority(a1);
        const auto dmg2 = dmg_lib->calculate_damage(local_player, a2, damage_type, 100.0) / (1 + a2->get_health()) * get_priority(a2);
        
        return dmg1 > dmg2;
    });

    return objects.front();
}

GameObject* getTargetClosest(const std::vector<GameObject*>& objects, DamageType damageType)
{
    float maxDistance = FLT_MAX;
    GameObject* ret = nullptr;
    for (const auto& obj : objects)
    {
        if (!obj)
            continue;

        const float distance = obj->get_distance(local_player);
        if (distance < maxDistance)
        {
            maxDistance = distance;
            ret = obj;
        }
    }

    return ret;
}

GameObject* getTargetHighestHp(const std::vector<GameObject*>& objects, DamageType damageType)
{
    float maxHealth = 0.f;
    GameObject* ret = nullptr;

    for (const auto& obj : objects)
    {
        if (!obj)
            continue;

        if (obj->get_health() > maxHealth)
        {
            maxHealth = obj->get_health();
            ret = obj;
        }
    }

    return ret;
}

GameObject* getTargetLowestHp(const std::vector<GameObject*>& objects, DamageType damageType)
{
    float maxHealth = FLT_MAX;
    GameObject* ret = nullptr;

    for (const auto& obj : objects)
    {
        if (!obj)
            continue;

        if (obj->get_health() < maxHealth)
        {
            maxHealth = obj->get_health();
            ret = obj;
        }
    }

    return ret;
}

GameObject* getTargetHighestMaxHp(const std::vector<GameObject*>& objects, DamageType damageType)
{
    float maxHealth = 0;
    GameObject* ret = nullptr;

    for (const auto& obj : objects)
    {
        if (!obj)
            continue;

        if (obj->get_max_health() > maxHealth)
        {
            maxHealth = obj->get_max_health();
            ret = obj;
        }
    }

    return ret;
}

GameObject* getTargetLowestMaxHp(const std::vector<GameObject*>& objects, DamageType damageType)
{
    float maxHealth = FLT_MAX;
    GameObject* ret = nullptr;

    for (const auto& obj : objects)
    {
        if (!obj)
            continue;

        if (obj->get_max_health() < maxHealth)
        {
            maxHealth = obj->get_max_health();
            ret = obj;
        }
    }

    return ret;
}

GameObject* getTargetStrictPriority(const std::vector<GameObject*>& objects, DamageType damageType)
{
    int maxPrio = 0;
    GameObject* ret = nullptr;

    for (const auto& obj : objects)
    {
        const int priority = get_priority(obj);

        if (priority > maxPrio)
        {
            maxPrio = priority;
            ret = obj;
        }
    }

    return ret;
}

GameObject* getTargetLeastAutos(std::vector<GameObject*> objects, DamageType damageType)
{
    if (objects.empty())
        return nullptr;
    
    std::sort(objects.begin(), objects.end(), [](GameObject* a1, GameObject* a2)
    {
        const auto dmg1 = dmg_lib->get_auto_attack_damage(local_player, a1) / (1 + a1->get_health()) * get_priority(a1);
        const auto dmg2 = dmg_lib->get_auto_attack_damage(local_player, a2) / (1 + a2->get_health()) * get_priority(a2);
        
        return dmg1 > dmg2;
    });
    
    return objects.front();
}

GameObject* getTargetLeastSpells(std::vector<GameObject*> objects, DamageType damageType)
{
    if (objects.empty())
        return nullptr;
    
    std::sort(objects.begin(), objects.end(), [](GameObject* a1, GameObject* a2)
    {
        const auto dmg1 = dmg_lib->calculate_damage(local_player, a1, DamageType::Magical, 100) / (1 + a1->get_health()) * get_priority(a1);
        const auto dmg2 = dmg_lib->calculate_damage(local_player, a2, DamageType::Magical, 100) / (1 + a2->get_health()) * get_priority(a2);
    
        return dmg1 > dmg2;
    });

    return objects.front();
}