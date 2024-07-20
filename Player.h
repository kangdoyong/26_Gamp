#pragma once
#include "Object.h"
class Player :
    public Object
{
private:
	D3DXVECTOR3 originPoint[4]; // 플레이어의 원점 정보를 갖는 배열
	D3DXVECTOR3 calPoint[4]; // 원점의 정보를 가지고 연산한 점들의 정보를 갖는 배열
	D3DXVECTOR3 calPointBack[4]; // 행렬 연산이 적용되지 않은 점들

	float speed; // 속력 
	float bodyAngle; // 탱크 몸체 회전 시, 사용할 각
	float gunBarrelLength; // 포신의 길이
	float gunBarrelAngle; // 포신 회전 시, 사용할 각
	D3DXVECTOR2 gunBarrelPoint; // 포신의 끝점 위치를 나타낼 벡터
	D3DXVECTOR3 moveDisp; // 키 입력으로 이동 시, 한 틱에 이동 변위량을 가질 벡터 

	D3DXMATRIX matScale; // 크기 행렬
	D3DXMATRIX matRotZ; // 회전 행렬 (z축)
	D3DXMATRIX matTrans; // 이동 행렬

	// 행렬의 곱셈은 교환법칙이 성립하지 않는다.
	// 연산 순서 (크기, 자전, 이동, 공전, 부모)
	D3DXMATRIX matSR; // 크기 * 회전 결과를 담을 행렬
	D3DXMATRIX matWorld; // 월드 행렬 (크기 * 회전 * 이동)

public:
    // Object을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Release() override;

	void DisplayText(HDC hdc);
	void DisplayVector(HDC hdc, const wchar_t* text, D3DXVECTOR2 value, D3DXVECTOR2 displayPt);
	void DisplayMat(HDC hdc, const wchar_t* text, D3DXMATRIX& value, D3DXVECTOR2 displayPt);

public:
    Player();
    virtual ~Player();
};

