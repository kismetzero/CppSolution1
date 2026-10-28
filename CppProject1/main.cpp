#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "MyHook.h"

extern bool mh_flag_init;
extern bool mh_flag_hook_create;
extern bool mh_flag_hook_en;

extern void CreateTrayIcon(void* hwnd);

int main(int argc, char *argv[])
{
	bool show_imgui = true;
	bool tmp_bool = false;
	int tmp_int = 114514;
	float tmp_float = 3.14f;

	InitWindow(800, 600, "你好！raylib!");
	SetTargetFPS(144);

	// CreateTrayIcon(GetWindowHandle());

	// rlImGuiSetup(true);
	rlImGuiBeginInitImGui();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;

	/*ImFontConfig hack_cfg;
	hack_cfg.SizePixels = 18.0f;
	hack_cfg.OversampleH = 2;
	hack_cfg.OversampleV = 1;
	io.Fonts->AddFontFromFileTTF(
		"assest/fonts/HackNerdFontMono-Regular.ttf",
		18.0f,
		&hack_cfg,
		io.Fonts->GetGlyphRangesDefault()
	);*/

	ImFontConfig msyh_cfg;
	msyh_cfg.MergeMode = true;
	msyh_cfg.SizePixels = 18.0f;
	msyh_cfg.OversampleH = 2;
	msyh_cfg.OversampleV = 2;
	msyh_cfg.FontNo = 0;
	io.Fonts->AddFontFromFileTTF(
		"assest/fonts/msyh.ttc",
		18.0f,
		&msyh_cfg,
		// io.Fonts->GetGlyphRangesChineseFull()
		io.Fonts->GetGlyphRangesChineseSimplifiedCommon()
	);

	rlImGuiEndInitImGui();

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
					ImGui::SameLine(0.0f, 5.0f);
					if (ImGui::Button("+")) { ++tmp_int; }
					ImGui::SameLine(0.0f, 5.0f);
					if (ImGui::Button("-")) { --tmp_int; }
					ImGui::SameLine(0.0f, 5.0f);
					ImGui::Text("tmp_int = %d", tmp_int);

					ImGui::SliderFloat("SliderFloat", &tmp_float, 0.0f, 10.0f);
					
					ImGui::Checkbox("初始化MH", &mh_flag_init);
					ImGui::SameLine(0.0f, 5.0f);
					ImGui::Checkbox("创建MH_HOOK", &mh_flag_hook_create);
					ImGui::SameLine(0.0f, 5.0f);
					ImGui::Checkbox("开启MH_HOOK", &mh_flag_hook_en);

					if (ImGui::Button("开启MH")) { mh_init(); }
					ImGui::SameLine(0.0f, 5.0f);
					if (ImGui::Button("创建MH_Hook")) { mh_hook_create(); }
					ImGui::SameLine(0.0f, 5.0f);
					if (ImGui::Button("开启MH_Hook")) { mh_hook_on(); }

					if (ImGui::Button("关闭MH")) { mh_uninit(); }
					ImGui::SameLine(0.0f, 5.0f);
					if (ImGui::Button("移除MH_Hook")) { mh_hook_remove(); }
					ImGui::SameLine(0.0f, 5.0f);
					if (ImGui::Button("关闭MH_Hook")) { mh_hook_off(); }

					if (ImGui::Button("弹窗")) { MBoxA(); }
				ImGui::End();
			rlImGuiEnd();
		}
		EndDrawing();

		if (IsKeyPressed(KEY_EQUAL)) { show_imgui = !show_imgui; }
		if (IsKeyPressed(KEY_Q)) { ++tmp_int; }
		if (IsKeyPressed(KEY_W)) { --tmp_int; }
		if (IsKeyPressed(KEY_E)) { tmp_bool = !tmp_bool; }
		if (IsKeyPressed(KEY_A)) { tmp_float += 1.1f; }
		if (IsKeyPressed(KEY_S)) { tmp_float -= 1.1f; }
	}
	rlImGuiShutdown();
	CloseWindow();
	return 0;
}
