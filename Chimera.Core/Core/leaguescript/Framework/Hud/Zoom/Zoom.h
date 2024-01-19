#pragma once

class Zoom final
{
	static Zoom* get_instance();
	static Zoom* get_instance_from_hud();
public:
	static void set_flag_value(int val);
	static float get_value();
	static float get_max_value();
	static float get_camera_angle();
	static void set_camera_angle(float f);
	static void set_value(float f);
	static void set_max_zoom(float f);
};
