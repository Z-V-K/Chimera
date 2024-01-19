---@class input
local input = { }

---@param key integer
---@return boolean
function input.is_key_down(key) end

---@param key integer
---@return boolean
function input.is_key_up(key) end

---@param key integer
---@return boolean
function input.is_key_pressed(key) end

---@type input
_G.input = { }