// Error reporting
#include <iostream>

// SDL Library
#include <SDL.h>
#ifndef SDL2
#pragma comment(lib, "SDLmain.lib") // Replace main with SDL_main
#endif
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "glu32.lib")

// SDL Specific Code
#if defined SDL2
#include "sdl2/timer.hpp"
#include "sdl2/input.hpp"
#else
#include "sdl/timer.hpp"
#include "sdl/input.hpp"
#endif

#include "video.hpp"

#include "romloader.hpp"
#include "trackloader.hpp"
#include "stdint.hpp"
#include "sharedresources.hpp"
#include "setup.hpp"
#include "engine/outrun.hpp"
#include "frontend/config.hpp"
#include "frontend/menu.hpp"

#include "cannonboard/interface.hpp"
#include "engine/oinputs.hpp"
#include "engine/ooutputs.hpp"
#include "engine/omusic.hpp"

// Direct X Haptic Support.
// Fine to include on non-windows builds as dummy functions used.
#include "directx/ffeedback.hpp"

// Initialize Shared Variables
using namespace cannonball;

int    cannonball::state       = STATE_BOOT;
double cannonball::frame_ms    = 0;
int    cannonball::frame       = 0;
bool   cannonball::tick_frame  = true;
int    cannonball::fps_counter = 0;

#ifdef COMPILE_SOUND_CODE
Audio cannonball::audio;
#endif