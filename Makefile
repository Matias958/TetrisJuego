#TP FINAL PROGRAMACION I: TETRIS

CC := gcc

OPTIONS_AL := -Wall -l allegro -l allegro_image -l allegro_font -l allegro_ttf -l allegro_audio -l allegro_acodec -l allegro_primitives -l allegro_color

OPTIONS := -Wall

#ALLEGRO
tetris_al: main_al.o element_al.o highscore_al.o buttons_al.o menu_al.o game_sel_al.o game_al.o highscore.o rules.o game.o highscore.txt
	${CC} main_al.o element_al.o highscore_al.o buttons_al.o menu_al.o game_sel_al.o game_al.o highscore.o rules.o game.o -o tetris_al ${OPTIONS_AL}

main_al.o: main_al.c element_al.h menu_al.h game_sel_al.h highscore_al.h game_state.h highscore.h
	${CC} main_al.c -c ${OPTIONS_AL}

element_al.o: element_al.c element_al.h
	${CC}  element_al.c -c ${OPTIONS_AL}

highscore_al.o: highscore_al.c highscore_al.h highscore.h game_state.h element_al.h buttons_al.h
	${CC} highscore_al.c -c ${OPTIONS_AL}

buttons_al.o: buttons_al.c buttons_al.h
	${CC} buttons_al.c -c ${OPTIONS_AL}

menu_al.o: menu_al.c menu_al.h buttons_al.h element_al.h game_state.h
	${CC} menu_al.c -c ${OPTIONS_AL}

game_sel_al.o: game_sel_al.c game_sel_al.h buttons_al.h element_al.h game_state.h
	${CC} game_sel_al.c -c ${OPTIONS_AL}

game_al.o: game_al.c game_al.h buttons_al.h game.h highscore.h game_state.h element_al.h
	${CC} game_al.c -c ${OPTIONS_AL}

#BACKEND

highscore.o: highscore.c highscore.h
	${CC} highscore.c -c ${OPTIONS}

rules.o: pieces.h rules.c rules.h
	${CC} rules.c -lm -c ${OPTIONS}

game.o: game.c game.h pieces.h game_state.h rules.h
	${CC} game.c -c ${OPTIONS}

clean:
	rm *.o