---@class obj_manager
local obj_manager = { }

---@param index integer
---@return gameobject
function obj_manager.find(index) end

---@param netid integer
---@return gameobject
function obj_manager.find_netid(netid) end

---@type obj_manager
_G.obj_manager = { }