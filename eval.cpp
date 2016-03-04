#include "eval.h"

int doubledPawn(int sq,U64 Pieces[2][7])
{
	bool side = bitboard.side;
	int file = sq%8;
	U64 checkdoubledpawn;
	checkdoubledpawn = bitboard.up_board[sq] | bitboard.down_board[sq];
	
	//checkdoubledpawn.display();
	//bitboard.doubledpawn[side] = (Pieces[side][pawn] & checkdoubledpawn);
	if( !(Pieces[side][pawn] & checkdoubledpawn).check() )
		return 0;
	else	
		return 12;
}

int isolatedPawn(int sq,U64 Pieces[2][7])
{
	bool side = bitboard.side;
	int file = sq%8;
	U64 checkisolatedpawn;
	for(int i=0; i<8; i++){
		int index = file + 8*i;
		if(file%8 != 0)
			checkisolatedpawn |= index-1;
		if(file%8 != 7)
			checkisolatedpawn |= index+1;
	}

	//checkisolatedpawn.display();		
	//bitboard.isolatedpawn[side] = (Pieces[side][pawn] & checkisolatedpawn);                 ////////to check;
 	if( !(Pieces[side][pawn] & checkisolatedpawn).check() )
		return isolatedpawnspenalty[file];
	else	
		return doubledPawn(sq,Pieces);
}


int backwardPawn(int sq,U64 Pieces[2][7])
{
	bool side = bitboard.side;
	int file = sq%8;
	U64 checkbackwardpawn;
	if(sq>7){
		if(file!=0)
			checkbackwardpawn = sq -8 -1;
		if(file!=7)
			checkbackwardpawn = sq -8 +1;
	}
	//bitboard.backwardpawn[side] = (bitboard.Pieces[side][pawn] & checkbackwardpawn);
	if( !(Pieces[side][pawn] & checkbackwardpawn).check() )
		return 0;
	else	
		return 6;	
}

int attacktobackward(int sq)
{
	bool side = bitboard.side;
	bool nside = side^1;
	U64 temp;
	int score=0;
	temp = sq;
	temp = temp & bitboard.attackboard[nside];
	
	if(!temp.check())
		return 0;
	else{
		while(temp.check()){
			temp.getAndClearLSB();
			score=score+4;
		}
	}
	
	return score;	
}

int halfopenfile(int sq)
{
	return 0;
}


int AttackingScore(int piece,int color,int sq)
{
  int score=0;
  U64 current;
  switch(piece){
      case pawn:
		  break;
      case knight:
		  current=genKnightAttackBoard(sq);
		  break;
      case bishop:
		  current=genBishopAttackBoard(sq);
		  break;
      case queen:
		  current=genQueenAttackBoard(sq);
		  break;
      case rook:
		  current=genRookAttackBoard(sq);
		  break;
      case king:
		  current=genKingAttackBoard(sq);
		  break;
  }

  while(current.check()){
	  int sq=current.getAndClearLSB();
	  score=score+ProtectingPoints[piece];
  }
  
  return score;
}

    
int ProtectingScore(int piece,int color,int sq)
{
  int score=0;
  U64 current;
  U64 board45,board135,board225,board315;
  U64 leftboard,rightboard,upboard,downboard;
  switch(piece){
      case pawn:
		current= (bitboard.Pawnsmove[sq][color] | bitboard.Pawnsdoublemove[sq][color])& bitboard.friendlyboard[color];
		break;
      case knight:
		current= bitboard.Knightsmove[sq] & bitboard.friendlyboard[color];
		break;
  
      case bishop:
		  
 board45 = (bitboard.occupiedboard[color] & bitboard._45deg_board[sq]);
 board45 = (board45<<9)|(board45<<18)|(board45<<27)|(board45<<36)|(board45<<45)|(board45<<54);
 board45 = (board45 & bitboard._45deg_board[sq]) ^ bitboard._45deg_board[sq];

 board135 = (bitboard.occupiedboard[color] & bitboard._135deg_board[sq]);
 board135 = (board135<<7)|(board135<<14)|(board135<<21)|(board135<<28)|(board135<<35)|(board135<<42);
 board135 = (board135 & bitboard._135deg_board[sq]) ^ bitboard._135deg_board[sq];

 board225 = (bitboard.occupiedboard[color] & bitboard._225deg_board[sq]);
 board225 = (board225>>9)|(board225>>18)|(board225>>27)|(board225>>36)|(board225>>45)|(board225>>54);
 board225 = (board225 & bitboard._225deg_board[sq]) ^ bitboard._225deg_board[sq];

 board315 = (bitboard.occupiedboard[color] & bitboard._315deg_board[sq]);
 board315 = (board315>>7)|(board315>>14)|(board315>>21)|(board315>>28)|(board315>>35)|(board315>>42);
 board315 = (board315 & bitboard._315deg_board[sq]) ^ bitboard._315deg_board[sq];

  current=(board45 | board135 | board225 | board315) & bitboard.friendlyboard[color];
		  break;

      case rook:
 leftboard = (bitboard.occupiedboard[color] & bitboard.left_board[sq]);
 leftboard = (leftboard>>1)|(leftboard>>2)|(leftboard>>3)|(leftboard>>4)|(leftboard>>5)|(leftboard>>6);
 leftboard = (leftboard & bitboard.left_board[sq])^bitboard.left_board[sq];

 rightboard = (bitboard.occupiedboard[color] & bitboard.right_board[sq]);
 rightboard = (rightboard<<1)|(rightboard<<2)|(rightboard<<3)|(rightboard<<4)|(rightboard<<5)|(rightboard<<6);
 rightboard = (rightboard & bitboard.right_board[sq]) ^ bitboard.right_board[sq];

 upboard = (bitboard.occupiedboard[color] & bitboard.up_board[sq]);
 upboard = (upboard<<8)|(upboard<<16)|(upboard<<24)|(upboard<<32)|(upboard<<40)|(upboard<<48);
 upboard = (upboard & bitboard.up_board[sq]) ^ bitboard.up_board[sq];

 downboard = (bitboard.occupiedboard[color] & bitboard.down_board[sq]);
 downboard = (downboard>>8)|(downboard>>16)|(downboard>>24)|(downboard>>32)|(downboard>>40)|(downboard>>48);
 downboard = (downboard & bitboard.down_board[sq]) ^ bitboard.down_board[sq]; 
    
 current =(leftboard|rightboard|upboard|downboard) & bitboard.friendlyboard[color];
  break;
    
      case queen:
		  break;
      
      case king:
		current=bitboard.Kingmove[sq] & bitboard.friendlyboard[color];
		break;
}  
	
  while(current.check()){
	  int sq=current.getAndClearLSB();
	  score=score+ProtectingPoints[piece];
  }
  
  //cout<<"protecting"<<score<<"\n";
  return score;
}

