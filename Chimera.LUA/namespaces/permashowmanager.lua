---@class permashowmanager
local permashowmanager = { }

---@param menu menu
---@param pos vec2
---@return permashow
function permashowmanager.add(menu, pos) end

---@param name string
---@return permashow
function permashowmanager.get(name) end

---@param permashow permashow
---@return boolean
function permashowmanager.remove(permashow) end

---@type permashowmanager
_G.permashow_manager = { }