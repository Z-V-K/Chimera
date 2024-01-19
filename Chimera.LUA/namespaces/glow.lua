---@class glow
local glow = { }

---@param obj gameobject
---@param color integer
---@param size integer
---@param blur integer
---@return boolean
function glow.add(obj, color, size, blur) end

---@param obj gameobject
---@return boolean
function glow.remove(obj) end

---@param obj gameobject
---@return boolean
function glow.is_glowing(obj) end


---@type glow
_G.glow = { }