#include <Novice.h>
#include<math.h>


#include"collision.h"

const char kWindowTitle[] = "GC1B_05_サカマキ_ゲンキ_タイトル";



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
		int isAlive;
	};

	//player構造体
	Player player = {
		player.pos.x = 10.0f,
		player.pos.y = 530.0f,
		player.width = 32.0f,
		player.heigth = 32.0f,
		player.velocity = {0.0f, 0.0f},
		player.acceleration = {2.0f, 2.0f},
		player.isAlive = true 
	};
	float playerRad = 16.0f;
	//playerの動く速度
	//float playerSpeed = 2.0f;
	// 
	//反発係数
	float e = 0.5f; //地面にぶつかったとき跳ねる動作をさせるための変数

	//junpの回数宣言
	int jumpCount = 2;

	//player読み込み
	int playerTexture = Novice::LoadTexture("./Resorces/player.png");

	//backGround読み込み
	//int backGroundTexture = Novice::LoadTexture("./Resorces/backGround.png");

	//背景画像ループ処理の座標
	float backGroundPosX = 0.0f;
	float backGroundPosX2 = -1280.0f;

	//ステージ１背景
	int stage1backGroundTexture = Novice::LoadTexture("./Resorces/stage1backGround.png");

#pragma region spike

	//とげ宣言
	struct Spike {
		Vector2 pos;
		float speed;
		float heightHalf;
		float widhtHalf;
		float  distance;
	};
	
	

	//とげ構造体
	Spike spike[10];
	for (int i = 0; i < 10; i++) {
		spike[i].pos.x = 500.0f + i * 500.0f;
		spike[i].pos.y = 514.0f;
		spike[i].speed = 5.0f;
		spike[i].heightHalf = 32.0f;
		spike[i].widhtHalf = 32.0f;
		spike[i].distance = collision((spike[i].pos.x - player.pos.x), ((spike[i].pos.y+spike[i].heightHalf/2) - player.pos.y));
		
	}
	//とげ読み込み
	int spikeTexture = Novice::LoadTexture("./Resorces/spike.png");
	//
	


#pragma endregion


#pragma region key

	//鍵宣言
	struct Key {
		Vector2 pos;
		float radius;
		int isAlive;
		float distance;
		float speed;
	};

	//鍵構造体
	Key key[3];
	for (int i = 0; i < 3; i++) {
		key[i].pos.x = 600.0f + i * 1200.0f;
		key[i].pos.y = 300.0f;
		key[i].radius = 32.0f;
		key[i].isAlive = true ;
		key[i].distance = collision((key[i].pos.x - player.pos.x), (key[i].pos.y - player.pos.y));
		key[i].speed = 5.0f;
	}

	//鍵読み込み
	int keyTexture = Novice::LoadTexture("./Resorces/key.png");

#pragma endregion

	//シーン切り替え
	enum SCENE {
		SCENE1, //title
		SCENE2, //stage1
		SCENE3, //stage2
		SCENE4, //stage3
		SCENE5, //gameclear
		SCENE6, //gameover
	
	};
	int scene = SCENE1;

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

		//プレイヤーと棘の当たり判定

		switch (scene){
		case SCENE1:
			//タイトル
			player.pos.y = 530.0f;
			for (int i = 0; i < 10; i++) {
				spike[i].pos.x = 500.0f + i * 500.0f;
				
			}

			for (int i = 0; i < 3; i++) {
				key[i].pos.x = 600.0f + i * 1200.0f;
				key[i].isAlive = true;
			}


			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = SCENE2;
			}
			break;
		case SCENE2:
			//ステージ１
		
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

		//とげの移動
		for (int i = 0; i < 10; i++) {
			spike[i].pos.x -= spike[i].speed;

			spike[i].distance = collision((spike[i].pos.x - player.pos.x), ((spike[i].pos.y + spike[i].heightHalf / 2) - player.pos.y));
			if (spike[i].distance <= spike[i].heightHalf / 2 + 32.0f) {
				player.isAlive = false;	
			}
		}

		if (player.isAlive == false) {
			scene = SCENE6;
		}



		//鍵の処理
		for (int i = 0; i < 3; i++) {
			key[i].pos.x -= key[i].speed;
			key[i].distance = collision((key[i].pos.x - player.pos.x), (key[i].pos.y - player.pos.y));
			if (key[i].distance <= key[i].radius + 32.0f) {
				key[i].isAlive = false;
			}
		}



		//背景地面の動作速度
		backGroundPosX -= 3;

		//背景地面ループの処理
		if (backGroundPosX <= -1280.0f) {
			backGroundPosX = 0.0f;
		}
		backGroundPosX2 = backGroundPosX + 1280.0f;
		break;

		case SCENE3:
			//ステージ２
			break;
		case SCENE4:
			//ステージ３
			break;
		case SCENE5:
			//ゲームクリア
			break;
		case SCENE6:
			//ゲームオーバー
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				player.isAlive = true;
				scene = SCENE1;
				
			}
			break;
		default:
			break;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		switch (scene){
		case SCENE1:
			//タイトル
			break;
		case SCENE2:
			//ステージ1
			//backGround描画
			Novice::DrawSprite(static_cast<int>(backGroundPosX), 0, stage1backGroundTexture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(static_cast<int>(backGroundPosX2), 0, stage1backGroundTexture, 1.0f, 1.0f, 0.0f, WHITE);

			//とげ描画
			for (int i = 0; i < 10; i++) {
				Novice::DrawSprite(static_cast<int>(spike[i].pos.x - spike[i].widhtHalf),
					static_cast<int>(spike[i].pos.y - spike[i].heightHalf), spikeTexture, 1.0f, 1.0f, 0.0f, WHITE);
				//棘の当たり判定部分
				//Novice::DrawTriangle(int(spike[i].pos.x ), int(spike[i].pos.y- spike[i].heightHalf),//上
				//	int(spike[i].pos.x-spike[i].widhtHalf), int(spike[i].pos.y + spike[i].heightHalf),//左下
				//	int(spike[i].pos.x + spike[i].widhtHalf), int(spike[i].pos.y + spike[i].heightHalf)//右下
				//	, WHITE, kFillModeWireFrame);

			};

			//鍵描写
			for (int i = 0; i < 3; i++) {
				if (key[i].isAlive) {
					Novice::DrawSprite(static_cast<int>(key[i].pos.x - key[i].radius),
						static_cast<int>(key[i].pos.y - key[i].radius), keyTexture, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}

			//player描画
			Novice::DrawSprite(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), playerTexture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawEllipse(static_cast<int>(player.pos.x + player.width / 2), static_cast<int>(player.pos.y + player.heigth / 2),
				static_cast<int>(playerRad), static_cast<int>(playerRad), 0.0f, WHITE, kFillModeWireFrame);
			break;

		case SCENE3:
			//ステージ２
			break;
		case SCENE4:
			//ステージ３
			break;
		case SCENE5:
			//ゲームクリア
			break;
		case SCENE6:
			//ゲームオーバー
			Novice::DrawBox(0, 0, 64, 64, 0.0f, RED, kFillModeSolid);
			break;
		default:
			break;
		
		}
		

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
