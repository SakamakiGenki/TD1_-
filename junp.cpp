#include "junp.h"
#include <Novice.h>

char keys[256] = { 0 };
char preKeys[256] = { 0 };

void janp(float playerVelocityY,float jumpCount,float playerAccelerationY,float playerPosY,float screenDown,float playerRad,
          float backGroundPosX,float backGroundPosX2,float e) {

	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	if (!keys[DIK_W] && preKeys[DIK_W]) {
		if (playerVelocityY < 0.0f) {
			playerVelocityY /= 4;
		}
	}
	if (keys[DIK_W] && !preKeys[DIK_W]) {
		if (jumpCount > 0) {
			playerVelocityY = -15.0f;
			jumpCount--;
		}
	} else { //������Ă��Ȃ��Ƃ�
		//�d�͉����x�̔���
		playerAccelerationY = 0.8f;

		//���x�ɉ����x�𑫂��Ă���
		playerVelocityY += playerAccelerationY;
	}
	//posy�ɑ��x�𑫂��Ă���(ball�͉������ɉ�������)
	playerPosY += playerVelocityY;

	//�n�ʂɂ߂荞�܂Ȃ�����
	if (playerPosY >= screenDown - playerRad) {
		playerPosY = screenDown - playerRad;
		playerVelocityY = playerVelocityY * -e;
		jumpCount = 2;
	}

	//�w�i�n�ʂ̓��쑬�x
	backGroundPosX -= 3;

	//�w�i�n�ʃ��[�v�̏���
	if (backGroundPosX <= -1280.0f) {
		backGroundPosX = 0.0f;
	}
	backGroundPosX2 = backGroundPosX + 1280.0f;

}