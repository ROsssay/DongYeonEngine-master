#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"

Game::Game()
	: mHwnd(nullptr)
	, mHdc(nullptr)
	, mWidth(0)
	, mHeight(0)
	, mBackHdc(NULL)
	, mBackBitmap(NULL)
{

}

Game::~Game()
{

}
void Game::Initialize(HWND hwnd, UINT width, UINT height)
{
	adjustWindowRect(hwnd, width, height);
	createBuffer(width, height);
	initializeEtc();

	SceneManager::Initialize();
}
void Game::Run()
{
	Update();
	LateUpdate();
	Render();
}
void Game::Update()
{
	Input::Update();
	Time::Update();

	SceneManager::Update();
}
void Game::LateUpdate()
{

}
void Game::Render()
{
	clearRenderTarget();

	Time::Render(mBackHdc);
	SceneManager::Render(mBackHdc);

	copyRenderTarget(mBackHdc, mHdc);
}

void Game::clearRenderTarget()
{
	//clear
	Rectangle(mBackHdc, -1, -1, 1601, 901);
}

void Game::copyRenderTarget(HDC source, HDC dest)
{
	BitBlt(dest, 0, 0, mWidth, mHeight
		, source, 0, 0, SRCCOPY);
}

void Game::adjustWindowRect(HWND hwnd, UINT width, UINT height)
{
	mHwnd = hwnd;
	mHdc = GetDC(hwnd);

	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	mWidth = rect.right - rect.left;
	mHeight = rect.bottom - rect.top;

	SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
	ShowWindow(hwnd, true);
}

void Game::createBuffer(UINT width, UINT height)
{
	//윈도우 해상도에 맞는 백버퍼(도화지)생성
	mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

	//백버퍼를 가르킬 DC생성
	mBackHdc = CreateCompatibleDC(mHdc);

	HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
	DeleteObject(oldBitmap);
}

void Game::initializeEtc()
{
	Input::Initailize();
	Time::Initailize();
}
