# Neumorphism Tetris game in C++ using SDL2 
*(SDL.h, SDL_image.h, SDL_ttf.h, SDL_mixer.h)*
![image](https://user-images.githubusercontent.com/40814521/169949095-2858bc9a-4d85-46a5-8bfa-081826770d53.png)

_______________________________
## How to play:
- Right/Left Arrow: move right/left
- Up Arrow: Rotate
- Down Arrow: Soft Drop
- Space: Hard Drop
- Shift/C: Hold
- Escape: Escape

_______________________________
## Instruction:
- Ghost Piece: to locate the current piece when hard drop.
- Hold Piece: swap the current piece with the hold piece.
- Lines: the numbers of cleared line.
- Level: the delay time when a piece (a tetromino) is falling. 10 cleared lines increase 1 level, which decreases the delay time by 100ms. If the cleared lines are more than 90 lines, the level is 10 and the delay time is 50ms. The start level is 1 (1000ms) and max level is 10 (50ms).
- Pause Button: pause the game.
- Theme Switch: switch between dark theme and light theme.
- Mute Sound Button: mute/unmute sound effects (when move piece or switch theme).
- Mute Music Button: pause/resume background music. The music is looped until the game is over. Music will still be played when the game is paused.
![image](https://user-images.githubusercontent.com/40814521/169949227-7d5b0fc2-9b8c-4183-912c-0225d4d5f5a7.png)

_______________________________
## Scoring:
- Soft drop: 10 * level(s) * line(s).
- Hard drop: 20 * level(s) * line(s).
- Line clear: 
  1 - 2 line(s) cleard at the same time: 100 * level(s) * line(s).
  3 lines cleard at the same time: 500 * level(s).
  4 lines cleared at the same time: 800 * level(s).

_______________________________
## High scores board:
- There will be 5 max highest scores saved in the high scores board, sorted by descending order.
- If the board has fewer than 5 scores, the new score will be added to the board, then the board will be sorted.
- If the board has 5 scores and the new score is higher than one of the score on the board, the lowest score will be removed from the board as the new score added to the board in descending order.
- Players can enter their names to be saved on the board.
![image](https://user-images.githubusercontent.com/40814521/169949449-2dec5c59-f7f2-47d3-8d4b-7b83191462eb.png)
![image](https://user-images.githubusercontent.com/40814521/169949513-82e2a009-8a53-4921-90e3-de0c9088eefc.png)

_______________________________
## Knowledges and Game logic design:

[SDL2 instructions: Lazy Foo's SDL tutorials](https://lazyfoo.net/tutorials/SDL/index.php) 

[Game logic: Javier Lopez's Tetris tutorial ](https://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners)

[Game Design: 2009 Tetris Design Guideline](https://tetris.fandom.com/wiki/Tetris_Guideline)

_______________________________
## Game Graphic Design: all designed by Lê Hoàng Minh Hà using Adobe Photoshop.
- Game window: 960px x 720px.
- Block size: 28px.
- Game field: 10 (blocks) x 22 (blocks) (the first two lines where new piece starts are hidden).
- Hold Piece box: 5 (blocks) x 5 (blocks).
- Next Piece box: 5 (blocks) x 5 (blocks).
- Buttons.

_______________________________
## Sound effects: All used sounds are no copyright
- [Count Down](https://assets.mixkit.co/sfx/download/mixkit-simple-game-countdown-921.wav)
- Move Piece
- Drop Piece
- Switch Theme
- [Clear Line](http://www.vertigogaming.org/downloads/svencoop/sound/sc_tetris/clear.wav)
