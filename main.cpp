#include "main.h"
#include <GLKit/GLKMatrix4.h>

void displayGUI(U64 current)
{
    int x, y;
    for(int i=31;i>=0;i--){
	    U32 var=(int)pow(2.0,(i));
	    U32 check=var&current.h;
	    if(check==var){
		    x = (i+32)%8;
		    y = (i+32)/8;
		    if(blackchance == 1)
			allowed[x][y] = 0.2;
	    }
    }
 
    for(int i=31;i>=0;i--){
	    U32 var=(int)pow(2.0,(i));
	    U32 check=var&current.l;
	    if(check==var){
		    x = (i)%8;
		    y = (i)/8;
		    allowed[x][y] = 0.2;
	    }
    }
}

// updates graphically the move ////
void finalupdateGUI(int fromsq, int tosq)
{
	int to = tosq;
	int from =  fromsq;
	int piec=-1, piec1=-1,  sq;
	chkfrom = from;
	chkto = to;
	allowedred[fromsq%8][fromsq/8]= 0.2;
	allowedred[tosq%8][tosq/8]= 0.2;
//	cout << from << "ggbhggf"<< to<<endl;
	for(int i=0; i<32; i++){
		sq = positionpieces[i][xcoord] + (positionpieces[i][ycoord])*8;
		//cout<< "  "<<sq<<endl;
		if(sq == from){
			piec = i;
			//cout<<" "<<sq<<endl;
		}
		if(sq == to){
			piec1 = i;
		}
	}
	if(piec!=-1){
		int Q = (to)%8;
		int R = (to)/8;
		xhite[piec] += (positionpieces[piec][xcoord]-Q)*1.3;
		yhite[piec] += (R-positionpieces[piec][ycoord])*1.3;
		positionpieces[piec][xcoord] = Q;
		positionpieces[piec][ycoord] = R;
	}

	if(piec1 != -1){
		murdered[piec1]  = 1;
		positionpieces[piec1][xcoord] = -100;
		xhite[piec1] = -100000;
	}
}

//// displays the possible moves of the  piece selected ///
void displaypossiblemoves(int position)
{
	int x, y;
	U64 current;
	x = positionpieces[position][xcoord];
	y = positionpieces[position][ycoord];
	int sq = x+ 8*y;
	int i=0;
 	if(position>15 && position <24){
		i = pawn;
		current =  genPawnAttackBoard(1, sq);
	}else if(position == 31 || position == 24){
		i = rook;
		current =  genRookAttackBoard(sq);
	}else if(position == 25 || position == 30){
		i = knight;
		current =  genKnightAttackBoard(sq);
	}else if(position == 26 || position == 29){
		i = bishop;
		current =  genBishopAttackBoard(sq);
	}else if(position == 27){
		i = king;
		current =  genKingAttackBoard(sq);
	}else if(position == 28){
		i = queen;
		current =  genQueenAttackBoard(sq);
	}

	
	U64 ul;
	//bitboard.kngchk[piece].display();
	ul = ~bitboard.kngchk[i];
	current = current & ul;
	//current.display();
	displayGUI(current);

}


void initialispositions()
{
	static int piecs = 0;
	for(int i=0; i<2; i++){
		for(int j=0; j<8; j++){
			positionpieces[piecs][xcoord] =j;
			positionpieces[piecs][ycoord] =i;
			piecs++;
			murderedxhite[j + 8*i] = (-1.3)*(8-j) + i*(-1.3);
		}
	}
	//cout<<"hjhgfd"<<positionpieces[0][1]<<endl;
	for(int i=6; i<8; i++){
		for(int j=0; j<8; j++){
			positionpieces[piecs][xcoord] =j;
			positionpieces[piecs][ycoord] =i;
			piecs++;
		}
	}
	
}

