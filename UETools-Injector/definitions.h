#pragma once






// =======================
// |  RENDERING SECTION  |
// =======================

//#define API_D3D11
#define API_OPENGL3

#if (defined(API_D3D11) + defined(API_OPENGL3)) == 0
	#error "Build Error: No Graphics API selected! Please define exactly one API (e.g., API_OPENGL3)."
#elif (defined(API_D3D11) + defined(API_OPENGL3)) > 1
	#error "Build Error: Multiple Graphics APIs selected! Please define ONLY ONE API."
#endif
