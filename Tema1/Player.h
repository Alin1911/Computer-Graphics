
class Player {
public:
    //poztia pe axa x si y
    float axeX, axeY;
    //coltul patratului
    float cx, cy;
    //viata 
    float health_point;
    //scorul
    int point;
    
    //verifica daca pot trage
    bool you_can_shot;

    //orientarea pentru tragere(dupa mouse)
    float angle_bullet;

    Player();

    Player(float health_point_start, int point_start, bool you_can_shot1);
    //am omorat un inamic
    void Scoreup();
    //primesc viata
    void Heal_me();
    //pierd viata
    void You_lose_your_life();
};