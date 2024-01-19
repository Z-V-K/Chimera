---@class draw
local draw = { }

---@param p1 vec2
---@param p2 vec2
---@param color integer
---@param rounding number
---@param thickness number
---@param filled boolean
---@return nil
function draw.screen_rectangle(p1, p2, color, rounding, thickness, filled) end

---@param start vec3
---@param _end vec3
---@param color integer
---@param width number
---@param rounding number
---@param thickness number
---@return nil
function draw.rectangle_2points(start, _end, color, width, rounding, thickness) end

---@param p1 vec3
---@param p2 vec3
---@param p3 vec3
---@param p4 vec3
---@param color integer
---@param thickness number
---@return nil
function draw.rectangle_4points(p1, p2, p3, p4, color, thickness) end

---@param p1 vec3
---@param p2 vec3
---@param color integer
---@param thickness number
---@return nil
function draw.line(p1, p2, color, thickness) end

---@param p1 vec2
---@param p2 vec2
---@param color integer
---@param thickness number
function draw.screen_line(p1, p2, color, thickness) end

---@param pos vec2
---@param text string
---@param color integer
---@param font_size integer
---@return nil
function draw.screen_text(pos, text, color, font_size) end

---@param pos vec3
---@param text string
---@param color integer
---@param font_size integer
---@return nil
function draw.text(pos, text, color, font_size) end

---@param texture texture
---@param pos vec2
---@param size vec2
---@param rounding number
---@param color integer
---@param uv_min vec2
---@param uv_max vec2
---@return nil
function draw.texture(texture, pos, size, rounding, color, uv_min, uv_max) end

---@param center vec2
---@param radius number
---@param color integer
---@param thickness number
---@param filled boolean
---@param num_points integer
---@return nil
function draw.screen_circle(center, radius, color, thickness, filled, num_points) end

---@param center vec2
---@param radius number
---@param color integer
---@param thickness number
---@param filled boolean
---@param num_points integer
---@return nil
function draw.screen_circle_minimap(center, radius, color, thickness, filled, num_points) end

---@param center vec3
---@param radius number
---@param color integer
---@param thickness number
---@param filled boolean
---@param num_points integer
---@return nil
function draw.circle(center, radius, color, thickness, filled, num_points) end

---@param center vec2
---@param radius number
---@param a1 number
---@param a2 number
---@param color integer
---@param thickness number
function draw.screen_arc(center, radius, a1, a2, color, thickness) end

---@param text string
---@param font_size integer
---@return vec2
function draw.calc_text_size(text, font_size) end

---@param r integer
---@param g integer
---@param b integer
---@param a integer
---@return integer
function draw.color(r, g, b, a) end

---@type draw
_G.draw = { }
