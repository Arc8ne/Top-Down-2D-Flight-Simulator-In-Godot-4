#ifndef EXAMPLE_REGISTER_TYPES_H

#define EXAMPLE_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

#include "MainWorld.hpp"

#include "Aircraft.hpp"

#include "MainFollowCamera.hpp"

#include "LoadingBar.hpp"

void initialize_main_module(godot::ModuleInitializationLevel p_level);

void uninitialize_main_module(godot::ModuleInitializationLevel p_level);

#endif // EXAMPLE_REGISTER_TYPES_H