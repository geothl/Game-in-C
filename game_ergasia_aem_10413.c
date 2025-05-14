#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <string.h>
#include <time.h>
#include<stdbool.h>
#define T 50
#define TM 100

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define RETURN 13
#define SPACE 32



void tr(int x);//Ο παίκτης που αντιστοιχεί στο στοιχείο δομής P[x] καθορίζει τη φορά της κίνησης που επιθυμεί να εκτελέσει με διακρατικά βελάκια που αντιστοιχούν στα αντίστοιχα πλήκτρα του πληκτρολόγιού.( Ταυτόχρονη εκτύπωση τους στον πίνακα στοιχείων).
void pinakas(void);//Εκτύπωση του πίνακα του παιχνιδιού στο οποίο θα προβάλλονται ο αριθμός του γύρου, στοιχεία κίνησης, σειράς παικτών και φορά/σφοδρότητα αέρα.
void clearair(void);//Καθαρισμός του χώρου που εκτυπώνονται τα στοιχεία του ανέμου στον πίνακα.
void wind(void);//Τυχαιοποίηση φοράς και σφοδρότητας ανέμου ανά γύρο και εκτύπωση τους στον πίνακα. Ειδικά effect για τον επερχόμενο άνεμο.  srand(clock()); Φύτρα.
void lose(int x); //ΣΥΝΑΡΤΗΣΗ ΣΕ ΠΕΡΙΠΤΩΣΗ ΠΟΥ ΠΕΣΕΙ ΣΤΟ ΝΗΣΙ
void landscape(void);//Εκτύπωση του χώρου του παιχνιδιού με χαρακτήρες.
void gotoxy(int x,int y);//Μετακίνηση του cursor της κονσόλας στο σημείο της κονσόλας με συντεταγμένες (x,y). Μode console πρέπει να είναι full screen.
void selevros(int x);//
void clearPAD(int x);//Καθαρισμός του χώρου που εκτυπώνονται τα στοιχεία του παίκτη P[x] στον πίνακα.
void arrowpad(int x,int y);//Αντιστοίχιση της tr(); στο πίνακα στοιχειών .
void animation(void);//Προβολή παικτών σε Hold state και εκτύπωση συντεταγμένων τον θέσεων τους. Κλήση όλων των άλλων συναρτήσεων προς την υλοποίηση του παιχνιδιού. Χειρισμός μεταβλητών νίκης.
void movingeffect(int x);//Εκτέλεση κινήσεων παίκτη P[x] με εμφωλευμένες εντολές switch με βασικό επίπεδο την ένταση ανέμου(intensity), δεύτερο το εύρος κίνησης, τρίτο τη φορά που διάλεξε ο παίκτης και τελευταίο επίπεδο τη φορά αέρα. Υλοποίηση των κανόνων παιχνιδιού.
short direction_air,intensity;//ΜΕΤΑΒΛΗΤΕΣ ΓΙΑ ΦΟΡΑ ΚΑΙ ΕΝΤΑΣΗ ΑΝΕΜΟΥ
char key;//ΓΙΑ ΥΠΟΔΟΧΗ ΧΑΡΑΚΤΗΡΩΝ
short round=1;//ΜΕΤΡΗΤΗΣ ΓΥΡΟΥ
short k=0;
struct player {//ΔΟΜΗ ΜΕ ΣΤΟΙΧΕΙΑ ΠΑΙΚΤΩΝ
int lastH;   //      Οριζόντια συντεταγμένη θέσης παίκτη κονσόλας.
int lastV;    // Κάθετης συντεταγμένη θέσης παίκτη κονσόλας.
short evros;   //Ευρός κίνησης παίκτη.

short ha;  // Αποθήκευση προηγούμενης κατεύθυνσης παίκτη.
int hold;  //Για χρήση σε animation κίνησης σε παραπάνω από μια θέσεις.
short prmv; //Καταμέτρηση θέσης κίνησής παίκτη.
short a1; //Χρήση για καθαρισμό βέλους κατεύθυνσης και Αποθήκευση κατεύθυνσης που θέλει να κινηθεί ο παίκτης.
} ;
struct player P[2];


//ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΟΡΙΩΝ ΝΗΣΙΟΥ
int corx[200]={40,41,42,39,40,42,43,38,44,45,46,37,38,47,48,49,50,51,52,36,37,51,52,36,50,51,52,53,54,55,56,57,58,35,36,55,70,71,72,34,56,57,58,59,60,61,70,71,72,73,74,75,35,36,62,63,64,65,66,67,68,69,70,75,76,36,74,75,37,38,74,75,36,37,70,71,72,73,35,36,66,67,68,69,70,34,65,66,35,36,37,38,39,66,67,68,39,40,60,61,62,63,64,65,40,41,57,58,59,60,42,43,44,45,56,57,45,46,47,48,49,50,51,52,53,54,55,56,57};


int cory[200]={10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,13,13,13,13,14,14,14,14,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,19,19,19,20,20,20,20,21,21,21,21,21,21,22,22,22,22,22,22,22,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28};

short dir;
short lost=20;//metavliti gia xrisi se mixanismo htas
short towinA=0; //στη μέση της διαδρομής του Α γίνεται 1.
short towinB=0;//στη μέση της διαδρομής του Β γίνεται 1.
short WinA=0; //στη τέλος της διαδρομής του Α γίνεται 1.
short WinB=0; //στη τέλος της διαδρομής του Β γίνεται 1.

