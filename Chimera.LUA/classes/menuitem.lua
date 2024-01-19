---@class menuitem
---@field public key string
---@field public name string
---@field public bool boolean
---@field public int integer
---@field public col number
local menuitem = { }

---@param item menuitem
---@return nil
function menuitem:set_visible(item) end

---@param str string
---@return nil
function menuitem:set_tooltip(str) end

---@param texture texture
---@return nil
function menuitem:set_texture(texture) end
