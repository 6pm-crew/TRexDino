#include "raylib.h"
#include "player.h"
#include "obstacle_manager.h"

#define TARGET_FPS         60

#define SCREEN_WIDTH       800
#define SCREEN_HEIGHT      600

#define BACKGROUND_COLOR   ((Color) { 255, 255, 255, 255 })
#define OBSTABCLE ((Color) {85, 85, 85, 255})

int main(void) {
    // 게임의 목표 FPS를 설정한다.
    SetTargetFPS(TARGET_FPS);
    SetTraceLogLevel(LOG_DEBUG);
    // 게임 창을 생성한다.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "T-Rex Game");
    
    // 게임 화면의 경계를 나타내는 직사각형을 정의한다.
    const Rectangle bounds = { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT };
    const Rectangle ground = {0,0.7f * SCREEN_HEIGHT,SCREEN_WIDTH,0.3f * SCREEN_HEIGHT};
    Player *p = create(SCREEN_WIDTH,SCREEN_HEIGHT);
    ObstacleManager *ob = ObManagerCreate(SCREEN_WIDTH,SCREEN_HEIGHT);
    // 사용자가 창을 닫거나, `ESC` 키를 누르기 전까지 반복한다.
    while (!WindowShouldClose()) {
        // 게임 화면을 그리기 위해 프레임 버퍼를 초기화한다.
        BeginDrawing();
        
        // 프레임 버퍼를 검은색으로 채운다.
        ClearBackground(BLACK);

        // 게임 화면에 어두운 회색 색상의 직사각형을 그린다.
        DrawRectangleRec(bounds, BACKGROUND_COLOR);
        // DrawRectangleRec(ground,OBSTABCLE);
        p->show(p);
        ob->show(ob);
        obstacleClosest(ob,p);
        // 게임 화면에 현재 FPS를 표시한다.
        DrawFPS(8, 8);

        // 더블 버퍼링 기법을 사용하여 게임 화면을 그리고,
        // 다음 프레임 버퍼를 준비한다.
        EndDrawing();
    }

    
    // 게임 창에 할당된 메모리를 해제한다.
    DeletePlayer(p);
    Delete_ObManager(ob);
    CloseWindow();


    return 0;
}