#include "cannonball_loader.h"
#include <windows.h>
#include <cstdint>
#include <string>

#include "externalinterface.hpp"

#ifdef _WIN64
#define DUBI_CANNONBALL_DLL	L"cannonball_x64.dll"
#else
#define DUBI_CANNONBALL_DLL	L"cannonball.dll"
#endif

CannonBall_Loader::CannonBall_Loader()
{

}

CannonBall_Loader::~CannonBall_Loader()
{

}

void CannonBall_Loader::Init()
{

}

void CannonBall_Loader::Run()
{
	HINSTANCE hInstance = LoadLibrary(DUBI_CANNONBALL_DLL);
	if (hInstance)
 	{
// 		funAdd fndynamicAdd = (funAdd)GetProcAddress(hInstance, "dynamicAdd");
// 		if (fndynamicAdd)
// 		{
// 			char msg[256];
// 			sprintf(msg, "test dynamic dll = %d \n", fndynamicAdd(4, 8));
// 			printf(msg);
// 		}
 	}

	ExternalInterface* pObj = ExternalInterface_new();

	if (pObj)
	{ 
		OutputDebugStringA("1");

		ExternalInterface_init(pObj);

		OutputDebugStringA("2");
		Sleep(1000);

		OutputDebugStringA("3");
		int nWidth = ExternalInterface_getScreenWidth(pObj);
		OutputDebugStringA("4");
		int nHeight = ExternalInterface_getScreenHeight(pObj);
		OutputDebugStringA("5");

		int nLength = nWidth*nHeight;

		// start
		ExternalInput pInput;
		pInput.is_start_pressed = true;
		pInput.is_accel_pressed = false;
		pInput.is_brake_pressed = false;
		pInput.is_coin_pressed = false;
		pInput.is_steer_left_pressed = false;
		pInput.is_steer_right_pressed = false;

		OutputDebugStringA("6");
		ExternalInterface_tick(pObj, pInput);
		OutputDebugStringA("7");

		pInput.is_start_pressed = false;
		pInput.is_coin_pressed = true;
		ExternalInterface_tick(pObj, pInput);
		Sleep(1000);

		do 
		{
			Sleep(10);

			uint32_t speed = ExternalInterface_getSpeed(pObj);

			char msg[256];
			sprintf(msg, "speed = %d", speed);
			OutputDebugStringA(msg);

			uint32_t score = ExternalInterface_getScore(pObj);

			sprintf(msg, "score = %d", score);
			OutputDebugStringA(msg);

			pInput.is_start_pressed = false;
			pInput.is_coin_pressed = true;
			ExternalInterface_tick(pObj, pInput);

			pInput.is_start_pressed = true;
			pInput.is_coin_pressed = false;
			ExternalInterface_tick(pObj, pInput);

			pInput.is_start_pressed = false;
			pInput.is_coin_pressed = false;
			pInput.is_accel_pressed = true;
			ExternalInterface_tick(pObj, pInput);
		} while (true);


	}
	
}