#pragma once






#define APP_VERSION_MAJOR 5
#define APP_VERSION_MINOR 4
#define APP_VERSION_PATCH 0
#define APP_VERSION_BUILD 0

#define APP_VERSION_INTERNAL_HELPER(x) #x
#define APP_VERSION_INTERNAL_TOSTR(x) APP_VERSION_INTERNAL_HELPER(x)

#define APP_VERSION_STRING_FULL APP_VERSION_INTERNAL_TOSTR(APP_VERSION_MAJOR) "." APP_VERSION_INTERNAL_TOSTR(APP_VERSION_MINOR) "." APP_VERSION_INTERNAL_TOSTR(APP_VERSION_PATCH) "." APP_VERSION_INTERNAL_TOSTR(APP_VERSION_BUILD)
#define APP_VERSION_STRING_SHORT APP_VERSION_INTERNAL_TOSTR(APP_VERSION_MAJOR) "." APP_VERSION_INTERNAL_TOSTR(APP_VERSION_MINOR)




/*
	#define ALLOC_CONSOLE

	Determines if application should create a console window and redirect output streams into it.
	NOTE: UETools UI & keybindings will only work within console window while it's present.
*/

#ifdef _DEBUG
	#define ENABLE_LOGGING
#endif




// =======================
// | SYSTEM PATH SECTION |
// =======================

#define PATH_CONFIG_FEATURES "UETools\\Features.cfg"
#define PATH_CONFIG_POSITIONS "UETools\\Positions.cfg"
#define PATH_CONFIG_KEYBINDINGS "UETools\\Keybindings.cfg"

#ifdef ENABLE_LOGGING
	#define PATH_LOG_GENERAL "UETools\\General.log"
	#define PATH_LOG_EXCEPTIONS "UETools\\Exceptions.log"
#endif




// =======================
// |  RENDERING SECTION  |
// =======================

//#define API_D3D11
#define API_OPENGL3

#if (defined(API_D3D11) + defined(API_OPENGL3)) == 0
	#error "Build Error: No Graphics API selected! Please define exactly one API (e.g., API_D3D11)."
#elif (defined(API_D3D11) + defined(API_OPENGL3)) > 1
	#error "Build Error: Multiple Graphics APIs selected! Please define ONLY ONE API."
#endif

/*
	#define INACTIVE_ZERO_SIZE

	Sets overlay window to { 0, 0 } size when menu isn't active or target window isn't in focus.
	Should only be used as an emergency solution for Windows 24H2+ black screen glitch as it disables all of background rendering features.
*/




// ======================
// |  GENERAL SECTION   |
// ======================

#define WAIT_FOR_TITLE_INIT
/*
	Delays the GUI initialization loop until the core title classes are valid.

	Use cases:
	- When loading as an ASI plugin (early injection).
	- To prevent crashes when accessing SDK pointers before the engine is fully set up.

	Note: This will block the initialization thread (but not the main title thread) until the title is ready.
*/

#define LARGE_BUFFER_OBJECTPATH
/*
	Expands the character limit for asset paths inputs. Can be found useful when dealing with large scale open worlds levels loading and etc.
*/
#ifdef LARGE_BUFFER_OBJECTPATH
	#define SIZE_BUFFER_SINGLEOBJECTPATH 2048
	#define SIZE_BUFFER_MULTIOBJECTPATH 16384
#else
	#define SIZE_BUFFER_SINGLEOBJECTPATH 255
	#define SIZE_BUFFER_MULTIOBJECTPATH 2048
#endif

#define LARGE_BUFFER_SEARCHFILTER
/*
	Expands the character limit for search filter inputs.
*/
#ifdef LARGE_BUFFER_SEARCHFILTER
	#define SIZE_BUFFER_SEARCHFILTER 2048
#else
	#define SIZE_BUFFER_SEARCHFILTER 255
#endif

#define SIZE_BUFFER_POSITIONSENTRY 255

#define SIZE_BUFFER_CONSOLE 2048




// ======================
// |  FEATURES SECTION  |
// ======================

/*
	#define UE5

	When targeting Unreal Engine 5 based titles, it's recommended to uncomment that define;
	In many cases that action alone would be enough to adapt entirity of solution for newer engine.
*/

/*
	#define ACTOR_TRACE

	The way Line Tracing work often differ from Engine to Engine (e.g. 4.25 -> 4.27),
	it's disabled by default in order to avoid a potential set of compilation errors.
*/

/*
	#define SOFT_PATH

	Enables everything related to soft path (e.g. Actor Summon & Widget Construct).
*/

#define SOFT_LOAD_FREEMEMORY
/*
	WARNING: Use with caution.
	In titles with active/aggressive Garbage Collection, Object would be unloaded too early in the process resulting in a game crash.
*/

/*
	#define ACTORS_TRACKING

	Enables everything related to Actors tracking (e.g. Enable Tracking).
*/

/*
	#define COLLISION_VISUALIZER

	Enables everything related to collision visualization (e.g. Draw Collision).
*/

/*
	#define ACTOR_KIND

	Enables everything related to Actor Kind subsystem (e.g. Point Light Settings, Spot Light Settings, Pawn Actions...).
*/

/*
	#define LEVEL_SEQUENCE

	Enables everything related to Level Sequences.
*/

/*
	#define FREE_CAMERA

	Enables everything related to Free Camera.
*/