int main(void){
srand(clock());
//P[0].ad =19;          //ΑΡΧΙΚΟΠΟΙΗΣΗ ΘΕΣΕΩΝ
//P[1].ad =19;
P[0].lastH= 50;
P[0].lastV=35;
P[1].lastH=50;
P[1].lastV=30;
P[0].evros=19;
P[1].evros=19;
printf("ΑΓΩΝΑΣ ΙΣΤΙΟΠΛΟΙΑΣ");
for(int i=1;i<=3;i++){
Sleep(1000);
printf(".");
}printf("ΣΤΗ ΛΙΜΝΗ ΤΩΝ ΑΝΕΜΩΝ");
printf("\n\n\n\nΠΑΡΑΚΑΛΩ ΑΝΟΙΞΤΕ ΤΟ ΠΑΡΑΘΥΡΟ ΤΟΥ ΠΡΟΓΡΑΜΜΑΤΟΣ ΣΕ ΠΛΗΡΗ ΟΘΟΝΗ.\nKANONEΣ ΠΑΙΧΝΙΔΙΟΥ ΣΤΟ ΕΓΓΡΑΦΟ ΤΕΚΜΗΡΙΩΣΗΣ.\nΓΙΑ ΚΑΘΟΡΙΣΜΟ ΦΟΡΑΣ ΑΞΙΟΠΟΙΗΣΤΕ ΤΑ ΒΕΛΗ ΤΟΥ ΠΛΗΚΤΡΟΛΟΓΙΟΥ\nΚΩΔΙΚΟΣΕΛΙΔΑ cp1253\nΠΑΤΗΣΤΕ ΕΝΤΕΡ ΓΙΑ ΕΝΑΡΞΗ.");
gotoxy(0,40);printf("Απο Θεολόγη Γεώργιο.");
landscape();
pinakas();
animation();

gotoxy(0,41);
return 0;
}

void seecoord(int x,int y){
gotoxy(30,6);
for (int k=1;k<=15;k++) printf("\b");
for (int k=1;k<=15;k++) printf(" ");
gotoxy(15,6);
printf("x:%d  y:%d",x,y);
gotoxy(x,y);
}

void gotoxy(int x, int y){
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
COORD position={x,y};
SetConsoleCursorPosition(h,position);
}





