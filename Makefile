PROG = out/server
MODULE_CFLAGS=-DMG_DISABLE_DAV

include ./server/examples.mk

targets=./out/server ./out/analyzer ## (abandoned) ./out/twitgrab ./out/dbimport

all: $(targets)

./out/analyzer: ./analyzer/analyzer.c
	gcc -o ./out/analyzer analyzer/analyzer.c -std=c99

#./out/twitgrab: ./twitter/twitgrab.cpp ./twitter/twitgrab.h ./twitter/secrets.h
#	g++ ./twitter/twitgrab.cpp -I ./include/ -L ./lib/ -ltwitcurl -o ./out/twitgrab
#
#./out/dbimport: dbimport/dbimport.c
#	gcc -o ./out/dbimport dbimport/dbimport.c $(pkg-config --libs --cflags libmongoc-1.0)
