#include <iostream>
#include <cstring>
#include <ctime>
#include <ncurses.h>
#include "box.hpp"
#include "player.hpp"
using namespace std;
class market:MENU{
    public:
    int priceJump, priceHealth;
    market(int h, int w, int y, int x, char tag[], char tag2[], char tag3[], char tag4[]):MENU(h, w, y, x, tag, tag2, tag3, tag4){
        this->priceHealth=50;
        this->priceJump=50;
    }
    int choice();
    bool checkCurrency(int price, player* player);
    void buyHealth(player* player);
    void buyJumpboost(player* player);
};