void startPicking() {

	GLint viewport[4];
	float ratio;

	glSelectBuffer(BUFSIZE,selectBuf);
	glGetIntegerv(GL_VIEWPORT,viewport);
	glRenderMode(GL_SELECT);
	glInitNames();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix(cursorX,viewport[3]-cursorY,5,5,viewport);
	//glMultMatrixf(GLKMatrix4MakePerspective(cursorX,viewport[3]-cursorY,5,5,viewport).m);
	ratio = (viewport[2]+0.0) / viewport[3];
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void processHits2 (GLint hits, GLuint buffer[], int sw)
{
   GLint i, j, numberOfNames;
   GLuint names, *ptr, minZ,*ptrNames;

   ptr = (GLuint *) buffer;
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) {	
      names = *ptr;
	  ptr++;
	  if (*ptr < minZ) {
		  numberOfNames = names;
		  minZ = *ptr;
		  ptrNames = ptr+2;
	  }
	  
	  ptr += names+2;
	}
   if (numberOfNames > 0) {
	ptr = ptrNames;
	
	if( *ptr <32){
		posii = *ptr;
		hite[*ptr]=1;
		displaypossiblemoves(posii);
		status = on;
	}else if(*ptr>31 || *ptr < 96 ){
		status = off;
	
		//boardpile[*ptr] = 1;
		int Q = (*ptr)%8;
		int R = (*ptr-32)/8;
	//	cout << *ptr<<  Q<<"  " <<R <<endl;
		xhite[posii] += (positionpieces[posii][xcoord]-Q)*1.3;
		yhite[posii] += (R-positionpieces[posii][ycoord])*1.3;
	
		froms = positionpieces[posii][xcoord] + positionpieces[posii][ycoord]*8;
		tos = (*ptr-32);
		yeye = -10.0;
		blackchance = 0;
		int piec1 =-1;
		for(int i=0; i<32; i++){
			int sq = positionpieces[i][xcoord] + (positionpieces[i][ycoord])*8;
			if(sq == tos){
				piec1 = i;
				break;
			}
		}
		if(piec1 != -1){
			positionpieces[piec1][xcoord] = -100;
			xhite[piec1] = -10000;
			//yhite[piec1] = positionpieces[piec1][ycoord]*1.3;
		}
		positionpieces[posii][xcoord] = Q;
		positionpieces[posii][ycoord] = R;
		//cout<<"chk "<<Q<< " " << R << " "<<endl;
		hite[posii]= 0;
		
	}
	
	
   }else{
	status = off;

	hite[posii] =0;
  }
}

void stopPicking() {

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if (hits != 0){
		processHits2(hits,selectBuf,0);
	}else
		status = off;
	mode = RENDER;
}

void setting()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	//Lights initialization and activation
    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_specular);
    glLightfv (GL_LIGHT1, GL_POSITION, light_position);    
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);

    //Materials initialization and activation
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_specular);
    glMaterialfv (GL_FRONT, GL_POSITION, mat_shininess);    

	//Other initializations
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Texture mapping perspective correction (OpenGL... thank you so much!)
    glEnable(GL_TEXTURE_2D); // Texture mapping ON
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
	glEnable(GL_CULL_FACE); // Enable the back face culling
    glEnable(GL_DEPTH_TEST); // Enable the depth test (also called z buffer)
}

