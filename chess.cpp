#include<iostream>
#include<cmath>
#include<stdio.h>
#include<string.h>
#include<algorithm>

#include "chess.h"

using namespace std;

// map initialisation to convert loaction into square no////
void initialise()
{
	m.insert ( pair<string,int>("a1",7) );
	m.insert ( pair<string,int>("b1",6) );
	m.insert ( pair<string,int>("c1",5) );
	m.insert ( pair<string,int>("d1",4) );
	m.insert ( pair<string,int>("e1",3) );
	m.insert ( pair<string,int>("f1",2) );
	m.insert ( pair<string,int>("g1",1) );
	m.insert ( pair<string,int>("h1",0) );

	m.insert ( pair<string,int>("a2",15) );
	m.insert ( pair<string,int>("b2",14) );
	m.insert ( pair<string,int>("c2",13) );
	m.insert ( pair<string,int>("d2",12) );
	m.insert ( pair<string,int>("e2",11) );
	m.insert ( pair<string,int>("f2",10) );
	m.insert ( pair<string,int>("g2",9) );
	m.insert ( pair<string,int>("h2",8) );

	m.insert ( pair<string,int>("a3",23) );
	m.insert ( pair<string,int>("b3",22) );
	m.insert ( pair<string,int>("c3",21) );
	m.insert ( pair<string,int>("d3",20) );
	m.insert ( pair<string,int>("e3",19) );
	m.insert ( pair<string,int>("f3",18) );
	m.insert ( pair<string,int>("g3",17) );
	m.insert ( pair<string,int>("h3",16) );
	
	m.insert ( pair<string,int>("a4",31) );
	m.insert ( pair<string,int>("b4",30) );
	m.insert ( pair<string,int>("c4",29) );
	m.insert ( pair<string,int>("d4",28) );
	m.insert ( pair<string,int>("e4",27) );
	m.insert ( pair<string,int>("f4",26) );
	m.insert ( pair<string,int>("g4",25) );
	m.insert ( pair<string,int>("h4",24) );

	m.insert ( pair<string,int>("a5",39) );
	m.insert ( pair<string,int>("b5",38) );
	m.insert ( pair<string,int>("c5",37) );
	m.insert ( pair<string,int>("d5",36) );
	m.insert ( pair<string,int>("e5",35) );
	m.insert ( pair<string,int>("f5",34) );
	m.insert ( pair<string,int>("g5",33) );
	m.insert ( pair<string,int>("h5",32) );

	m.insert ( pair<string,int>("a6",47) );
	m.insert ( pair<string,int>("b6",46) );
	m.insert ( pair<string,int>("c6",45) );
	m.insert ( pair<string,int>("d6",44) );
	m.insert ( pair<string,int>("e6",43) );
	m.insert ( pair<string,int>("f6",42) );
	m.insert ( pair<string,int>("g6",41) );
	m.insert ( pair<string,int>("h6",40) );

	m.insert ( pair<string,int>("a7",55) );
	m.insert ( pair<string,int>("b7",54) );
	m.insert ( pair<string,int>("c7",53) );
	m.insert ( pair<string,int>("d7",52) );
	m.insert ( pair<string,int>("e7",51) );
	m.insert ( pair<string,int>("f7",50) );
	m.insert ( pair<string,int>("g7",49) );
	m.insert ( pair<string,int>("h7",48) );

	m.insert ( pair<string,int>("a8",63) );
	m.insert ( pair<string,int>("b8",62) );
	m.insert ( pair<string,int>("c8",61) );
	m.insert ( pair<string,int>("d8",60) );
	m.insert ( pair<string,int>("e8",59) );
	m.insert ( pair<string,int>("f8",58) );
	m.insert ( pair<string,int>("g8",57) );
	m.insert ( pair<string,int>("h8",56) );

}


int equivalent(string s)
{
    return m.find(s)->second;
}

//Declaration of all the oveloaded function defined in chess.h////
U64 U64::operator |(U64 ob){
	U64 temp;
	temp.l= l | ob.l;
	temp.h= h | ob.h;
	return temp;
}

U64 U64::operator &(U64 ob){
	U64 temp;
	temp.l= l & ob.l;
	temp.h= h & ob.h;
	return temp;
 }

U64 U64::operator ^(U64 ob){
	U64 temp;
	temp.l= l ^ ob.l;
	temp.h= h ^ ob.h;
	return temp;
}

U64 U64::operator ~()
{	U64 temp;
	temp.l = ~l;
	temp.h = ~h;
	return temp;
}

void U64::operator =(int sq){
	if(sq <32)
		l = (int)pow(2.0, sq);
	else
		h = (int)pow(2.0, sq-32);
}

void U64::operator |=(int sq){
	if(sq <32)
		l |= (int)pow(2.0, sq);
	else
		h |= (int)pow(2.0, sq-32);
}


