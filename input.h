#pragma once
#include <dinput.h>

namespace Input {
	static LPDIRECTINPUT8 g_pDI;
	static LPDIRECTINPUTDEVICE8 g_pKeyboard;
	static DIDATAFORMAT format;
	static BYTE keys[256] = {};


	void initKey(HINSTANCE hinstance, HWND hwnd);
	void SetInputState();
	bool GetInputState(int key);
}