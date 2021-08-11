# Code-Breaking Game(MM)
- A simple mastermind board game that the user will have to guess the combination of random colors. 
- User will need to enter how many rows they want to play first
- There is 6 colors: yellow, green, blue, red, white, pink. 
- The combination of colors can be duplicate. 
- The user will have 6 chances to guess the colors combination.
- The user can enter either full string or char of the color
```
 r or red for red color
```

- The game has save function that will let the user to save the game. 
- It also has function that remember the current game and let the user comeback to plays later.

## About clonning

- You can clone a repository from GitHub to your local computer to make it easier to fix merge conflicts, add or remove files, and push larger commits. 
- When you clone a repository, you copy the repository from GitHub to your local machine.
- Cloning a repository pulls down a full copy of all the repository data that GitHub has at that point in time, including all versions of every file and folder for the project. 
- You can push your changes to the remote repository on GitHub, or pull other people's changes from GitHub. For more information, see "Using Git".
- You can clone your existing repository or clone another person's existing repository to contribute to a project.

## To clone 

- Open Terminal.
- Change the current working directory to the location where you want the cloned directory.

```
$ git clone https://github.com/jenlcmc/Code-Breaking-Game.git
```

- Press Enter to create your local clone.
- It shoud kind of look like under example except the https is different

```
$ git clone https://github.com/YOUR-USERNAME/YOUR-REPOSITORY
> Cloning into `Spoon-Knife`...
> remote: Counting objects: 10, done.
> remote: Compressing objects: 100% (8/8), done.
> remove: Total 10 (delta 1), reused 10 (delta 1)
> Unpacking objects: 100% (10/10), done.
```

## Requirements

- gcc compiler
- C++ 11 and above

## To compile the files
```
make
```

The result will be the **game** file 

## To run the file
```
./game
```

## To remove all the .o and execute files
```
make clean
```

## Remove VSCode folers

.vscode folders are used for running and debugging within VS Code text editor

.vscode folder may be hidden in Unix like system but vissible on Windows OS to find remove from terminal/powershell:

```
ls -la //.vscode folder should be visible

rm -rf .vscode
```

## Known Issues
- Scoreboard not function correctly

## Upcoming function
- Let 2 users play together
- Add highest scoreboard

## Notes
- If there are any errors or trouble with run the game, please make a pull request
- This is 1st year school project, if anyone want me to remove it, please contact, I will pull it down.

## REFERENCE
[Mastermind Game](https://en.wikipedia.org/wiki/Mastermind_(board_game))