void landscape(void){

gotoxy(0,0);
if(k==0){
do{
key=getch();
 system ("cls");
}while(key!=13);
k++;}
system("color 3");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQ\n");
printf("QQQQQQQQQQ\n");
printf("QQQQQQQQQ\n");
printf("QQQQQQQQ\n");
printf("QQQQQQQ\n");
printf("QQQQ\n");
printf("QQQQ\n");
printf("QQQQ\n");
printf("QQQ\n");
printf("QQQQ\n");
printf("QQQQQ\n");
printf("QQQQQ\n");
printf("QQQQQ\n");
printf("QQQQQ\n");
printf("QQQQQQ\n");
printf("QQQQQQ\n");
printf("QQQQQQQ\n");
printf("QQQQQQQ\n");
printf("QQQQQQQQQ\n");
printf("QQQQQQQQQ\n");
printf("QQQQQQQQQ\n");
printf("QQQQQQQQQ\n");
printf("QQQQQQQQQQ\n");
printf("QQQQQQQQQQ\n");
printf("QQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
 gotoxy(50,39);
printf("|--->|");
gotoxy(70,39);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(72,38);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(74,37);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(75,36);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(83,35);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(86,34);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(86,33);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(86,32);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(87,31);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(89,30);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(92,29);
printf("QQQQQQQQQQQQQQQQQQQQQQQ");

gotoxy(93,28);
printf("QQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(93,27);
printf("QQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(93,26);
printf("QQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(93,25);
printf("QQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(94,24);
printf("QQQQQQQQQQQQQQQQQQQQQ");
gotoxy(95,23);
printf("QQQQQQQQQQQQQQQQQQQQ");
gotoxy(96,22);
printf("QQQQQQQQQQQQQQQQQQQ");
gotoxy(97,21);
printf("QQQQQQQQQQQQQQQQQQ");
gotoxy(97,20);
printf("QQQQQQQQQQQQQQQQQQ");
gotoxy(97,19);
printf("QQQQQQQQQQQQQQQQQQ");
gotoxy(96,18);
printf("QQQQQQQQQQQQQQQQQQQ");
gotoxy(96,17);
printf("QQQQQQQQQQQQQQQQQQQ");
gotoxy(96,16);
printf("QQQQQQQQQQQQQQQQQQQ");
gotoxy(98,15);
printf("QQQQQQQQQQQQQQQQQ");
gotoxy(98,14);
printf("QQQQQQQQQQQQQQQQQ");
gotoxy(98,13);
printf("QQQQQQQQQQQQQQQQQ");
gotoxy(98,12);
printf("QQQQQQQQQQQQQQQQQ");
gotoxy(97,11);
printf("QQQQQQQQQQQQQQQQQQ");
gotoxy(97,10);
printf("QQQQQQQQQQQQQQQQQQ");
gotoxy(97,9);
printf("QQQQQQQQQQQQQQQQQQ");
gotoxy(93,8);
printf("QQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(93,7);
printf("QQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(90,6);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(90,5);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(80,4);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(79,3);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(79,2);
printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
gotoxy(40,10);//ΕΚΤΥΠΩΣΗ ΝΗΣΙΟΥ ΜΕ PRINTF
printf("aaa");
gotoxy(39,11);
printf("aaaaa");
gotoxy(38,12);
printf("aaaa*aaaa");
gotoxy(37,13);
printf("aaa*aa*aa*aaaaaa");
gotoxy(36,14);
printf("aaaa*aaa*____*aaa");
gotoxy(36,15);
printf("aaaa*a /_____| aaaaa--]");
gotoxy(35,16);
printf("aaaaaa /______) aaaaa");
gotoxy(70,16);printf("aaa");
gotoxy(34,17);
printf("aaaaaa | ISOLA | aaaaaaaaaaa");
gotoxy(70,17);printf("aaaaaa");
gotoxy(35,18);
printf("aaaaaa |     | aaaaaaaaaaaaaaaaaaaaaaaaaaa");
gotoxy(36,19);
printf("aaaaa |_____| aaaaaaaaaaaaaaaaaaaaaaaaaa");
gotoxy(37,20);
printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
gotoxy(36,21);
printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
gotoxy(35,22);
printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
gotoxy(34,23);
printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
gotoxy(35,24);printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
gotoxy(39,25);
printf("aaaaaaaaaaaaaaaaaaaaaaaaaaa");
gotoxy(40,26);
printf("aaaaaaaaaaaaaaaaaaaaa");
gotoxy(42,27);
printf("aaaaaaaaaaaaaaaa");
gotoxy(45,28);
printf("aa /START/ aa");

}


void pinakas(void){

gotoxy(130,2);for(int k=1;k<=38;k++){putchar('_');}
for(int i=3;i<=40;i++) {
gotoxy(130,i);
putchar('|');
}
for(int i=15;i<=25;i++) {
gotoxy(147,i);
putchar('|');
}
for(int i=3;i<=40;i++) {
gotoxy(167,i);
putchar('|');
}
gotoxy(131,8);for(int k=1;k<=36;k++){putchar('_');}
gotoxy(130,40);for(int k=1;k<=38;k++){putchar('*');}
gotoxy(131,15); for(int k=1;k<=36;k++){putchar('_');}
gotoxy(131,25); for(int k=1;k<=36;k++){putchar('_');}
gotoxy(131,26); printf("          ΜΕΤΡΗΤΗΣ ΑΕΡΑ");
gotoxy(131,5);  printf("             ΓΥΡΟΣ %d",round);
gotoxy(131,16);  printf("  ΠΑΙΚΤΗΣ A           ΠΑΙΚΤΗΣ B");
gotoxy(131,10);  printf("ΣΕΙΡΑ ΤΟΥ ΠΑΙΚΤΗ Α");

//gotoxy(lastH,lastV);
}




void selevros(int x){
    fflush(stdin);
if(x==0){
gotoxy(131,22);
printf("Διαλεξε ευρος");
gotoxy(131,23);
printf("κινησης(0-3):");
do{
gotoxy(138,24);
printf(" \b");

scanf("%d",&P[0].evros);
}while((P[0].evros!=0)&&(P[0].evros!=1)&&(P[0].evros!=2)&&(P[0].evros!=3));
gotoxy(P[0].lastH,P[0].lastV);
}
else{
gotoxy(150,22);
printf("Διαλεξε ευρος");
gotoxy(150,23);
printf("κινησης(0-3):");
do{
gotoxy(156,24);
printf(" \b");

scanf("%d",&P[1].evros);
}while((P[1].evros!=0)&&(P[1].evros!=1)&&(P[1].evros!=2)&&(P[1].evros!=3));
gotoxy(P[1].lastH,P[1].lastV);
}

}


void tr(int x){
P[x].a1=20;
char c;
c=(x==0)?'A':'B';
do{
key=getch();

if(P[x].a1==0) {gotoxy(P[x].lastH-3,P[x].lastV);for(int i=1;i<=3;i++){printf(" ");}}
if(P[x].a1==1) {gotoxy(P[x].lastH+1,P[x].lastV); for(int i=1;i<=3;i++){printf(" ");}}
if(P[x].a1==2){gotoxy(P[x].lastH,P[x].lastV-2);printf(" ");gotoxy(P[x].lastH,P[x].lastV-1);printf(" ");
}
if(P[x].a1==3) {gotoxy(P[x].lastH,P[x].lastV+1);printf(" ");}
gotoxy(P[x].lastH,P[x].lastV); printf("%c",c);
gotoxy(P[x].lastH,P[x].lastV);

switch(key){
case KEY_LEFT:
     for(int i=1;i<=3;i++){printf("\b");}
    printf("<");
     for(int i=1;i<=2;i++){printf("-");}
     arrowpad(0,x);
      P[x].a1=0;

    // P[x].ad=0;
     break;
case KEY_RIGHT:
    gotoxy(P[x].lastH+1,P[x].lastV);
     for(int i=1;i<=2;i++){printf("-");}
     printf(">");
     arrowpad(1,x);
     P[x].a1=1;

    // P[x].ad=1;
     break;

 case KEY_UP:
    gotoxy(P[x].lastH,P[x].lastV-1); printf("|");
 gotoxy(P[x].lastH,P[x].lastV-2);
    printf("^");
    arrowpad(2,x);
    P[x].a1=2;

    //P[x].ad=2;
     break;
case KEY_DOWN:
    gotoxy(P[x].lastH,P[x].lastV+1); printf("!");
    arrowpad(3,x);
    P[x].a1=3;

    //P[x].ad=3;//a is the descision of where to finally move
     break;



 default:
    break;

}
landscape();
}while(key!=13);
gotoxy(P[x].lastH,P[x].lastV);}



void clearPAD(int x){
int clr;
clr=(x==1)?17:0;
for(int h=0;h<7;h++){
gotoxy(131+clr,18+h);

printf("               ");

}
}

void arrowpad(int x,int y){
int ar;
if(y==0)ar=0;
if(y==1)ar=18;
clearPAD(y);
gotoxy(138+ar,20);
switch(x){
case 0:
     for(int i=1;i<=3;i++){printf("\b");}
    printf("<");
     for(int i=1;i<=2;i++){printf("-");}
break;
case 1:
     for(int i=1;i<=2;i++){printf("-");}
     printf(">");
     break;

 case 2:
    gotoxy(138+ar,19); printf("|");
    gotoxy(138+ar,18);
    printf("^");
     break;
case 3:
    gotoxy(138+ar,21); printf("!");
     break;
default:
    break;
}
gotoxy(P[x].lastH,P[x].lastV);
}


void wind(void)
{
short randintensity;
clearair();
//srand(clock());
intensity=rand()%3;//ΓΙΑ ΔΙΑΧΕΙΡΙΣΗ ΔΥΣΚΟΛΙΑΣ
direction_air=rand()%4;

gotoxy(148,31);
switch(direction_air){
case 0:
     for(int i=1;i<=3;i++){printf("\b");}
    printf("<");
     for(int i=1;i<=2;i++){printf("-");}
     break;
case 1:
     for(int i=1;i<=2;i++){printf("-");}
     printf(">");
     break;

 case 2:
    gotoxy(148,30); printf("|");
 gotoxy(148,29);
    printf("^");
     break;
case 3:
    gotoxy(148,32); printf("!");
     break;
}
switch(intensity){
case 0:
//case 5:
Sleep(2000);
 system("color 3");
gotoxy(142,38); printf("ΑΠΝΟΙΑ");

     break;
 case 1:

Sleep(500);
    system("color 1");
    Sleep(500);
    system("color 3");
    Sleep(500);
    system("color 1");
    Sleep(500);
    system("color 3");
    Sleep(500);
    system("color 1");
  gotoxy(142,38); printf("ΚΑΝΟΝΙΚΟΣ ΑΝΕΜΟΣ");
     break;
case 2:

    Sleep(500);
    system("color 4");
    Sleep(500);
    system("color 3");
    Sleep(500);
    system("color 4");
    Sleep(500);
    system("color 3");
    Sleep(500);
    system("color 4");
      gotoxy(142,38); printf("ΔΥΝΑΤΟΣ ΑΝΕΜΟΣ");
     break;
}
}

void clearair(void){
    gotoxy(131,17); printf("                              ");
gotoxy(131,29);
for(int h=0;h<4;h++){
gotoxy(131,29+h);

printf("                            ");

}
gotoxy(140,38);printf("                           ");
}


void animation(void){
gotoxy(P[0].lastH,P[0].lastV);//ΑΡΧΙΚΕΣ ΘΕΣΕΙΣ ΠΑΙΚΤΩΝ
printf("A");
gotoxy(P[1].lastH,P[1].lastV);
printf("B");
gotoxy(133,17);
printf(" (%d,%d)",P[0].lastH,P[0].lastV);
gotoxy(153,17);
printf(" (%d,%d)",P[1].lastH,P[1].lastV);
do{

gotoxy(131,10);printf("                            ");
gotoxy(131,10);  printf("ΣΕΙΡΑ ΤΟΥ ΠΑΙΚΤΗ Α");//ΜΟΡΦΟΠΟΙΗΣΕΙΣ ΣΕΙΡΑΣ ΠΑΙΚΤΩΝ ΣΤΟΝ ΠΙΝΑΚΑ ΚΑΙ ΑΝΑΜΟΝΗ ΑΝΕΜΩΝ

tr(0);
selevros(0);
gotoxy(131,10);  printf("ΣΕΙΡΑ ΤΟΥ ΠΑΙΚΤΗ Β");
tr(1);
selevros(1);

gotoxy(131,10);printf("                           ");








gotoxy(131,10);  printf("          ΑΝΑΜΟΝΗ ΓΙΑ ΑΝΕΜΟ");
Sleep(800);
wind();
P[0].hold=0;
P[1].hold=0;
gotoxy(131,10);printf("                           ");gotoxy(131,10);  printf("           ΑΦΙΞΗ ΑΝΕΜΟΥ  ");
gotoxy(P[0].lastH,P[0].lastV);
printf(" ");
movingeffect(0);
gotoxy(P[1].lastH,P[1].lastV);
printf(" ");
movingeffect(1);
P[0].ha=P[0].a1;//ΑΠΟΘΗΚΕΥΣΗ ΤΗΣ ΚΑΤΕΥΘΥΝΣΗΣ ΓΙΑ ΤΟΝ ΕΠΟΜΕΝΟ ΓΥΡΟ
P[1].ha=P[1].a1;//ΑΠΟΘΗΚΕΥΣΗ ΤΗΣ ΚΑΤΕΥΘΥΝΣΗΣ ΓΙΑ ΤΟΝ ΕΠΟΜΕΝΟ ΓΥΡΟ
clearPAD(0);
clearPAD(1);
++round;//ΑΥΞΗΣΗ ΜΕΤΡΗΤΗ ΓΥΡΟΥ
gotoxy(133,17);
printf(" (%d,%d)",P[0].lastH,P[0].lastV);//ΕΚΤΥΠΩΣΗ ΤΩΡΙΝΩΝ ΣΥΝΤΕΤΑΓΜΕΝΩΝ
gotoxy(152,17);
printf(" (%d,%d)",P[1].lastH,P[1].lastV);
Sleep(1000);
 system("color 3");
 lose(0);
 lose(1);
 if(lost==1) break;
gotoxy(131,5);  printf("             ΓΥΡΟΣ %d",round);//ΕΚΤΥΠΩΣΗ ΓΥΡΟΥ

if(P[0].lastH<=40&&(P[0].lastV<10))towinA=1;
if((towinA==1)&&(P[0].lastH==40||P[0].lastH==41||P[0].lastH==42)&&(P[0].lastV<10)){WinA=1; break; }//ΣΥΝΘΗΚΕΣ ΝΙΚΗΣ
if(P[1].lastH>=40&&(P[1].lastV<10))towinB=1;
if((towinB==1)&&(P[1].lastH==40||P[1].lastH==41||P[1].lastH==42)&&(P[1].lastV<10)){WinB=1;}
if((towinB==1)&&(P[0].lastH==40||P[0].lastH==41||P[0].lastH==42)&&(P[0].lastV<10))break;
if((towinB==1)&&(P[1].lastH==40||P[1].lastH==41||P[1].lastH==42)&&(P[1].lastV<10))break;



}while(1);

if(WinA==1){gotoxy(131,16); printf("Ο ΠΑΙΚΤΗΣ A ΚΕΡΔΙΣΕ!!!\nΣΥΓΧΑΡΗΤΗΡΙΑ");}
if(WinB==1){gotoxy(131,16); printf("Ο ΠΑΙΚΤΗΣ Β ΚΕΡΔΙΣΕ!!!\nΣΥΓΧΑΡΗΤΗΡΙΑ");}
if((WinA==WinB)&&(lose!=1)){gotoxy(131,16); printf("ΙΣΟΠΑΛΙΑ");}
}



void movingeffect(int x){//4 ΕΠΙΠΕΔΑ ΕΦΩΛΕΥΜΕΝΩΝ SWITCH
char c;//ΚΑΘΟΡΙΣΜΟΣ ΧΑΡΑΚΤΗΡΑ ΠΑΙΚΤΗ

if(x==1)c='B';
else c='A';

switch(intensity){
 case 0:

switch(P[x].evros){
case 0:
    printf("\b");
    P[x].prmv=0;
    printf("%c",c);
   break;
 case 1:
     printf("\b");
       P[x].prmv=0;
       printf("%c",c);
   break;
 case 2:
      P[x].prmv=0;
     printf("\b");
     printf("%c",c);
   if(P[x].prmv>=3){
       switch(P[x].ha){
   case 0:
       printf("\b ");
       --P[x].lastH;
       gotoxy(P[x].lastH,P[x].lastV);

       break;
     case 1:
         printf("\b ");
         ++P[x].lastH;
       gotoxy(P[x].lastH,P[x].lastV);
       break;
    case 2:
        printf("\b ");
         --P[x].lastV;
       gotoxy(P[x].lastH,P[x].lastV);
       break;
     case 3:
         printf("\b ");
         ++P[x].lastV;
       gotoxy(P[x].lastH,P[x].lastV);

       break;}
       printf("%c",c);
        }
   break;
case 3:
     P[x].prmv=0;
    printf("\b");
    printf("%c",c);
    if(P[x].prmv>=3){
  switch(P[x].ha){
   case 0:
       printf("\b ");
       --P[x].lastH;
       gotoxy(P[x].lastH,P[x].lastV);
       break;
     case 1:
         printf("\b ");
         ++P[x].lastH;
       gotoxy(P[x].lastH,P[x].lastV);
       break;
    case 2:
        printf("\b ");
         --P[x].lastV;
       gotoxy(P[x].lastH,P[x].lastV);
       break;
     case 3:
         printf("\b ");
         ++P[x].lastV;
       gotoxy(P[x].lastH,P[x].lastV);
       break;}
        printf("%c",c);}
   break;

}  break; //end of no wind




//NORMAL WIND
            case 1:
switch(P[x].evros){
case 0:
printf("\b");
P[x].prmv=0;
 printf("%c",c);
break;

case 1://evros 1 me normal aera
switch(P[x].a1){
                 case 0:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa pania
  printf("\b ");
P[x].prmv=1;
--P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
 printf("%c",c);
break;
case 1://evros 1 me normal aera me fora dejia kai antiropa pania
P[x].prmv=0;
printf("\b");
 printf("%c",c);
 break;
case 2://evros 1 me normal aera me fora NS dejia kai katheta pania
case 3:
printf("\b ");
P[x].prmv=1;
--P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
 printf("%c",c);
break;
}
                     break;

                     case 1:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai antiropa pania
printf("\b");
P[x].prmv=0;
 printf("%c",c);
break;
case 1://evros 1 me normal aera me fora dejia kai omoropa pania
 printf("\b ");
P[x].prmv=1;
++P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
 printf("%c",c);
 break;
case 2://evros 1 me normal aera me fora NS dejia kai katheta pania
case 3:
printf("\b ");
P[x].prmv=1;
++P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
 printf("%c",c);
break;
}
                         break;

                         case 2:
  switch(direction_air){
case 0://evros 1 me normal aera me fora WE kai katheta pania
case 1:
 printf("\b ");
P[x].prmv=1;
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
 printf("%c",c);
 break;

case 2://evros 1 me normal aera me fora North  kai omoropa pania
     printf("\b ");
P[x].prmv=1;
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
 printf("%c",c);
break;
case 3://evros 1 me normal aera me fora South  kai antiropa pania
printf("\b");
P[x].prmv=0;
 printf("%c",c);
break;
}
                            break;

                         case 3:
switch(direction_air){
case 0://evros 1 me normal aera me fora WE kai katheta pania
case 1:
 printf("\b ");
P[x].prmv=1;
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
 printf("%c",c);
 break;
case 2://evros 1 me normal aera me fora North  kai antiropa pania
 printf("\b");
P[x].prmv=0;
 printf("%c",c);
break;
case 3://evros 1 me normal aera me fora North  kai omoropa pania
printf("\b ");
P[x].prmv=1;
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
 printf("%c",c);
break;
}
                             break;
}
break;//end of evros 1












//////////////////////////////////////////////////////////////////////////////////////////////////



                   case 2://evros 2 me normal aera
switch(P[x].a1){
case 0:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa paniz
for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastH-i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
   printf("%c",c);
Sleep(TM);    }
    P[x].lastH-=2;
       P[x].prmv=2;
break;
case 1://evros 2 me normal aera me fora dejia kai antiropa pania
printf("\b");
P[x].prmv=0;
printf("%c",c);
 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
case 3:
printf("\b ");
P[x].prmv=1;
--P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
}
                     break;

                     case 1:
switch(direction_air){
case 0://evros 2 me normal aera me fora aristera kai antiropa pania
printf("\b");
P[x].prmv=0;
printf("%c",c);
break;
case 1://evros 2 me normal aera me fora dejia kai omoropa pania
 for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastH+i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
   printf("%c",c);
Sleep(TM);    }
    P[x].lastH+=2;
       P[x].prmv=2;
 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
case 3:
printf("\b ");
P[x].prmv=1;
++P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
}
                         break;

                         case 2:
  switch(direction_air){
case 0://evros 1 me normal aera me fora WE kai katheta pania
case 1:
 printf("\b ");
P[x].prmv=1;
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
 break;

case 2://evros 1 me normal aera me fora North  kai omoropa pania
 for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastV-i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastV-=2;
   P[x].prmv=2;
break;
case 3://evros 1 me normal aera me fora South  kai antiropa pania
    printf("\b");
P[x].prmv=0;
printf("%c",c);
break;
}
                            break;

                         case 3:
switch(direction_air){
case 0://evros 1 me normal aera me fora WE kai katheta pania
case 1:
 printf("\b ");
P[x].prmv=1;
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
 break;
case 2://evros 2 me normal aera me fora North  kai antiropa pania
 printf("\b");
P[x].prmv=0;
printf("%c",c);
break;
case 3://evros 2 me normal aera me fora North  kai omoropa pania
 for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastV+i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
   printf("%c",c);
Sleep(TM);    }
    P[x].lastV+=2;
    P[x].prmv=2;
break;
}
                             break;
}
break;//end of evros 2












//////////////////////////////////////////////////////////////////////////////////////////////////






                   case 3://evros 3 me normal aera
switch(P[x].a1){
                       case 0:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa pania
for(int i=1;i<=3;i++){
   printf("\b ");
    P[x].hold=P[x].lastH-i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
printf("%c",c);
Sleep(TM);    }
    P[x].lastH-=3;
       P[x].prmv=3;
break;
case 1://evros 2 me normal aera me fora dejia kai antiropa pania
P[x].prmv=1;
printf("\b ");
++P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
printf("\b ");
P[x].prmv=1;
--P[x].lastH;
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
case 3:
printf("\b ");
P[x].prmv=1;
--P[x].lastH;
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
}
                     break;

                     case 1:
switch(direction_air){
case 0://evros 2 me normal aera me fora aristera kai antiropa pania
P[x].prmv=1;
printf("\b ");
--P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
case 1://evros 2 me normal aera me fora dejia kai omoropa pania
 for(int i=1;i<=3;i++){
   printf("\b ");
    P[x].hold=P[x].lastH+i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastH+=3;
       P[x].prmv=3;
 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
printf("\b ");
P[x].prmv=1;
++P[x].lastH;
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
case 3:
printf("\b ");
P[x].prmv=1;
++P[x].lastH; ++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
}
                         break;

                         case 2:
  switch(direction_air){
case 0://evros 1 me normal aera me fora WE kai katheta pania
printf("\b ");
P[x].prmv=1;
--P[x].lastH;
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
case 1:
printf("\b ");
P[x].prmv=1;
++P[x].lastH; --P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;

case 2://evros 1 me normal aera me fora North  kai omoropa pania
 for(int i=1;i<=3;i++){
   printf("\b ");
    P[x].hold=P[x].lastV-i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
   printf("%c",c);
Sleep(TM);    }
    P[x].lastV-=3;
    P[x].prmv=3;
break;
case 3://evros 1 me normal aera me fora South  kai antiropa pania
P[x].prmv=1;
printf("\b ");
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
break;
}
                            break;

                         case 3:
switch(direction_air){
case 0://evros 1 me normal aera me fora WE kai katheta pania
printf("\b ");
P[x].prmv=1;
--P[x].lastH;
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
case 1:
printf("\b ");
P[x].prmv=1;
++P[x].lastH; ++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
case 2://evros 2 me normal aera me fora North  kai antiropa pania
P[x].prmv=1;
printf("\b ");
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
case 3://evros 2 me normal aera me fora North  kai omoropa pania
 for(int i=1;i<=3;i++){
   printf("\b ");
    P[x].hold=P[x].lastV+i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
printf("%c",c);
Sleep(TM);    }
    P[x].lastV+=3;
    P[x].prmv=3;
break;
}
                             break;
}
break;//end of evros 3


}


break;//END OF NORMAL WIND





















/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////






//STRONG







  case 2:
switch(P[x].evros){
case 0:
printf("\b");
P[x].prmv=0;
printf("%c",c);
break;

case 1://evros 1 me strong aera
switch(P[x].a1){

                       case 0:



switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa pania
 for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastH-i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastH-=2;
    P[x].prmv=2;
break;
case 1://evros 1 me normal aera me fora dejia kai antiropa pania
printf("\b");
P[x].prmv=0;
printf("%c",c);
 break;
case 2://evros 1 me normal aera me fora NS dejia kai katheta pania
case 3:
printf("\b ");
P[x].prmv=1;
--P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
}
                     break;

                     case 1:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai antiropa pania
printf("\b");
P[x].prmv=0;
printf("%c",c);
break;
case 1://evros 1 me normal aera me fora dejia kai omoropa pania
 for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastH+i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
  printf("%c",c);
Sleep(TM);    }
    P[x].lastH+=2;
    P[x].prmv=2;
 break;
case 2://evros 1 me normal aera me fora NS dejia kai katheta pania
case 3:
printf("\b ");
P[x].prmv=1;
++P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
}
                         break;

                         case 2:
  switch(direction_air){
case 0://evros 1 me normal aera me fora WE kai katheta pania
case 1:
 printf("\b ");
P[x].prmv=1;
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
 break;

case 2://evros 1 me normal aera me fora North  kai omoropa pania
for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastV-i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastV-=2;
    P[x].prmv=2;
 break;
break;
case 3://evros 1 me normal aera me fora South  kai antiropa pania
printf("\b");
P[x].prmv=0;
printf("%c",c);
break;
}
                            break;

                         case 3:
switch(direction_air){
case 0://evros 1 me normal aera me fora WE kai katheta pania
case 1:
 printf("\b ");
P[x].prmv=1;
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
 break;
case 2://evros 1 me normal aera me fora North  kai antiropa pania
printf("\b");
P[x].prmv=0;
printf("%c",c);
break;
case 3://evros 1 me normal aera me fora North  kai omoropa pania
for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastV+i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
   printf("%c",c);
Sleep(TM);    }
    P[x].lastV+=2;
    P[x].prmv=2;
break;
}
                             break;
}
break;//end of evros 1












