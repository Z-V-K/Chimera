---@class menu
---@field public key string
---@field public name string
local menu = { }

---@param key string
---@param name string
---@return menuitem
function menu:separator(key, name) end

---@param key string
---@param name string
---@param default_value boolean
---@param icon string
---@return menuitem
function menu:checkbox(key, name, default_value, icon) end

---@param key string
---@param name string
---@param default_value integer
---@param min integer
---@param max integer
---@param icon string
---@return menuitem
function menu:slider(key, name, default_value, min, max, icon) end

---@param key name
---@param name name
---@param default_value integer
---@param icon string
---@return menuitem
function menu:color(key, name, default_value, icon) end

---@param key string
---@param name string
---@param default_value number
---@param values string[]
---@param icon string
---@return menuitem
function menu:combo(key, name, default_value, values, icon) end

---@param key string
---@param name string
---@param hold boolean
---@param default_key integer
---@param default_value integer
---@param icon string
---@return menuitem
function menu:key(key, name, hold, default_key, default_value, icon) end

---@param key string
---@param name string
---@param button_text string
---@param fn function
---@return menuitem
function menu:button(key, name, button_text, fn) end

---@param texture texture
---@return nil
function menu:set_texture(texture) end

---@param item menuitem
---@return nil
function menu:set_enabled(item) end

---@param item menuitem
---@return boolean
function menu:delete(item) end

---@param key string
---@return boolean
function menu:delete_key(key) end

---@param key string
---@return menuitem
function menu:get(key) end

