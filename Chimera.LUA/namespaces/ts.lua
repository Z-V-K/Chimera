---@class ts
---@field public selected_target gameobject
local ts = { }

---@param range number
---@param damage_type integer
---@param ignore_invulnerability boolean
---@return gameobject
function ts.get_target(range, damage_type, ignore_invulnerability) end

---@param list gameobject[]
---@param damage_type integer
---@return gameobject
function ts.get_target_filter(list, damage_type) end

---@type ts
_G.ts = { }