// Intialises the 3d objects and the images (path is specified)////
void init(void)
{
	MatrGenerateLookupTab();
	
	//glScalef(10, 10, 10);
  //  glClearColor(0.0, 0.5, 0.7, 0.0); // Clear background color to black
	glClearColor(0,0,0,0);
    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);
	//loadallimages();

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,10000.0f); // We define the "viewing volume"
    gluLookAt(xeye, yeye, zeye, xlook, ylook, zlook, 0,1,0);

	setting();

	char skull_texture[] = "texture/images/skull.bmp";
	char water_texture[] = "texture/images/water.bmp";
	char rook_obj[] = "texture/set/rook.3ds";
	char knight_obj[] = "texture/set/knight.3ds";
	char bishop_obj[] = "texture/set/bishop.3ds";
	char king_obj[] = "texture/set/king.3ds";
	char queen_obj[] = "texture/set/queen.3ds";
	char pawn_obj[] = "texture/set/pawn.3ds";

	ObjLoad (rook_obj,skull_texture,             4.55, -4.5, -5.95,    0,0,0);
	ObjLoad (knight_obj,skull_texture,             3.25, -4.5, -6.275,    0,0,0);
	ObjLoad (bishop_obj,skull_texture,             1.95, -4.5, -6.275,    0,0,0);
	ObjLoad (king_obj,skull_texture,             0.65, -4.5, -6.275,    0,0,0);
	ObjLoad (queen_obj,skull_texture,             -0.65, -4.5, -6.275,    0,0,0);
	ObjLoad (bishop_obj,skull_texture,             -1.95, -4.5, -6.275,    0,0,0);
	ObjLoad (knight_obj,skull_texture,             -3.25, -4.5, -6.275,    0,0,0);
	ObjLoad (rook_obj,skull_texture,             -4.55, -4.5, -5.95,    0,0,0);
	ObjLoad (pawn_obj,skull_texture,             4.55, -3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,skull_texture,             3.25, -3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,skull_texture,             1.95, -3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,skull_texture,             0.65, -3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,skull_texture,             -0.65, -3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,skull_texture,             -1.95, -3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,skull_texture,             -3.25, -3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,skull_texture,             -4.55, -3.25, -6.28,    0,0,0);
	
	ObjLoad (pawn_obj,water_texture,             4.55, 3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,water_texture,             3.25, 3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,water_texture,             1.95, 3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,water_texture,             0.65, 3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,water_texture,             -0.65, 3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,water_texture,             -1.95, 3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,water_texture,             -3.25, 3.25, -6.28,    0,0,0);
	ObjLoad (pawn_obj,water_texture,             -4.55, 3.25, -6.28,    0,0,0);
	ObjLoad (rook_obj,water_texture,             4.55, 4.5, -5.95,    0,0,0);
	ObjLoad (knight_obj,water_texture,             3.25, 4.5, -6.275,    0,0,0);
	ObjLoad (bishop_obj,water_texture,             1.95, 4.5, -6.275,    0,0,0);
	ObjLoad (king_obj,water_texture,             0.65, 4.5, -6.275,    0,0,0);
	ObjLoad (queen_obj,water_texture,             -0.65, 4.5, -6.275,    0,0,0);
	ObjLoad (bishop_obj,water_texture,             -1.95, 4.5, -6.275,    0,0,0);
	ObjLoad (knight_obj,water_texture,             -3.25, 4.5, -6.275,    0,0,0);
	ObjLoad (rook_obj,water_texture,             -4.55, 4.5, -5.95,    0,0,0);
	
	loadallimages();
}


//Handles Resize of display Screen ////
void resize (int p_width, int p_height)
{
	if (screen_width==0 && screen_height==0) exit(0);
    screen_width=p_width; // We obtain the new screen width values and store it
    screen_height=p_height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f);
	///gluLookAt(xeye, yeye, zeye, xlook, ylook, zlook, 0,1,0);
    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

///Keyboard Functions////
void keyboard(unsigned char p_key, int p_x, int p_y)
{  
	cout <<  "keyboard is active" << endl;
    switch (p_key)
    {
		/*
        case ' ':
            rotation_x_increment=0;
            rotation_y_increment=0;
            rotation_z_increment=0;
        break;
		*/

	case 'w':
		yeye+= 0.1;
		byeye+= 0.1;
		break;
	case 'a':
		xeye-=0.1;
		bxeye-= 0.1;
		break;
	case 's':
		yeye-=0.1;
		byeye-=0.1;
		break;
	case 'd':
		xeye+=0.1;
		bxeye+=0.1;
		break;
	case 'z':
		zeye+=0.1;
		bzeye+=0.1;
		break;
	case 'x':
		zeye-=0.1;
		bzeye-=0.1;
		break;
	case 't':
		cout<<byeye<<" "<<bzeye<<endl;
		break;
	//obj_control =0;
		case 'j': case 'J':
		//	ObjTranslate(&object[obj_control],1,1,0);
        break;
		case 'm': case 'M':
			//ObjTranslate(&object[obj_control],-1,-1,0);
        break;
        case 'k': case 'K':
			ObjRotate(&object[obj_control],0,20,0);
        break;
        case 'l': case 'L':
			ObjRotate(&object[obj_control],0,-20,0);
			break;
		case 'r': case 'R':
            if (filling==0)
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
                filling=1;
            }   
            else 
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
                filling=0;
            }
        break;
		case 27:
			exit(0);
		break;
    }
}


