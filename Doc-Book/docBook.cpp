#include<graphics.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<string.h>
#include<math.h>
#include<iostream.h>

void header();
void bg_color();
void quit();
void mainscreen1();
void mainscreen2();
void drawbox(int,int,int,int,int);

struct classes{              // strcuture of mainscreen-1
   char file[20];
   char subject[20];
   char name[30];
   char password[30];
   char classno[4];
}screen1ob;

REGS in;
class mouse{
public:
  void initmouse(){
     in.x.ax=0;
     int86(0x33,&in,&in);
  }
  void showmouse(){
     in.x.ax=1;
     int86(0x33,&in,&in);
  }
  void hidemouse(){
     in.x.ax=2;
     int86(0x33,&in,&in);
  }
  void status(int&x,int&y,int&but){
     in.x.ax=3;
     x=in.x.cx;
     y=in.x.dx;
     but=in.x.bx&7;
     int86(0x33,&in,&in);
  }
}mob;


	    /*********************************************
		   FUNCTIONS,CLASSES FOR MAINSCREEN-2
	    *********************************************/


struct data{
   char name[30];
   char age[4],pnum[20],roll[4],rank[4];
   char maths[4],chem[4],phy[4],eng[4],subject[4];
}structob;

class dataclass{
public:
  void create();
  void search();
  void readdata(int);
  void edit();
  void save(data&);
}dclassob;
template<class tb>tb datchar(int x,int y,tb p){
   tb s;
   gotoxy(x,y);
   cin>>s;
   return s;
}

void dataclass::create(){   // for one student's data storage
   int gd=DETECT,gm;
   initgraph(&gd,&gm,"");
   header();
   settextstyle(3,0,1);
   outtextxy(140,120,"ENTER NAME: ");
   strcpy(structob.name,datchar(33,9,"dsf"));
   outtextxy(140,153,"ENTER AGE: ");
   gotoxy(33,11);
   cin>>structob.age;
   outtextxy(140,186,"ENTER PHONE NUMBER: ");
   gotoxy(44,13);
   cin>>structob.pnum;
   outtextxy(140,219,"ENTER ROLL NUMBER: ");
   gotoxy(42,15);
   cin>>structob.roll;
   outtextxy(140,252,"ENTER CLASS RANK: ");
   gotoxy(42,17);
   cin>>structob.rank;
   delay(1000);
   cleardevice();
   header();
   settextstyle(3,0,1);
   outtextxy(140,60,"NOW ENTER MARKS:- ");
   outtextxy(140,120,"MATHEMATICS: ");
   gotoxy(36,9);
   cin>>structob.maths;
   outtextxy(140,153,"CHEMISTRY: ");
   gotoxy(33,11);
   cin>>structob.chem;
   outtextxy(140,186,"PHYSICS: ");
   gotoxy(33,13);
   cin>>structob.phy;
   outtextxy(140,219,"ENGLISH: ");
   gotoxy(33,15);
   cin>>structob.eng;
   char*s;
   strcpy(s,screen1ob.subject);
   strcat(s," : ");
   outtextxy(140,252,s);
   gotoxy(33,17);
   cin>>structob.subject;

   rectangle(140,280,490,330);
   setfillstyle(SOLID_FILL,RED);
   outtextxy(150,335,"SAVING DATA");
   for(int i=141;i<490;i++){
      bar(141,281,i,329);
      delay(10);
   }
   save(structob);
   outtextxy(140,370,"Press enter to continue");
   getch();
   closegraph();
   mainscreen2();
}

void dataclass::save(data &ob){
  ofstream file(screen1ob.file,ios::out);
  file.seekp(0,ios::end);
  file.write((char*)&ob,sizeof(ob));
  file.close();
  return;
}

void dataclass::readdata(int pos){
  ifstream file(screen1ob.file,ios::in);
  file.seekg(pos*sizeof(structob),ios::beg);
  file.read((char*)&structob,sizeof(structob));
  file.close();
}

