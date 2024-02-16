all:
	g++ -I src/include -o game game.cpp enemy.cpp player.cpp -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image   
	
#may actually want to use this but not sure lets see 
#g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 
