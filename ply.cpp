#include "ply.h"
#include "main.cpp"

void U64cpy(U64 Pieces[2][7],U64 Pie[2][7])
{
	for(int i=0;i<2;i++)
	      for(int j=0;j<7;j++)
			Pieces[i][j]=Pie[i][j];
}


node* createroot(U64 Pieces[2][7])
{
	node* ro = new node;
	U64cpy(ro->Pieces,Pieces);
	U64cpy(ro->Config,Pieces);
	ro->ply = 0;
	return ro;
}

void update(node* pres,node* temp,int piece,int fromsq,int tosq,int ply)
{
      int side=bitboard.side;
      int nside=side^1;

      U64 var1;
	var1=fromsq;
      U64 var2;
	var2=tosq;
      
      U64 current;
      var1=~(var1);

      temp->Pieces[side][piece] = (pres->Pieces[side][piece]) & var1;
      
	if(piece==pawn && (tosq/8==0 || tosq/8==7))
		temp->Pieces[side][queen]=  (temp->Pieces[side][piece]) | var2;
      else
      		temp->Pieces[side][piece]=  (temp->Pieces[side][piece]) | var2;
      
      for(int i=1;i<8;i++){
	      if(i!=piece)
		temp->Pieces[side][i] = pres->Pieces[side][i];

	      current=pres->Pieces[nside][i];
	      temp->Pieces[nside][i]=(~var2) & pres->Pieces[nside][i];
      }
}

int checkifcheck(U64 Pieces[2][7],int team)
{
    int side=bitboard.side;
    int nside= side^1;
  
    genUtilBoards(Pieces);
    
    U64 opponent,itself;
    opponent=Pieces[nside][king] & bitboard.attackboard[side];

    itself = Pieces[side][king] & bitboard.attackboard[nside];

    
    if(team==1){
	if(opponent.check()){
	    return 75;
	}
	else 
	    return 0;
    }
    else{ 
	if(itself.check()){
	    return 1;
	}
	else
	    return 0;
    }
}



int checkifmate(U64 Pieces[2][7])
{
    int side=bitboard.side;
    int nside=side^1;
    
    bitboard.side=nside;
  
    node* checking = createroot(Pieces);
//	cat = 1;
    generateAllMoves(checking,1,checking->Pieces);
//	cat = 0;
    bitboard.side = side;
    
    if(checking->no_of_child==0)
	      return 1;
    else
	      return 0;
}

int addMove(node* present,int piece,int fromsq,int tosq,int ply)
{
	node *temp;
	temp = new node;
	
	update(present,temp,piece,fromsq,tosq,ply);
	int kingcheck=checkifcheck(temp->Pieces,0);		//itself king //check
	    
	if(kingcheck){
		bitboard.kngchk[piece] |= tosq; 
	}else{
		temp->parent = present;
		int beta = present->no_of_child;
		beta++;
		present->child[beta]=temp;
		present->no_of_child=beta;
		temp->ply=ply;
		//temp->piece=piece;	
	}
	
	int score;
	score=PositionalScore(temp->Pieces); 
	
	kingcheck=checkifcheck(temp->Pieces,1);                  	//opponent king check	
	if(kingcheck)
	      score = score + kingcheck;
	
	if(piece == king && abs(fromsq-tosq)==2)
		score = score+100;

	if(ply%2==1)
	    temp->score=((present->score)+score);
	else
	    temp->score=((present->score)-score);
	

	//cout<<fromsq<<" "<<tosq<<" "<<"present score "<<present->score<<"  "<<temp->score <<"ply " <<ply<<endl;
	
	if(ply==1){
		temp->fromsq = fromsq;
		temp->tosq = tosq;
		U64cpy(temp->Config,temp->Pieces);
	}
	else{
		temp->fromsq = present->fromsq;
		temp->tosq = present->tosq;
		U64cpy(temp->Config,present->Config);
	}

	return 1;
}

node* minimax(node *ro,int ply)
{    
    if (ro->no_of_child==0 || ply==0){
        return ro;
  }

    node* maximum = new node;
	maximum->score =  3489099;
    
    for(int i=1;i<=ro->no_of_child;i++){
	  node * val = minimax(ro->child[i],ply-1);
	    if(maximum->score > -1*val->score){
	      maximum = val;
	      maximum->score *= -1; 
	   }
    }

    return maximum;
}

void scoreforcheckmate(node* ro,int ply)
{
	if(ro->no_of_child==0 && ply!=0)
		ro->score = ro->score + 123456;
	
	for(int i=1;i<ro->no_of_child;i++)
		scoreforcheckmate(ro->child[i],ply-1);
	
}


void blackupdate(int fromsq, int tosq)
{

      int side=bitboard.side;
      int nside=side^1;

      U64 var1;
      var1=fromsq;
      U64 var2;
	var2=tosq;
      
      int piece;
      U64 current;
      for(int i=1;i<8;i++){
	      current= bitboard.Pieces[side][i] & var1;
	      if(current.check())
			piece=i;
      }
	    
      var1=~var1;
      bitboard.Pieces[side][piece]=  bitboard.Pieces[side][piece]  & var1;
      if(piece==pawn && (tosq/8==0 || tosq/8==7))
		bitboard.Pieces[side][queen]=  bitboard.Pieces[side][piece]  | var2;
      else
      		bitboard.Pieces[side][piece]=  bitboard.Pieces[side][piece]  | var2;
   
      
      for(int i=1;i<8;i++){
	      current=bitboard.Pieces[nside][i];
	      bitboard.Pieces[nside][i]=(~var2)&bitboard.Pieces[nside][i];
      }
    
}
void choosebestmoveupdate(node *ro,int ply)
{
	scoreforcheckmate(ro,ply);
	node* final;
	final=minimax(ro,ply);
	int x, y;
	x = final->fromsq;
	y = final->tosq;

	finalupdateGUI(x,y);
	U64cpy(bitboard.Pieces,final->Config);
	
	if(final->fromsq==3 || final->fromsq == 59){
		castling[bitboard.side][0]=0;
		castling[bitboard.side][1]=0;
	}
		
	if(final->fromsq==0 || final->fromsq==56)
		castling[bitboard.side][0]=0;
	
	if(final->fromsq==7 || final->fromsq==63){
		castling[bitboard.side][1]=0;
	}
	
	int side =bitboard.side;
	int nside= side^1;

	if(final->tosq==0 || final->tosq==56)
		castling[nside][0]=0;

	if(final->tosq==7 || final->tosq==63)
		castling[nside][1]=0;
	
	//cout<<"pice:"<<final->piece<<"xx"<<x<<"yy"<<y<<endl;	
	if((final->fromsq==3 || final->fromsq == 59) && abs(x-y)==2){
			cout<<"inside";
			if(x>y){
				blackupdate(y-1,y+1);
		      		finalupdateGUI(y-1,y+1);
			}
			else{
				blackupdate(y+2,y-1);	
				finalupdateGUI(y+2,y-1);
			}
	}
}

void think(node* ro,int ply)
{
      node* present = ro;
 //     cat = 0;
      generateAllMoves(present,ply,present->Pieces);
      int side;
      
      
      if(ply<3){
	      side = bitboard.side;
	      bitboard.side=side^1;
	      for(int i=1;i<=present->no_of_child;i++){
		  think(present->child[i],ply+1);      
	      }
	      bitboard.side = side;
      }
      
}


