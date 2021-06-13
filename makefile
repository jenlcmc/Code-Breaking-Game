game: mainGame.o mastermindDrive.o
	g++ mainGame.o mastermindDrive.o -o game

main: mainGame.cpp
	g++ -c mainGame.cpp

mastermind: mastermindDrive.cpp
	g++  -c mastermindDrive.cpp

clean:
	rm mainGame.o
	rm mastermindDrive.o
	rm game