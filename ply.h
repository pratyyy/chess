/*******************************************************
* Examines all possible moves calculates the score 
	repeates the step to a depth 
	Using the minimax approach traverses the various nodes and choose the 
	best out of it.

* Author : Prateek Vaishnav 
	   Gaurav Kishore

*********************************************************/ 


#include<iostream>


using namespace std;

void U64cpy(U64 Pieces[2][7],U64 Pie[2][7]);   // copies the content of argument 2 to argument 1
node* createroot(U64 Pieces[2][7]);
void update(node* pres,node* temp,int piece,int fromsq,int tosq,int ply);
int checkifcheck(U64 Pieces[2][7],int team);    // checks if the king is under check 
int checkifmate(U64 Pieces[2][7]);		// checks if the king is check mate 
int addMove(node* present,int piece,int fromsq,int tosq,int ply);  // add the move to the graph 
node* minimax(node *ro,int ply);                  // traverses the graph and gives the best path out of it 
void scoreforcheckmate(node* ro,int ply);         // adds bonus point for checkmation the opponents king
void blackupdate(int fromsq, int tosq);           // updates the move in the bitboard
void choosebestmoveupdate(node *ro,int ply);               
void think(node* ro,int ply);                    // determines the no of depth to think 