void keyboard_s (int p_key, int p_x, int py)
{
    switch (p_key)
    {
        case GLUT_KEY_UP:
			ObjRotate(&object[obj_control],-20,0,0);
            //rotation_x_increment = rotation_x_increment +0.005;
        break;
        case GLUT_KEY_DOWN:
			ObjRotate(&object[obj_control],20,0,0);
            //rotation_x_increment = rotation_x_increment -0.005;
        break;
        case GLUT_KEY_LEFT:
			ObjRotate(&object[obj_control],0,0,20);
            //rotation_y_increment = rotation_y_increment +0.005;
        break;
        case GLUT_KEY_RIGHT:
			ObjRotate(&object[obj_control],0,0,-20);
            //rotation_y_increment = rotation_y_increment -0.005;
        break;
        case GLUT_KEY_PAGE_UP:
			obj_control++;
			if (obj_control>=obj_qty) obj_control=0;
		break;
        case GLUT_KEY_PAGE_DOWN:
			obj_control--;
			if (obj_control<0) obj_control=obj_qty-1;
		break;
    }
}

void endgameGUI(int i)
{
	if(i==1)
		screenvar = 0;
	else
		screenvar = 0 ;
//	pthread_exit(NULL);

}


// All the 3ds objects are loaded with a particular id ////
void display(void)
{
    int i,j;
	
	
    for (i=0;i<obj_qty;i++)
	{
	
		glPushMatrix(); // We save the current matrix
		glPushName(i);
		
		glTranslatef(xhite[i], yhite[i], hite[i]);	
		/*if(i<16)
			glColor3f(1,1,1);
		else if(i<32)
			glColor3f(1,0,0);
*/
	
		if(i==1 || i==6)
			glColor3f(1,0,0);
		
		if(i==25 || i==30)
			glColor3f(1,1,1);
		
		if(i==1 || i==6 || i==3 || i==4){
//			glColor3f(1,1,0);
			glTranslatef(0,0,-1);
					
		}else if(i==25 || i==30 || i==28 || i ==27){
//			glColor3f(1,0,0);
			glTranslatef(0,0,-1);
		}
		glMultMatrixf(&object[i].matrix[0][0]); // Now let's multiply the object matrix by the identity-first matrix
		if(i==1 || i==6 ){
			glScalef(0.4,0.4,0.4);
			glRotatef(90, 1 , 0 ,0 );
			glRotatef(180, 0,1,0);
			//glTranslatef(0,0,0);	
		}else if(i==25 || i==30 ){
			glScalef(0.4,0.4,0.4);
			glRotatef(90, 1 , 0 ,0 );
		}else if(i==3 || i==4 || i==28 || i==27){
			glScalef(20,20,20);
			glRotatef(90, 1, 0,0);
		}
		if (object[i].id_texture!=-1 && i!=1 && i!=6 && i!=25 && i!= 30)// && i!=1 && i!=6 && i!=25 && i!= 30 && i!= 3 && i!=4 && i!= 28 && i!=27) 
		{
			glBindTexture(GL_TEXTURE_2D, object[i].id_texture); // We set the active texture 
		    glEnable(GL_TEXTURE_2D); // Texture mapping ON
			setting();
		}
		else
		    glDisable(GL_TEXTURE_2D); // Texture mapping OFF
		
		glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
		for (j=0;j<object[i].polygons_qty;j++)
		{
			
			//if(i==3)
			//cout <<i<<" "<<j<<" :::::1 "<< object[i].mapcoord[ object[i].polygon[j].a ].u<< "  "<< object[i].mapcoord[ object[i].polygon[j].a ].v << endl;
		
			glNormal3f( object[i].normal[ object[i].polygon[j].a ].x,
						object[i].normal[ object[i].polygon[j].a ].y,
						object[i].normal[ object[i].polygon[j].a ].z);
	
			glTexCoord2f(0.0f, 0.0f);
			/*
			if( (object[i].mapcoord[ object[i].polygon[j].a ].u) >0){
			glTexCoord2f( object[i].mapcoord[ object[i].polygon[j].a ].u,
						  object[i].mapcoord[ object[i].polygon[j].a ].v);
			}
		*/
			glVertex3f( object[i].vertex[ object[i].polygon[j].a ].x,
						object[i].vertex[ object[i].polygon[j].a ].y,
						object[i].vertex[ object[i].polygon[j].a ].z);
			//if(i==3)
			//cout<< i<<"  "<<j<<" :::::2 "<< object[i].mapcoord[ object[i].polygon[j].b ].u << "   " << object[i].mapcoord[ object[i].polygon[j].b ].v << endl;
			glNormal3f( object[i].normal[ object[i].polygon[j].b ].x,
						object[i].normal[ object[i].polygon[j].b ].y,
						object[i].normal[ object[i].polygon[j].b ].z);
/*
			
			if( (object[i].mapcoord[ object[i].polygon[j].a ].u) >0){
			glTexCoord2f( object[i].mapcoord[ object[i].polygon[j].b ].u,
						  object[i].mapcoord[ object[i].polygon[j].b ].v);
			}
*/			
			glTexCoord2f(0.0f, 1.0f);	
			glVertex3f( object[i].vertex[ object[i].polygon[j].b ].x,
						object[i].vertex[ object[i].polygon[j].b ].y,
						object[i].vertex[ object[i].polygon[j].b ].z);
			//if(i==3)
			//cout << i<<"  "<<j<<" :::::3 "<< object[i].mapcoord[ object[i].polygon[j].c ].u << "   " << object[i].mapcoord[ object[i].polygon[j].c ].v << endl;
			glNormal3f( object[i].normal[ object[i].polygon[j].c ].x,
						object[i].normal[ object[i].polygon[j].c ].y,
						object[i].normal[ object[i].polygon[j].c ].z);
			
/*			if( (object[i].mapcoord[ object[i].polygon[j].a ].u) >0){
			glTexCoord2f( object[i].mapcoord[ object[i].polygon[j].c ].u,
						  object[i].mapcoord[ object[i].polygon[j].c ].v);
		
			}	
*/			
			glTexCoord2f(1.0f, 0.0f);	
			glVertex3f( object[i].vertex[ object[i].polygon[j].c ].x,
						object[i].vertex[ object[i].polygon[j].c ].y,
						object[i].vertex[ object[i].polygon[j].c ].z);

		}
		glEnd();
		
		glPopName();
		glPopMatrix(); // Restore the previous matrix 
	}

	
}


