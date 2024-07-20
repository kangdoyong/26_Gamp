#include "Player.h"

// ������ ����������
//  -> �׷����� ����ϱ������ ����
// �������� �κ��� �׷��Ƚ� ���̺귯������, �׸��� ������ �׷��Ƚ� ���̺귯����
// �������� �������� �κ��� �ణ�� �ٸ�����, �ٽ����� ������ ��� ������

// ��(����) �����̽� -> ���� �����̽� 

// 3d ��(��ü)���� ���� �ڱ� �ڽŸ��� ��ǥü�踦 ������ ����
// �� ��ü���� ���� ���� ��(�ϳ��� ����)�� �ø��� �Ǹ�
// ���� ��ǥ�� �������� �� ��ǥ ü���� ��ȯ�� �߻� ��

// �� ��, ���� ����� ����� ���� ��ȯ
// ���� ��ȯ�� �ϴ� ����?
// ����� �̿��� ���� ��ȯ�� ����, ���� ���� �� ��ȯ�� ������ ��������
// -> �����δ� ���� ��ȯ

// ũ�� (���� ��ȯ), ȸ�� (���� ��ȯ), ��ġ (���� ��ȯ ��, ������ ����)
// -> ��ġ ��ȯ���� ���� ��ȯ�� ������ �����鼭, ��� �ϳ��� ũ��/ȸ��/��ġ�� ��Ÿ�� �� ���� ��

// ��� ��� ��, ���� ���� Ȯ���ؾ��� ��
// ���� �̿��ϴ� ���� or �׷��Ƚ� ���̺귯������
// ��켱 or ���켱 ��� �� � ����� �̿��ϴ���?
// -> directX ���� ��켱, unity ���� ���켱

// ��켱 ����
// 1��° ��, ��ü�� ���� X�� (����)
// 2��° ��, ��ü�� ���� Y�� (����)
// 3��° ��, ��ü�� ���� Z�� (����)
// 4��° ��, ��ü�� ��ġ (����Ʈ)
// 4��° ��, ���Ϳ� ���� �����Ѵ�. (������ǥ��)
//  


void Player::Initialize()
{
	speed = 3.f;
	info.pos = D3DXVECTOR3(WIN_SIZE_X / 2.f, WIN_SIZE_Y / 2.f, 0);
	info.dir = D3DXVECTOR3(0, 0, 0);
	info.look = D3DXVECTOR3(1.f, 0, 0);
	info.size = D3DXVECTOR3(50.f, 50.f, 0);
	moveDisp = D3DXVECTOR3(0, 0, 0);

	bodyAngle = 0;
	gunBarrelAngle = 0;
	gunBarrelLength = 100.f;

	// ��, ��
	originPoint[0].x = info.pos.x - info.size.x;
	originPoint[0].y = info.pos.y - info.size.y;
	// ��, ��
	originPoint[1].x = info.pos.x + info.size.x;
	originPoint[1].y = info.pos.y - info.size.y;
	// �Ʒ�, ��
	originPoint[2].x = info.pos.x + info.size.x;
	originPoint[2].y = info.pos.y + info.size.y;
	// �Ʒ�, ��
	originPoint[3].x = info.pos.x - info.size.x;
	originPoint[3].y = info.pos.y + info.size.y;
}