//////////////////////////////////////////////////////////////////////////////////////////////////



                   case 2://evros 2 me strong aera
switch(P[x].a1){
case 0:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa pania
for(int i=1;i<=3;i++){
   printf("\b ");
    P[x].hold=P[x].lastH-i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastH-=3;
       P[x].prmv=3;
break;
case 1://evros 2 me normal aera me fora dejia kai antiropa pania
P[x].prmv=1;
printf("\b ");
++P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);

 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
printf("\b ");
P[x].prmv=1;
--P[x].lastH; --P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);


case 3:
printf("\b ");
P[x].prmv=1;
--P[x].lastH; ++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
}
                     break;

                     case 1:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa pania
P[x].prmv=1;
printf("\b ");
--P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);





break;
case 1://evros 2 me normal aera me fora dejia kai antiropa pania
for(int i=1;i<=3;i++){
   printf("\b ");
    P[x].hold=P[x].lastH+i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
  printf("%c",c);
Sleep(TM);    }
    P[x].lastH+=3;
       P[x].prmv=3;




 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
printf("\b ");
P[x].prmv=1;
++P[x].lastH; --P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);


case 3:
printf("\b ");
P[x].prmv=1;
++P[x].lastH; ++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
break;
}

                         break;

                         case 2:
  switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa pania


