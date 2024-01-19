#pragma once

enum class MessageType
{
	Log,
	Debug,
	Info,
	Warning,
	Error
};

struct Output {
	std::string text, time;
	bool draw_time;
	MessageType type;

	Output(std::string text_, bool drawTime_, MessageType type_) {
		text = text_;
		draw_time = drawTime_;
		type = type_;
	}
};

class Console {
	void render_log(Output& output);
	void render_log_error(Output& output);
	void render_log_warning(Output& output);
	void render_log_debug(Output& output);
	void render_log_info(Output& output);

	char input_buf[256];
	std::vector<Output> output_arr;

public:
	bool DRAW_CONSOLE = true;

	void render();
	void clear();

	void log(const char*, ...);
	void log_error(const char*, ...);
	void log_info(const char*, ...);
	void log_warning(const char*, ...);
	void log_debug(const char*, ...);

	virtual void __EXPORTlog (const std::string& msg);
	virtual void __EXPORTdbg (const std::string& msg);
	virtual void __EXPORTerr (const std::string& msg);
	virtual void __EXPORTwarn(const std::string& msg);
	virtual void __EXPORTinfo(const std::string& msg);
};