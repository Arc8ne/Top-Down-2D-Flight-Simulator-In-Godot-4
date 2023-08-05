#pragma once

#include <map>

#include <godot_cpp/godot.hpp>

#include <godot_cpp/classes/camera2d.hpp>

#include <godot_cpp/classes/input_event.hpp>

#include <godot_cpp/classes/input_event_key.hpp>

#include <godot_cpp/classes/global_constants.hpp>

#include <godot_cpp/classes/sprite2d.hpp>

#include <godot_cpp/classes/label.hpp>

#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/classes/v_box_container.hpp>

#include <godot_cpp/classes/viewport.hpp>

#include <godot_cpp/variant/transform2d.hpp>

#include <godot_cpp/classes/style_box.hpp>

#include <godot_cpp/classes/input_event_mouse_motion.hpp>

#include <godot_cpp/classes/input_event_mouse_button.hpp>

#include <godot_cpp/classes/check_button.hpp>

#include "SimulatorCore.hpp"

namespace godot
{
	class MainFollowCamera : public godot::Camera2D
	{
		GDCLASS(MainFollowCamera, godot::Camera2D)
	private:
		int acceleration = 1;

		int deceleration = 1;

		int turnRate = 50;

		int maxVelocity = 300;

		int velocity = 0;

		int altitude = 0;

		double altitudeChangeRate = 0;

		std::map<int, bool> keyToPressedStatusMap = std::map<int, bool>();

		godot::Sprite2D* aircraftSpritePtr = nullptr;

		godot::Sprite2D* aircraftShadowPtr = nullptr;

		godot::VBoxContainer* hudVBoxContainerPtr = nullptr;

		godot::Label* airspeedLabelPtr = nullptr;

		godot::Label* altitudeLabelPtr = nullptr;

		godot::Vector2 shadowOffset = godot::Vector2(0, 0);

		godot::Color redColor = godot::Color(255, 0, 65, 1);

		godot::Color whiteColor = godot::Color(255, 255, 255, 1);

		godot::CheckButton* gpsCheckButtonPtr = nullptr;

		int lowAltitude = 101;

		void RegulateVelocity();

		void RegulateAltitude();

		void UpdateAirspeedLabel();

		void UpdateAltitudeLabel();

		void UpdateShadowBasedOnAltitude();

		void UpdateShadowBasedOnRotation();

		void UpdateHUDBasedOnCameraZoom();

		godot::Vector2 GetLift();

		void OnInputMouseMotion(godot::InputEventMouseMotion* inputEventMouseMotionPtr);

		void OnInputMouseButton(godot::InputEventMouseButton* inputEventMouseButtonPtr);

		void OnGPSCheckButtonToggled(bool isButtonPressed);
	protected:

	public:
		static void _bind_methods();

		MainFollowCamera() = default;

		~MainFollowCamera() = default;

		void _ready();

		void _input(godot::InputEvent* inputEventPtr);

		void _physics_process(float delta);
	};
}
