---@class cb
---@field public on_before_attack integer
---@field public on_after_attack integer
---@field public on_before_move integer
---@field public on_after_move integer
---@field public tick integer
---@field public slowtick integer
---@field public draw integer
---@field public create_obj integer
---@field public delete_obj integer
---@field public process_spell integer
---@field public issue_order integer
---@field public cast_spell integer
---@field public stop_cast integer
---@field public cast_complete integer
---@field public draw_env integer
---@field public spell_impact integer
---@field public play_anim integer
---@field public buff_gainlose integer
---@field public set_path integer
---@field public process_auto integer
---@field public notify_event integer
---@field public before_attack_orb integer
---@field public after_attack_orb integer
---@field public before_move_orb integer
---@field public after_move_orb integer
local cb = { }

---@param callback integer
---@param fn function
---@return nil
function cb.add(callback, fn) end

---@param callback integer
---@param fn function
---@return nil
function cb.remove(callback, fn) end

---@type cb
_G.cb = { }