int PositionalScore(U64 Pieces1[2][7])
{
  int side=bitboard.side;
  int nside=side^1;

  int score=0;
  U64 currentPiece;

  currentPiece = Pieces1[side][pawn];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score+=PiecePoints[pawn]+PawnTable[sq];//+ProtectingScore(pawn,side,sq);
    score+=isolatedPawn(sq,Pieces1)+backwardPawn(sq,Pieces1)+attacktobackward(sq);
  }
    
 // cout<<"pawn"<<score;
  currentPiece = Pieces1[side][knight];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score+=PiecePoints[knight]+KnightTable[sq];//+ProtectingScore(knight,side,sq);
  }

  //cout<<"knight"<<score;
  currentPiece = Pieces1[side][bishop];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score+=PiecePoints[bishop]+BishopTable[sq];//+ProtectingScore(bishop,side,sq);
  }
  //cout<<"bishop"<<score;
  
  currentPiece = Pieces1[side][rook];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score+=PiecePoints[rook];//+ProtectingScore(rook,side,sq);
  }

  //cout<<"rook"<<score;
  currentPiece = Pieces1[side][queen];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score+=PiecePoints[queen];//+ProtectingScore(queen,side,sq);
  }

  //cout<<"queen"<<score;
  currentPiece = Pieces1[side][king];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score+=PiecePoints[king]+KingTable[sq];//+ProtectingScore(king,side,sq);
  }
  //cout<<"king"<<score;
  
  currentPiece = Pieces1[nside][pawn];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score-=PiecePoints[pawn];//+PawnTable[sq]+AttackingScore(pawn,black,sq);
  }
  
 //cout<<"black pawn "<<score;
  currentPiece = Pieces1[nside][knight];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score-=PiecePoints[knight];//+KnightTable[sq];//+AttackingScore(knight,black,sq);
  }
  
  currentPiece = Pieces1[nside][bishop];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score-=PiecePoints[bishop];//+BishopTable[sq];//+AttackingScore(bishop,black,sq);
  }

  
  currentPiece = Pieces1[nside][rook];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score-=PiecePoints[rook];//+AttackingScore(rook,black,sq);
  }

  
  currentPiece = Pieces1[nside][queen];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score-=PiecePoints[queen];//+AttackingScore(queen,black,sq);
  }
  
  currentPiece = Pieces1[nside][king];
  while (currentPiece.check()){
    int sq = currentPiece.getAndClearLSB();
    score-=PiecePoints[king];//+KingTable[sq];//+AttackingScore(king,black,sq);
  }

  //cout<<"final"<<score<<endl			;
  int mobility=0;
  //int mobility=generateAllMoves(1);
  //cout<<score+mobility;
  return score+mobility;
}