void Player::Update()
{
	// ��ũ ��ü ȸ�� A, DŰ
	if (GetAsyncKeyState('A'))
	{
		bodyAngle -= D3DXToRadian(5.f);
	}

	if (GetAsyncKeyState('D'))
	{
		bodyAngle += D3DXToRadian(5.f);
	}

	// ��ü ȸ�� ���� ���� �ش� ������ ���� WŰ
	if (GetAsyncKeyState('W'))
	{
		D3DXVECTOR3 forwordDir;
		forwordDir.x = info.look.x * cosf(bodyAngle) - info.look.y * sinf(bodyAngle);
		forwordDir.y = info.look.x * sinf(bodyAngle) + info.look.y * cosf(bodyAngle);
		forwordDir.z = 0;


		info.pos += forwordDir * speed;
	}

	// ũ�� ���
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 1.f);

	// ȸ�� ���
	D3DXMatrixRotationZ(&matRotZ, bodyAngle);

	// ũ�� * ȸ�� ����� ����� ����
	matSR = matScale * matRotZ;

	// �̵� ���
	D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y, info.pos.z);

	// ũ�� * ȸ�� * �̵� ���� (���� ���)
	matWorld = matScale * matRotZ * matTrans;

	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);

	// ���� Ÿ�Գ��� ������ ���� ����Ʈ ��ǥ�� ���ͷ� ��ȯ
	D3DXVECTOR3 mousePos(mouse.x, mouse.y, 0);

	// �÷��̾ ���콺���� �ٶ󺸰� �Ϸ��� ��
	
	// �÷��̾�� ���콺 ������ ���ϴ� ���͸� ����
	info.dir = mousePos - info.pos;
	// ���⺤�ͷ� ����� ����, ������ ũ�⸦ 1�� ������ ��
	//  -> ������ ũ�⸦ ���ؼ�, ������ �� ���Ҹ� ũ��� ������.

	// ������ ũ�⸦ ���Ѵ�. 
	/*float length = sqrt(info.dir.x * info.dir.x + info.dir.y * info.dir.y);
	if (length < 3.f)
	{
		return;
	}
	info.dir.x /= length;
	info.dir.y /= length;*/

	// ���͸� ��������ȭ �Ѵ�.
	D3DXVec3Normalize(&info.dir, &info.dir);

	// ������ �� ���г��� ���ϰ�, ���ϴ� �۾�
	// -> ������ ����
	// D3DXVec3Dot
	// angle = acosf(info.dir.x * info.look.x + info.dir.y * info.look.y);
	// ������ ������ ���⺤�� ������ ����

	// look ���ʹ� ���� ����(���� 2d x��)������ ���� ���� ũ�Ⱑ 1�� ����
	// �ش� ������ ���а� ĳ���Ͱ� �ٶ󺸴� ���� ���г��� ���� ��,
	// ����� ������ ��, ��������� x�� ���� ���� ���� ��
	// �� ��, dir�� ũ�Ⱑ 1�� ���� �����̹Ƿ�, ���� ���� �����Ѵٰ� �� �� ����
	// ���� ���� �����Ѵٸ�, x�� ���� cos ��Ÿ�� �ǹ���
	// cos ��Ÿ�� �غ�/�����̰�, �ش� ���� ���Լ��� ���� ��, ���������
	// ���ϴ� ��Ÿ ���� ���� �� ����
	gunBarrelAngle = acosf(D3DXVec3Dot(&info.dir, &info.look));

	// ���Լ��� 180������ �ۿ� ǥ���� ���ϹǷ�, ���� ó��
	if (mouse.y > info.pos.y)
	{
		gunBarrelAngle = 2 * D3DX_PI - gunBarrelAngle;
	}

	// ���� ���� ����
	gunBarrelPoint = D3DXVECTOR2(cosf(gunBarrelAngle) * gunBarrelLength + info.pos.x,
		-sinf(gunBarrelAngle) * gunBarrelLength + info.pos.y);

	// ��, ��
	originPoint[0].x = info.pos.x - info.size.x;
	originPoint[0].y = info.pos.y - info.size.y;
	// ��, ��
	originPoint[1].x = info.pos.x + info.size.x;
	originPoint[1].y = info.pos.y - info.size.y;
	// �Ʒ�, ��
	originPoint[2].x = info.pos.x + info.size.x;
	originPoint[2].y = info.pos.y + info.size.y;
	// �Ʒ�, ��
	originPoint[3].x = info.pos.x - info.size.x;
	originPoint[3].y = info.pos.y + info.size.y;

	// �÷��̾ ��Ÿ�� 4���� ���� ����
	POINT temp;
	for (int i = 0; i < 4; ++i)
	{
		// ���� ���� ��������
		calPoint[i] = originPoint[i];

		// ������ �÷��̾��� ��ġ�� ����
		// -> ũ�⿡ ���� ���� ���� ��
		//    ũ�⸸ ���Ҵٴ� ����, �÷��̾ ���� �� �����ϴ� �Ͱ� ������
		// -> �÷��̾��� ���� ��ǥ�� ǥ��
		calPoint[i].x -= info.pos.x;
		calPoint[i].y -= info.pos.y;

		// ��ȯ�Ǳ� ���� ���� ��ǥ�� ���� ������ ���� ����ϱ� ���� ���
		// -> ���� ��������� ����Ǳ� ���� ���� Ȯ���� ����
		calPointBack[i] = calPoint[i];

		// ���� ��ġ�� ���� ����� ���� ����� ����
		// ����Ʈ * ��� ����
		D3DXVec3TransformCoord(&calPoint[i], &calPoint[i], &matWorld);

		// �� ��ġ�� ���ְ�, ũ�⸸ �������?
		// -> ��ȯ�� ������ ����, ��ǥ������ ȸ�� �� ��ü�� ��ġ���� ����� 
		//    ���ڸ� ȸ���� ǥ���Ϸ��� ��ġ�� ����� �� 
		// �ﰢ�Լ��� ���� ����
		// x�� ȸ���� ��ǥ = cosf * cosf - sinf * sinf;
		// y�� ȸ���� ��ǥ = cosf * sinf + sinf * cosf;
		//temp = calPoint[i];
		// -> ������ �İ� ������ ����
		//calPoint[i].x = temp.x * cosf(bodyAngle) + (-temp.y * sinf(bodyAngle));
		//calPoint[i].y = temp.x * sinf(bodyAngle) + (temp.y * cosf(bodyAngle));

		// ���� ȸ���� �������Ƿ�, �ٽ� �÷��̾��� ��ġ�� ���� ���������� ȸ���� ��ġ�� ��Ÿ��
		// -> ���� ��ǥ�� ���� ��ǥ�� �ٲ�
		// calPoint[i].x += info.pos.x + moveDisp.x;
		// calPoint[i].y += info.pos.y + moveDisp.y;
	}
}

