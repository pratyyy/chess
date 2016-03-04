/*******************************************************
* Evaluation function 

* Functions used to calculate score :
	Piece points , isolated pawn , backward pawn , points table ,
	Protecting points , Attacking point, attack to backward pawn 
	(refer to wikipedia for the explanation of these terms) 

* Author : Prateek Vaishnav 
	   Gaurav Kishore

*********************************************************/ 

#include<iostream>

using namespace std;
    
int PieceTable[7][64];
 
int PiecePoints[8]={0,100,330,330,520,980,32767};
int ProtectingPoints[8]={0,6,5,4,3,2,1};
int isolatedpawnspenalty[8]={12,14,16,20,20,16,14,12};

//////Points Table : Each Piece has its own  value at each square eg:A knight is more likely to move towards the centre ////

static const short KnightTable[64] =
{0, 4, 8, 10, 10, 8, 4, 0,
 4, 8, 16, 20, 20, 16, 8, 4,
 8, 16, 24, 28, 28, 24, 16, 8,
 10, 20, 28, 32, 32, 28, 20, 10,
 10, 20, 28, 32, 32, 28, 20, 10,
 8, 16, 24, 28, 28, 24, 16, 8,
 4, 8, 16, 20, 20, 16, 8, 4,
 0, 4, 8, 10, 10, 8, 4, 0};

static const short BishopTable[64] =
{14, 14, 14, 14, 14, 14, 14, 14,
 14, 22, 18, 18, 18, 18, 22, 14,
 14, 18, 22, 22, 22, 22, 18, 14,
 14, 18, 22, 22, 22, 22, 18, 14,
 14, 18, 22, 22, 22, 22, 18, 14,
 14, 18, 22, 22, 22, 22, 18, 14,
 14, 22, 18, 18, 18, 18, 22, 14,
 14, 14, 14, 14, 14, 14, 14, 14};

static const short PawnTable[64] =
{0, 0, 0, 0, 0, 0, 0, 0,
 4, 4, 4, 0, 0, 4, 4, 4,
 6, 8, 2, 10, 10, 2, 8, 6,
 6, 8, 12,16, 16, 12, 8, 6,
 8, 12, 16, 24, 24, 16, 12, 8,
 12, 16, 24, 32, 32, 24, 16, 12,
 12, 16, 24, 32, 32, 24, 16, 12,
 0, 0, 0, 0, 0, 0, 0, 0};

static const short KingTable[64] =
{0, 0, -4, -10, -10, -4, 0, 0,
 -4, -4, -8, -12, -12, -8, -4, -4,
 -12, -16, -20, -20, -20, -20, -16, -12,
 -16, -20, -24, -24, -24, -24, -20, -16,
 -16, -20, -24, -24, -24, -24, -20, -16,
 -12, -16, -20, -20, -20, -20, -16, -12,
 -4, -4, -8, -12, -12, -8, -4, -4,
 0, 0, -4, -10, -10, -4, 0, 0};

/////////////////////////////////

///Functions to calculate the points to be awarded or deducted for the particular board configuration ////

int doubledPawn(int sq,U64 Pieces[2][7]);
int isolatedPawn(int sq,U64 Pieces[2][7]);
int backwardPawn(int sq,U64 Pieces[2][7]);
int attacktobackward(int sq);
int halfopenfile(int sq);
int AttackingScore(int piece,int color,int sq);
int ProtectingScore(int piece,int color,int sq);

// function to sum  up the toatal point for particular configuration ///
int PositionalScore(U64 Pieces1[2][7]);

