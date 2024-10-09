#include "stage.h"
#include <stdio.h>

void stage1(int backGroundPosX, int backGroundPosX2) {

	//背景地面の動作速度
	backGroundPosX -= 3;

	//背景地面ループの処理
	if (backGroundPosX <= -1280.0f) {
		backGroundPosX = 0.0f;
	}

	backGroundPosX2 = backGroundPosX + 1280.0f;

}

