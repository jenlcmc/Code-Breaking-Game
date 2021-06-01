game: mainGame.o mastermindDrive.o
	g++ -g mainGame.o mastermindDrive.o -o game

main: mainGame.cpp
	g++ -g -c mainGame.cpp

mastermind: mastermindDrive.cpp
	g++ -g -c mastermindDrive.cpp

clean:
	rm mainGame.o
	rm mastermindDrive.o
	rm game