U64 U64::operator <<(int a){	
	U64 oc;	
	U32 temp,temp1;
	oc.l=l;
	oc.h=h;
	temp = (int)pow(2.0, 31);
	for(int i=0;i<a;i++){
		temp1 = oc.l & temp;
		oc.l = oc.l << 1;
		oc.h = oc.h<< 1;
		if(temp1!=0)
			oc.h |= (int)pow(2.0, 0);	
	}	
	return oc;
}

U64 U64::operator >>(int a){	
	U64 oc;	
	U32 temp,temp1;
	oc.l=l;
	oc.h=h;
	temp = (int)pow(2.0, 0);
	for(int i=0;i<a;i++){
		temp1 = oc.h & temp;
		oc.l = oc.l >> 1;
		oc.h = oc.h >> 1;
		if(temp1!=0){
			temp1 = (int)pow(2.0, 31);
			oc.l |= temp1;
		}	
	}	
	return oc;
}

///Declaration of other functions ////
void U64::display()
  {	
      int pos=8;
      cout<<pos<<"  ";
    for(int i=31;i>=0;i--){
	    U32 var=(int)pow(2.0,(i));
	    U32 check=var&h;
	    if(check==var)
		    cout<<1<<" ";
	    else
		    cout<<0<<" ";
	    if(i%8==0){
		    cout<<endl;
		    cout<<--pos<<"  ";
	    }
    }
 
    for(int i=31;i>=0;i--){
	    U32 var=(int)pow(2.0,(i));
	    U32 check=var&l;
	    if(check==var)
		    cout<<1<<" ";
	    else
		    cout<<0<<" ";
	    if(i%8==0){
		    cout<<endl;
		    if(pos!=1)
		    cout<<--pos<<"  ";
	    }
    }
    
    cout<<"\n   A B C D E F G H \n";
}


int U64::getAndClearLSB()
{
	if (l!=0) {
		for(int i=0;i<32;i++){
	    		U32 var=(int)pow(2.0,(i));
	   	 	U32 check=var&l;
	    		if(check==var){
			    l = l^check;
		 	   return i;
			}
		}
	} else if (h!=0) {
		for(int i=0;i<32;i++){
	    		U32 var=(int)pow(2.0,(i));
	   	 	U32 check=var&h;
	    		if(check==var){
			    h = h^check;
		 	   return i+32;
			}
		}
	}

	return -1;
}


