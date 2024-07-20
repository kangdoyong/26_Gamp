#pragma once
#include "framework.h"

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600

extern HWND g_hWnd;

// 특정 객체를 그릴 때, 위치와 사이즈가 필요
// 그럼 그 때 마다 위치와 사이즈를 매번 새로 선언하기 귀찮으니까
// 자주 사용되는 데이터를 구조체로 만들어 처리
typedef struct tagInfo
{
	D3DXVECTOR3 pos; // 위치벡터
	D3DXVECTOR3 dir; // 방향벡터 (크기가 1인 벡터)
	D3DXVECTOR3 look; // 0도를 바라보는 크기 1의 방향 벡터 (단위 벡터)
	D3DXVECTOR3 size; // 크기
}INFO;

