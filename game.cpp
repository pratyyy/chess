#include "chess.cpp"
#include "movegen.cpp"
#include "eval.cpp"
#include "ply.cpp"

using namespace std;

void* func1(void* treadid)
{
  bitboard.validmove();
  initialise();
  initialispositions();

    for(int i=0;i<2;i++)
	for(int j=0;j<2;j++)
		castling[i][j]=1;

  string s;
  int from,to;
  bitboard.side=white;
 
    
  while(true)
  {
	blackchance =0;
	int ply=1;
	root = createroot(bitboard.Pieces);
	think(root,ply);
	while(screenvar!=0){};
	choosebestmoveupdate(root,3);

	for(int i=1;i<=6;i++){
		bitboard.kngchk[i].l = 0x0000;
		bitboard.kngchk[i].h = 0x0000;
	}

	int kingcheck=checkifmate(bitboard.Pieces);                  	//opponent king check	
	genUtilBoards(bitboard.Pieces);

	if(kingcheck){
	      cout<<"black is checkmate\nWhite Wons\n";
	      endgameGUI(2);
	      break;
	}
	cout<<endl;
	if(anim==1){
		byeye=-3.0; bzeye= 5.0;
	}
	blackchance = 1;

	bitboard.side=black;
 
	//black chance///
  	while(blackchance==1){};	

	if(froms==3 || froms==59){
		castling[bitboard.side][0]=0;
		castling[bitboard.side][1]=0;
	}
	if( froms==0 || froms==56)
		castling[bitboard.side][0]=0;
	else if(froms==7 || froms== 63)
		castling[bitboard.side][1]=0;

	int side=bitboard.side;
	int nside = side^1;
	if(tos==0 || tos==56)
		castling[nside][0]=0;

	
	if(tos==7 || tos==63)
		castling[nside][1]=0;

	allowedred[froms%8][froms/8]= 0.2;
	allowedred[tos%8][tos/8]= 0.2;
	blackupdate(froms,tos);

	if(posii==27 && abs(froms-tos)==2){
		if(froms>tos){
			froms=tos-1;
			tos=tos+1;		
		}
		else{
			froms=tos+2;
			tos=tos-1;	
		}	
		
		allowedred[froms%8][froms/8]= 0.2;
		allowedred[tos%8][tos/8]= 0.2;
		blackupdate(froms,tos);
		finalupdateGUI(froms,tos);
	}
	
	kingcheck=checkifmate(bitboard.Pieces);                  	//opponent king check	
	
	genUtilBoards(bitboard.Pieces);
	if(kingcheck){
	      cout<<"white is checkmate\nBlack Wons\n";
		endgameGUI(1);
	      break;
	}
	bitboard.side=white;
	cout<<endl;
  }
	pthread_exit(NULL);	
}


void* func2(void* threadid)
{
	mainnn();                           // the main glut function present in main.cpp
}


//////main function//////
int main(int argc, char** argv)
{
	glutInit(&argc, argv); 
	pthread_t thread1,thread2;
	int pid1,pid2;
	int t=0;
	void * status;

	//First Thread for the execution of the game //////
	pid1=pthread_create(&thread1,NULL,func1, (void*)t);
	if(pid1){
		cout<<"Error in thread1"<<endl;
		exit(0);
	}

	////Second Thread for the graphical display/////
	pid2=pthread_create(&thread2,NULL,func2,(void*)t);
	if(pid2){
		cout<<"Error in thread2"<<endl;
		exit(0);
	}
	

	pthread_join(thread1,&status);
	pthread_join(thread2,&status);

	cout<<"end";
	return 0;
}  
