all: attacksocket attackpx4 serversocketmain

attacksocket:	attacksocket.c
	gcc -fno-stack-protector -g3 -Xlinker -Map=attacksocket.map  -o attacksocket attacksocket.c

attackpx4:	attackpx4.c
	gcc -fno-stack-protector -g3 -Xlinker -Map=attackpx4.map  -o attackpx4 attackpx4.c

serversocketmain:	serversocketmain.c
	gcc -fno-stack-protector -g3 -Xlinker -Map=serversocketmain.map  -o serversocketmain serversocketmain.c

clean:
	rm attacksocket attackpx4 serversocketmain *.map
