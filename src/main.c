#include "raylib.h"
#include "player.h"
#include "obstacle_manager.h"
#include "texture_manager.h"

#include "main.h"

/** 게임 종료 변수*/
bool isGameOver = 0;

/** 게임 디버그 변수*/
bool game_debug = false;

bool isOkayToStart = false;

bool takeout = false;
int tmeptmep = 0;

int main(void) {

    SetTargetFPS(TARGET_FPS);   // 목표 fps 설정

    if(game_debug)
        SetTraceLogLevel(LOG_DEBUG); // 디버그 활성화 

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "T-Rex Game");// 게임 창을 생성한다.
    SetExitKey(KEY_NULL);       // ESC 종료 방지
    
    // 게임 화면의 경계를 나타내는 직사각형을 정의한다.
    const Rectangle bounds = { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT };
    
    // 플레이어의 변수를 생성한다.
    Player *p = createPlayer();
    // 장애물 관리자를 생성한다.
    ObstacleManager *ob = ObManagerCreate();

    // 사용할 스프라이트를 불러온다.
    Texture2D texture = LoadTexture("res/images/offline-sprite-2x.png");

    // 각 생성된 구조체 변수에 텍스쳐를 등록한다.
    setPlayerTexture(texture);
    setObstacleTexture(texture);

    // 사용자가 창을 닫거나, `ESC` 키를 누르기 전까지 반복한다.
    while (!WindowShouldClose()) {
        // 게임 화면을 그리기 위해 프레임 버퍼를 초기화한다.
        BeginDrawing();
        
        // 프레임 버퍼를 검은색으로 채운다.
        ClearBackground(BLACK);

        // 게임 화면에 어두운 회색 색상의 직사각형을 그린다.
        DrawRectangleRec(bounds, BACKGROUND_COLOR);
        drawBackground(texture,ob->moveSpeed);

        // 장애물 관리자 장애물 표시
        ob->show(ob);
        // 플레이어 표시
        p->show(p);
        // 가장 가까운 장애물 반환
        Obstacle * temp = obstacleClosest(ob,p);
        // 충돌시 게임 꺼짐
        if(temp != NULL)
            if(CheckCollisionRecs(temp->aabb, p->aabb)) isGameOver = true;

        if(isGameOver){
            gameOverBackround(texture);
            
            if(takeout && (IsKeyReleased(KEY_R) || IsKeyReleased(KEY_SPACE))) {
                tmeptmep = 1;
                resetObManager(ob);
                resetPlayer(p);
                isGameOver = false;
                isOkayToStart = false;
                takeout = false;
            }            
            else if(isOkayToStart && (IsKeyDown(KEY_R) || IsKeyDown(KEY_SPACE))) {
                takeout = true;
            }
            else if(!(IsKeyDown(KEY_R) || IsKeyDown(KEY_SPACE))) {
                isOkayToStart = true;
            }

            printf("%d\n",tmeptmep);

        }

        // 게임 화면에 현재 FPS를 표시한다.
        DrawFPS(8, 8);

        // 더블 버퍼링 기법을 사용하여 게임 화면을 그리고,
        // 다음 프레임 버퍼를 준비한다.
        EndDrawing();
    }

    // 플레이어 동적할당 해제
    DeletePlayer(p);

    // 장애물 관리자 동적할당 해제
    Delete_ObManager(ob);
    
    // 게임 창에 할당된 메모리를 해제한다.
    UnloadTexture(texture);

    CloseWindow();

    return 0;
}