PROG = out/server
MODULE_CFLAGS=-DMG_DISABLE_DAV

include ./server/examples.mk

targets=./out/twitgrab ./out/dbimport ./out/server

all: $(targets)

./out/twitgrab: ./twitter/twitgrab.cpp ./twitter/twitgrab.h ./twitter/secrets.h
	-g++ ./twitter/twitgrab.cpp -I ./include/ -L ./lib/ -ltwitcurl -o ./out/twitgrab

./out/dbimport: dbimport/dbimport.c
	-gcc -o ./out/dbimport dbimport/dbimport.c $(pkg-config --libs --cflags libmongoc-1.0)
