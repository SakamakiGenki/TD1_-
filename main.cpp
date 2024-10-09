#include <Novice.h>
#include<math.h>


#include"collision.h"

const char kWindowTitle[] = "GC1B_05_サカマキ_ゲンキ_タイトル";

float collision(float  a, float b) {
	return sqrtf(a * a + b * b);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	struct Vector2 {
		float x;
		float y;
	};

	float screenDown = 530.0f;

	//struct Player宣言
	struct Player {
		Vector2 pos; //playerのPos
		float width; //画像の横幅	
		float heigth; //画像の縦幅
		Vector2 velocity; //player速度
		Vector2 acceleration; //player加速度
	};

	//player構造体
	Player player = {
		player.pos.x = 10.0f,
		player.pos.y = 530.0f,
		player.width = 32.0f,
		player.heigth = 32.0f,
		player.velocity = {0.0f, 0.0f},
		player.acceleration = {2.0f, 2.0f},
	};
	float playerRad = 16.0f;
	//playerの動く速度
	//float playerSpeed = 2.0f;
	//反発係数
	float e = 0.5f; //地面にぶつかったとき跳ねる動作をさせるための変数

	//junpの回数宣言
	int jumpCount = 2;

	//player読み込み
	int playerTexture = Novice::LoadTexture("./Resorces/player.png");

	//backGround読み込み
	int backGroundTexture = Novice::LoadTexture("./Resorces/backGround.png");

	//背景画像ループ処理の座標
	float backGroundPosX = 0.0f;
	float backGroundPosX2 = -1280.0f;

	//score宣言
	//int score = 00000;
	//int displayScore = score;
	//numberArrays宣言
	//int numbersArray[5] = {};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
	
		//player速度
		//player.pos.x += playerSpeed;

		//playerのジャンプ処理
		if (!keys[DIK_W] && preKeys[DIK_W]) {
			if (player.velocity.y < 0.0f) {
				player.velocity.y /= 4;
			}
		}
		if (keys[DIK_W] && !preKeys[DIK_W]) {
			if (jumpCount > 0) {
				player.velocity.y = -15.0f;
				jumpCount--;
			}
		} else { //押されていないとき
			//重力加速度の反射
			player.acceleration.y = 0.8f;

			//速度に加速度を足していく
			player.velocity.y += player.acceleration.y;
		}
		//posyに速度を足していく(ballは下向きに加速する)
		player.pos.y += player.velocity.y;

		//地面にめり込まない処理
		if (player.pos.y >= screenDown - playerRad) {
			player.pos.y = screenDown - playerRad;
			player.velocity.y = player.velocity.y * -e;
			jumpCount = 2;
		}

		//背景地面の動作速度
		backGroundPosX -= 3;

		//背景地面ループの処理
		if (backGroundPosX <= -1280.0f) {
			backGroundPosX = 0.0f;
		}
		backGroundPosX2 = backGroundPosX + 1280.0f;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//backGround描画
		Novice::DrawSprite(static_cast<int>(backGroundPosX), 0, backGroundTexture, 1.0f, 1.0f, 0.0f, WHITE);
		Novice::DrawSprite(static_cast<int>(backGroundPosX2), 0, backGroundTexture, 1.0f, 1.0f, 0.0f, WHITE);

		//player描画
		Novice::DrawSprite(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), playerTexture, 1.0f, 1.0f, 0.0f, WHITE);
		Novice::DrawEllipse(static_cast<int>(player.pos.x + player.width / 2), static_cast<int>(player.pos.y + player.heigth / 2),
			                static_cast<int>(playerRad), static_cast<int>(playerRad), 0.0f, WHITE, kFillModeWireFrame);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
