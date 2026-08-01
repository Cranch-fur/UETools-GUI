#pragma once
#include "resource.h"






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




// =================================
// |   BACKGROUND TASKS SECTION    |
// =================================
#define TASK_CONSTRUCT_CONSOLE
/*
	Background task that ensures the Console exists (creating it if missing) and sets up keybinds to open it.
*/

/*
	#define TASK_CONSTRUCT_CHEATMANAGER

	Background task that ensures the Cheat Manager exists (creating it if missing).
	Note: This may cause random crashes when transitioning between levels.
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
	#define SOFT_PATH

	Enables everything related to soft path (e.g. Actor Summon & Level Sequence).
*/

/*
	#define SOFT_LOAD_FREEMEMORY

	Determines if we should unload Actor we tried to summon / Object we tried to construct from memory once it's no longer needed.
*/

/*
	#define COLLISION_VISUALIZER

	Enables everything related to collision visualization (e.g. Draw Collision).
*/