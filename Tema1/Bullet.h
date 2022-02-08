
class Bullet {
public:
    //pozitia pe axa x
    float x;
    //pozitia pe axa y
    float y;
    //indicele de crestere pe axa x
    float distX;
    //indicele de crestere pe axa y
    float distY;
    //starea 
    bool dmg;
    //unghiul de inclinare
    float angle;
    //timpul pentru care glontul e printat
    float time = 5.0;

    Bullet();
    Bullet(float x1, float y1, float distX1, float distY1, float angle1);
    void Disappear();
    void Time_move(float deltaTime);
    void Reset(float x1, float y1, float distX1, float distY1);
};