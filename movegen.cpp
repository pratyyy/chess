#include "movegen.h"
#include "ply.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
inline U64 genKnightAttackBoard(int sq)
{
    bool side=bitboard.side;
    return bitboard.Knightsmove[sq] & bitboard.notfriendlyboard[side];
}

inline U64 genKingAttackBoard(int sq)
{
    bool side=bitboard.side;
    U64 temp,temp1,p;

    // Move if castling is allowed 
    if(castling[side][0]==1 && (sq==3 || sq == 59)){
	      temp |= sq-1;
	      temp |= sq-2;
	      //genUtilBoards(bitboard.Pieces);
	      temp = temp & (bitboard.enemyboard[0]|bitboard.friendlyboard[0]);
	      if(temp.check());
	      else
		 p |=sq-2;
    }
	
    if(castling[side][1]==1 && (sq==3 || sq == 59)){
	      temp1 |= sq+1;
	      temp1 |= sq+2;
	      temp1 |= sq+3;
	      //genUtilBoards(bitboard.Pieces);
	      temp1 = temp1 & (bitboard.enemyboard[0]|bitboard.friendlyboard[0]);
	      if(temp1.check());
	      else
		 p |=sq+2;
    }
	///////////
  
    temp = (bitboard.Kingmove[sq] & bitboard.notfriendlyboard[side]);
    temp = temp | p;
    return temp;

}

//***************************************************************************
int generateAllMoves(node *present,int ply,U64 Pieces[2][7])
{

 int moves=0;
 int side = bitboard.side;
 genUtilBoards(Pieces);

 U64 currentPiece = Pieces[side][knight];
 while (currentPiece.check())
  {
   int sq = currentPiece.getAndClearLSB();
   moves+=bitboardToMoves(present,genKnightAttackBoard(sq),knight,sq,ply);
  }

 genUtilBoards(Pieces);
 currentPiece = Pieces[side][bishop];
 while (currentPiece.check())
  {
   int sq = currentPiece.getAndClearLSB();
   moves+=bitboardToMoves(present,genBishopAttackBoard(sq),bishop,sq,ply);
  }

	genUtilBoards(Pieces);
 currentPiece =Pieces[side][rook];
 while (currentPiece.check())
  {
   int sq = currentPiece.getAndClearLSB();
   moves+=bitboardToMoves(present,genRookAttackBoard(sq),rook,sq,ply);
  }

	genUtilBoards(Pieces);
 currentPiece = Pieces[side][queen];
 while (currentPiece.check())
  {
   int sq = currentPiece.getAndClearLSB();
   moves+=bitboardToMoves(present,genQueenAttackBoard(sq),queen,sq,ply);
  }

	genUtilBoards(Pieces);
 currentPiece = Pieces[side][pawn];
 while (currentPiece.check())
  {
   int sq = currentPiece.getAndClearLSB();
   moves+=bitboardToMoves(present,genPawnAttackBoard(side,sq),pawn,sq,ply);
  }

	genUtilBoards(Pieces);
 currentPiece = Pieces[side][king];
 while (currentPiece.check())
  {
   int sq = currentPiece.getAndClearLSB();
   moves+=bitboardToMoves(present,genKingAttackBoard(sq),king,sq,ply);
  }
  //cout<<"king:" << moves <<endl;
 return moves;
}

//***************************************************************************
int bitboardToMoves(node* present,U64 board, int piece, int fromsq, int ply)
{
 int moves=0;

 while (board.check())
   {
    int tosq = board.getAndClearLSB();
    if (!addMove(present,piece,fromsq,tosq, ply)) return 0; //checkmate!
    else moves++;
   }

 return moves;
}

void genattackboard(int side,U64 Pieces[2][7])
{
	U64 temp;
	U64 currentPiece = Pieces[side][knight];
 	while (currentPiece.check())
  	{
   		int sq = currentPiece.getAndClearLSB();
   		temp =	temp  | genKnightAttackBoard(sq);
		//temp.display();
  	}
	
 	currentPiece = Pieces[side][bishop];
 	while (currentPiece.check())
 	{
   		int sq = currentPiece.getAndClearLSB();
   		temp = temp | genBishopAttackBoard(sq);
  	}

 	currentPiece = Pieces[side][rook];
 	while (currentPiece.check())
  	{
   		int sq = currentPiece.getAndClearLSB();
   		temp = temp | genRookAttackBoard(sq);
  	}

 	currentPiece = Pieces[side][queen];
	 while (currentPiece.check())
 	 {
   		int sq = currentPiece.getAndClearLSB();
   		temp = temp | genQueenAttackBoard(sq);
  	}

 	currentPiece = Pieces[side][pawn];
	while (currentPiece.check())
 	{
  	 	int sq = currentPiece.getAndClearLSB();
   		temp = temp | bitboard.Pawnsattackmove[sq][side];
 	}

 	currentPiece = Pieces[side][king];
 	while (currentPiece.check())
  	{
   		int sq = currentPiece.getAndClearLSB();
   		temp = temp | genKingAttackBoard(sq);
  	}
	//temp.display();
	bitboard.attackboard[side] = temp;
}

