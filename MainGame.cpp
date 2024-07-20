#include "MainGame.h"
#include "Player.h"

void MainGame::Initialize()
{
	srand(GetTickCount64());

	// 전역 윈도우 핸들을 통해 dc를 가져온다
	hdc = GetDC(g_hWnd);

	player = new Player();
	player->Initialize();


}

void MainGame::Update()
{
	player->Update();

	
}

void MainGame::Render()
{
	// 창 해상도만큼 사각형을 새로 그려, 화면이 지워진 것처럼 보이게 함
	Rectangle(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y);
	player->Render(hdc);

}

void MainGame::Release()
{
	// 플레이어 객체가 존재한다면 해제
	if (player)
	{
		delete player;
		player = nullptr;
	}

	// 가져왔던 dc를 시스템에 반환 (해제)
	ReleaseDC(g_hWnd, hdc);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
