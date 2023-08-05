#pragma once

#include <godot_cpp/godot.hpp>

#include <godot_cpp/classes/node2d.hpp>

class MainWorld : public godot::Node2D
{
	GDCLASS(MainWorld, godot::Node2D)
private:

protected:
	static void _bind_methods();
public:
	void _ready();
};
