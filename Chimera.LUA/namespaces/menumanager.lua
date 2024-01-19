---@class menumanager
local menumanager = { }

---@param key string
---@param name string
---@param icon string
---@return menu
function menumanager.create(key, name, icon) end

---@param menu menu
---@return boolean
function menumanager.delete(menu) end

---@param key string
---@return boolean
function menumanager.delete_key(key) end

---@param key string
---@return menu
function menumanager.get(key) end

---@return menu[]
function menumanager.list() end

---@type menumanager
_G.menu = { }