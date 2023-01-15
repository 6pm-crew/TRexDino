#include "raylib.h"
#include "player.h"
#include "obstacle_manager.h"
#include "texture_manager.h"
#include "main.h"

/** boolean type flag */
bool isGameOver     = false;                                                // 게임 오버 플래그
bool game_debug     = false;                                                // 게임 디버그 온/오프
bool isReady        = false;                                                // 게임 시작 준비 플래그
bool isStart        = false;                                                // 게임 재시작 플래그
bool displayRecord  = false;                                                // 최고 기록 표시
bool spawnObstacle  = false;                                                // 장애물 충돌 여부 플래그

/** display score material */
int bestRecord;                                                             // 최고 기록 저장
int record[5];                                                              // 최고 기록 저장 및 출력
int digits[5];                                                              // 점수 자릿수 저장 및 출력
const Rectangle text = {.x =  1154, .y = 2, .width = 38, .height = 23};     // HI   텍스쳐 출력 위치
const Vector2 digitsPosition[10] = {                                        // 점수 텍스쳐 출력 위치
    {.x = SCREEN_WIDTH * 0.8f + 99, .y = 40},   // SC     1
    {.x = SCREEN_WIDTH * 0.8f + 75, .y = 40},   // SC    10
    {.x = SCREEN_WIDTH * 0.8f + 51, .y = 40},   // SC   100
    {.x = SCREEN_WIDTH * 0.8f + 27, .y = 40},   // SC  1000
    {.x = SCREEN_WIDTH * 0.8f +  3, .y = 40},   // SC 10000
    {.x = SCREEN_WIDTH * 0.6f + 99, .y = 40},   // HI     1
    {.x = SCREEN_WIDTH * 0.6f + 75, .y = 40},   // HI    10
    {.x = SCREEN_WIDTH * 0.6f + 51, .y = 40},   // HI   100
    {.x = SCREEN_WIDTH * 0.6f + 27, .y = 40},   // HI  1000
    {.x = SCREEN_WIDTH * 0.6f +  3, .y = 40},   // HI 10000
};

int background_color_temp = 13;
Color background_color_variable = { 255, 255, 255, 255 };

int main(void) {

    /** default start option */
    SetTargetFPS(TARGET_FPS);                                               // fps 설정
    if(game_debug) 
        SetTraceLogLevel(LOG_DEBUG);                                        // 디버그 출력
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "T-Rex Game");                  // 화면 생성
    SetExitKey(KEY_NULL);                                                   // ESC 종료 방지
    
    /** window border of rectangle type */
    const Rectangle bounds = { .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT };
    
    /** game entity option */
    Player          *p  = createPlayer();                                   // T-Rex 생성
    ObstacleManager *ob = ObManagerCreate();                                // 장애물 관리자 생성

    /** texture option */
    Texture2D  texture  = LoadTexture("res/images/offline-sprite-2x.png");  // 리소스 불러오기
    setPlayerTexture(texture);                                              // 플레이어 텍스쳐 설정
    setObstacleTexture(texture);                                            // 장애물 텍스쳐 설정

    while (!WindowShouldClose()) {                                          // 사용자가 창을 닫을 때 까지 반복
        
        /** frame buffer option */
        BeginDrawing();                                                     // 프레임 버퍼 초기화
        ClearBackground(BLACK);                                             // 프레임 버퍼 색상

        /** game background option */
        DrawRectangleRec(bounds, background_color_variable);                // 화면에 짙은 회색 직사각형 그리기
        drawBackground(texture,ob->moveSpeed);                              // 지면 텍스쳐 그리기

        /** game entity option */
        ob->show(ob);                                                       // 장애물 출력
        p->show(p);                                                         // 플레이어 출력
        
        /** display score */
        int score = ob->timePass;
        for(int i = 0; i < 5; i++) {                                        // 자릿수 별로 숫자 출력
            digits[i] = score % 10;
            score /= 10;
            drawNumberAt(texture ,digitsPosition[i],digits[i]);
        }

        /** day cycle(1-cycle: day(600) + night(400)) */
        int dayCycle = ob->timePass % 1000;
        if(dayCycle == 600) {
            if(background_color_variable.r == 255) {    // -208, each 13p 16 times
                background_color_variable.r = 47;
                background_color_variable.g = 47;
                background_color_variable.b = 47;
            }
        } else if (dayCycle == 0) {
            if(background_color_variable.r == 47) {     // +208
                background_color_variable.r = 255;
                background_color_variable.g = 255;
                background_color_variable.b = 255;
            }
        }

        /** best record display option */
        if(displayRecord) {                                                 // 최고 기록 출력
            drawResourceAt(texture, text);
            for(int i = 0; i < 5; i++)
                drawNumberAt(texture, digitsPosition[i+5], record[i]);
        }

        /** game event option */
        Obstacle *temp = obstacleClosest(ob,p);                             // 가장 가까운 장애물 반환
        if(temp != NULL && spawnObstacle)                                   // 장애물과 충돌 시 게임오버
            if(CheckCollisionRecs(temp->aabb, p->aabb))
                isGameOver = true;

        /** game play option */
        if(isGameOver){                                                     // 게임 오버 및 재시작
            gameOverBackround(texture);

            if(isStart && (IsKeyReleased(KEY_R) || IsKeyReleased(KEY_SPACE) || IsKeyReleased(KEY_UP))) {
                if(bestRecord < ob->timePass) {
                    bestRecord = ob->timePass;
                    TraceLog(LOG_DEBUG, "best record: %d", bestRecord);
                    for(int i = 0; i < 5; i++) {                            // 최고 기록 저장
                        record[i] = ob->timePass % 10;
                        ob->timePass /= 10;
                    }
                }
                resetObManager(ob);                                         // 엔티티 및 플래그 초기화
                resetPlayer(p);
                isGameOver    = false;
                isReady       = false;
                isStart       = false;
                displayRecord = true;
            }        

            else if(isReady && (IsKeyDown(KEY_R) || IsKeyDown(KEY_SPACE) || IsKeyReleased(KEY_UP))) 
                isStart = true;                                             // 게임 재시작

            else if(!(IsKeyDown(KEY_R) || IsKeyDown(KEY_SPACE) || IsKeyReleased(KEY_UP))) 
                isReady = true;                                             // 게임 시작 준비
        }
        DrawFPS(8, 8);                                                      // x, y 위치에 fps 출력
        EndDrawing();                                                       // 다음 프레임 버퍼 준비(더블 버퍼링 기법)
    }

    /** release a memory */
    deletePlayer(p);                                                        // T-Rex 동적할당 해제
    delete_ObManager(ob);                                                   // 장애물 관리자 동적할당 해제
    UnloadTexture(texture);                                                 // 리소스 메모리 동적할당 해제

    CloseWindow();                                                          // 화면 출력 종료

    return 0;
}