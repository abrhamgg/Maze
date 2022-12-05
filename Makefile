build:
	gcc -std=c99 ./src/*.c -lSDL2 -lm -o main
run:
	./main
clear:
	rm main
