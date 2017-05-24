#pragma once

//#include "globals.hpp"

#ifdef COMPILE_SOUND_CODE
#ifdef SDL2
#include "sdl2/audio.hpp"
#else
#include "sdl/audio.hpp"
#endif
#endif

#include "externalinput.hpp"

#ifdef KV_EXPORTS
#define KV_API __declspec(dllexport)
#else
#define KV_API __declspec(dllimport)
#endif

class KV_API ExternalInterface
{
public:
    ExternalInterface();
    ~ExternalInterface();

    void init();
    void reset();
    void close();
    void tick(ExternalInput external_input);

    uint32_t* get_pixels_rgb();
    uint32_t* get_pixels_greyscale();
    int get_screen_width();
    int get_screen_height();
    uint32_t get_score();
    uint32_t get_speed();
    uint32_t num_wheels_off_road();
    bool is_crashed();
    bool is_game_over();
};

// Expose these methods for posterior usage inside python
// Since ctypes can only talk to C functions, you need to provide those declaring them as extern "C"
#ifdef __cplusplus
extern "C"
{
#endif
	KV_API ExternalInterface* ExternalInterface_new();
	KV_API void ExternalInterface_init(ExternalInterface* externalInterface);
	KV_API void ExternalInterface_reset(ExternalInterface* externalInterface);
	KV_API void ExternalInterface_close(ExternalInterface* externalInterface);
	KV_API void ExternalInterface_tick(ExternalInterface* externalInterface, ExternalInput externalInput);
	KV_API uint32_t* ExternalInterface_getPixelsRGB(ExternalInterface* externalInterface);
	KV_API uint32_t* ExternalInterface_getPixelsGreyscale(ExternalInterface* externalInterface);
	KV_API int ExternalInterface_getScreenWidth(ExternalInterface* externalInterface);
	KV_API int ExternalInterface_getScreenHeight(ExternalInterface* externalInterface);
	KV_API uint32_t ExternalInterface_getScore(ExternalInterface* externalInterface);
	KV_API uint32_t ExternalInterface_getSpeed(ExternalInterface* externalInterface);
	KV_API uint32_t ExternalInterface_numWheelsOffRoad(ExternalInterface* externalInterface);
	KV_API bool ExternalInterface_isCrashed(ExternalInterface* externalInterface);
	KV_API bool ExternalInterface_isGameOver(ExternalInterface* externalInterface);
#ifdef __cplusplus
}
#endif

extern KV_API ExternalInterface external_interface;