int retsize(char filename[]){
   int size=0;
   ifstream file(filename,ios::in);
   file.seekg(0,ios::beg);
   while(!file.eof())
      size++;
   file.close();
   return size;
}

void dataclass::search(){
   int gd=DETECT,gm,x,y,but,datasize,pos=0;
   char filename[30];

   strcpy(filename,screen1ob.file);
   ifstream infile(filename,ios::in);
   datasize=retsize(filename);

   clrscr();
   initgraph(&gd,&gm,"");
   bg_color();
   header();

   setfillstyle(SOLID_FILL,RED);
   bar(50,50,getmaxx()-50,getmaxy()-50);
   rectangle(50,50,getmaxx()-50,getmaxy()-50);

   settextstyle(2,0,7);
   drawbox(51,51,55+textwidth("FIRST"),61+textheight("FIRST"),9);
   drawbox(getmaxx()-60-textwidth("LAST"),51,getmaxx()-51,55+textheight("LAST"),9);
   outtextxy(55,55,"FIRST");
   outtextxy(getmaxx()-55-textwidth("LAST"),50,"LAST");

   drawbox(195,51,230,77,9);        // for<<
   drawbox(395,51,430,77,9);         //for >>
   settextstyle(2,0,8);
   outtextxy(200,50,"<<");
   outtextxy(400,50,">>");
   outtextxy(60,110,"NAME: ");
   outtextxy(60,140,"AGE: ");
   outtextxy(60,170,"PHONE NUMBER: ");
   outtextxy(60,200,"ROLL NUMBER: ");
   outtextxy(60,230,"RANK: ");

   setfillstyle(SOLID_FILL,8);
   bar(60,270,getmaxx()-60,getmaxy()-55);
   rectangle(60,270,getmaxx()-60,getmaxy()-55);
   outtextxy(70,275,"MARKS:-");
   outtextxy(70,315,"MATHEMATICS: ");
   outtextxy(350,315,"CHEMISTRY: ");
   outtextxy(70,350,"PHYSICS: ");
   outtextxy(350,350,"ENGLISH");
   outtextxy(70,385,screen1ob.subject);

   drawbox(getmaxx()/2-textwidth("EDIT")/2-5,51,getmaxx()/2+textwidth("EDIT")/2,80,9);
   outtextxy(getmaxx()/2-textwidth("EDIT")/2,51,"EDIT");
again:
   readdata(pos);

   drawbox(60+textwidth("NAME: "),110,getmaxx()-100,110+textheight("N"),RED);
   drawbox(60+textwidth("AGE: "),140,getmaxx()-100,140+textheight("P"),RED);
   drawbox(60+textwidth("PHONE NUMBER: "),170,getmaxx()-100,170+textheight("P"),RED);
   drawbox(60+textwidth("ROLL NUMBER: "),200,getmaxx()-100,200+textheight("P"),RED);
   drawbox(60+textwidth("RANK: "),230,getmaxx()-100,230+textheight("P"),RED);
   drawbox(70+textwidth("MATHEMATICS: "),315,70+textwidth("MATHEMATICS: ")+40,315+textheight("M"),RED);
   drawbox(350+textwidth("CHEMISTRY: "),315,350+textwidth("CHEMISTRY: ")+40,315+textheight("C"),RED);
   drawbox(70+textwidth("PHYSICS: "),350,70+textwidth("PHYSICS: ")+40,350+textheight("P"),RED);
   drawbox(350+textwidth("ENGLISH"),350,350+textwidth("ENGLISH")+40,350+textheight("E"),RED);
   drawbox(70+textwidth(screen1ob.subject)+3,385,70+textwidth(screen1ob.subject)+3+40,385+textheight("P"),RED);

   outtextxy(60+textwidth("NAME:  "),110,structob.name);
   outtextxy(60+textwidth("AGE:  "),140,structob.age);
   outtextxy(60+textwidth("PHONE NUMBER:  "),170,structob.pnum);
   outtextxy(60+textwidth("ROLL NUMBER:  "),200,structob.roll);
   outtextxy(60+textwidth("RANK: "),230,structob.rank);
   outtextxy(70+textwidth("MATHEMATICS:  "),315,structob.maths);
   outtextxy(350+textwidth("CHEMISTRY:  "),315,structob.chem);
   outtextxy(70+textwidth("PHYSICS:  "),350,structob.phy);
   outtextxy(350+textwidth("ENGLISH:  "),350,structob.eng);
   outtextxy(70+textwidth(screen1ob.subject)+5,385,structob.subject);

   mob.initmouse();
   mob.showmouse();
   while(!kbhit()){
      mob.status(x,y,but);
      if(x>195&&y>51&&x<230&&y<77){       //for<<
	 if(pos!=0){
	    --pos;
	    goto again;
	 }
      }
      else if(x>395&&y>51&&x<430&&y<77){   // for>>
	 if(pos!=datasize){
	    ++pos;
	    goto again;
	 }
      }
      else if(x>51&&y>51&&x<55+textwidth("FIRST")&&y<61+textheight("FIRST")){
	 pos=0;
	 goto again;
      }
      else if(x>getmaxx()-60-textwidth("LAST")&&y>51&&x<getmaxx()-51&&y<55+textheight("LAST")){
	 pos=datasize;
	 goto again;
      }
      else if(x>getmaxx()/2-textwidth("EDIT")/2-5&&y>51&&x<getmaxx()/2+textwidth("EDIT")/2&&y<80)
	 dclassob.edit();
   }
   getch();
   closegraph();
   mainscreen2();
}


