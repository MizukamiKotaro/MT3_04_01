#include <Novice.h>
#include"MyMatrix4x4.h"
#include"MatrixScreenPrintf.h"
#include"MyVector3.h"
#include"VectorScreenPrintf.h"
#include"calc.h"
#include"Grid.h"
#include"Sphere.h"
#include<imgui.h>
#include"Line.h"
#include"Collision.h"
#include"Camera.h"
#include"Plane.h"
#include"Triangle.h"
#include"AABB.h"
#include"OBB.h"
#include"Draw.h"
#include"Spring.h"
#include"Ball.h"
#include"Behavior.h"

const char kWindowTitle[] = "学籍番号";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Ball ball{};
	ball.position = { 0.8f,0.0f,0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = 0xFFFFFFFF;

	float angularVelocity = 3.14f;
	float angle = 0.0f;
	float radius = 0.8f;

	bool start = false;

	Camera camera{};
	camera.Initialize({ 0.0f,1.9f,-6.49f }, { 0.26f,0.0f,0.0f });

	MyMatrix4x4 projectionMatrix = MyMatrix4x4::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	MyMatrix4x4 viewportMatrix = MyMatrix4x4::MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	
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
		
		ImGui::Begin("Window");
		ImGui::Text("SPACE : Start");
		if (ImGui::Button("Start")) {
			start = true;
		}
		ImGui::Text("R : Reset");
		if (ImGui::Button("Reset")) {
			angle = 0.0f;


			ball.position = { 0.8f,0.0f,0.0f };

			start = false;

			camera.Initialize({ 0.0f,1.9f,-6.49f }, { 0.26f,0.0f,0.0f });
		}
		ImGui::End();

		if (keys[DIK_SPACE] && !start) {
			start = true;
		}

		if (start) {
			BehaviorCircleMovement(&ball.position, angularVelocity, &angle, radius, {});
		}

		if (keys[DIK_R]) {
			
			angle = 0.0f;
			

			ball.position = { 0.8f,0.0f,0.0f };

			start = false;

			camera.Initialize({ 0.0f,1.9f,-6.49f }, { 0.26f,0.0f,0.0f });
		}

		camera.Update(keys, preKeys);

		MyMatrix4x4 cameraMatrix = MyMatrix4x4::MakeAffinMatrix(camera.GetScale(), camera.GetRotate(), camera.GetTranslate());
		MyMatrix4x4 viewMatrix = MyMatrix4x4::Inverse(cameraMatrix);
		MyMatrix4x4 viewProjectionMatrix = MyMatrix4x4::Multiply(viewMatrix, projectionMatrix);

	

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Grid::DrawGrid(viewProjectionMatrix, viewportMatrix);

		ball.Draw(viewProjectionMatrix, viewportMatrix);
	
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