//Generates the Valid move of each piece from each square and store in bitboard///
void CBoard::validmove()
{
	//White Pawn moves..
    for(int i=8;i<16;i++){
	  Pawnsmove[i][white] |= (i+8);
	  Pawnsdoublemove[i][white] |= (i+16);
	  if(i%8==0)
		Pawnsattackmove[i][white] |= (i+9);
	  else if ((i+1)%8==0)
		Pawnsattackmove[i][white] |= (i+7);
	  else{
		Pawnsattackmove[i][white] |= (i+7);
		Pawnsattackmove[i][white] |= (i+9);
	}
    }
    for(int i=16;i<56;i++){
	  Pawnsmove[i][white] |= (i+8);
	  if(i%8==0)
		Pawnsattackmove[i][white] |= (i+9);
	  else if ((i+1)%8==0)
		Pawnsattackmove[i][white] |=  (i+7);
	  else{
		Pawnsattackmove[i][white] |= (i+7);
		Pawnsattackmove[i][white] |= (i+9);
	}
    }
  
    // Black Pawn Move
    for(int i=48;i<56;i++){
	  Pawnsmove[i][black] |= (i-8);
	  Pawnsdoublemove[i][black] |= (i-16);
	  if(i%8==0)
		Pawnsattackmove[i][black] |= (i-7);
	  else if ((i+1)%8==0)
		Pawnsattackmove[i][black] |= (i-9);
	  else{
		Pawnsattackmove[i][black] |= (i-7);
		Pawnsattackmove[i][black] |= (i-9);
 		}   
	}
    for(int i=8;i<48;i++){
	  Pawnsmove[i][black] |= (i-8);
	  if(i%8==0)
		Pawnsattackmove[i][black]=(i-7);
	  else if ((i+1)%8==0)
		Pawnsattackmove[i][black]=(i-9);
	  else{
		Pawnsattackmove[i][black] |= (i-7);
		Pawnsattackmove[i][black] |= (i-9);
 		} 
		
    }

    int possibleMoves[10];
     /*------------------------ Knights valid Moves ----------------------------------*/
    for(int i = 0; i < 64; i++) {
        possibleMoves[0] = i + 10;
	possibleMoves[1] = i +  6;
        possibleMoves[2] = i + 17;
        possibleMoves[3] = i + 15;
        possibleMoves[4] = i - 10;
        possibleMoves[5] = i -  6;
        possibleMoves[6] = i - 17;
        possibleMoves[7] = i - 15;
	
	for(int j = 0; j < 8; j++) {
            if ( possibleMoves[j] < 0 || possibleMoves[j] > 63 ) {
	  	continue;
            }
            switch(abs(possibleMoves[j]/8 - i/8)) {
                case 1:
                    if ( abs(i%8 - possibleMoves[j]%8) != 2 ) 
                        continue;
                    else
			Knightsmove[i] |= possibleMoves[j];
		    break;
                case 2:
                    if ( abs(i%8 - possibleMoves[j]%8) != 1 ) 
                        continue;
                    else
			Knightsmove[i] |= possibleMoves[j];
		    
                    break;
                default:
                    continue;
            }
     }
    }
      /*   -----------------------------------------Knight's valid moves over-------------------------------*/
     /*---------------------------------------------Rooks valid Moves ----------------------------------*/
    
    for(int i=0;i<64;i++){
	  int rank=i/8;
	  int file=i%8;
	  
	  for(int j=file+1;j<8;j++)
			  right_board[i] |= (8*rank+j);

	  for(int j=0;j<file;j++)
			  left_board[i] |= (8*rank+j);
	
	  for(int j=8*rank+file+8;j<64;j=j+8)
			  up_board[i] |= (j);

	  for(int j=8*rank+file-8;j>=0;j=j-8)
			  down_board[i] |= (j);

    }	
      /*   -----------------------------------------Rook's valid moves over---------------------------*/
//           ---------------------------------------Bishop's valid moves ----------------------------     
    for(int i=0;i<64;i++){
	  int rank=i/8;
	  int file=i%8;
	
	  for(int j=rank+1;j<8;j++){
			    if((j-rank+file)<8 && (j-rank+file)>=0)
				_45deg_board[i] |= (8*j+j-rank+file);
			    if((j-rank+file-2*(j-rank))<8 && j-rank+file-2*(j-rank)>=0)
				_135deg_board[i] |= (8*j+j-rank+file-2*(j-rank));
	  }
	        
	  for(int j=rank-1;j>=0;j--){
			   if((j-rank+file)<8 && (j-rank+file)>=0)
				  _225deg_board[i] |= (8*j+(j-rank+file));
			  if((j-rank+file-2*(j-rank))<8 && j-rank+file-2*(j-rank)>=0)
				  _315deg_board[i] |= (8*j+(j-rank+file-2*(j-rank)));
	  }        
    }
    
//   ---------------------------Bishop's valid moves over--------------------------------
// -------------------------------King's valid move ----------------------------------------------------
   
    for(int i=0;i<8;i++){
	  Kingmove[i] |= (i+8);
	  if(i%8==0){
		Kingmove[i] |= (i+9); 
		Kingmove[i] |= (i+1);
	  }else if ((i+1)%8==0){
		Kingmove[i] |= (i+7); 
		Kingmove[i] |= (i-1);
	  }else{
		Kingmove[i] |= (i+7);
    		Kingmove[i] |= (i+9);
		Kingmove[i] |= (i+1);
		Kingmove[i] |= (i-1);
	  }
    }
    
    for(int i=8;i<56;i++){
	  Kingmove[i] |= (i+8);
	  Kingmove[i] |= (i-8);
	  if(i%8==0){
		Kingmove[i] |= (i-7);
	  	Kingmove[i] |= (i+1);
		Kingmove[i] |= (i+9);
	  }
	  else if ((i+1)%8==0){
		Kingmove[i] |= (i-9);
	  	Kingmove[i] |= (i-1);
		Kingmove[i] |= (i+7);
	  }
	  else{
		Kingmove[i] |= (i-7);
	  	Kingmove[i] |= (i+1);
		Kingmove[i] |= (i+9);
		Kingmove[i] |= (i-9);
	  	Kingmove[i] |= (i-1);
		Kingmove[i] |= (i+7);
	  }
    }

    for(int i=56;i<64;i++){
	  Kingmove[i] |= (i-8);
	  	  
	  if(i%8==0){
		Kingmove[i] |= (i-7);
		Kingmove[i] |= (i+1);
	  }	
	 
	  else if ((i+1)%8==0){
		Kingmove[i] |= (i-9);
		Kingmove[i] |= (i-1);
	  }			
	  else{
		Kingmove[i] |= (i-7);
		Kingmove[i] |= (i-9);
		Kingmove[i] |= (i+1);
		Kingmove[i] |= (i-1);
	  }
	  
    }
  
}


///Intial positions of various pieces////

CBoard::CBoard()
{   
   Pieces[white][pawn].l=  0xff00; 
   Pieces[white][knight].l= 0x0042;
   Pieces[white][bishop].l=0x0024;
   Pieces[white][rook].l=  0x0081;
   Pieces[white][queen].l= 0x0010;
   Pieces[white][king].l=   0x0008;

 
   Pieces[black][pawn].h   =  0x00ff0000;
   Pieces[black][knight].h  =0x42000000;
   Pieces[black][bishop].h  =0x24000000;
   Pieces[black][rook].h    =  0x81000000;
   Pieces[black][queen].h  = 0x10000000;
   Pieces[black][king].h    =   0x08000000;

 
   fullboard[0].l=0xffffffff;
   fullboard[0].h=0xffffffff;
   fullboard[1].l=0xffffffff;
   fullboard[1].h=0xffffffff;

}


