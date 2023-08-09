#include "LoadingBar.hpp"

LoadingBar::LoadingBar()
{
	this->mainWorldPtr = nullptr;
}

void LoadingBar::_bind_methods()
{

}

void LoadingBar::_ready()
{
	if (godot::Engine::get_singleton()->is_editor_hint() == false)
	{
		this->mainWorldPtr = godot::Object::cast_to<MainWorld>(
			this->get_parent()
		);
	}
	else
	{
		this->set_process_internal(false);

		this->set_physics_process_internal(false);
	}
}

void LoadingBar::_process()
{

}
