#include "gameEngine.hpp"
typedef void * (*THREADFUNCPTR)(void *);
//game score of player
int game_scr = 0;

void initialize(){
    initscr(); //initialization of screen and memory
    refresh(); //refresh screen to be compatible with what is in memory
    noecho(); //impedisce all'user di typare
    curs_set(false); //cursor hider
}

void pregame(class BOX box, int y_scr, int x_scr){
    WINDOW* fin=box.create_box();
    mvwprintw(fin,y_scr/4,(x_scr/4)-3,"THE GAME");
    mvwprintw(fin,(y_scr/4)+1,(x_scr/4)-10,"press a key to start");
    refresh();
    wrefresh(fin);
    getch();
    clear();
}

void death_screen(class BOX box, int y_scr, int x_scr, class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int seed){
    WINDOW* fin=box.create_box();
    mvwprintw(fin,y_scr/4,(x_scr/4)-4,"YOU DIED");
    mvwprintw(fin,(y_scr/4)+1,(x_scr/4)-6,"Your SCORE: %d", game_scr);
    mvwprintw(fin,(y_scr/4)+2,(x_scr/4)-10," press a key to exit");
    refresh();
    wrefresh(fin);
    getch();
    clear();
    return;
}

int map_randomizer(class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int prev_seed, bool next_seed){
        if(next_seed==true){
            if(prev_seed==1)
                return 2;
            else if(prev_seed==2)
                return 3;
            else if(prev_seed==3)
                return 4;
            else if(prev_seed==4)
                return 5;
            else if(prev_seed==5)
                return 6;
            else if(prev_seed==6)
                return 7;
            else if(prev_seed==7)
                return 8;
            else if(prev_seed==8)
                return 9;
            else if(prev_seed==9)
                return 10;
            else
                return 1;
        }else{
            srand(time(0));
            int result=rand()%10;
            if(result==1)
                return map1.map_seed;
            else if(result==2)
                return map2.map_seed;
            else if(result==3)
                return map3.map_seed;
            else if(result==4)
                return map4.map_seed;
            else if(result==5)
                return map5.map_seed;
            else if(result==6)
                return map6.map_seed;
            else if(result==7)
                return map7.map_seed;
            else if(result==8)
                return map8.map_seed;
            else if(result==9)
                return map9.map_seed;
            else
                return map10.map_seed;
            }
}

WINDOW* map_generator(class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int seed, bool nxt_lvl){
        if(nxt_lvl==true){
            if(seed==1)
                return map2.create_map();
            else if(seed==2)
                return map3.create_map();
            else if(seed==3)
                return map4.create_map();
            else if(seed==4)
                return map5.create_map();
            else if(seed==5)
                return map6.create_map();
            else if(seed==6)
                return map7.create_map();
            else if(seed==7)
                return map8.create_map();
            else if(seed==8)
                return map9.create_map();
            else if(seed==9)
                return map10.create_map();
            else if(seed==10)
                return map1.create_map();
        }else{
            if(seed==1)
                return map1.create_map();
            else if(seed==2)
                return map2.create_map();
            else if(seed==3)
                return map3.create_map();
            else if(seed==4)
                return map4.create_map();
            else if(seed==5)
                return map5.create_map();
            else if(seed==6)
                return map6.create_map();
            else if(seed==7)
                return map7.create_map();
            else if(seed==8)
                return map8.create_map();
            else if(seed==9)
                return map9.create_map();
            else if(seed==10)
                return map10.create_map();
        }
}

