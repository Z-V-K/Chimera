---@class permashow
---@field public name string
local permashow = { }

---@param item menuitem
---@param name string
---@return boolean
function permashow:add_element(item, name) end

---@param item menuitem
---@return boolean
function permashow:remove_element(item) end

---@return nil
function permashow:clear() end

---@param item menuitem
---@return nil
function permashow:set_draw(item) end
