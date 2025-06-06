#pragma once

#include "GameObject.h"


class Game
{
public:
	Game();
	~Game();

	void Initialize(HWND hwnd, UINT width, UINT height);
	void Run();

	void Update();
	void LateUpdate();
	void Render();

private:
	void clearRenderTarget();
	void copyRenderTarget(HDC source, HDC dest);
	void adjustWindowRect(HWND hwnd, UINT width, UINT height);
	void createBuffer(UINT width, UINT height);
	void initializeEtc();

private:
	HWND mHwnd;
	HDC mHdc;

	HDC mBackHdc;
	HBITMAP mBackBitmap;

	UINT mWidth;
	UINT mHeight;

};