printf("\b ");
P[x].prmv=1;
--P[x].lastH; --P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);



break;
case 1://evros 2 me normal aera me fora dejia kai antiropa pania
printf("\b ");
P[x].prmv=1;
++P[x].lastH; --P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);


 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
for(int i=1;i<=3;i++){
   printf("\b ");
    P[x].hold=P[x].lastV-i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
   printf("%c",c);
Sleep(TM);    }
    P[x].lastV-=3;
       P[x].prmv=3;

case 3:
   P[x].prmv=1;
printf("\b ");
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);




break;
}
                            break;

                         case 3:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa pania


printf("\b ");
P[x].prmv=1;
--P[x].lastH; ++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);



break;
case 1://evros 2 me normal aera me fora dejia kai antiropa pania
printf("\b ");
P[x].prmv=1;
++P[x].lastH; ++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);


 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
 P[x].prmv=1;
printf("\b ");
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);



case 3:

   for(int i=1;i<=3;i++){
   printf("\b ");
    P[x].hold=P[x].lastV+i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
printf("%c",c);
Sleep(TM);    }
    P[x].lastV+=3;
       P[x].prmv=3;



break;
}

                             break;
}
break;//end of evros 2












//////////////////////////////////////////////////////////////////////////////////////////////////






                   case 3://evros 3 me strong aera
