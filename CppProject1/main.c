#include "raylib.h"

int main() {
	InitWindow(800, 600, "Hello raylib!");
	while (!WindowShouldClose()) {
		BeginDrawing();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}