void list(){
   outtextxy(140,120,"1. NAME");
   outtextxy(140,153,"2. AGE");
   outtextxy(140,186,"3. PHONE NUMBER");
   outtextxy(140,219,"4. ROLL NUMBER");
   outtextxy(140,252,"5. RANK");
   outtextxy(140,285,"6. MARKS") ;
   outtextxy(140,318,"7. EXIT");
   outtextxy(140,351,"ENTER CHOICE: ");
}
void list2(){
    char*s;
    strcpy(s,"5. ");
    strcat(s,screen1ob.subject);
    outtextxy(140,120,"1. MATHEMATICS");
    outtextxy(140,153,"2. CHEMISTRY");
    outtextxy(140,186,"3. PHYSICS");
    outtextxy(140,219,"4. ENGLISH");
    outtextxy(140,252,s);
    outtextxy(140,285,"ENTER CHOICE: ");
}
void putagain(){
   cleardevice();
   header();
   settextstyle(3,0,1);
}

void dataclass::edit(){
   int gd=DETECT,gm,ch1,ch2,choice;
   char fname[20],filename[20];
   clrscr();
   initgraph(&gd,&gm,"");
   header();
   settextstyle(3,0,1);
   outtextxy(140,120,"ENTER NAME: ");
   gotoxy(33,9);
   cin>>fname;

   putagain();

   strcpy(filename,screen1ob.file);
   strcat(strcat("class",filename),".txt");
   ifstream file(filename,ios::in);
   file.seekg(0,ios::beg);
   while(!file.eof()){
      file.read((char*&)structob,sizeof(structob));
      if(strcmp(structob.name,fname)==0){
	  do{
	     outtextxy(140,80,"What Do You Want To Edit?");
	     list();
	     cin>>choice;
	     switch(ch1){
		case 1:
		      putagain();
		      outtextxy(140,120,"Enter Name: ");
		      gotoxy(33,9);
		      cin.getline(structob.name,sizeof(structob.name));
		break;
		case 2:
		      putagain();
		      outtextxy(140,120,"Enter Age: ");
		      gotoxy(33,9);
		      cin>>structob.age;
		break;
		case 3:
		     putagain();
		     outtextxy(140,120,"Enter Phone Number: ");
		     gotoxy(33,9);
		     cin>>structob.pnum;
		break;
		case 4:
		     putagain();
		     outtextxy(140,120,"Enter Roll Number: ");
		     gotoxy(33,9);
		     cin>>structob.roll;
		break;
		case 5:
		      putagain();
		      outtextxy(140,120,"Enter Rank: ");
		      gotoxy(33,9);
		      cin>>structob.rank;
		break;
		case 6:
		      putagain();
		      list2();
		      cin>>ch2;
		      switch(ch2){
			  case 1:
				outtextxy(120,318,"Enter New Marks: ");
				gotoxy(33,15);
				cin>>structob.maths;
			  break;
			  case 2:
				outtextxy(120,318,"Enter New Marks: ");
				gotoxy(33,15);
				cin>>structob.chem;
			  break;
			  case 3:
				outtextxy(120,318,"Enter New Marks: ");
				gotoxy(33,15);
				cin>>structob.phy;
			  break;
			  case 4:
				outtextxy(120,318,"Enter New Marks: ");
				gotoxy(33,15);
				cin>>structob.eng;
			  break;
			  case 5:
				outtextxy(120,318,"Enter New Marks: ");
				gotoxy(33,15);
				cin>>structob.subject;
			  break;
			  default:
				continue;
		      }
		break;
		case 7:
		      mainscreen2();
		break;
		default:
		       continue;
	     }
	  }while(ch1!='7');
      }  //end if
   }     // end while */
   getch();
   closegraph();
   mainscreen2();
}


	 /**************************************************
	      END OF FUNCTIONS,CLASSES FOR MAINSCREEN-2
	 ***************************************************/

		    /*************************
			GENERAL FUNCTIONS
		    **************************/