// Fuction does all the drawing stuff ////
void Drawscene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
	glMatrixMode(GL_MODELVIEW); // Modeling transformation
	glLoadIdentity(); // Initialize the model matrix as identity
	
	
	if(screenvar==0){ // main screen
		 glPushMatrix();
		gluLookAt(xeye+alpha, -3.0, zeye, xlook, ylook, zlook, 0,1,0);
		welcome1();
		glPopMatrix();
		if(anim ==1){	
			if(blackchance==0)
				gluLookAt(xeye+alpha, yeye, zeye, xlook, ylook, zlook, 0,1,0);
			else		
				gluLookAt(bxeye+alpha, byeye, bzeye, bxlook, bylook, bzlook, 0,1,0);
		}else{
			gluLookAt(bxeye+alpha, byeye, bzeye, bxlook, bylook, bzlook, 0,1,0);
			glRotatef(180,0,0,1);
			glRotatef(45, 1,0,0);
		}		
		if (mode == SELECT) {
			startPicking();
		}
	
		
		glPushMatrix();
		if(anim == 1){
			if(blackchance == 1 ){
				glRotatef(180,0,0,1);
				glRotatef(45, 1,0,0);
			}
		}
		glScalef(0.5,0.5,0.5);
		glTranslatef(0.0, 7.0, 0.0); 
		glRotatef(-15, 1, 0,0);

		glTranslatef(0.0f, 0.0f, -11.0f);
		background();
		//glTranslatef(0,0,1);
		//animate(0);
			
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				glPushMatrix();
				glPushName(32+ i + j*8);
				glTranslatef(0,0,-0.1+allowed[i][j]);
				boardimages(-2*i,2*j);
				glPopName();
				glPopMatrix();
			}
		}
	
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				glPushMatrix();
				
				glTranslatef(0,0,-0.1+allowedred[i][j]);
				boardredimages(-2*i,2*j);
			
				glPopMatrix();
			}
		}
		glTranslatef(0,0,-0.1);
		glTranslatef(0.0f, 0.0f, 11.0f);
		glScalef(1.5, 1.5,1.5);
		glPushMatrix();
		if(status)
			ObjRotate(&object[posii],0,0,20);
		glPopMatrix();
		display();

		glPopMatrix();
	}else if(screenvar == 1) //  endgame screeen 
		endgameimage();
	else if(screenvar == 2)
		endgameimage();
	else if(screenvar == 3){
		gluLookAt(xeye+alpha, -3.0, zeye, xlook, ylook, zlook, 0,1,0);
		welcome();
		glTranslatef(-14,0,0);
		animate(addanimate);
		glTranslatef(14,0,0);
		newgame(addnew);
		glTranslatef(-0.30,-1.5,0);
		exitgame(exitnew);
		
		glTranslatef(0.30,1.5,0);
	}   ////wecome screen
	if (mode == SELECT){
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
					allowed[i][j] =0.0;
			}
		}
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
					allowedred[i][j] =0.0;
			}
		}
		hite[posii] =0;
		stopPicking();
	}else{
	glFlush();
	glutSwapBuffers();
	}
	
}


