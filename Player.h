#pragma once
#include "Object.h"
class Player :
    public Object
{
private:
	D3DXVECTOR3 originPoint[4]; // �÷��̾��� ���� ������ ���� �迭
	D3DXVECTOR3 calPoint[4]; // ������ ������ ������ ������ ������ ������ ���� �迭
	D3DXVECTOR3 calPointBack[4]; // ��� ������ ������� ���� ����

	float speed; // �ӷ� 
	float bodyAngle; // ��ũ ��ü ȸ�� ��, ����� ��
	float gunBarrelLength; // ������ ����
	float gunBarrelAngle; // ���� ȸ�� ��, ����� ��
	D3DXVECTOR2 gunBarrelPoint; // ������ ���� ��ġ�� ��Ÿ�� ����
	D3DXVECTOR3 moveDisp; // Ű �Է����� �̵� ��, �� ƽ�� �̵� �������� ���� ���� 

	D3DXMATRIX matScale; // ũ�� ���
	D3DXMATRIX matRotZ; // ȸ�� ��� (z��)
	D3DXMATRIX matTrans; // �̵� ���

	// ����� ������ ��ȯ��Ģ�� �������� �ʴ´�.
	// ���� ���� (ũ��, ����, �̵�, ����, �θ�)
	D3DXMATRIX matSR; // ũ�� * ȸ�� ����� ���� ���
	D3DXMATRIX matWorld; // ���� ��� (ũ�� * ȸ�� * �̵�)

public:
    // Object��(��) ���� ��ӵ�
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

