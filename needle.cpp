#include "needle.h"
#include <Novice.h>

int needleTexture = Novice::LoadTexture("./Resources/spike.png");

void needle(float x,float y) {
	
	Novice::DrawSprite(x, y, needleTexture, 1.0f, 1.0f, 0.0f, WHITE);

}

void needleCollision() {





}