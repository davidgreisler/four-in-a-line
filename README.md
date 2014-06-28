Four in a line
============
Four in a line is a two-player game in which two players first select a color and then take turns dropping a token
of their color from the top into a grid. The token falls straight down, occupying the
lowest free cell in the grid. The first player who has four tokens in a row, either
horizontally/vertically or diagonally, wins the game.

It is possible to play the game with two human players, either locally or over the network, or with
one human player playing against a computer player. When playing over the network, the players can
communicate using an in-game chat. The number of won/lost/drawn games of each player are stored in
a highscore list.

The program was created within the scope of an assignment for the course Multimedia: Entwicklung Multimedialer Systeme.

Authors
-------
* David Greisler <kontakt@davidgreisler.de>
* Simon Mühlichen <s0530738@htw-berlin.de>

Requirements
------------
The game is written using the Qt framework.

* Qt 5

Project structure
-----------------
This list gives an overview over the modules/subprojects of this application.

* `app`
      
  The main application.

* `src`
    
  Source code for the main application.

* `src/GameLogic`

  Game board and other general classes that could be used for board games.

* `src/GameLogic/FourInALine`

  The four in a line game logic and artificial intelligence.

* `src/Game`

  Integrates the game logic into the application. Extends the game logic making
  it aware of different player types and implementing network functionality.
  Contains classes for saving/loading games/replays. Also contains the game controller
  which manages the gameplay.

* `src/Game/Players`

  Player classes representing the different player types (human player, AI player,
  network player, ...).
   
* `src/GUI`

  The graphical user interface of the application. Contains main window and views.
  The main window has a menu bar and multiple toolbars containing actions for the 
  application's functionality. The central widget of the main window is either controlled
  by the GameView when the user is playing a game, or by the ReplayView when
  the user is watching a replay.

* `src/GUI/Actions`

  Containers for the application's actions which are used throughout in the GUI. The
  containers take care of disabling/enabling the actions according to current application
  state.

* `src/GUI/Widgets`

  Custom widgets used by the GUI.
    
* `src/GUI/Dialogs`
      
  Dialogs shown by the GUI.

* `tests`

  Unit-tests.

License
-------
Four in a line is free software and is distributed under the terms of the MIT license. The full license text is available in the LICENSE.md file.

This program uses some of the "Farm-Fresh Web Icons" from FatCow ( http://www.fatcow.com/free-icons ).
They are licensed under a Creative Commons Attribution 3.0 License ( http://creativecommons.org/licenses/by/3.0/us/ ).
Some icons were modified.
