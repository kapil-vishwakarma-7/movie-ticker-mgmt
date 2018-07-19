#include<conio.h>
#include<stdio.h>
#include<string.h>
#define username "nikita"
#define password "nikita"


/**
Developed By Kapil Vishwakarma.
CSE 2nd Year.
SISTec E
Copyright @kvishwakarma
*/

/*
  SEAT ARRANGEMENT
		   SILVER    A-H
		   GOLD      I-N
		   PLATINUM  O-T
		   DIAMOND   U-Z
		   twenty seats for an alphabet
		   totalSeats = 26*20 = 520;
*/



FILE * f1 ;
char *showTime[5] = {"","12- 3","3 - 6","6 - 9","9 -12"};
char *ticketType[5]={"","SILVER","GOLD","PLATINUM","DIAMOND"};
float price[] = {0.00f,120.0f,200.0f,440.0f,600.0f};
struct mdate{
int dd,mm,yy;
};
struct Ticket{
char movieName[30],name[20],rowName;
int ticketNumber,show,number,type,seatNumber;
};

struct Show{
char name[30];
int show[5];
};

void cancelTicket();
void bookTicket();
void access();
void addMovie();
void deleteShow();
void showBookedTicket();


void main()
{
char pass[10],user[10];
clrscr();
printf("Enter Username : "); scanf("%s",&user);
printf("Enter Password : "); scanf("%s",&pass);
if(strcmp(username,user) != 0 && strcmp(pass,password) != 0)
return;
access();
}


void cancelTicket(){
struct Ticket ticket;
FILE *f2;
int num,flag=0;
clrscr();
textcolor(WHITE);
gotoxy(10,4);cprintf("Enter Ticket Number : ");scanf("%d",&num);
f1 = fopen("ticket.dat","ab+");
f2 = fopen("temp.dat","ab+");
 while(fread(&ticket,sizeof(ticket),1,f1) == 1){
  if(ticket.ticketNumber != num){
   fwrite(&ticket,sizeof(ticket),1,f2);
  }
  else{
  flag=1;
  }
 }
 fclose(f1);
 fclose(f2);
 remove("ticket.dat");
 rename("temp.dat","ticket.dat");
 if(flag) {
 gotoxy(10,6);cprintf("Ticket Canceled.");
 }
 else{
 gotoxy(10,6);cprintf("Ticket Number Invalid.");
 }
 getch();
}


void deleteShow(){
struct Show show;
char *movieName;
int flag=0;
FILE * f2;
clrscr();
textcolor(WHITE);
gotoxy(10,4); cprintf("Enter Name : ");scanf("\n%[^\n]",movieName);
f2 = fopen("temp.dat","ab+");
f1 = fopen("movie.dat","ab+");
 while(fread(&show,sizeof(show),1,f1) == 1){
  if(strcmp(movieName,show.name) != 0){
    fwrite(&show,sizeof(show),1,f2);
   }else{
   flag=1;
   }
 }
 fclose(f1);
 fclose(f2);
 remove("movie.dat");
 rename("temp.dat","movie.dat");
 if(flag){cprintf("Show Deleted ");}
 else{cprintf("Not Found");
 }
 getch();
}


void heading(char msg[] ){
int i;
textcolor(BLUE);gotoxy(1,1);for(i=0;i<79;i++) cprintf("\xDB");
textcolor(WHITE+BLINK);gotoxy(32,1);cprintf("%s",msg);
textcolor(WHITE);
}


