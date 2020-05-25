# Cannibal Snakes
Cannibal Snakes, a game made for ICA Component 2 for the module 'Games Development with C++'. This is Snake, built from scratch with SFML and C++, with a 'Gobble Mode' mechanic, in which you can intercept with other snakes and, instead of dying, you gobble them up to their tail. This project was done in just over a month, with around a thousand lines of C++ code, featuring a full menu system, homemade graphics in an 80's retro style, sound effects and music courtesy of https://opengameart.org/content/library-of-game-sounds. The full game can be downloaded and played with the zip folder in the Releases Tab! 
## Game Screenshots
![The Title Screen](http://www.tomdotscott.com/images/Github/Snake/Snake_Titles.png)

When the .exe is loaded up, the player is greeted with a lovely retro-feeling title screen. They use the arrow keys to choose an option and the space key to select it.
### Single Player

![The Controls Menu](http://www.tomdotscott.com/images/Github/Snake/Snake_Controls.png)

Inspired by retro games, if Single Player mode is selected, the player is shown a screen that explains the premise and controls of the games, including all fo the fruits' worth. It also explains the games main mechanic - Gobble Mode

![Single Player](http://www.tomdotscott.com/images/Github/Snake/Snake_In-Game_SinglePlayer.png)

I wanted the game to feel like it got ripped straight out of the 1980's, so inspired by Commodore 64 games and old GameBoy Games, the UI is very simple, and the colour pallette is limited. 
In Single Player mode, the player pits himself off against AI snakes. These AI Snakes implement a form of Dijkstra's pathfinding algorithm, wherein they find the shortest route that has no interruptions. When they are in Gobble Mode, the AI snakes head directly to the player, ploughing through whatever is in their way. Gobble Mode itself is indicated, as shown in the image above, by the snake turning Yellow. This happens to the AI and the Players.

![Game Over](http://www.tomdotscott.com/images/Github/Snake/Snake_SinglePlayer_GameOver_1.png)

The aim of the game is to be the last snake standing or, when the time runs out, be the snake with the most points. If this is the case, the player is displayed a screen that says that they win, with their score and the highscore.

![Game Over](http://www.tomdotscott.com/images/Github/Snake/Snake_SinglePlayer_GameOver_2.png)

If this is not the case, the player is displayed a Game Over screen and given the opportunity to play the game again. 
### Two Player
This game also supports 2 players, with the use of the arrow keys and WASD keys. 

![Two Players](http://www.tomdotscott.com/images/Github/Snake/Snake_In-Game-TwoPlayer.png)

When playing in 2 player mode, the UI is simplified, making it look a bit more visually appealing, in my opinion. 

![Two Player Game Over](http://www.tomdotscott.com/images/Github/Snake/Snake_TwoPlayerGameOver.png)

The aim of the game is the same as in Single Player. On the Game Over screen, the winner is displayed in their colours. The game over display also displays if the game is a draw if, for instance, both snakes have a head on collision, or the time runs out and they have the same amount of points. 
