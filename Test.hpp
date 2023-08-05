#pragma once

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/method_ptrcall.hpp>

namespace godot
{
    class Test : public Camera2D
    {
        GDCLASS(Test, Camera2D);

    public:
        static void _bind_methods();

    protected:
        Vector2 get_asdf() const;
        void set_asdf(Vector2 v);

    private:
        Vector2 m_vec{ 0, 0 };
    };
}