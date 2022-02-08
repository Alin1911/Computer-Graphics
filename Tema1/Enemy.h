
class Enemy {
public:
    //viata unui inamic
    int health_point;
    //poztia pe axa x
    float x;
    //pozitia pe axa y
    float y;
    //unghiul pentru orientare
    float angle;

    Enemy();
    Enemy(float x1, float y1);
    //corectie pentru o pozitie intiala gresita
    void Check_reset();
    //inamicul reapare la alte pozitii
    void Reset();
    //inamicul moare
    void You_lose_your_life();
    //inamicul traiestie
    bool In_life();
    //verificare poztie (sa fie pe mapa)
    bool Check_enemy(float move, bool Xmov, bool Ymov);
    //verificare interval
    bool Corect_interval(float nr, float bot_limit, float top_limit);
};