void header(){
   setfillstyle(CLOSE_DOT_FILL,RED);
   settextstyle(2,0,9);
   bar(0,0,getmaxx(),40);
   outtextxy(getmaxx()/2-textwidth("DocBook")/2,0,"DocBook");
   line(0,40,getmaxx(),40);
}

void bg_color(){
   setfillstyle(CLOSE_DOT_FILL,BLUE);
   bar(0,0,getmaxx(),getmaxy());
}

void drawbox(int x1,int y1,int x2,int y2,int color){
   setfillstyle(SOLID_FILL,color);
   bar(x1,y1,x2,y2);
}
void back(){
      int i;
      int xpos, ypos, color;
      int xmax = getmaxx();
      int ymax = getmaxy();
      setbkcolor(BLUE);
      setcolor(WHITE);
      for(i = 0; i < 5000; i++){
	    xpos = rand() % xmax;
	    ypos = rand() % ymax;
	    color = rand() % 12;
	    putpixel(xpos, ypos, color);
      }
}

void loading(){
   int gd=DETECT,gm;
   initgraph(&gd,&gm,"");
   char*s="DocBook";
   settextstyle(3,0,9);
   setfillstyle(SOLID_FILL,9);
   bar(100,100,getmaxx()-100,getmaxy()-200);
   outtextxy(getmaxx()/2-textwidth(s)/2,getmaxy()/2/2,s);
   void   *buffer;
  unsigned int size;
  line(230,330,370,330);
  line(230,350,370,350);
  line(226,335,226,345);
  line(226,335,230,330);
  line(226,345,230,350);
  line(374,335,374,345);
  line(374,335,370,330);
  line(374,345,370,350);
  back();
  int x=232,y=336,x1=236,y1=344;
  for(int i=1;i<5;i++){
     setfillstyle(1,RED);
     bar(x,y,x1,y1);
     x=x1+2;
     x1=x1+6;
  }
  size=imagesize(232,336,256,344);
  buffer=malloc(size);
  getimage(232,336,256,344,buffer);
  x=232;
  int m=0;
  while(!kbhit()){
     putimage(x,336,buffer,XOR_PUT);
     x=x+2;
     if(x>=350){
	m++;
	x=232;
     if(m==5)                         // m is no of times bar moves
	mainscreen1();
     }
     putimage(x,336,buffer,XOR_PUT);
     delay(20);                      // delay(time) is the speed of moving
  }
   getch();
   closegraph();

}

