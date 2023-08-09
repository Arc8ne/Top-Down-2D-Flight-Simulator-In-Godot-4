#pragma once

#include <godot_cpp/variant/string.hpp>

#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/classes/sprite2d.hpp>

/*
Physics goals:
- Airspeed should affect altitude.
- Pitch, roll and altitude should not affect airspeed.
*/

class Aircraft : public godot::Sprite2D
{
	GDCLASS(Aircraft, godot::Sprite2D)
private:
	godot::String name = "";

	godot::Vector2 velocity = godot::Vector2(0, 0);

	double area = 0;

	double airPressure = 1.0;

	double liftCoefficient = 1.0;

	double dragCoefficient = 1.0;

	double angleOfAttack = 0.0;
protected:
	static void _bind_methods();
public:
	void _ready();

	double GetLift();

	double GetDrag();
};