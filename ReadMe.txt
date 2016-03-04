Chess 2.0

Authors : 
    1. Gaurav kishore  iit2008015
    2. Prateek Vaishnav iit2008022

Requirements:
    1. Opengl Package
    2. Glut Package 
    3. gcc compiler 
    
How to operate:
Step 1: Install all necessary packages (opengl & glut )

Step 2: Open konsole window and run ./chess

Note:The chess game is fully functional you can easily play with the computer having Artificial intelligence

Development Procedure:The chess game has been developed in mainly 5 stages.

1.Board Representation : Two unsigned int number is used to represent the board since the compiler is 32 bit . A class having all the functions of 64 bit has been made by overloading all the requires operators.

2.Move Generation: All  the different Pieces possible moves has been precalculated and stored in bitboard. The calculation become easy as it required only shift operations.

3.Evalution fuction: Points have been alloted to the pieces and for protecting & attacking an opponent piece.Points for checking and checkmating the king is allotted.

4.Depth Searching : Adding evaluation function was not enough ,thinking in depth was required Minmax tree was implemented.

5.End game: The possible moves that led itself king check was blocked and the condition for checkmate was implemented so that the game could end.

To give a 3D look OpenGL was used.

Hope you enjoy Playing. 

Thanking You