void front(char*s){
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"");
  bg_color();
  header();
  outtextxy(130,160,s);
  loading();
  closegraph();
}

void drawbar(int x1,int y1,int x2,int y2,char*s){      // to draw boxes
   setfillstyle(SOLID_FILL,RED);
   bar(x1,y1,x2,y2);
   rectangle(x1,y1,x2,y2);
   settextstyle(3,0,5);
   outtextxy((x1+x2)/2-textwidth(s)/2,y1+20,s);
}

void quit(){
   int gd=DETECT,gm;
   initgraph(&gd,&gm,"");
   bg_color();
   header();
   setfillstyle(SOLID_FILL,RED);
   bar(200,200,getmaxx()-200,getmaxy()-200);
   outtextxy(220,220,"SAVING FILES");
   delay(2000);
   bar(200,200,getmaxx()-200,getmaxy()-200);
   rectangle(220,210,getmaxx()-210,230);
   outtextxy(220,235,"Exiting");
   setfillstyle(SOLID_FILL,BLUE);
   for(int i=221;i<getmaxx()-210;i++){
      bar(221,211,i,229);
      delay(10);
   }
   delay(40);
   exit(0);
   closegraph();
}


	       /**********************************
		    END OF GENERAL FUNCTIONS
	       ***********************************/


void mainscreen2(){
   int gd=DETECT,gm;
   int x,y,but;
   char*topname="WELCOME ";
   strcat(topname,screen1ob.name);
   initgraph(&gd,&gm,"");
   mob.initmouse();
   bg_color();
   settextstyle(3,0,12);
   outtextxy(getmaxx()/2-textwidth(topname)/2,45,topname);
   header();
   drawbar(100,100,300,200,"CREATE");
   drawbar(400,100,600,200,"SEARCH");
   drawbar(100,250,300,350,"EDIT");
   drawbar(400,250,600,350,"EXIT");
   mob.showmouse();
   while(!kbhit()){
      mob.status(x,y,but);
      if(x>100&&y>100&&x<300&&y<200&&in.x.bx&7)
	 dclassob.create();
      else if(x>400&&y>100&&x<600&&y<200&&in.x.bx&7)
	 dclassob.search();
      else if(x>100&&y>250&&x<300&&y<350&&in.x.bx&7)
	 dclassob.edit();
      else if(x>400&&y>250&&x<600&&y<350&&in.x.bx&7)
	 quit();
   }
   getch();
   closegraph();
}


	    /**************************************************
		   FUNCTIONS,CLASSES FOR MAINSCREEN-1
	    ***************************************************/

void createaccount(){
   int gd=DETECT,gm;
   char fname[30];
   initgraph(&gd,&gm,"");
   bg_color();
   header();
   settextstyle(3,0,1);
   outtextxy(140,120,"ENTER CLASS: ");
   gotoxy(35,9);
   cin>>screen1ob.classno;
   outtextxy(140,153,"ENTER CLASS\'S FIFTH SUBJECT: ");
   gotoxy(53,11);
   cin>>screen1ob.subject;
   outtextxy(140,186,"ENTER NAME: ");
   gotoxy(35,13);
   cin>>screen1ob.name;
   outtextxy(140,219,"ENTER PASSWORD: ");
   gotoxy(40,15);
   cin>>screen1ob.password;
   strcpy(fname,screen1ob.name);
   strcat(strcat(fname,screen1ob.classno),".txt");
   ifstream file(fname,ios::in);
   if(file.good()){
      putagain();
      outtextxy(getmaxx()/2,getmaxy()/2,"FILE ALREADY EXIST.");
      delay(1000);
      file.close();
      mainscreen1();
   }
   else{
     ofstream ofile("accounts.txt",ios::out);
     rectangle(140,280,390,330);
     setfillstyle(SOLID_FILL,RED);
     for(int i=141;i<390;i++){
	bar(141,281,i,329);
	if(i<325)
	    outtextxy(180,290,"CHECKING FIELDS");
	else
	    outtextxy(200,290,"SAVING DATA");
	delay(10);
     }
     ofile.seekp(0,ios::end);
     ofile.write((char*)&screen1ob,sizeof(screen1ob));
     ofile.close();
   }
   closegraph();
   mainscreen1();
}

