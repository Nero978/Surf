#pragma once

#define GAME_NAME "Surf"
#define GAME_VERSION "Release-1.1.0"
#define GAME_AUTHOR "Chris Liu"
#define GAME_AUTHOR_EMAIL "ChrisLiu@bjfu.edu.cn"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define SCORE_PATH "D:/Surf/Score.txt"
#define LIB_PATH "D:/Surf"

//外部资源文件路径
#define GAME_RES_PATH "./Surf.qrc" 
#define BG_MUSIC_PATH "qrc:/assets/bgm.mp3"
#define BG_PATH ":/assets/images/bg1280.png"
#define GAME_ICON ":/assets/images/favicon.ico"
#define GAME_BG ":/assets/images/bg.jpg"
#define GAME_PLAYER ":/assets/images/player64.png"
#define INTERFACE_PATH ":/assets/images/interface24.png"
#define OBJECTS32_PATH ":/assets/images/objects32.png"
#define OBJECTS64_PATH ":/assets/images/objects64.png"
#define ISLANDS_PATH ":/assets/images/sandbar256.png"
#define AMBIENT_PATH ":/assets/images/ambient64.png"
#define INTERACT_PATH ":/assets/images/interact64.png"
#define ENEMY_PATH ":/assets/images/enemy128.png"

#define GAME_RATE 10 //游戏帧率
#define MAP_SPEED 1 //地图与玩家滚动速度
#define PLAYER_Y 240 //玩家初始位置

#define BLOOD 3 //玩家初始血量
#define BLOOD_X 500 //血量位置
#define BLOOD_Y 20
#define SPEED_X 700 //速度位置
#define SPEED_Y 20

#define MAX_OBJECTS 15 //最大物体数量
#define MAX_INTERACT 5 //最大交互物体数量
#define CHEAT_TIME 5000 //作弊时间
#define FLY_TIME 5000 //飞行时间