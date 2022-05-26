#pragma once

constexpr double GAME_PLAYER_W = 32.0;
constexpr double GAME_PLAYER_H = 32.0;

constexpr int GAME_SCREEN_WIDTH = 600;
constexpr int GAME_SCREEN_HEIGHT = 800;


// GAME CONFIG

// 중력 가속도
constexpr double GAME_GRAVITY = 7.0;

// 플레이어의 최대 낙하 속도, 이 값 이상으로는 수직 속도가 증가하지 않음
constexpr double GAME_PLAYER_MAX_V_Y = 80.0;

// 플레이어의 좌우 이동 속도
constexpr double GAME_PLAYER_SPEED = 300.0;

// 화면이 밑으로 이동하는 속도
constexpr double GAME_SCROLL_SPEED = 20.0;

// 발판과 발판 사이의 간격
constexpr double GAME_FLOOR_GAP = 150.0;

// 화면의 이동속도가 빨라지는 화면의 가장 위에서부터의 거리
constexpr double GAME_CAMERA_HALF_SPEED_LINE = 700.0;

// 화면의 이동속도가 최대 낙하 속도가 되는 화면의 가장 위에서부터의 거리
constexpr double GAME_CAMERA_FULL_SPEED_LINE = 780.0;

// 움직이는 발판의 최소 이동 속도
constexpr double GAME_FLOOR_MOVE_MIN_SPEED = 5.0;

// 움직이는 발판의 최대 이동 속도
constexpr double GAME_FLOOR_MOVE_MAX_SPEED = 30.0;