switch(P[x].a1){
                       case 0:
switch(direction_air){
case 0://evros 1 me normal aera me fora aristera kai omoropa pania
for(int i=1;i<=4;i++){
   printf("\b ");
    P[x].hold=P[x].lastH-i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
   printf("%c",c);
Sleep(TM);    }
    P[x].lastH-=4;
       P[x].prmv=4;
break;
case 1://evros 2 me normal aera me fora dejia kai antiropa pania
for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastH+i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
  printf("%c",c);
Sleep(TM);    }
    P[x].lastH+=2;
    P[x].prmv=2;
 break;
case 2://evros 2 me normal aera me fora NS dejia kai katheta pania
Sleep(TM);
--P[x].lastH;
--P[x].lastV;
    gotoxy(P[x].lastH,P[x].lastV);
    printf("%c",c);
Sleep(TM);
printf("\b ");
Sleep(TM);
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
Sleep(TM);
P[x].prmv=2;


break;
case 3:
Sleep(TM);
--P[x].lastH;
++P[x].lastV;
    gotoxy(P[x].lastH,P[x].lastV);
    printf("%c",c);
Sleep(TM);
printf("\b ");
Sleep(TM);
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
Sleep(TM);
P[x].prmv=2;


break;
}
                     break;

                     case 1:
