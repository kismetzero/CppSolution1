#include "raylib.h"
#include "imgui/imgui.h"
#include "rlImGui/rlImGui.h"

int main()
{
	bool show_imgui = true;
	bool tmp_bool = false;
	int tmp_int = 114514;
	float tmp_float = 3.14f;

	InitWindow(800, 600, "你好！raylib!");
	SetTargetFPS(144);

	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF(
		"C:/Windows/Fonts/msyh.ttc",
		18.0f,
		NULL,
		io.Fonts->GetGlyphRangesChineseFull()
		// io.Fonts->GetGlyphRangesChineseSimplifiedCommon()
	);
	io.Fonts->Build();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);
		if (show_imgui)
		{
			rlImGuiBegin();
				ImGui::Begin("你好！ImGui!");
					ImGui::Text("当前帧率: %.1f FPS", io.Framerate);
					ImGui::Text("tmp_bool=0x%X tmp_int=0x%X tmp_float=0x%X", &tmp_bool, &tmp_int, &tmp_float);
					ImGui::Checkbox("Checkbox", &tmp_bool);
					ImGui::SliderFloat("SliderFloat", &tmp_float, 0.0f, 10.0f);
					ImGui::BeginGroup();
						if (ImGui::Button("+")) { ++tmp_int; }
						ImGui::SameLine();
						if (ImGui::Button("-")) { --tmp_int; }
						ImGui::SameLine();
						ImGui::Text("tmp_int = %d", tmp_int);
					ImGui::EndGroup();
				ImGui::End();
			rlImGuiEnd();
		}
		EndDrawing();

		if (IsKeyPressed(KEY_EQUAL)) { show_imgui = !show_imgui; }
		if (IsKeyPressed(KEY_Q)) { ++tmp_int; }
		if (IsKeyPressed(KEY_W)) { --tmp_int; }
		if (IsKeyPressed(KEY_E)) { tmp_bool = !tmp_bool; }
		if (IsKeyPressed(KEY_A)) { tmp_float += 1.1; }
		if (IsKeyPressed(KEY_S)) { tmp_float -= 1.1; }
	}
	rlImGuiShutdown();
	CloseWindow();
	return 0;
}
