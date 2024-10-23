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

	//タイトル画像
	int titolTexture = Novice::LoadTexture("./Resorces/keyCollect_title.png");
	//ステージ１選択画像
	int selectstage1Texture =Novice::LoadTexture("./Resorces/stageSelect_1.png");
	//ステージ2選択画像
	int selectstage2Texture = Novice::LoadTexture("./Resorces/stageSelect_2.png");

	

	//ステージ１背景
	int stage1backGroundTexture = Novice::LoadTexture("./Resorces/stage1backGround.png");
	//ステージ２背景
	int stage2backGroundTexture = Novice::LoadTexture("./Resorces/stage2backGround.png");
	//ゲームクリア画像
	int gameClearTexture = Novice::LoadTexture("./Resorces/gameClear.png");
	//ゲームオーバー画像
	int gameOverTexture = Novice::LoadTexture("./Resorces/gameOver.png");

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
	
	//ステージ２用
	struct Spike2 {
		Vector2 pos;
		float speed;
		float heightHalf;
		float widhtHalf;
		float  distance;
	};
	//とげ構造体
	Spike spike2[100];
	for (int i = 0; i < 100; i++) {
		spike2[i].pos.x = 500.0f + i * 220.0f;
		spike2[i].pos.y = 514.0f;
		spike2[i].speed = 5.0f;
		spike2[i].heightHalf = 32.0f;
		spike2[i].widhtHalf = 32.0f;
		spike2[i].distance = collision((spike2[i].pos.x - player.pos.x), ((spike2[i].pos.y + spike2[i].heightHalf / 2) - player.pos.y));

	}


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

	//鍵宣言
	struct Key2 {
		Vector2 pos;
		float radius;
		int isAlive;
		float distance;
		float speed;
	};

	//鍵構造体
	Key key2[3];
	for (int i = 0; i < 3; i++) {
		key2[i].pos.x = 600.0f + i * 3600.0f;
		key2[i].pos.y = 510.0f;
		key2[i].radius = 32.0f;
		key2[i].isAlive = true;
		key2[i].distance = collision((key2[i].pos.x - player.pos.x), (key2[i].pos.y - player.pos.y));
		key2[i].speed = 5.0f;
	}

	int getkey = 0;

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

	int stageslect = 1;

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
			getkey = 0;
			for (int i = 0; i < 10; i++) {
				spike[i].pos.x = 500.0f + i * 500.0f;
				spike2[i].speed = 5.0f;
			}

			for (int i = 0; i < 3; i++) {
				key[i].pos.x = 600.0f + i * 1200.0f;
				key[i].isAlive = true;
				key2[i].pos.x = 600.0f + i * 2400.0f;
				key2[i].isAlive = true;
				key2[i].speed = 5.0f;

			}
			for (int i = 0; i < 100; i++) {
				spike2[i].pos.x = 500.0f + i * 220.0f;
			}


			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = SCENE2;
			}
			break;
		case SCENE2:
			//ステージ選択画面

			if (keys[DIK_D] && !preKeys[DIK_D]) {
				if (stageslect == 1) {
					stageslect++;
				}
			}

			if (keys[DIK_A] && !preKeys[DIK_A]) {
				if (stageslect == 2) {
					stageslect--;
				}
			}
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				if (stageslect == 1) {
					scene = SCENE3;
				}
				if (stageslect == 2) {
					scene = SCENE4;
					
				}

			}
			break;
		case SCENE3:
			//ステージ１/////////////////////////////////
		
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

			if (key[i].pos.x <= 0 && key[i].isAlive) {
				key[i].pos.x = 1280.0f + i * 600.0f;
			}

			if (key[i].isAlive == false && key[i].pos.x == 0) {
					getkey = getkey + 1;
			}
		}

		
		if (getkey >= 3) {
			scene = SCENE5;
			//ゲームクリア
		}

		if (spike[9].pos.x <= -100.0f && getkey != 3) {
			//ゲームオーバー
			scene = SCENE6;
		}



		//背景地面の動作速度
		backGroundPosX -= 3;

		//背景地面ループの処理
		if (backGroundPosX <= -1280.0f) {
			backGroundPosX = 0.0f;
		}
		backGroundPosX2 = backGroundPosX + 1280.0f;
		break;

		case SCENE4:
			//ステージ２///////////////////
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
			for (int i = 0; i < 100; i++) {
				spike2[i].pos.x -= spike2[i].speed;

				spike2[i].distance = collision((spike2[i].pos.x - player.pos.x), 
					((spike2[i].pos.y + spike2[i].heightHalf / 2) - player.pos.y));
				if (spike2[i].distance <= spike2[i].heightHalf / 2 + 32.0f) {
					player.isAlive = false;
				}
				//鍵を一個取ったら棘が加速(蛇足だったら消す)//
			    if (getkey >= 1) {
					spike2[i].speed = 7.0f;
				}

				if (getkey >= 2) {
					spike2[i].speed = 8.5f;
				}

			}

			if (player.isAlive == false) {
				scene = SCENE6;
			}

			//鍵の処理
			for (int i = 0; i < 3; i++) {
				key2[i].pos.x -= key2[i].speed;
				key2[i].distance = collision((key2[i].pos.x - player.pos.x), (key2[i].pos.y - player.pos.y));
				if (key2[i].distance <= key2[i].radius + 32.0f) {
					key2[i].isAlive = false;
				}

				if (key2[i].pos.x <= 0 && key2[i].isAlive) {
					key2[i].pos.x = 1280.0f + i * 1200.0f;
				}

				if (key2[i].isAlive == false && key2[i].pos.x == 0) {
					getkey = getkey + 1;
				}

			}

			/*if (getkey >= 1) {
				key2[1].speed = 7.0f;
			}

			if (getkey >= 2) {
				key2[2].speed = 7.5f;
			}*/

			if (getkey >= 3) {
				scene = SCENE5;
				//ゲームクリア
			}

			if (spike[9].pos.x <= -100.0f && getkey != 3) {
				//ゲームオーバー
				scene = SCENE6;
			}


			//背景地面の動作速度
			backGroundPosX -= 4;

			//背景地面ループの処理
			if (backGroundPosX <= -1280.0f) {
				backGroundPosX = 0.0f;
			}
			backGroundPosX2 = backGroundPosX + 1280.0f;

			break;
		
		case SCENE5:
			//ゲームクリア
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				player.isAlive = true;
				scene = SCENE1;

			}
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
			Novice::DrawSprite(0, 0, titolTexture, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case SCENE2:
			//ステージ選択画面
			if (stageslect == 1) {
				Novice::DrawSprite(0, 0, selectstage1Texture, 1.0f, 1.0f, 0.0f, WHITE);
			}
			if (stageslect == 2) {
				Novice::DrawSprite(0, 0, selectstage2Texture, 1.0f, 1.0f, 0.0f, WHITE);
			}

			/*Novice::ScreenPrintf(100, 100, "%d", stageslect);
			Novice::DrawBox(0, 0, 64, 64, 0.0f, WHITE, kFillModeSolid);*/
			break;
		case SCENE3:
			//ステージ1
			//backGround描画
			Novice::DrawSprite(static_cast<int>(backGroundPosX), 0, stage1backGroundTexture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(static_cast<int>(backGroundPosX2), 0, stage1backGroundTexture, 1.0f, 1.0f, 0.0f, WHITE);

			//とげ描画
			for (int i = 0; i < 10; i++) {
				Novice::DrawSprite(static_cast<int>(spike[i].pos.x - spike[i].widhtHalf),
					static_cast<int>(spike[i].pos.y - spike[i].heightHalf), spikeTexture, 1.0f, 1.0f, 0.0f, WHITE);
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
			/*Novice::DrawEllipse(static_cast<int>(player.pos.x + player.width / 2), static_cast<int>(player.pos.y + player.heigth / 2),
				static_cast<int>(playerRad), static_cast<int>(playerRad), 0.0f, WHITE, kFillModeWireFrame);*/

			break;

		case SCENE4:
			//ステージ２
			
			//背景
			Novice::DrawSprite(static_cast<int>(backGroundPosX), 0, stage2backGroundTexture, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(static_cast<int>(backGroundPosX2), 0, stage2backGroundTexture, 1.0f, 1.0f, 0.0f, WHITE);

			// //とげ描画
			for (int i = 0; i < 100; i++) {
				Novice::DrawSprite(static_cast<int>(spike2[i].pos.x - spike2[i].widhtHalf),
					static_cast<int>(spike2[i].pos.y - spike2[i].heightHalf), spikeTexture, 1.0f, 1.0f, 0.0f, WHITE);
			};

			//鍵描写
			for (int i = 0; i < 3; i++) {
				if (key2[i].isAlive) {
					Novice::DrawSprite(static_cast<int>(key2[i].pos.x - key2[i].radius),
						static_cast<int>(key2[i].pos.y - key2[i].radius), keyTexture, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}

			//デバッグ　
			//Novice::ScreenPrintf(0, 0, "%d", getkey);

			//player描画
			Novice::DrawSprite(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), playerTexture, 1.0f, 1.0f, 0.0f, WHITE);
			/*Novice::DrawEllipse(static_cast<int>(player.pos.x + player.width / 2), static_cast<int>(player.pos.y + player.heigth / 2),
				static_cast<int>(playerRad), static_cast<int>(playerRad), 0.0f, WHITE, kFillModeWireFrame);*/
			break;
		
		case SCENE5:
			//ゲームクリア
			Novice::DrawSprite(0, 0, gameClearTexture, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case SCENE6:
			//ゲームオーバー
			Novice::DrawSprite(0, 0, gameOverTexture, 1.0f, 1.0f, 0.0f, WHITE);
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
