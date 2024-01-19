---@class health_pred
local health_pred = { }

---@param obj gameobject
---@param time integer ticks
---@param delay integer ticks
---@return number
function health_pred.predict(obj, time, delay) end

---@param obj gameobject
---@param time integer ticks
---@param delay integer ticks
---@return number
function health_pred.get_incoming_damage(obj, time, delay) end

---@param obj gameobject
---@return boolean
function health_pred.has_turret_aggro(obj) end

---@param obj gameobject
---@return boolean
function health_pred.has_minion_aggro(obj) end

---@param obj gameobject
---@return integer
function health_pred.turret_aggro_start_time(obj) end

---@param obj gameobject
---@return gameobject
function health_pred.aggro_turret(obj) end

---@type health_pred
_G.health_pred = { }