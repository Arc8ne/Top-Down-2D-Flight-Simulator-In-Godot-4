#ifndef LOADING_BAR_HPP

#define LOADING_BAR_HPP

#include <queue>

#include <godot_cpp/classes/progress_bar.hpp>

#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include "MainWorld.hpp"

class MainWorld;

class LoadingBar : public godot::ProgressBar
{
	GDCLASS(LoadingBar, godot::ProgressBar)
private:
	MainWorld* mainWorldPtr;
protected:

public:
	LoadingBar();

	~LoadingBar() = default;

	static void _bind_methods();

	void _ready();

	void _process();
};

#endif