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
	} else { //押されていないとき
		//重力加速度の反射
		playerAccelerationY = 0.8f;

		//速度に加速度を足していく
		playerVelocityY += playerAccelerationY;
	}
	//posyに速度を足していく(ballは下向きに加速する)
	playerPosY += playerVelocityY;

	//地面にめり込まない処理
	if (playerPosY >= screenDown - playerRad) {
		playerPosY = screenDown - playerRad;
		playerVelocityY = playerVelocityY * -e;
		jumpCount = 2;
	}

	//背景地面の動作速度
	backGroundPosX -= 3;

	//背景地面ループの処理
	if (backGroundPosX <= -1280.0f) {
		backGroundPosX = 0.0f;
	}
	backGroundPosX2 = backGroundPosX + 1280.0f;

}