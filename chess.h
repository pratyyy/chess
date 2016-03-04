/**************************************************************************************

* Creates bitboard and sets the foundation for the game development . Board Setup

* Author:Gaurav Kishore
	Prateek Vaishnav
	
**************************************************************************************/

#include<iostream>
#include<cmath>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<map>

using namespace std;

typedef unsigned long U32;

//Assigning the various pieces an integer value /// 
const   int pnil   = 0; 
const   int pawn   = 1;
const   int knight = 2;
const   int bishop = 3;
const   int rook   = 4;
const   int queen  = 5;
const   int king   = 6;

const   int white  = 0;
const   int black  = 1;

map<string,int> m;


/*************************************************************************

* Class defining a bitboard which comprises of two U32 numbers 

* This makes a board of 64 bits 

* All the bitwise operators are overloaded so as to work with two 32 bit no.

**************************************************************************/
 
class U64
{
	public:
	U32 l, h;
	U64()
	{
		l = 0x0;
		h = 0x0;
	}
	U64 operator |(U64);
	U64 operator &(U64);
	U64 operator ^(U64);
	U64 operator ~(void);
	U64 operator <<(int a);
	U64 operator >>(int b);
	void operator =(int sq);
	void operator |=(int sq);

	void display();
	int getAndClearLSB();
	
	bool check(){
		if( !( l | h) )
			return false;
		else
			return true;
	}
};


/*************************************************************************

* Class defining bitboard of various Pieces. 

* It also defines various boards that are precalculated and stored such as
	possible moves . 

* The constructor declares the initial status of all the bitboards of 
	various pieces

**************************************************************************/

class CBoard
{
	public:
	
	int side;
	  
	U64 Pieces[2][7];

   	U64 Knightsmove[64];
   	U64 Kingmove[64];
 
 
   	U64 right_board[64];
   	U64 left_board[64];
   	U64 up_board[64];
   	U64 down_board[64];
	
   	U64 _45deg_board[64];
   	U64 _225deg_board[64];
   	U64 _135deg_board[64];
  	U64 _315deg_board[64];

	U64 Pawnsmove[64][2];
	U64 Pawnsdoublemove[64][2];
	U64 Pawnsattackmove[64][2];

	U64 fullboard[2];
  	U64 occupiedboard[2];
	U64 unoccupiedboard[2];
   	U64 enemyboard[2];
	U64 notfriendlyboard[2];
	U64 friendlyboard[2];

	U64 attackboard[2];
	
	U64 doubledpawn[2];
	U64 isolatedpawn[2];
	U64 backwardpawn[2];
	
	U64 kngchk[7];
   	void validmove();
   	CBoard();

}bitboard;

void initialise();
