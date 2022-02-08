#include "lab_m1/Tema1/Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy() {
    health_point = 20;
    x = rand() % 1200 + 30;
    y = rand() % 650 + 30;
    while (!Check_enemy(x - 50, true, false) || !Check_enemy(y - 50, false, true))
        Check_reset();
}

Enemy::Enemy(float x1, float y1) {
    health_point = 20;
    x = x1;
    y = y1;
}

bool Enemy::Check_enemy(float move, bool Xmov, bool Ymov) {
    //unde apare OX
    if (Xmov) {
        if (Corect_interval(move, 0, 30) && Corect_interval(y, 0, 720))
            return false;
        if (Corect_interval(move, 1220, 1280) && Corect_interval(y, 0, 720))
            return false;
        if (Corect_interval(move, 760, 1010) && Corect_interval(y, 160, 410))
            return false;
    }
    //unde apare OY
    if (Ymov) {
        if (Corect_interval(x, 0, 1280) && Corect_interval(move, 660, 720))
            return false;
        if (Corect_interval(x, 0, 1280) && Corect_interval(move, 0, 30))
            return false;
        if (Corect_interval(x, 760, 1010) && Corect_interval(move, 160, 410))
            return false;

    }
    return true;
}

bool Enemy::Corect_interval(float nr, float bot_limit, float top_limit) {
    // verifica daca un numar apartine unui interval
    if (nr >= bot_limit && nr <= top_limit)
        return true;
    else
        return false;
}

void Enemy::Check_reset() {
    x = rand() % 1200 + 30;
    y = rand() % 650 + 30;
}

void Enemy::Reset() {
    x = rand() % 1200 + 30;
    y = rand() % 650 + 30;
    health_point = 20;
    while (!Check_enemy(x - 50, true, false) || !Check_enemy(y - 50, false, true))
        Check_reset();
}

void Enemy::You_lose_your_life() {
    health_point = 0;
}

bool Enemy::In_life() {
    return health_point == 20;
}