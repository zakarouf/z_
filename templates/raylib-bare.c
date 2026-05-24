#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#define Z__IMPLEMENTATION
#include <z_/std/primitives.h>

typedef struct Display Display;
struct Display {
    z__u32 screenWidth;
    z__u32 screenHeight;
};

typedef struct App App;
struct App {
    Display display;
    int exit;
};

static void _update(App *app)
{   BeginDrawing();
        ClearBackground(WHITE);
        if(WindowShouldClose()) app->exit = true;
    EndDrawing();
}

static void _init(App const *app) {
    InitWindow(app->display.screenWidth
            ,  app->display.screenHeight, "App");
    SetTargetFPS(60);
}

static void _deinit(App const *app) {
    CloseWindow();
}

int main(int argc, char *argv[])
{
    App app = {.display = {800, 600}};
    _init(&app);
    while(!app.exit) _update(&app);
    _deinit(&app);
    return EXIT_SUCCESS;
}
