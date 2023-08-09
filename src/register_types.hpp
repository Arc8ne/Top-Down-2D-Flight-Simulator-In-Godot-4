#pragma once

#include <godot_cpp/core/class_db.hpp>

namespace godot 
{
    void initialize_main_module(godot::ModuleInitializationLevel p_level);
    void uninitialize_main_module(godot::ModuleInitializationLevel p_level);
}
