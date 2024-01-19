---@class nav_mesh
local nav_mesh = { }

---@param pos vec3
---@return number
function nav_mesh.get_height(pos) end

---@param pos vec3
---@return integer
function nav_mesh.get_flags(pos) end

---@param pos vec3
---@return boolean
function nav_mesh.is_in_fow(pos) end

---@param pos vec3
---@param flags integer
---@return nil
function nav_mesh.set_cell_flags(pos, flags) end

---@type nav_mesh
_G.nav_mesh = { }
