---@class damage
local damage = { }

--- @param src gameobject
---@param target gameobject
---@param damage_type integer
---@param base_damage number
function damage.calculate_damage(src, target, damage_type, base_damage) end

---@param src gameobject
---@param target gameobject
---@param slot integer
---@param stage integer
---@param stacks integer
---@return damageoutput
function damage.get_spell_damage(src, target, slot, stage, stacks) end

---@param src gameobject
---@param target gameobject
---@param input damageinput
---@return damageoutput
function damage.get_damage(src, target, input) end

---@param src gameobject
---@param target gameobject
---@param passive boolean
---@param items boolean
function damage.get_auto_damage(src, target, passive, items) end

---@type damage
_G.damage = { }