void game_flow(int y_scr, int x_scr, WINDOW* map, class BOX box,
                class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                class MAP map9, class MAP map10, int seed, bool new_lvl){
    srand(time(0));
    int player_x, player_y, money, life;

	//FOLLOWING: default values for creating player-class items
	player_x=4;
	player_y=15;
	money=100;
	life=3;
	int saltoH=10;
    int mapSeed=0;
    /*
	 * ultima versione del salvataggio
	 * le righe hanno una piccola descrizione di cosa rappresenta il numero che segue nel file di salvataggio
	 * per selezionare solo il dato, ho implementato questo insieme di operazioni
	 * in caso in cui il dato non venisse ritrovato, ritorna un messaggio di errore e ripristina i valori predefiniti per quel dato
	 */

	
        ifstream savegame;
	    string lel, dump;
	    savegame.open("savegame.txt");

        if(savegame.is_open())
        {   
            getline(savegame, lel, '#');
            if(lel.compare("Y_loc")==0)
            {
                getline(savegame, lel,'\n');
                player_y = stoi(lel);	//NOTE: stoi(<string>) converts a string to int
            }else
            {
                clear();
                mvprintw((y_scr/2)-5, (x_scr/2)-2, "error in locating Y_loc in savedata");
                mvprintw((y_scr/2)-4, (x_scr/2)-2, "resorting to default value");
                refresh();
                getch();
                getline(savegame, dump);	//goes to next line without saving

            }

            getline(savegame, lel, '#');
            if(lel.compare("X_loc")==0)
            {
                getline(savegame, lel,'\n');
                player_x = stoi(lel);	//NOTE: stoi(<string>) converts a string to int
            }else
            {
                clear();
                mvprintw((y_scr/2)-5, (x_scr/2)-2, "error in locating X_loc in savedata");
                mvprintw((y_scr/2)-4, (x_scr/2)-2, "resorting to default value");
                refresh();
                getch();
                getline(savegame, dump);
            }

            getline(savegame, lel, '#');		//check for saving of player health
            if(lel.compare("life")==0)
            {
                getline(savegame, lel, '\n');
                life=stoi(lel);
            }else
            {
                clear();
                mvprintw((y_scr/2)-5, (x_scr/2)-2, "error in locating player health");
                mvprintw((y_scr/2)-4, (x_scr/2)-2, "resorting to default value");
                refresh();
                getch();
                getline(savegame, dump);
            }


            getline(savegame, lel, '#');		//check for saving of player money
            if(lel.compare("credits")==0)
            {
                getline(savegame, lel, '\n');
                money=stoi(lel);
            }

            getline(savegame, lel, '#');		//check for jumpHeight
            if(lel.compare("jumpH")==0)
            {
                getline(savegame, lel, '\n');
                saltoH=stoi(lel);
            }

            getline(savegame, lel, '#');		//check for seed of Map
            if(lel.compare("map")==0)
            {
                getline(savegame, lel, '\n');
                mapSeed=stoi(lel);
            }


            savegame.close();
	    }

    //set position of player if there was savefile and proceed in a new level
    if(new_lvl==true){
        player_x=4;
	    player_y=22;
    }

    player * p = new player(map, player_y, player_x, 'P', money, life);
        //(finestra, y da cui il personagio spawna,
        //x da cui il personaggio spawna, icona del personaggio)

    p->salto=saltoH;
    //sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico, 
    //              vita del nemico, icona del nemico (lasciala 'e'), soldi rilasciati alla morte)
	basicenemy * e1 = new basicenemy(map, 15, 25, 1, 'e', 50);

	basicenemy * e2 = new basicenemy(map, 15, 35, 1, 'e', 50);

	basicenemy * e3 = new basicenemy(map, 15, 65, 3, 'e', 80);

	//sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico, vita del nemico, 
    //              icona del nemico (lasciala 'e'),
	//soldi rilasciati alla morte, difficoltà del nemico !PIU IL NUMERO 
    //E' BASSO PIU E' DIFFICILE! (non usare numeri negativi; sconsiglio di scendere sotto a 3)
	jumpingenemy * e4 = new jumpingenemy (map, 15, 95, 3, 'E', 100, 4);

	//Inizializzazione del thread giocatore e nemici
	pthread_t playerthread, enemythread;

    basicenemy* b_e;
    jumpingenemy* j_e=jumping_enemy_randomizer(e4);
    if(j_e==NULL)
        b_e=basic_enemy_randomizer(e1,e2,e3);
    //prevents infinite money
    int count_money=0;
    //counter if enemy is dead
    bool dead_enemy=false;
	do{
		//Creazione del thread
		pthread_create(&playerthread, NULL, (THREADFUNCPTR) &player::display, p);
		//Aspetta che il thread finisca di elaborare
		pthread_join(playerthread, NULL);
        //Creazione del thread nemico

        if(j_e==NULL){
            pthread_create(&enemythread, NULL, (THREADFUNCPTR) &basicenemy::behaviour, b_e);
            pthread_join(enemythread, NULL);
            //reward killing basic enemy
            if(b_e->life==0 && count_money==0){
                dead_enemy=true;
                game_scr+=40;
                p->money=p->money+b_e->money;
                count_money++;
            }
        }else{
            pthread_create(&enemythread, NULL, (THREADFUNCPTR) &jumpingenemy::behaviour, j_e);
            pthread_join(enemythread, NULL);
            //reward killing jumping enemy
            if(j_e->life==0 && count_money==0){
                dead_enemy=true;
                game_scr+=60;
                p->money=p->money+j_e->money;
                count_money++;
            }
        }

        mvwprintw(map, 0, (x_scr/4)+5, "SCORE: %d", game_scr);

		refresh();
		wrefresh(map);

        remove("savegame.txt");

	}while(p->move()!=27 && p->life!=0 && p->playeroutput(1)<=116);

    //entrance in new level 
    if(p->playeroutput(1)>=116){
        clear();
        refresh();
        //reward for passing lvl
        game_scr+=100;
        int seed_generated=map_randomizer(map1,map2,map3,map4,map5,map6,map7,
                                               map8,map9,map10,seed,true);
        WINDOW* new_map = map_generator(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated,false);
        game_flow(y_scr,x_scr,new_map,box,map1,map2,map3,map4,map5,
                    map6,map7,map8,map9,map10,seed_generated,true);
        endwin();
        return;
    }

    //death of player
    if(p->life<1){
        clear();
        refresh();
        death_screen(box,y_scr,x_scr,map1,map2,map3,map4,map5,map6,map7,
                        map8,map9,map10,seed);
        remove("savegame.txt");
        endwin();
        return;
    }

    char v1[20], v2[20], v3[20], v4[20];
        strcpy(v1,"Menu");
        strcpy(v2,"Resume");
        strcpy(v3,"Market");
        strcpy(v4,"Save and exit");

    MENU menu(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v1,v2,v3,v4);

    char v5[20], v6[20], v7[20], v8[20];
        strcpy(v5,"Market");
        strcpy(v6,"Health boost");
        strcpy(v7,"Jump boost");
        strcpy(v8,"Return to the game");

    market market(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v5,v6,v7,v8);

        clear();
        refresh();

        int cx=menu.choice();
    if(cx==1){
            clear();
            refresh();
            int kek=save_data(p, seed, "savegame.txt" );
            if(kek==1){
                clear();
                mvprintw(0, 0, "loading");
                mvprintw(1, 0, "press a key to continue");
                refresh();
                getch();
                clear();
                refresh();
            }else{
                clear();
                mvprintw(0, 0, "error in load screen ");
                mvprintw(1, 0, "press a key to continue");
                refresh();
                getch();
                clear();
                refresh();
            }
            WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                            map7,map8,map9,map10,seed,false);
            game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                        map6,map7,map8,map9,map10,seed,false);
            endwin();
            return;
    }else if(cx==2){
            //accesso al market
           int mx=market.choice();
            if(mx==1){
                market.buyHealth(p);
                clear();
                refresh();
                int kek=save_data(p, seed, "savegame.txt" );
                if(kek==1){
                	clear();
                	mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
                	refresh();
                	getch();
                	clear();
                	refresh();
                }else{
                	clear();
                	mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
                	refresh();
                	getch();
                	clear();
                	refresh();
                }
                WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                                map7,map8,map9,map10,seed,false);
                game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                            map6,map7,map8,map9,map10,seed,false);
                endwin();
                return;
            }else if(mx==2){
                market.buyJumpboost(p);
                clear();
                refresh();
                int kek=save_data(p, seed, "savegame.txt" );
                if(kek==1){
                	clear();
                    mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
                    refresh();
                    getch();
                    clear();
                    refresh();
                }else{
                	clear();
                	mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
                	refresh();
                	getch();
                	clear();
                	refresh();
                }
                WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                                map7,map8,map9,map10,seed,false);
                game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                            map6,map7,map8,map9,map10,seed,false);
                endwin();
                return;
            }else{
                clear();
                refresh();
                /*
                 * giving back player data after resume
                 *
                 */
                int kek=save_data(p, seed, "savegame.txt" );
                if(kek==1){
            		clear();
            		mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
            		refresh();
            		getch();
            		clear();
            		refresh();
            	}else{
                	clear();
            		mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
            		refresh();
            	    getch();
            	    clear();
            	    refresh();
            	}
            WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                            map7,map8,map9,map10,seed,false);
            game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                        map6,map7,map8,map9,map10,seed,false);
            endwin();
            return;
            }
    }else if(cx==3){
        //save game
    	int kek=save_data(p, seed, "savegame.txt" );
    	if(kek==1)
    	{
    		clear();
    		mvprintw(0, 0, "game saved");
            mvprintw(1, 0, "press a key to exit");
    		refresh();
    		getch();
    	}else
    	{
    		clear();
    		mvprintw(0, 0, "game could not be saved, oopsie :) ");
            mvprintw(1, 0, "press a key to exit");
    		refresh();
    	    getch();
    	}
        endwin();
        return;
    }
}