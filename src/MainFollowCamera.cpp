#include "MainFollowCamera.hpp"

void MainFollowCamera::RegulateVelocity()
{
	if (this->velocity >= 0)
	{
		if (this->velocity > this->maxVelocity)
		{
			this->velocity = this->maxVelocity;
		}
	}
	else
	{
		this->velocity = 0;
	}
}

void MainFollowCamera::RegulateAltitude()
{
	if (this->altitude < 0)
	{
		this->altitude = 0;
	}
}

void MainFollowCamera::UpdateAirspeedLabel()
{
	this->airspeedLabelPtr->set_text(
		godot::String::num(this->velocity) + (godot::String)" kts"
	);

	// godot::Godot::print("Lift: " + this->GetLift());
}

void MainFollowCamera::UpdateAltitudeLabel()
{
	this->altitudeLabelPtr->set_text(
		godot::String::num(this->altitude) + (godot::String)" ft"
	);

	if (this->altitude < this->lowAltitude)
	{
		this->altitudeLabelPtr->add_theme_color_override(
			"font_color",
			this->redColor
		);
	}
	else
	{
		this->altitudeLabelPtr->add_theme_color_override(
			"font_color",
			this->whiteColor
		);
	}
}

void MainFollowCamera::UpdateShadowBasedOnAltitude()
{
	this->shadowOffset.x = this->altitude * -0.2;

	this->shadowOffset.y = this->altitude * 0.2;

	this->aircraftShadowPtr->set_position(
		this->aircraftSpritePtr->get_position() + this->shadowOffset
	);
}

void MainFollowCamera::UpdateShadowBasedOnRotation()
{
	this->aircraftShadowPtr->set_rotation(
		this->aircraftSpritePtr->get_rotation()
	);
}

void MainFollowCamera::UpdateHUDBasedOnCameraZoom()
{
	// return;

	this->hudVBoxContainerPtr->set_position(
		this->get_viewport_rect().size / 2 + godot::Vector2(40, 40)
	);
}

godot::Vector2 MainFollowCamera::GetLift()
{
	godot::Vector2 lift = godot::Vector2(0, 0);

	lift = (1.0 / 2.0) * 1.0 * (this->velocity * this->velocity) * 1.0 * this->aircraftSpritePtr->get_rect().get_size();

	return lift;
}

void MainFollowCamera::OnInputMouseMotion(godot::InputEventMouseMotion* inputEventMouseMotionPtr)
{

}

void MainFollowCamera::OnInputMouseButton(godot::InputEventMouseButton* inputEventMouseButtonPtr)
{
	if (inputEventMouseButtonPtr->is_pressed() == true)
	{
		int64_t buttonIndex = inputEventMouseButtonPtr->get_button_index();

		if (buttonIndex == godot::MOUSE_BUTTON_WHEEL_UP)
		{
			this->set_zoom(
				this->get_zoom() - godot::Vector2(0.1, 0.1)
			);
		}
		else if (buttonIndex == godot::MOUSE_BUTTON_WHEEL_DOWN)
		{
			this->set_zoom(
				this->get_zoom() + godot::Vector2(0.1, 0.1)
			);
		}
	}
}

void MainFollowCamera::OnGPSCheckButtonToggled(bool isButtonPressed)
{

}

void MainFollowCamera::_bind_methods()
{
	godot::ClassDB::bind_method(
		godot::D_METHOD("get_lift"),
		&MainFollowCamera::GetLift
	);
}

void MainFollowCamera::_ready()
{
	if (godot::Engine::get_singleton()->is_editor_hint() == false)
	{
		godot::UtilityFunctions::print("Ready.");

		SimulatorCore::instancePtr = new SimulatorCore();

		/*
		this->aircraftSpritePtr = this->get_node<godot::Sprite2D>("AircraftSprite");

		this->aircraftShadowPtr = this->get_node<godot::Sprite2D>("AircraftShadowSprite");

		this->hudVBoxContainerPtr = this->get_node<godot::VBoxContainer>(
			"HUDCanvasLayer/HUDVBoxContainer"
		);

		this->airspeedLabelPtr = this->hudVBoxContainerPtr->get_node<godot::Label>(
			"AirspeedLabel"
		);

		this->altitudeLabelPtr = this->hudVBoxContainerPtr->get_node<godot::Label>(
			"AltitudeLabel"
		);

		this->gpsCheckButtonPtr = this->get_node<godot::CheckButton>(
			"HUDCanvasLayer/TopRightVBoxContainer/GPSCheckButton"
		);

		this->gpsCheckButtonPtr->connect(
			"toggled",
			godot::Callable(
				this,
				"OnGPSCheckButtonToggled"
			)
		);

		this->UpdateAirspeedLabel();

		this->UpdateAltitudeLabel();

		this->UpdateHUDBasedOnCameraZoom();
		*/
	}
	else
	{
		this->set_process_internal(false);

		this->set_physics_process_internal(false);
	}
}

void MainFollowCamera::_input(godot::InputEvent* inputEventPtr)
{
	if (inputEventPtr->is_class("InputEventKey") == true)
	{
		godot::InputEventKey* inputEventKeyPtr = godot::Object::cast_to<godot::InputEventKey>(inputEventPtr);
	
		this->keyToPressedStatusMap[inputEventKeyPtr->get_keycode()] = inputEventPtr->is_pressed();
	}
	else if (inputEventPtr->is_class("InputEventMouseButton") == true)
	{
		this->OnInputMouseButton(
			godot::Object::cast_to<godot::InputEventMouseButton>(
				inputEventPtr
			)
		);
	}
}

void MainFollowCamera::_physics_process(float delta)
{
	godot::UtilityFunctions::print("Calling _physics_process.");

	/*
	if (this->keyToPressedStatusMap[godot::KEY_PAGEUP] == true)
	{
		this->velocity += this->acceleration;

		this->RegulateVelocity();

		this->UpdateAirspeedLabel();
	}
	else if (this->keyToPressedStatusMap[godot::KEY_PAGEDOWN] == true)
	{
		this->velocity -= this->deceleration;

		this->RegulateVelocity();

		this->UpdateAirspeedLabel();
	}
	
	if (this->keyToPressedStatusMap[godot::KEY_A] == true)
	{
		this->aircraftSpritePtr->set_rotation_degrees(
			this->aircraftSpritePtr->get_rotation_degrees() - this->turnRate * delta
		);

		this->UpdateShadowBasedOnRotation();
	}
	else if (this->keyToPressedStatusMap[godot::KEY_D] == true)
	{
		this->aircraftSpritePtr->set_rotation_degrees(
			this->aircraftSpritePtr->get_rotation_degrees() + this->turnRate * delta
		);

		this->UpdateShadowBasedOnRotation();
	}

	if (this->keyToPressedStatusMap[godot::KEY_W] == true)
	{
		this->altitude += 1;

		this->RegulateAltitude();

		this->UpdateAltitudeLabel();

		this->UpdateShadowBasedOnAltitude();
	}
	else if (this->keyToPressedStatusMap[godot::KEY_S] == true)
	{
		this->altitude -= 1;

		this->RegulateAltitude();

		this->UpdateAltitudeLabel();

		this->UpdateShadowBasedOnAltitude();
	}

	this->set_position(
		this->get_position() + (godot::Vector2(0, 0) * this->velocity * delta).rotated(
			this->aircraftSpritePtr->get_rotation()
		)
	);
	*/
}

void MainFollowCamera::_process(float delta)
{

}