void Player::Render(HDC hdc)
{
	DisplayText(hdc);

	// �÷��̾� �׸���
	MoveToEx(hdc, calPoint[0].x, calPoint[0].y, NULL);
	LineTo(hdc, calPoint[1].x, calPoint[1].y);
	LineTo(hdc, calPoint[2].x, calPoint[2].y);
	LineTo(hdc, calPoint[3].x, calPoint[3].y);
	LineTo(hdc, calPoint[0].x, calPoint[0].y);

	// ���� �׸���
	MoveToEx(hdc, info.pos.x, info.pos.y , NULL);
	LineTo(hdc, gunBarrelPoint.x, gunBarrelPoint.y);
}

void Player::Release()
{
}

void Player::DisplayText(HDC hdc)
{
	// ���콺 ��ǥ
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);
	DisplayVector(hdc, L"���콺", D3DXVECTOR2(mouse.x, mouse.y), D3DXVECTOR2(10, 10));

	// ���� ���� (�÷��̾ ���콺���� �ٶ󺸴� ����)
	DisplayVector(hdc, L"���� ����", D3DXVECTOR2(info.dir.x, info.dir.y), D3DXVECTOR2(10, 30));

	// ���Ű� (����, ��׸�)
	DisplayVector(hdc, L"���Ű� (r, d)", D3DXVECTOR2(gunBarrelAngle, D3DXToDegree(gunBarrelAngle)), D3DXVECTOR2(10, 50));

	// ��ü�� (����, ��׸�)
	DisplayVector(hdc, L"��ü�� (r, d)", D3DXVECTOR2(bodyAngle, D3DXToDegree(bodyAngle)), D3DXVECTOR2(10, 70));

	// ���� ���� ��ġ
	DisplayVector(hdc, L"���� ����", D3DXVECTOR2(gunBarrelPoint.x, gunBarrelPoint.y), D3DXVECTOR2(10, 90));

	// ���� ��� ���� ��, 4�� ��ġ
	for (int i = 0; i < 4; ++i)
	{
		wchar_t str[32];
		swprintf_s(str, L"���� ��� ���� ��, %d", i);
		DisplayVector(hdc, str, D3DXVECTOR2(calPointBack[i].x, calPointBack[i].y),
			D3DXVECTOR2(10, 120 + i * 20));
	}

	// ���� ��� ���� ��, 4�� ��ġ
	for (int i = 0; i < 4; ++i)
	{
		wchar_t str[32];
		swprintf_s(str, L"���� ��� ���� ��, %d", i);
		DisplayVector(hdc, str, D3DXVECTOR2(calPoint[i].x, calPoint[i].y),
			D3DXVECTOR2(10, 220 + i * 20));
	}

	// ��� ���� ���
	DisplayMat(hdc, L"����", matWorld, D3DXVECTOR2(WIN_SIZE_X - 300, 30));
	DisplayMat(hdc, L"ũ��", matScale, D3DXVECTOR2(WIN_SIZE_X - 300, 150));
	DisplayMat(hdc, L"ȸ��(z)", matRotZ, D3DXVECTOR2(WIN_SIZE_X - 300, 300));
	DisplayMat(hdc, L"�̵�", matTrans, D3DXVECTOR2(WIN_SIZE_X - 300, 450));
	DisplayMat(hdc, L"ũ�� * ȸ��", matSR, D3DXVECTOR2(WIN_SIZE_X - 600, 450));

}

void Player::DisplayVector(HDC hdc, const wchar_t* text, D3DXVECTOR2 value, D3DXVECTOR2 displayPt)
{
	wchar_t temp[128];
	swprintf_s(temp, L"%s : %.2f, %.2f", text, value.x, value.y);
	TextOut(hdc, displayPt.x, displayPt.y, temp, wcslen(temp));
}

void Player::DisplayMat(HDC hdc, const wchar_t* text, D3DXMATRIX& value, D3DXVECTOR2 displayPt)
{
	wchar_t temp[128];
	swprintf_s(temp, L"%s", text);
	TextOut(hdc, displayPt.x, displayPt.y - 20, temp, wcslen(temp));

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			swprintf_s(temp, L"%.2f", value.m[i][j]);
			TextOut(hdc, displayPt.x + 60 * j, displayPt.y + 20 * i, temp, wcslen(temp));
		}
	}
}

Player::Player()
{
}

Player::~Player()
{
}
