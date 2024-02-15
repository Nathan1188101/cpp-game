all:
	g++ -I src/include -o drawplayer drawplayer.cpp -Lsrc/lib -lmingw32 -lSDL2main -lSDL2  
	
#may actually want to use this but not sure lets see 
#g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 
