#include "lab_m1/Tema1/Bullet.h"

#include <iostream>

using namespace std;

Bullet::Bullet() {
    x = 0;
    y = 0;
    dmg = false;
}

Bullet::Bullet(float x1, float y1, float distX1, float distY1, float angle1) {
    x = x1;
    y = y1;
    distX = distX1;
    distY = distY1;
    dmg = true;
    angle = angle1;
}

void Bullet::Disappear() {
    dmg = false;
    time = 5.0;
}
void Bullet::Time_move(float deltaTime) {
    time -= deltaTime;
}

void Bullet:: Reset(float x1, float y1, float distX1, float distY1) {
    distX = distX1;
    distY = distY1;
    dmg = true;
    x = x1;
    y = y1;
    time = 5.0;
}