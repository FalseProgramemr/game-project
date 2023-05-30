#include "market.hpp"

bool market::checkCurrency(int price, player* P1){
    if(price > (P1->money))
    {
    	return false;
    }else
    	return true;
}

void market::buyHealth(player* player){
    if(checkCurrency(priceHealth, player)){
        player->life=player->life+1;
        player->money=player->money-priceHealth;
        priceHealth=priceHealth+10;
    }
}
void market::buyJumpboost(player* player){
    if(checkCurrency(priceJump, player)){
        (player->salto) ++;
        player->money=player->money-priceJump;
        priceJump=priceJump+10;
    }
}
int market::choice(){
    WINDOW* fin= BOX::modify_box(tag);
    keypad(fin,true);
    string choice[3]{tag2,tag3,tag4};
    int user_typing, h_light=0, exit_value;
    bool found=false;
    while(1 && !found){
        for(int i=0;i<3;i++){
            if(i==h_light){
                wattron(fin,A_REVERSE);
            }
            mvwprintw(fin,i+1,1,choice[i].c_str());
            wattroff(fin,A_REVERSE);
        }
        user_typing=wgetch(fin);

        if(user_typing==KEY_UP){
            h_light--;
            if(h_light==-1)
                h_light=0;    
        }else if(user_typing==KEY_DOWN){
            h_light++;
            if(h_light==3)
                h_light=2;
        }
        if(user_typing=='k'){
            found=true;
            clear();
            exit_value=h_light+1;
        }
    }
    return exit_value;
}