void bookTicket(){
struct Show show[10];
struct Ticket ticket,t1;
int i=1,ch,tn=1;
char st;
clrscr();
f1 = fopen("movie.dat","ab+");
rewind(f1);
  while(fread(&show[i],sizeof(show[i]),1,f1) == 1){
  gotoxy(10,4+i);cprintf("%d. %s",i,show[i].name);
  i++;
 }
 gotoxy(10,4+i);ch = getch()-48;
 if(ch >= i || ch < 0) return;
 sprintf(ticket.movieName,show[ch].name);
  clrscr();
  gotoxy(20,5);cprintf("Enter Customer Name :");
  i=1;
  gotoxy(20,7);cprintf("          Show Time : ");
  gotoxy(9,8);cprintf("[");
  while(i<5){
   if(show[ch].show[i] == 1){
   textcolor(GREEN);
   cprintf("%d:%s, ",i,showTime[i]);
   }
   else{
   textcolor(RED);
   cprintf("%d:%s, ",i,showTime[i]);
   }
   i++;
  }
  textcolor(WHITE);cprintf("\b\b]");
  gotoxy(23,5);

  gotoxy(20,10);cprintf("        Ticket Type : ");
  gotoxy(1,11);cprintf("[1:%s 2:%s 3:%s 4:%s]",ticketType[1],ticketType[2],ticketType[3],ticketType[4]);
  gotoxy(20,13);cprintf("    Number of seats : ");
  gotoxy(42,5);scanf("\n%[^\n]",ticket.name);
  gotoxy(42,7); ticket.show = getche()-48;
  gotoxy(42,10); ticket.type = getche()-48;
  gotoxy(42,13);scanf("%d",&ticket.number);

  f1 = fopen("ticket.dat","ab+");
  switch(ticket.type){
  case 1:
    ticket.rowName = 'A';
   break;
  case 2:
    ticket.rowName = 'I';
   break;
  case 3:
    ticket.rowName = 'O';
    break;
  case 4:
    ticket.rowName = 'U';
   break;
  }
  ticket.seatNumber=0;
  i=1;
  while(fread(&t1,sizeof(t1),1,f1) == 1){
	if(t1.type==ticket.type && t1.show == ticket.show){
	  if(ticket.seatNumber+ticket.number > 20){
	   ticket.rowName = t1.rowName+1;
	   ticket.seatNumber = 1;
	  }
	  else{
	   ticket.seatNumber = (t1.seatNumber+ticket.number);
	  }
	}
	// Ticket Number Logic
	  if(i != tn)
	    tn = i;
  i++;
  }
  ticket.ticketNumber = tn;

  if(fwrite(&ticket,sizeof(ticket),1,f1)==1){
   gotoxy(10,15);
   textcolor(GREEN+BLINK);cprintf("Amount is Rs. %.2f TICKET BOOKED",ticket.number*price[ticket.type]);
  }
  fclose(f1);
 getch();
}
void showBookedTicket(){
int i=1;
struct Ticket ticket;
clrscr();
heading("Booked Ticket");
textcolor(WHITE);
gotoxy(1,4);cprintf("TN.");
gotoxy(6,4);cprintf("MOVIE NAME");
gotoxy(30,4);cprintf("CUST. NAME");
gotoxy(45,4);cprintf("Show Time");
gotoxy(58,4);cprintf("TYPE");
gotoxy(68,4);cprintf("NO");
gotoxy(73,4);cprintf("SEATS");
f1 = fopen("ticket.dat","ab+");
while(fread(&ticket,sizeof(ticket),1,f1) == 1)  {
gotoxy(1,4+i);cprintf("%d",ticket.ticketNumber);
gotoxy(6,4+i);cprintf("%s",ticket.movieName);
gotoxy(48,4+i);cprintf("%s",showTime[ticket.show]);
gotoxy(30,4+i);cprintf("%s",ticket.name);
gotoxy(68,4+i);cprintf("%d",ticket.number);
gotoxy(58,4+i);cprintf("%s",ticketType[ticket.type]);
gotoxy(73,4+i);cprintf("%c%d-%c%d",ticket.rowName,ticket.seatNumber,ticket.rowName,ticket.number+ticket.seatNumber-1);
i++;
}
getch();
}

void addMovie(){
struct Show show;

f1 = fopen("movie.dat","ab+");
if(f1 == NULL){
printf("Cannot Open File.");
getch();
return;
}
clrscr();
textcolor(WHITE);
gotoxy(10,6);printf("      Movie Name : ");
gotoxy(10,8);printf("show Time (12-3) : ");
gotoxy(10,10);printf("show Time (3-6)  : ");
gotoxy(10,12);printf("show Time (6-9)  : ");
gotoxy(10,14);printf("show Time (9-12) : ");
gotoxy(30,6);scanf("\n%[^\n]",&show.name);
gotoxy(30,8);show.show[1] = getche()-48;
gotoxy(30,10);show.show[2]= getche()-48;
gotoxy(30,12);show.show[3]= getche()-48;
gotoxy(30,14);show.show[4]= getche()-48;
if(fwrite(&show,sizeof(show),1,f1) == 1 ){
	gotoxy(25,16);cprintf("Show Added.");
	getch();
}
fclose(f1);
}




void access(){
int ch ;

while(ch != 6){
  ch = menu();
  switch(ch){
	  case 1:
		bookTicket();
		break;
	  case 2:
		cancelTicket();
		break;
	  case 3:
		addMovie();
		break;
	  case 4:
		deleteShow();
		break;
	  case 5:
		showBookedTicket();
		break;
	  case 6:
		exit(0);
		break;

 }
}
}


int menu(){
int ch,select=1;
char c;

clrscr();
heading("Dashboard");
textbackground(BLACK);

do{

switch(c){
	 case 72:
	   if(select == 1 ) select =6;
	   else select--;
	   break;

	case 80:
	   if(select == 6) select=1;
	   else select++;
       break;
	}
textbackground(BLACK);
textcolor(WHITE);gotoxy(20,4);cprintf("1.Book Ticket.");
textcolor(WHITE);gotoxy(20,6);cprintf("2.Cancel Ticket.");
textcolor(WHITE);gotoxy(20,8);cprintf("3.Add New Show.");
textcolor(WHITE);gotoxy(20,10);cprintf("4.Delete Show.");
textcolor(WHITE);gotoxy(20,12);cprintf("5.See Booked Tickets.");
textcolor(WHITE);gotoxy(20,14);cprintf("6.Exit.");
textbackground(BLUE);
switch(select){
case 1:textcolor(WHITE);gotoxy(20,4);cprintf("1.Book Ticket.");
	   break;
case 2:textcolor(WHITE);gotoxy(20,6);cprintf("2.Cancel Ticket.");
	   break;
case 3:textcolor(WHITE);gotoxy(20,8);cprintf("3.Add New Show.");
	   break;
case 4:textcolor(WHITE);gotoxy(20,10);cprintf("4.Delete Show.");
	   break;
case 5:textcolor(WHITE);gotoxy(20,12);cprintf("5.See Booked Tickets.");
	   break;
case 6:textcolor(WHITE);gotoxy(20,14);cprintf("6.Exit.");
	   break;
}

}while((c = getch()) != 13);
 textbackground(BLACK);

return select;
}

