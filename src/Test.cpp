#include "Test.hpp"

namespace godot
{
    void Test::_bind_methods()
    {
        ClassDB::bind_method(D_METHOD("get_asdf"), &Test::get_asdf);
        ClassDB::bind_method(D_METHOD("set_asdf", "v"), &Test::set_asdf);
    }

    Vector2 Test::get_asdf() const
    {
        return m_vec;
    }

    void Test::set_asdf(Vector2 v)
    {
        m_vec = v;
    }
}