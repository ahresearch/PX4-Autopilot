all: attacksocket attackpx4 serversocket

attacksocket:	attacksocket.c
	gcc -fno-stack-protector -g3 -Xlinker -Map=attacksocket.map  -o attacksocket attacksocket.c

attackpx4:	attackpx4.c
	gcc -fno-stack-protector -g3 -Xlinker -Map=attackpx4.map  -o attackpx4 attackpx4.c

serversocket:	serversocketmain.c serversocket.c
	gcc -fno-stack-protector -g3 -Xlinker -Map=serversocket.map  -o serversocket serversocketmain.c serversocket.c

clean:
	rm attacksocket attackpx4 serversocket *.map
