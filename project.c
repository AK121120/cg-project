#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<string.h>
void display();
GLfloat displacement = 0.0,count=2.0,wolf=4.0,sheep=4.0,grass=4.0,t=0.0;  // displacement of the shapes
int left[4]={1,1,1,1},right[4]={0,0,0,0},state=0;
int refreshMills = 20; // refresh interval in milliseconds
void init()
{
	glClearColor(0.8,0.9,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1000,0,800);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void keys(unsigned char k,int x,int y)
{
	if(k=='m'){
		if(count==2){
			count=1;
			left[0]=0;
			right[0]=1;
		}else if(count==0) {
			count=1;
			left[0]=0;
			right[0]=1;
		}else{
			count=0;
			left[0]=1;
			right[0]=0;
		}
	}
	if(k=='w'){
		if(wolf==4&&(count==2||count==0)){
			wolf=1;
			left[1]=0;
		}else if(wolf==0&&(count==2||count==0)){
			wolf=1;
			left[1]=0;
		}else if(wolf==1&&(count==2||count==0)){
			wolf=0;
			left[1]=1;
		}else if(wolf==2&&count==1){
			wolf=3;
			right[1]=1;
		}else if(wolf==3&&count==1){
			wolf=2;
			right[1]=0;
		}
	}
	if(k=='s'){
		if(sheep==4&&(count==2||count==0)){
			sheep=1;
			left[2]=0;
		}else if(sheep==0&&(count==2||count==0)){
			sheep=1;
			left[2]=0;
		}else if(sheep==1&&(count==2||count==0)){
			sheep=0;
			left[2]=1;
		}else if(sheep==2&&count==1){
			sheep=3;
			right[2]=1;
		}else if(sheep==3&&count==1){
			sheep=2;
			right[2]=0;
		}
	}
	if(k=='g'){
		if(grass==4&&(count==2||count==0)){
			grass=1;
			left[3]=0;
		}else if(grass==0&&(count==2||count==0)){
			grass=1;
			left[3]=0;
		}else if(grass==1&&(count==2||count==0)){
			grass=0;
			left[3]=1;
		}else if(grass==2&&count==1){
			grass=3;
			right[3]=1;
		}else if(grass==3&&count==1){
			grass=2;
			right[3]=0;
		}
	}
	glutPostRedisplay();
}
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}
void status(){
	if(right[0]==1&&count==1&&displacement==400&&right[1]==1&&right[2]==1&&right[3]==1){
		char s1[]="YOU WON";
		glRasterPos2f(475,400);
		for(int i=0;i<strlen(s1);i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13,s1[i]);
		}
	}
	if(state!=0){
		t++;
		if(t>100){
			/*char s1[]="restart";
			glRasterPos2f(475,400);
			for(int i=0;i<strlen(s1);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,s1[i]);
			}*/
			displacement = 0.0,count=2.0,wolf=4.0,sheep=4.0,grass=4.0,t=0.0;
			for(int i=0;i<4;i++){
				left[i]=1;
				right[i]=0;
			}
			state=0;
			init();
			glutDisplayFunc(display);
		}
	}
	if(left[0]==0&&count==1&&displacement==400&&t<100){
		if(left[1]==1&&left[2]==1){
			char s1[]="game over";
			glRasterPos2f(475,400);
			state=1;
			for(int i=0;i<strlen(s1);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,s1[i]);
			}
		}else if(left[2]==1&&left[3]==1){
			char s1[]="game over";
			glRasterPos2f(475,400);
			state=2;
			for(int i=0;i<strlen(s1);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,s1[i]);
			}
		}
	}else if(right[0]==0&&count==0&&displacement==0&&t<100){
		if(right[1]==1&&right[2]==1){
			char s1[]="game over";
			glRasterPos2f(475,400);
			state=3;
			for(int i=0;i<strlen(s1);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,s1[i]);
			}
		}else if(right[2]==1&&right[3]==1){
			char s1[]="game over";
			state=4;
			glRasterPos2f(475,400);
			for(int i=0;i<strlen(s1);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,s1[i]);
			}
		}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	status();
	{
	char s[]="RIVER CROSSING PUZZLE, MAN HAS TO CROSS THE RIVER. BUT HE CAN ONLY TAKE ONE ANIMAL AT A TIME.";
	char s1[]="IF SHEEP LEFT WITH GRASS EATS IT SIMILARLY WOLF LEFT WITH SHEEP EATS IT.";
	glColor3f(1,0,0);
	glRasterPos2f(200,700);
	for(int i=0;i<strlen(s);i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
	}
	glColor3f(1,0,0);
	glRasterPos2f(275,650);
	for(int i=0;i<strlen(s1);i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s1[i]);
	}
	}
	glBegin(GL_QUADS);
	
		glColor3f(0.8,0.9,1.0);//sky
		glVertex2f(0,400);
		glVertex2f(0,800);
		glColor3f(1,0.9,0.6);
		glVertex2f(1000,800);
		glColor3f(0.8,0.9,1.0);
		glVertex2f(1000,400);
		
		glColor3f(0.6,0.2,0.0);//land left
		glVertex2f(0,0);
		glColor3f(0.6,0.4,0.0);
		glVertex2f(0,120);
		glColor3f(0.6,0.4,0.0);
		glVertex2f(200,120);
		glColor3f(0.6,0.2,0.0);
		glVertex2f(200,0);
		
		glColor3f(0.0,0.5,0.0);//grass left
		glVertex2f(0,120);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(0,165);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(200,165);
		glColor3f(0.0,0.5,0.0);
		glVertex2f(200,120);
		
		glColor3f(0.0,0.0,1.0);//water
		glVertex2f(200,0);
		glColor3f(0.0,0.7,1.0);
		glVertex2f(200,150);
		glColor3f(0.0,0.7,1.0);
		glVertex2f(800,150);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(800,0);
		
		glColor3f(0.6,0.2,0.0);//land right
		glVertex2f(800,0);
		glColor3f(0.6,0.4,0.0);
		glVertex2f(800,120);
		glColor3f(0.6,0.4,0.0);
		glVertex2f(1000,120);
		glColor3f(0.6,0.2,0.0);
		glVertex2f(1000,0);
		
		glColor3f(0.0,0.5,0.0);//grass right
		glVertex2f(800,120);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(800,165);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(1000,165);
		glColor3f(0.0,0.5,0.0);
		glVertex2f(1000,120);
	glEnd();
	
	glPushMatrix();      // Save model-view matrix setting
	if(state==1||state==3)glTranslatef(62,0,0);
	if(wolf==1&&displacement==400&&count==1)wolf=2;
	if(wolf==2&&displacement==0&&count==0)wolf=1;
	if (wolf==0)glTranslatef(0,0,0);               
	if (wolf==1)glTranslatef(320,20,0);
	if (wolf==2&&count==0){glTranslatef(320,20,0);
	}else if (wolf==2)glTranslatef(720,20,0);
	if (wolf==3)glTranslatef(800,0,0);
	if((wolf==1&&count==1)||(wolf==2&&count==0))glTranslatef(displacement,0,0);
	glBegin(GL_QUADS);//wolf
		
		glColor3f(0.8,0.9,1.0);
		glVertex2f(31,230);
		glVertex2f(31,250);
		glVertex2f(45,250);
		glVertex2f(45,230);
		
		glColor3f(0,0,0);
		glVertex2f(30,230);
		glVertex2f(30,250);
		glVertex2f(46,250);
		glVertex2f(46,230);
		
		glColor3f(0.88,0.88,0.88);
		glVertex2f(30,210);
		glVertex2f(30,230);
		glVertex2f(46,230);
		glVertex2f(46,210);
		
		glColor3f(0.95,0.95,0.95);//light grey
		glVertex2f(16,240);
		glVertex2f(14,250);
		glVertex2f(62,250);
		glVertex2f(60,240);
		
		glColor3f(0.76,0.76,0.76);//grey
		glVertex2f(16,230);
		glVertex2f(16,240);
		glVertex2f(60,240);
		glVertex2f(60,230);
		
		glColor3f(1,0,0);//ears
		glVertex2f(14,230);
		glVertex2f(14,250);
		glVertex2f(62,250);
		glVertex2f(62,230);
		
		glColor3f(0.95,0.95,0.95);//light grey
		glVertex2f(14,220);
		glVertex2f(14,230);
		glVertex2f(62,230);
		glVertex2f(62,220);
		
		glColor3f(0.76,0.76,0.76);//grey
		glVertex2f(14,210);
		glVertex2f(14,220);
		glVertex2f(62,220);
		glVertex2f(62,210);
		
		glColor3f(0,0,0);//nose
		glVertex2f(33,188);
		glVertex2f(33,198);
		glVertex2f(43,198);
		glVertex2f(43,188);
		
		glColor3f(1,1,1);//front mouth white
		glVertex2f(26,177);
		glVertex2f(26,198);
		glVertex2f(50,198);
		glVertex2f(50,177);
		
		glColor3f(0.68,0.68,0.68);//back mouth grey
		glVertex2f(22,180);
		glVertex2f(22,200);
		glVertex2f(54,200);
		glVertex2f(54,180);
		
		glColor3f(0.98,0.66,0.38);//chin
		glVertex2f(14,190);
		glVertex2f(14,200);
		glVertex2f(62,200);
		glVertex2f(62,190);
		
		glColor3f(0.6,0.4,0.18);//cheek
		glVertex2f(14,180);
		glVertex2f(14,190);
		glVertex2f(62,190);
		glVertex2f(62,180);
		
		glColor3f(0.6,0.4,0.18);//brown
		glVertex2f(30,190);
		glVertex2f(30,210);
		glVertex2f(46,210);
		glVertex2f(46,190);
		
		glColor3f(0,0,0);//eyes
		glVertex2f(22,200);
		glVertex2f(22,210);
		glVertex2f(54,210);
		glVertex2f(54,200);
		
		glColor3f(1,1,1);//eyes back
		glVertex2f(15,200);
		glVertex2f(15,210);
		glVertex2f(61,210);
		glVertex2f(61,200);
		
		glColor3f(0,0,0);//mouth
		glVertex2f(26,162);
		glVertex2f(26,177);
		glVertex2f(50,177);
		glVertex2f(50,162);
		
		glColor3f(1,1,1);//bottom white
		glVertex2f(22,170);
		glVertex2f(22,180);
		glVertex2f(54,180);
		glVertex2f(54,170);
		
		glColor3f(0.51,0.51,0.51);//bottom grey
		glVertex2f(22,170);
		glVertex2f(14,180);
		glVertex2f(62,180);
		glVertex2f(54,170);
		
	glEnd();
	glPopMatrix();
	glPushMatrix();      // Save model-view matrix setting
	if(state==2||state==4)glTranslatef(62,0,0);
	if(sheep==1&&displacement==400&&count==1)sheep=2;
	if(sheep==2&&displacement==0&&count==0)sheep=1;
	if (sheep==0)glTranslatef(0,0,0);               
	if (sheep==1)glTranslatef(250,30,0);
	if (sheep==2&&count==0){glTranslatef(250,30,0);
	}else if (sheep==2)glTranslatef(650,30,0);
	if (sheep==3)glTranslatef(800,0,0);
	if((sheep==1&&count==1)||(sheep==2&&count==0))glTranslatef(displacement,0,0);
	if(state!=1&&state!=3){
	glBegin(GL_QUADS);//sheep
		
		glColor3f(1.0,0.8,0.5);
		glVertex2f(95,210);
		glVertex2f(95,220);
		glVertex2f(107,220);
		glVertex2f(107,210);
		
		glColor3f(1,1,1);
		glVertex2f(89,210);
		glVertex2f(89,220);
		glVertex2f(113,220);
		glVertex2f(113,210);
		
		glColor3f(0,0,0);
		glVertex2f(83,210);
		glVertex2f(83,220);
		glVertex2f(119,220);
		glVertex2f(119,210);	
			
		glColor3f(1.0,0.8,0.5);
		glVertex2f(83,200);
		glVertex2f(83,230);
		glVertex2f(119,230);
		glVertex2f(119,200);
		
		glColor3f(1.0,0.5,0.6);
		glVertex2f(95,190);
		glVertex2f(95,200);
		glVertex2f(107,200);
		glVertex2f(107,190);
		
		glColor3f(1.0,0.92,0.95);
		glVertex2f(95,180);
		glVertex2f(95,190);
		glVertex2f(107,190);
		glVertex2f(107,180);
		
		glColor3f(1.0,0.8,0.5);
		glVertex2f(89,180);
		glVertex2f(89,200);
		glVertex2f(113,200);
		glVertex2f(113,180);
		
		glColor3f(1,1,1);
		glVertex2f(76,170);
		glVertex2f(76,250);
		glVertex2f(126,250);
		glVertex2f(126,170);
	glEnd();
	}
	glPopMatrix();
	glBegin(GL_QUADS);
		glColor3f(0.0,0.5,0.0);//grass 
		glVertex2f(138,165);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(138,170);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(188,170);
		glColor3f(0.0,0.5,0.0);
		glVertex2f(188,165);
		
		glColor3f(0.0,0.5,0.0);//grass 
		glVertex2f(76,165);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(76,170);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(126,170);
		glColor3f(0.0,0.5,0.0);
		glVertex2f(126,165);
		
		glColor3f(0.0,0.5,0.0);//grass 
		glVertex2f(12,165);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(12,170);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(64,170);
		glColor3f(0.0,0.5,0.0);
		glVertex2f(64,165);
		
		glColor3f(0.0,0.5,0.0);//grass 
		glVertex2f(938,165);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(938,170);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(988,170);
		glColor3f(0.0,0.5,0.0);
		glVertex2f(988,165);
		
		glColor3f(0.0,0.5,0.0);//grass 
		glVertex2f(876,165);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(876,170);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(926,170);
		glColor3f(0.0,0.5,0.0);
		glVertex2f(926,165);
		
		glColor3f(0.0,0.5,0.0);//grass 
		glVertex2f(812,165);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(812,170);
		glColor3f(0.0,0.9,0.0);
		glVertex2f(864,170);
		glColor3f(0.0,0.5,0.0);
		glVertex2f(864,165);
		
	glEnd();
	glPushMatrix();      // Save model-view matrix setting
	if(grass==1&&displacement==400&&count==1)grass=2;
	if(grass==2&&displacement==0&&count==0)grass=1;
	if (grass==0)glTranslatef(0,0,0);               
	if (grass==1)glTranslatef(190,30,0);
	if (grass==2&&count==0){glTranslatef(190,30,0);
	}else if (grass==2)glTranslatef(590,30,0);
	if (grass==3)glTranslatef(800,0,0);
	if((grass==1&&count==1)||(grass==2&&count==0))glTranslatef(displacement,0,0);
	if(state!=2&&state!=4){
	glBegin(GL_TRIANGLES);  //grass
	       
		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(150,200);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(155,240);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(150,230);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(150,180);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(150,250);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(160,275);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(170,300);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(180,275);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(190,250);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(200,250);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(195,250);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(185,225);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(175,220);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(165,240);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(188,190);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(188,200);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      		
      		glColor3f(0,0.5,0); 
      		glVertex2f(162,170);
      		glColor3f(0.9,0.9,0);
     		glVertex2f(185,190);
     		glColor3f(0,0.5,0);
      		glVertex2f(166,170);
      	glEnd();
      	}
      	glPopMatrix();
	glPushMatrix();                     // Save model-view matrix setting
	glTranslatef(displacement,0,0);
	glBegin(GL_QUADS);
		glColor3f(0.5,0.5,0.5);//boat
		glVertex2f(220,160);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(218,165);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(382,165);
		glColor3f(0.5,0.5,0.5);
		glVertex2f(380,160);
		
		glColor3f(1.0,0.1,0.1);//boat
		glVertex2f(225,150);
		glColor3f(1.0,0.7,0.5);
		glVertex2f(205,190);
		glColor3f(1.0,0.7,0.5);
		glVertex2f(395,190);
		glColor3f(1.0,0.1,0.1);
		glVertex2f(375,150);
		
		glColor3f(0.0,0.0,0.0);//boat
		glVertex2f(200,190);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(200,200);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(400,200);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(400,190);
	glEnd();
	glPopMatrix();
	glPushMatrix();                     // Save model-view matrix setting
	glTranslatef(displacement,0,0);
	glBegin(GL_QUADS);
		glColor3f(1.0,0.0,1.0);//man
		glVertex2f(230,200);
		glColor3f(1.0,0.7,1.0);
		glVertex2f(230,250);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(280,250);
		glColor3f(1.0,0.0,1.0);
		glVertex2f(280,200);
		
		glColor3f(1.0,0.5,0.5);//man left hand
		glVertex2f(220,200);
		glColor3f(1.0,1.0,0.0);
		glVertex2f(220,250);
		glColor3f(1.0,1.0,0.0);
		glVertex2f(230,250);
		glColor3f(1.0,0.5,0.5);
		glVertex2f(230,200);
		
		glColor3f(1.0,0.5,0.5);//man right hand
		glVertex2f(280,200);
		glColor3f(1.0,1.0,0.0);
		glVertex2f(280,250);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(290,250);
		glColor3f(1.0,0.5,0.5);
		glVertex2f(290,200);
		
		glColor3f(1,1,1);//teeth
		glVertex2f(250,269);
		glVertex2f(250,273);
		glVertex2f(254,273);
		glVertex2f(254,269);
		
		glColor3f(1,1,1);//teeth
		glVertex2f(256,269);
		glVertex2f(256,273);
		glVertex2f(260,273);
		glVertex2f(260,269);
		
		glColor3f(1,0,0);//mouth
		glVertex2f(245,267);
		glVertex2f(245,273);
		glVertex2f(265,273);
		glVertex2f(265,267);
		
		glColor3f(0,0,0);//eyebrows left
		glVertex2f(240,290);
		glVertex2f(240,292);
		glVertex2f(250,292);
		glVertex2f(250,290);
		
		glColor3f(0,0,0);//eyebrows right
		glVertex2f(260,290);
		glVertex2f(260,292);
		glVertex2f(270,292);
		glVertex2f(270,290);
		
		glColor3f(0,0,0);//eyes ball left
		glVertex2f(243,280);
		glVertex2f(243,285);
		glVertex2f(247,285);
		glVertex2f(247,280);
		
		glColor3f(0,0,0);//eyes ball right
		glVertex2f(263,280);
		glVertex2f(263,285);
		glVertex2f(267,285);
		glVertex2f(267,280);
		
		glColor3f(1,1,1);//eyes left
		glVertex2f(240,280);
		glVertex2f(240,288);
		glVertex2f(250,288);
		glVertex2f(250,280);
		
		glColor3f(1,1,1);//eyes right
		glVertex2f(260,280);
		glVertex2f(260,288);
		glVertex2f(270,288);
		glVertex2f(270,280);
		
	glEnd();
		/*glColor3f(1.0,0.8,0.5);//head
		glVertex2f(238,260);
		glVertex2f(238,300);
		glColor3f(1,1,1);
		glVertex2f(272,300);
		glColor3f(1.0,0.8,0.5);
		glVertex2f(272,260);*/
	glPopMatrix();
	glPushMatrix();                     // Save model-view matrix setting
	glTranslatef(displacement,0,0);
	glBegin(GL_POLYGON);            // These vertices form a closed polygon
		glColor3f(1.0,0.8,0.5);//head
		glVertex2f(270,258);
		glVertex2f(272,260);
		glColor3f(1,1,1);
		glVertex2f(272,300);
		glColor3f(1.0,0.8,0.5);
		glVertex2f(238,300);
		glVertex2f(238,262);
		glVertex2f(240,260);
	glEnd();
	glPopMatrix();
	glPushMatrix();                     // Save model-view matrix setting
	glTranslatef(displacement,0,0);
	glBegin(GL_QUADS);
		glColor3f(1.0,0.5,1.0);//neck
		glVertex2f(245,250);
		glVertex2f(245,260);
		glColor3f(1,1,1);
		glVertex2f(265,260);
		glColor3f(1.0,0.5,1.0);
		glVertex2f(265,250);
		
		glColor3f(1.0,0.8,0.5);//ear
		glVertex2f(235,275);
		glColor3f(1.0,0.8,0.5);
		glVertex2f(235,290);
		glColor3f(1,1,1);
		glVertex2f(275,290);
		glColor3f(1.0,0.8,0.5);
		glVertex2f(275,275);
		
		glColor3f(0,0,0);//hair
		glVertex2f(235,290);
		glVertex2f(235,315);
		glColor3f(1,1,1);
		glVertex2f(275,315);
		glColor3f(0,0,0);
		glVertex2f(275,290);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
	if(count==1){
		if(displacement<400){
			displacement+=10.0;
		}else if(displacement==400){
			displacement=400.0;
		}
	}else if(count==0){
		if(displacement>0){
			displacement-=10.0;
		}else if(displacement==0){
			displacement=0.0;
		}
	}
	glFlush();
}
void main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(1200,800);
	glutCreateWindow("Anantha krishna G.K 4SF18CS011 Perspective View");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(0, Timer, 0);
	glEnable(GL_DEPTH_TEST);
	glutKeyboardFunc(keys);
	glutMainLoop();
}
