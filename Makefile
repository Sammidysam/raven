targets=./out/twitgrab

all: $(targets)

./out/twitgrab: ./twitter/twitgrab.cpp ./twitter/twitgrab.h ./twitter/secrets.h
	g++ ./twitter/twitgrab.cpp -I ./include/ -L ./lib/ -ltwitcurl -o ./out/twitgrab
