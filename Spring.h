#pragma once
#include "MyVector3.h"

struct Spring {
	//アンカー。固定された端の位置
	MyVector3 anchor;
	float naturalLength; // 自然長
	float stiffness; // 剛性。ばねの定数k
	float dampingCoefficient; // 減衰係数
};
