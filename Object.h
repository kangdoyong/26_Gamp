#pragma once
#include "Define.h"

// 모든 게임 객체의 베이스가 될 추상 클래스
class Object abstract
{
protected:
	// 게임 객체들이 공통적으로 갖는 데이터를 선언
	INFO info;

public:
	virtual void Initialize() abstract; // 모든 객체는 생성 후, 초기화 과정을 갖는다
	virtual void Update() abstract; // 모든 객체는 특정 연산을 한다.
	virtual void Render(HDC hdc) abstract; // 모든 객체는 화면에 그려질 수 있다.
	virtual void Release() abstract; // 모든 객체는 파괴될 때, 동적메모리를 사용 중이라면 해제한다.

public:
	Object();
	// 클래스 상속관계에서 다형성을 이용 시, 소멸자를 가상 소멸자로 만들지 않는다면
	// 정상적으로 소멸자가 호출되지 않음
	virtual ~Object(); 
};