void mouseStuff(int button, int state, int x, int y) {
	cout << "getiing mouse" << endl;
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;
	if(button ==0){
		if(state == 0){
			if(screenvar==3){
				if(x>805&& x<921 && y>621 && y<681){
					screenvar = 0;
				}else if(x>805 && x<921 && y>708 && y<769){
					exit(0);
				}else if(x>24 && x<140 && y>620 && y<683){
					anim = 1^anim;
				}
			}
		}
	}	
	cursorX = x;
	cursorY = y;
	mode = SELECT;
}

///Updates the display screen //////
void update(int value){
	if(yeye<-3 && screenvar == 0){
		yeye = yeye +0.1;
		//byeye = byeye +0.1;
	}
	
	if(byeye>-9.4 && blackchance==1){
		byeye -= 0.1;
	}
	if(bzeye<8 && blackchance==1){
		bzeye += 0.1;
	}
	glutTimerFunc(5, update, 0);
}

// Mouse Function/////
void mouse_move_CB(int x,int y)
{
	cout << x <<" x " <<y << "y"<<endl;
	if(screenvar == 3){
		if(x>805&& x<921 && y>621 && y<681){
			addnew = 0.5;
			
		}else if(x>805 && x<921 && y>708 && y<769){
			exitnew = 0.5;
		}else if(x>24 && x<140 && y>620 && y<683){
			addanimate = 0.5;
		}else{
			addnew = 0.0;
			exitnew = 0.0;
			addanimate = 0.0;
		}
	}
}


// glut main function ////
void mainnn()
{   
    	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    	glutInitWindowSize(screen_width,screen_height);
    	glutInitWindowPosition(0,0);
	//while(blackchance ==0 ){};
    	mainwindow = glutCreateWindow("Chess 1.0");    
		init();
		glutDisplayFunc(Drawscene);
		glutIdleFunc(Drawscene);
		glutReshapeFunc (resize);
		glutKeyboardFunc (keyboard);
		glutSpecialFunc (keyboard_s);
		glutMouseFunc(mouseStuff);
		glutPassiveMotionFunc(mouse_move_CB);
		glutTimerFunc(5,update, 1);
		glutPassiveMotionFunc(mouse_move_CB);
		glutMainLoop();
}


