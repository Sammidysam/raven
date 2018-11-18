targets=./out/twitgrab

all: $(targets)

./out/twitgrab: ./twitter/twitgrab.cpp
	g++ ./twitter/twitgrab.cpp -I ./include/ -L ./lib/ -ltwitcurl -o ./out/twitgrab