switch(direction_air){
case 0://evros 2 me strong aera me fora aristera kai antiropa pania
for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastH-i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastH-=2;
    P[x].prmv=2;
break;
case 1://evros 2 me strong aera me fora dejia kai omoropa pania
 for(int i=1;i<=4;i++){
   printf("\b ");
    P[x].hold=P[x].lastH+i;
       Sleep(TM);
    gotoxy(P[x].hold,P[x].lastV);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastH+=4;
       P[x].prmv=4;
 break;
case 2://evros 2 me strong aera me fora NS dejia kai katheta pania
Sleep(TM);
++P[x].lastH;
--P[x].lastV;
    gotoxy(P[x].lastH,P[x].lastV);
    printf("%c",c);
Sleep(TM);
printf("\b ");
Sleep(TM);
--P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
Sleep(TM);
P[x].prmv=2;


break;
case 3:
Sleep(TM);
++P[x].lastH;
++P[x].lastV;
    gotoxy(P[x].lastH,P[x].lastV);
    printf("%c",c);
Sleep(TM);
printf("\b ");
Sleep(TM);
++P[x].lastV;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
Sleep(TM);
P[x].prmv=2;


break;
}
                         break;

                         case 2:
  switch(direction_air){
case 0://evros 1 me strong aera me fora WE kai katheta pania
Sleep(TM);
--P[x].lastH;
--P[x].lastV;
    gotoxy(P[x].lastH,P[x].lastV);
    printf("%c",c);
Sleep(TM);
printf("\b ");
Sleep(TM);
--P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
Sleep(TM);
P[x].prmv=2;
break;
case 1:
Sleep(TM);
++P[x].lastH;
--P[x].lastV;
    gotoxy(P[x].lastH,P[x].lastV);
    printf("%c",c);
Sleep(TM);
printf("\b ");
Sleep(TM);
++P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
Sleep(TM);
P[x].prmv=2;
break;

case 2://evros 1 me strong aera me fora North  kai omoropa pania
 for(int i=1;i<=4;i++){
   printf("\b ");
    P[x].hold=P[x].lastV-i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastV-=4;
    P[x].prmv=4;
break;
case 3://evros 1 me strong aera me fora South  kai antiropa pania
for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastV+i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastV+=2;
    P[x].prmv=2;
break;
break;
}
                            break;

                         case 3:
switch(direction_air){
case 0://evros 1 me strong aera me fora WE kai katheta pania
Sleep(TM);
--P[x].lastH;
++P[x].lastV;
    gotoxy(P[x].lastH,P[x].lastV);
   printf("%c",c);
Sleep(TM);
printf("\b ");
Sleep(TM);
--P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
Sleep(TM);

P[x].prmv=2;
break;
case 1:
Sleep(TM);
++P[x].lastH;
++P[x].lastV;
    gotoxy(P[x].lastH,P[x].lastV);
   printf("%c",c);
Sleep(TM);
printf("\b ");
Sleep(TM);
++P[x].lastH;
gotoxy(P[x].lastH,P[x].lastV);
printf("%c",c);
Sleep(TM);
P[x].prmv=2;
break;
case 2://evros 2 me strong aera me fora North  kai antiropa pania
for(int i=1;i<=2;i++){
   printf("\b ");
    P[x].hold=P[x].lastV-i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
   printf("%c",c);
Sleep(TM);    }
    P[x].lastV-=2;
    P[x].prmv=2;
break;


case 3://evros 2 me strong aera me fora North  kai omoropa pania
 for(int i=1;i<=4;i++){
   printf("\b ");
    P[x].hold=P[x].lastV+i;
       Sleep(TM);
    gotoxy(P[x].lastH,P[x].hold);
    printf("%c",c);
Sleep(TM);    }
    P[x].lastV+=4;
    P[x].prmv=4;
break;
}
                             break;
}
break;//end of evros 3


}


break;//END OF strong WIND



}


}


void lose(int x){
for(int i=0;i<=199;i++){
if((corx[i]==P[x].lastH)&&(cory[i]==P[x].lastV)){
char c,cw;
c=(x==0)?'A':'B';
cw=(x==0)?'B':'A';
gotoxy(131,10);printf("                          ");
gotoxy(131,10);
printf("Ο ΠΑΙΚΤΗΣ %c ΕΠΕΣΕ ΣΤΟ ΝΗΣΙ.\nΟ ΠΑΙΚΤΗΣ %c ΝΙΚΗΣΕ!!",c,cw);
lost=1;break;
}


}

}



































