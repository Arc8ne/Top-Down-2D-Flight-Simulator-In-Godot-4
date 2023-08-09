#include "register_types.hpp"

#include "Test.hpp"
#include "MainWorld.hpp"
#include "MainFollowCamera.hpp"
#include "Aircraft.hpp"

namespace godot 
{
    void initialize_main_module(godot::ModuleInitializationLevel p_level)
    {
	    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
		    return;

	    ClassDB::register_class<Test>();
	    ClassDB::register_class<MainWorld>();
	    ClassDB::register_class<Aircraft>();
	    ClassDB::register_class<MainFollowCamera>();
    }

    void uninitialize_main_module(godot::ModuleInitializationLevel p_level)
    {
	    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
		    return;
    }

    extern "C"
    {
	    GDExtensionBool GDE_EXPORT main_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization)
	    {
		    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		    init_obj.register_initializer(initialize_main_module);

		    init_obj.register_terminator(uninitialize_main_module);

		    init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

		    /*
		    Error context:
		    The following errors are logged in the editor's console:
		    Attempt to get non-existent interface function:
		    classdb_register_extension_class_property_indexed

		    Unable to load GDExtension interface function
		    classdb_register_extension_class_property_indexed()

		    core/extension/gdextension.cpp:476 - GDExtension initialization function
		    'example_library_init' returned an error.
		
		    Failed loading resource: res://example.gdextension. Make sure resources have been
		    imported by opening the project in the editor at least once.

		    Error occurred somewhere in this method.
		    */
		    return init_obj.init();

		    // return 1;
	    }
    }
}