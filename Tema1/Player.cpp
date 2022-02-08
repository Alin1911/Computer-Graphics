#include "lab_m1/Tema1/Player.h"

#include <iostream>

using namespace std;

Player::Player() {
    health_point = 100;
    point = 0;
    you_can_shot = true;
}

Player::Player(float health_point_start, int point_start, bool you_can_shot1) {
    health_point = health_point_start;
    point = point_start;
    you_can_shot = you_can_shot1;
}

void Player::Scoreup() {
    point += 100;
}

void Player::Heal_me() {
    health_point += 10;
}

void Player::You_lose_your_life() {
    health_point -= 10;
}