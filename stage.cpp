#include "stage.h"
#include <stdio.h>

void stage1(int backGroundPosX, int backGroundPosX2) {

	//�w�i�n�ʂ̓��쑬�x
	backGroundPosX -= 3;

	//�w�i�n�ʃ��[�v�̏���
	if (backGroundPosX <= -1280.0f) {
		backGroundPosX = 0.0f;
	}

	backGroundPosX2 = backGroundPosX + 1280.0f;

}