//***************************************************************************
void genUtilBoards(U64 Pieces[2][7])
{
 int side  = bitboard.side;
 int nside = bitboard.side^1;

 bitboard.enemyboard[side] =  Pieces[nside][pawn]   | Pieces[nside][knight] |
			      Pieces[nside][bishop] | Pieces[nside][rook]   |
			      Pieces[nside][queen]  | Pieces[nside][king];

 bitboard.friendlyboard[side] =Pieces[side][pawn]   | Pieces[side][knight] |
                         Pieces[side][bishop] | Pieces[side][rook]   |
                         Pieces[side][queen]  | Pieces[side][king];


 bitboard.occupiedboard[side] = bitboard.enemyboard[side] | bitboard.friendlyboard[side];
 bitboard.unoccupiedboard[side] = ~bitboard.occupiedboard[side];

 bitboard.notfriendlyboard[side] = bitboard.unoccupiedboard[side] | bitboard.enemyboard[side];
	

/////////////////////////////////////////////////////////////////////////
bitboard.enemyboard[nside] =  Pieces[side][pawn]   | Pieces[side][knight] |
                        Pieces[side][bishop] | Pieces[side][rook]   |
                        Pieces[side][queen]  | Pieces[side][king];


 bitboard.friendlyboard[nside] =Pieces[nside][pawn]   | Pieces[nside][knight] |
                         Pieces[nside][bishop] | Pieces[nside][rook]   |
                         Pieces[nside][queen]  | Pieces[nside][king];


 bitboard.occupiedboard[nside] = bitboard.enemyboard[nside] | bitboard.friendlyboard[nside];
 bitboard.unoccupiedboard[nside] = ~bitboard.occupiedboard[nside];

 bitboard.notfriendlyboard[nside] = bitboard.unoccupiedboard[nside] | bitboard.enemyboard[nside];

	genattackboard(side,Pieces);
	bitboard.side=nside;	
	genattackboard(nside,Pieces);
	bitboard.side=side;
}

//***************************************************************************
inline U64 genRookAttackBoard(int sq)
{    
	bool side=bitboard.side;
 U64 leftboard = (bitboard.occupiedboard[side] & bitboard.left_board[sq]);
 leftboard = (leftboard>>1)|(leftboard>>2)|(leftboard>>3)|(leftboard>>4)|(leftboard>>5)|(leftboard>>6);
 leftboard = (leftboard & bitboard.left_board[sq])^bitboard.left_board[sq];

 U64 rightboard = (bitboard.occupiedboard[side] & bitboard.right_board[sq]);
 rightboard = (rightboard<<1)|(rightboard<<2)|(rightboard<<3)|(rightboard<<4)|(rightboard<<5)|(rightboard<<6);
 rightboard = (rightboard & bitboard.right_board[sq]) ^ bitboard.right_board[sq];

 U64 upboard = (bitboard.occupiedboard[side] & bitboard.up_board[sq]);
 upboard = (upboard<<8)|(upboard<<16)|(upboard<<24)|(upboard<<32)|(upboard<<40)|(upboard<<48);
 upboard = (upboard & bitboard.up_board[sq]) ^ bitboard.up_board[sq];

 U64 downboard = (bitboard.occupiedboard[side] & bitboard.down_board[sq]);
 downboard = (downboard>>8)|(downboard>>16)|(downboard>>24)|(downboard>>32)|(downboard>>40)|(downboard>>48);
 downboard = (downboard & bitboard.down_board[sq]) ^ bitboard.down_board[sq];

 return (leftboard | rightboard | upboard | downboard) & bitboard.notfriendlyboard[side];
}

//***************************************************************************
inline U64 genBishopAttackBoard(int sq)
{
	bool side=bitboard.side;
 U64 board45 = (bitboard.occupiedboard[side] & bitboard._45deg_board[sq]);
 board45 = (board45<<9)|(board45<<18)|(board45<<27)|(board45<<36)|(board45<<45)|(board45<<54);
 board45 = (board45 & bitboard._45deg_board[sq]) ^ bitboard._45deg_board[sq];

 U64 board135 = (bitboard.occupiedboard[side] & bitboard._135deg_board[sq]);
 board135 = (board135<<7)|(board135<<14)|(board135<<21)|(board135<<28)|(board135<<35)|(board135<<42);
 board135 = (board135 & bitboard._135deg_board[sq]) ^ bitboard._135deg_board[sq];

 U64 board225 = (bitboard.occupiedboard[side] & bitboard._225deg_board[sq]);
 board225 = (board225>>9)|(board225>>18)|(board225>>27)|(board225>>36)|(board225>>45)|(board225>>54);
 board225 = (board225 & bitboard._225deg_board[sq]) ^ bitboard._225deg_board[sq];

 U64 board315 = (bitboard.occupiedboard[side] & bitboard._315deg_board[sq]);
 board315 = (board315>>7)|(board315>>14)|(board315>>21)|(board315>>28)|(board315>>35)|(board315>>42);
 board315 = (board315 & bitboard._315deg_board[sq]) ^ bitboard._315deg_board[sq];

 return (board45 | board135 | board225 | board315) & bitboard.notfriendlyboard[side];
}

//***************************************************************************
inline U64 genQueenAttackBoard(int sq)
{
 return genRookAttackBoard(sq) | genBishopAttackBoard(sq);
}

//***************************************************************************
inline U64 genPawnAttackBoard(int side,int sq)
{

	//move 1 forward
	U64 pawnmoves = (bitboard.Pawnsmove[sq][side] & bitboard.unoccupiedboard[side]);
	//move 2 forward
	if(pawnmoves.check()) {
		pawnmoves = pawnmoves | (bitboard.Pawnsdoublemove[sq][side] & bitboard.unoccupiedboard[side]);
	}
	//captures
	pawnmoves = pawnmoves |(bitboard.Pawnsattackmove[sq][side] & bitboard.enemyboard[side]);

	return pawnmoves;
}

//***************************************************************************