void login(){
   int gd=DETECT,gm;
   char fname[20],password[20];
   initgraph(&gd,&gm,"");
   bg_color();
   header();
   settextstyle(3,0,1);
   outtextxy(140,120,"ENTER FILE-NAME: ");
   gotoxy(40,9);
   cin>>fname;
   outtextxy(140,153,"ENTER PASSWORD: ");
   gotoxy(40,11);
   cin>>password;
   ifstream file("accounts.txt",ios::in);
   file.seekg(0,ios::beg);
   while(!file.eof()){
      file.read((char*)&screen1ob,sizeof(screen1ob));
      if(strcmp(screen1ob.name,fname)==0&&strcmp(screen1ob.password,password)==0){
	file.close();
	mainscreen2();
      }
   }
   closegraph();
   mainscreen1();
}
void copydata(char*s){
   ifstream in("accounts.txt");
   ofstream out("newaccounts.txt");
   in.seekg(0,ios::beg);
   out.seekp(0,ios::beg);
   while(!in.eof()){
       in.read((char*)&screen1ob,sizeof(screen1ob));
       if(strcmp(s,screen1ob.name)==0)
	 continue;
       else
	  out.write((char*)&screen1ob,sizeof(screen1ob));
   }
   unlink("accounts.txt");
   rename("newaccounts","accounts");
   in.close();
   out.close();
}
void deleteaccount(){
   int gd=DETECT,gm;
   char fname[30],password[30];
   clrscr();
   initgraph(&gd,&gm,"");
   bg_color();
   header();
   settextstyle(3,0,1);
   outtextxy(140,120,"ENTER CLASS: ");
   gotoxy(3,9);
   cin>>fname;
   outtextxy(140,153,"ENTER PASSWORD: ");
   gotoxy(40,11);
   cin>>password;
   ifstream file("accounts.txt",ios::in);
   file.seekg(0,ios::beg);
   while(!file.eof()){
      file.read((char*)&screen1ob,sizeof(screen1ob));
      if(strcmp(screen1ob.name,fname)==0&&strcmp(screen1ob.password,password)==0){
	 unlink(screen1ob.file);
	 copydata(fname);
	 file.close();
	 break;
      }
      else{
	  putagain();
	  outtextxy(getmaxx()/2,getmaxy()/2,"WRONG IDENTITY");
	  delay(1000);
	  file.close();
	  mainscreen1();
      }
   }
   closegraph();
}


	/*****************************************************
		  END  FUNCTIONS    OF MAINSCREEN-1
	******************************************************/


void mainscreen1(){
   int gd=DETECT,gm;
   int x,y,but;
   clrscr();
   initgraph(&gd,&gm,"");
   mob.initmouse();
   bg_color();
   header();
   drawbar(100,100,300,200,"CREATE");
   drawbar(400,100,600,200,"LOGIN");
   drawbar(100,250,300,350,"DELETE");
   drawbar(400,250,600,350,"EXIT");
   mob.showmouse();
   while(!kbhit()){
      mob.status(x,y,but);
      if(x>100&&y>100&&x<300&&y<200&&in.x.bx&7)
	 createaccount();
      else if(x>400&&y>100&&x<600&&y<200&&in.x.bx&7)
	 login();
      else if(x>100&&y>250&&x<300&&y<350&&in.x.bx&7)
	 deleteaccount();
      else if(x>400&&y>250&&x<600&&y<350&&in.x.bx&7)
	 quit();
   }
   getch();
   closegraph();
}

void main(){
   front("asfdfd");
   clrscr();
   mainscreen1();
   getch();
   return;
}