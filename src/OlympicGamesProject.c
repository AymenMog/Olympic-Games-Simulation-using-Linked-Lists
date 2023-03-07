#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define nb_ep 200
#define nb_py 150
#define ESC 27   // la touche echape pour retourner en menu
int nb_psup = 0; // nombre des pays supprimés
int nb_esup = 0; // nombre des epreuves supprimés

/********************************************/
// monsieur si il ya un problem avec le vocale */
// ilfaut telecharger l"application espeak     */
/********************************************/

// des types qui vont nous servir :

typedef char string[50]; // le type chaine

enum bool
{
  True,
  False
}; // c'est une structure similaire a bollean

typedef struct maillon
{
  string name;
  struct maillon *suiv; // le maillon
} maillon;

typedef maillon *participants; // type pointeur sur LLC

/* **********************Machine Abstrrite**********************************/
//***************************************************************************
void allouer(participants *p)
{
  *p = malloc(sizeof(maillon)); // malloc
}

void liberer(participants p)
{ // free pour liberer l'espace memoire
  free(p);
}

void Affect_val(participants p, char v[50])
{
  strcpy(p->name, v); // (p->name) <=> (*p.name)
}

void Affect_adr(participants c, participants p)
{
  c->suiv = p;
}

char *valeur(participants p)
{
  return p->name;
}

participants Suivant_mai(participants p)
{
  return p->suiv;
}

//**********************des structures de donnés qui vont nous servir:************************
// les pays arabes participants:
string paysarab[] = {"Algerie", "Arabie Saoudite", "Djibouti", "Egypte", "Emirats arabes unis", "Irak", "Jordanie", "Koweit", "Liban", "Libye", "Maroc", "Oman", "Palestine", "Qatar", "Somalie", "Soudan", "Syrie", "Tunisie", "Yemen"};
// nom des athletes (homme/femme)(etranger/arabe):
string name_boyet[] = {"Arthur", "Jack", "Saul", "Mark", "Noah", "Frank", "Simon", "Sam", "Jason", "Peter", "Leo", "Eric", "Michel", "Rafael", "George", "Toni", "Will", "Vincent", "Victor", "Kevin", "Martin", "Iker", "Mathio", "Alonso", "Emanuel", "Gaspard", "Diego", "Philip", "Samuel", "Jakob"};
string name_boyar[] = {"Ahmed", "Amine", "Raouf", "Younes", "Youcef", "Toufik", "Samir", "Mehdi", "Karim", "Abdelhak", "Adem", "Akram", "Mohammed", "Abdelhamid", "Abdelkader", "Adel", "Ihab", "Omar", "Ali", "Othman", "Zayd", "Yamene", "Imad", "Riad", "Islam", "Ilyes", "Ramzi", "Okba", "Haithem", "Houadaifa"};
string name_girlet[] = {"Jessica", "Violet", "Clara", "Alice", "Jasmin", "Rosie", "Ive", "Olivia", "Emily", "Noemie", "Ava", "Elsa", "Anna", "Lisa", "Emmy", "Soline", "Rosa", "Catrin", "Julie", "Ella", "Isabella", "Charlotte", "Scarlett", "Annabela", "Roxane", "Lily", "Liana", "Diana", "Livia", "Lilou"};
string name_girlar[] = {"Soumia", "yousra", "Anfel", "Manel", "Israa", "Amel", "Sihem", "Tasnime", "Farah", "Loubna", "Fatima", "Yassmine", "Ahlam", "Ikram", "Aicha", "Khadidja", "Nesrine", "Asmaa", "Kaouthar", "Imene", "Hind", "Lamia", "Narineme", "Nahla", "Rihem", "Hadjer", "Loubna", "Zayneb", "Oum khalthoum", "Hajar"};

string tabepreuve[nb_ep];
string tabpays[nb_py]; // les srtucture demendé
participants tabjo[nb_ep][nb_py];

//*********************colors and interface******************:
// couleur du Texte :
void Textecolor(int ForgC)
{
  WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  // We use csbi for the wAttributes word.
  if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
  {
    // Mask out all but the background attribute, and add in the forgournd color
    wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
    SetConsoleTextAttribute(hStdOut, wColor);
  }
  return;
}
// Texte couleur et fond:
void Color(int couleurdutexte, int couleurdufond)
{

  HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(H, couleurdufond * 16 + couleurdutexte);
}

// manipuler les cordonnés de la console gotoxy :
void gotoxy(int x, int y)
{
  COORD c;
  c.X = x;
  c.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//********************************************Interface*********************************
//****************************************************************************************
void welcome()

{
  int k;
  string voice;
  string charCommand;
  system("Cls");
  for (k = 0; k < 10; k++)
  {
    if (k % 2 == 0)
      Textecolor(5);
    if (k % 2 == 1)
      Textecolor(3);
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t  .----------------.  .----------------.  .----------------.\n");
    printf("\t\t\t\t | .--------------. || .--------------. || .--------------. |\n");
    printf("\t\t\t\t | |  _________   | || |    _______   | || |     _____    | |\n");
    printf("\t\t\t\t | | |_   ___  |  | || |   /  ___  |  | || |    |_   _|   | |\n");
    printf("\t\t\t\t | |   | |_  \\_|  | || |  |  (__ \\_|  | || |      | |     | |\n");
    printf("\t\t\t\t | |   |  _|  _   | || |   \'.___`-.   | || |      | |     | |\n");
    printf("\t\t\t\t | |  _| |___/ |  | || |  |`\\____) |  | || |     _| |_    | |\n");
    printf("\t\t\t\t | | |_________|  | || |  |_______.\'  | || |    |_____|   | |\n");
    printf("\t\t\t\t | |              | || |              | || |              | |\n");
    printf("\t\t\t\t | \'--------------\' || \'--------------\' || \'--------------\' |\n");
    printf("\t\t\t\t  \'----------------\'  \'----------------\'  \'----------------\'\n");
    Sleep(200);
    system("cls");
  }
  Textecolor(5);
  printf("\t\t\t          R%cpublique Alg%crienne D%cmocratique et Populaire           \n", 130, 130, 130);
  printf("\t\t\tMinist%cre de l'Enseignement Sup%crieur et de la Recherche Scientifique\n", 130, 130);
  printf("\t\t\t     _______________________________________________________\n");
  printf("\t\t\t    |        _______     _______     _                      |\n");
  printf("\t\t\t    |       |  _____|   |  _____|   | |  %ccole nationale    |\n", 130);
  printf("\t\t\t    |       | |_____    | |_____    | |                     |\n");
  printf("\t\t\t    |       |  _____|   |_____  |   | |  sup%crieure         |\n", 130);
  printf("\t\t\t    |       | |_____     _____| |   | |                     |\n");
  printf("\t\t\t    |       |_______|   |_______|   |_|  d'informatique     |\n");
  printf("\t\t\t    |_______________________________________________________|\n\n");
  Textecolor(3);
  printf("\t\t\t\tCPI - 1%cre Ann%ce - Ann%ce Universitaire 2021/2022 \n", 138, 130, 130);
  printf("\t\t\t ___________________________________________________________________\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t| REALISE PAR : MOUGARI AYMEN ABDERRAHMANE                          |\n");
  printf("\t\t\t|                              &                                    |\n");
  printf("\t\t\t|                          BOUCHOUCHA MOHAMMED EL AMINE             |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|         \tSECTION : C           GROUPE: 09                    |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|         \tTP1 : Les listes lin%caires chain%ces                 |\n", 130, 130);
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t|           \t      < LES Jeux Olympique >                        |\n");
  printf("\t\t\t|                     Matrice Des listes                            |\n");
  printf("\t\t\t|                                                                   |\n");
  printf("\t\t\t| ENCADRE PAR :Dr. KERMI ADEL                                       |\n");
  printf("\t\t\t|___________________________________________________________________|\n\n\n");
  strcpy(voice, "Salam everybody");
  strcpy(charCommand, "espeak \"");
  strcat(charCommand, voice);
  system(charCommand);
  Sleep(200);
  strcpy(voice, "THis is our Tp of Data structure");
  strcpy(charCommand, "espeak \"");
  strcat(charCommand, voice);
  system(charCommand);
  Sleep(200);
  strcpy(voice, "I hope you enjoy");
  strcpy(charCommand, "espeak \"");
  strcat(charCommand, voice);
  system(charCommand);
  Textecolor(5);
  printf("\n");
  printf("\t\t\t                             PLease                                         \n");
  printf("\t\t\t                    Press any key to continue..                             ");
  getch();
}
// charrgement affichage:
void Chargement()
{
  int i;
  for (i = 0; i < 2; i++)
  {
    system("cls");
    Textecolor(4);
    gotoxy(12, 12);
    printf("\t\t\t\t\t\t  Chargement.\n\n");
    Sleep(200);
    system(";cls");
    gotoxy(12, 12);
    printf("\t\t\t\t\t\t  Chargement..\n\n");
    Sleep(200);
    system(";cls");
    gotoxy(12, 12);
    printf("\t\t\t\t\t\t  Chargement...\n\n");
    Sleep(200);
    system(";cls");
  }
}
// barre du chargement:

void Barrechargement()
{
  system("cls");
  Textecolor(4);
  gotoxy(10, 15);
  printf("\t\t\t|||                                                 5%%  ");
  Sleep(300);
  system(";cls");
  gotoxy(10, 15);
  printf("\t\t\t|||||                                               20%%  ");
  Sleep(300);
  system(";cls");
  gotoxy(10, 15);
  printf("\t\t\t||||||||||||||||                                    30%%  ");
  Sleep(300);
  system(";cls");
  gotoxy(10, 15);
  printf("\t\t\t|||||||||||||||||||||||||                           45%%  ");
  Sleep(300);
  system(";cls");
  gotoxy(10, 15);
  printf("\t\t\t|||||||||||||||||||||||||||||||                     60%%  ");
  Sleep(300);
  system(";cls");
  gotoxy(10, 15);
  printf("\t\t\t||||||||||||||||||||||||||||||||||||||||            80%%  ");
  Sleep(300);
  system(";cls");
  gotoxy(10, 15);
  printf("\t\t\t||||||||||||||||||||||||||||||||||||||||||||||||||  100%% ");
  system("cls");
}

// openign interface 2:
void WelcomeJo()
{
  system("cls");
  Textecolor(5);
  printf("\t\t\t  _____________________________________________________________________\n");
  printf("\t\t\t |                                                                     |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("  ********** *******   **          **       **         ******       ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf(" /////**/// /**////** ***          /**      /**        **////**     ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("    /**    /**   /**//**           /**      /**       **    //      ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("    /**    /*******  /**    *****  /**      /**      /**            ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("    /**    /**////   /**   /////   /**      /**      /**            ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("    /**    /**       /**           /**      /**      //**    **     ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("    /**    /**       ****          /********/******** //******      ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("    //     //       ////           //////// ////////   //////       ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("                                                                    ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("                                                                    ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("         ******** ********** **     **  *******   ********          ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("        /**///// /////**/// /**    /** /**////** /**/////           ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("       /**          /**    /**    /* */**    /**/**                 ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("      /*******     /**    /**    /** /**    /**/*******             ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("      /**////      /**    /**    /** /**    /**/**////              ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("     /**          /**    /**    /** /**    ** /**                   ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("      /********    /**    //*******  /*******  /********            ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("      ////////     //      ///////   ///////   ////////             ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("                                                                    ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("                                                                    ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("         *******   ********     ******      **      ********        ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("       /**////** /**/////     **////**    ****    **//////          ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("       /**    /**/**         **    //    **//**  /**                ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("       /**    /**/*******   /**         **  //** /*********         ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("       /**    /**/**////    /**        **********////////**         ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("       /**    ** /**        //**    **/**//////**       /**         ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("       /*******  /********   //****** /**     /** ********          ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |");
  Textecolor(3);
  printf("       ///////   ////////     //////  //      // ////////           ");
  Textecolor(5);
  printf(" |\n");
  printf("\t\t\t |                                                                     |\n");
  printf("\t\t\t |                                                                     |\n");
  printf("\t\t\t |                                                                     |\n");
  printf("\t\t\t |_____________________________________________________________________|\n");
  Sleep(3500);
  system("cls");
}

// les dessins:
void fire_olymp()
{
  int i;
  gotoxy(7, 8);
  Textecolor(14);
  printf("_______\\__/_______");
  Textecolor(5);
  printf("     :,        .,:::\"\"::,.     .,:o8OO::,.         ,:");
  gotoxy(7, 9);
  Textecolor(14);
  printf(" `--.._      _..--'");
  Textecolor(5);
  printf("     :,,      .:' ,:8oo `:.   .:'oo8:,, `:.     ,,:");
  gotoxy(7, 10);
  Textecolor(14);
  printf("      `\\  /'");
  Textecolor(5);
  printf("             `^OOoo:\"O^'     `^88oo:\"8^'     `^O\":ooOO^'");
  gotoxy(7, 11);
  Textecolor(14);
  printf("        ||");
  Textecolor(5);
  printf("                      :,           ,: :,           ,:");
  gotoxy(7, 12);
  Textecolor(14);
  printf("        ||");
  Textecolor(5);
  printf("                       :,,       ,,:   :,,       ,,:");
  gotoxy(7, 13);
  Textecolor(14);
  printf("        ||");
  Textecolor(5);
  printf("                        `^Oo,,,oO^'     `^OOoooOO^`");
  Textecolor(5);
  gotoxy(19, 5);
  printf("              .,::OOO::,.     .,ooOOOoo,.     .,::OOO::,.");
  gotoxy(19, 6);
  printf("           .:'         `:. .8'         `8. .:'         `:.");
  gotoxy(19, 7);
  printf("           :\"           \": 8\"           \"8 :\"            \":");
  Textecolor(14);
  gotoxy(84, 8);
  printf("_______\\__/_______");
  gotoxy(84, 9);
  printf(" `--.._      _..--'");
  gotoxy(84, 10);
  printf("      `\\  /'");
  gotoxy(84, 11);
  printf("        ||");
  gotoxy(84, 12);
  printf("        ||");
  gotoxy(84, 13);
  printf("        ||");
  printf("\n\n\n");
  Textecolor(3);
  printf("\t               ::::::::  :::     :::   :::  :::   :::   ::::::::: ::::::::::: ::::::::\n");
  printf("\t            :+:    :+: :+:     :+:   :+: :+:+: :+:+:  :+:    :+:    :+:    :+:    :+:\n");
  printf("\t           +:+    +:+ +:+      +:+ +:+ +:+ +:+:+ +:+ +:+    +:+    +:+    +:+\n");
  printf("\t          +#+    +:+ +#+       +#++:  +#+  +:+  +#+ +#++:++#+     +#+    +#+\n");
  printf("\t         +#+    +#+ +#+        +#+   +#+       +#+ +#+           +#+    +#+\n");
  printf("\t        #+#    #+# #+#        #+#   #+#       #+# #+#           #+#    #+#    #+#\n");
  printf("\t        ########  ########## ###   ###       ### ###       ########### ########\n");
  printf("\t                  ::::::::      :::       :::   :::   :::::::::: ::::::::\n");
  printf("\t                :+:    :+:   :+: :+:    :+:+: :+:+:  :+:       :+:\n");
  printf("\t               +:+         +:+   +:+  +:+ +:+:+ +:+ +:+       +:+\n");
  printf("\t              :#:        +#++:++#++: +#+  +:+  +#+ +#++:++#  +#++:++#++\n");
  printf("\t            +#+   +#+# +#+     +#+ +#+       +#+ +#+              +#+\n");
  printf("\t            #+#    #+# #+#     #+# #+#       #+# #+#       #+#    #+#\n");
  printf("\t            ########  ###     ### ###       ### ########## ########\n");

  for (i = 0; i < 8; i++)
  {
    if (i % 2 == 0)
      Textecolor(12);
    else
      Textecolor(0);
    gotoxy(7, 7);
    Sleep(180);
    printf("      ( (  )");
    gotoxy(84, 7);
    Sleep(180);
    printf("      ( (  )");
    gotoxy(7, 6);
    Sleep(180);
    printf("       )  (,");
    gotoxy(84, 6);
    Sleep(180);
    printf("       )  (,");
    gotoxy(7, 5);
    Sleep(180);
    printf("        /|,");
    gotoxy(84, 5);
    Sleep(180);
    printf("        /|,");
  }
  system("cls");
}

void generique()
{
  system("cls");
  Sleep(500);
  // cycling
  //-------- __@      __@       __@       __@      __~@
  //  ----- _`\<,_    _`\<,_    _`\<,_     _`\<,_    _`\<,_
  //  ---- (*)/ (*)  (*)/ (*)  (*)/ (*)  (*)/ (*)  (*)/ (*)
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Textecolor(4);
  printf("\n\n\n\n\n");
  Sleep(100);
  printf("---------------- __@      __@       __@       __@      __@        __@      __@       __@       __@      __~@\n");
  Sleep(100);
  printf("------------- _`\\<,_    _`\\<,_    _`\\<,_     _`\\<,_    _`\\<,_  _`\\\\<,_    _`\\<,_    _`\\<,_     _`\\<,_    _`\\<,_\n");
  Sleep(100);
  printf("------------ (*)/ (*)  (*)/ (*)  (*)/ (*)  (*)/ (*)  (*)/ (*) (*)/ (*)  (*)/ (*)  (*)/ (*)  (*)/ (*)  (*)/ (*) \n");
  Sleep(100);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
  Textecolor(14);
  Sleep(100);
  printf("\n\n\n");
  Sleep(100);
  printf("                     o    \n");
  Sleep(100);
  printf("           /|   o         o    \n");
  Sleep(100);
  printf("           \\|=--            o    \n");
  Sleep(100);
  printf("             ##    \n");
  Sleep(100);
  printf("                              \\\\                                             '\\                   .  .         \n");
  Sleep(100);
  printf("                           /   \\O     \n");
  Sleep(100);
  printf("                          O_/   T                                  ___\n");
  Sleep(100);
  printf("                          T    /|                   o__        o__ o   | o |\\                O             .   O__,o\n");
  Sleep(100);
  printf("                          |\\  | |                  /|       o  /\\      |   |X\\              <,o _____#_____   /\\(\n");
  Sleep(100);
  printf("           _______________|_|________              / > o        <\\     |   |XX\\           _/_>______Y_________< \\__\n");
  Textecolor(11);
  Sleep(100);
  printf("\n\n\n");
  Sleep(100);
  printf("                         _               _        \n");
  Sleep(100);
  printf("                     __ ( }             { ) __             \\              .     '     ' .               |\n");
  Sleep(100);
  printf("                   '---. _`---,     ,---'_ .---'          O>>         .                 'o              |\n");
  Sleep(100);
  printf("                   ___/ /                \\ \\__             \\       .                                    |\n");
  Sleep(100);
  printf("                 /,---'\\\\                //'---,\\          /\\    .                                      |\n");
  Sleep(100);
  printf("                       //                \\\\               / /  .'                                       |\n");
  Sleep(100);
  printf("                      '==                ==           ^^^^^^^`^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
  Textecolor(13);
  Sleep(100);
  printf("\n\n\n\n");
  Sleep(100);
  printf("                      ___\n");
  Sleep(100);
  printf("                    .'__ '.\n");
  Sleep(100);
  printf("                   / /_ |ST\\                       ____                                     ___\n");
  Sleep(100);
  printf("                   |  | |  |                     (|    |)                 >>>----         /\\ _ /\\\n");
  Sleep(100);
  printf("                   \\ <___> /                       \\  /                                  / /\\ /\\ \\\n");
  Sleep(100);
  printf("                    ;.___.;                         )(                         >>>----  |---(*)---|\n");
  Sleep(100);
  printf("                    |::|;;|                       _|~~|_                                 \\ \\/_\\/ /\n");
  Sleep(100);
  printf("                    |::/;;|                      |______|                 >>>----         \\/___\\/\n");
  Sleep(100);
  printf("                    |:/`\\;|                             \n");
  Sleep(100);
  printf("                    |/   \\|\n");
  Sleep(100);
  printf("\n\n\n");
  Textecolor(3);
  Sleep(100);
  printf("                                                           .-\"\"\"-.\n");
  Sleep(100);
  printf("                                                          /       \\\n");
  Sleep(100);
  printf("                                                         ;_.-\"\"\"-._;\n");
  Sleep(100);
  printf("                                      .,_       __,.---.-(=(o)-(o)=)-.---.,__       _,.\n");
  Sleep(100);
  printf("                                      '._'--\"```          \\   ^   /          ```\"--'_.'\n");
  Sleep(100);
  printf("                                             ``\"''~---~~%%^%%^.%%.`._0_.'%%,^%%^%%^~~---~''\"``\n");
  Sleep(100);
  printf("                                               ~^~- `^-%% ^~.%%~%%.^~-%%-~.%%-^.%% ~`%% ~-`%%^`-~^~\n");
  Sleep(100);
  printf("                                               ~^- ~^- `~.^- %%`~.%%~-'%%~^- %%~^- ~^\n");
  Sleep(100);
  printf("\n\n\n");
  Sleep(100);
  printf("                                                            \\_\\\n");
  Sleep(100);
  printf("                                                              \\_()\n");
  Sleep(100);
  printf("                                                               \\/>\n");
  Sleep(100);
  printf("                                                       .--===='-\\_====--.\n");
  Sleep(100);
  printf("                                             ~^~~~~_~^~-^_^~-^~^-\\_\\^~-^~-^~^_^~^~\n");
  Sleep(100);
  printf("                                              ~^~-~^~^~-~^~^~^-^~^~^~~-~^~^~-~^~^~\n");
  Sleep(100);
  printf("\n\n\n");
  Textecolor(14);
  Sleep(100);
  printf("                o   o\n");
  Sleep(100);
  printf("               |= <\n");
  Sleep(100);
  printf("              /| /\\\n");
  Sleep(100);
  printf("###################     \\|\n");
  Sleep(100);
  printf("             :|"
         ""
         "     _\\/\n");
  Sleep(100);
  printf("             :|           o\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|           |/\n");
  Sleep(100);
  printf("             :|          \\/\n");
  Sleep(100);
  printf("             :|          o\\\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|         o/_/\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|          o\n");
  Sleep(100);
  printf("             :|          -\\'\n");
  Sleep(100);
  printf("             :|           /|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|           _o/\n");
  Sleep(100);
  printf("             :|            |\n");
  Sleep(100);
  printf("             :|           / \\\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|           \\o/\n");
  Sleep(100);
  printf("             :|            |\n");
  Sleep(100);
  printf("             :|           / \\\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|            o\n");
  Sleep(100);
  printf("             :|           <|>\n");
  Sleep(100);
  printf("             :|           / \\\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|           _o_\n");
  Sleep(100);
  printf("             :|            |\n");
  Sleep(100);
  printf("             :|           / \\\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|           _o_\n");
  Sleep(100);
  printf("             :|           / \\\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|           =o=\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|           . ,\n");
  Sleep(100);
  printf("             :|           -o-\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|           \\ /\n");
  Sleep(100);
  printf("             :|            |\n");
  Sleep(100);
  printf("             :|           /o\\\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|\n");
  Sleep(100);
  printf("             :|            .\n");
  Sleep(100);
  printf("             :|___       .\'/.          _o/         ____\n");
  Textecolor(9);
  Sleep(100);
  printf("             :::::|~~~~~~~***~~~~~~~~~~~~~~~~~~~~~~|::::\n");
  Sleep(100);
  printf("                 :|        o            / \\        |:\n");
  Sleep(100);
  printf("                 :|                                |:\n");
  Sleep(100);
  printf("                 :|                                |:\n");
  Sleep(100);
  printf("                 :|                                |:\n");
  Sleep(100);
  printf("                 :|        \\|           _|_        |:\n");
  Sleep(100);
  printf("                 :|         \\-          \\ /        |:\n");
  Sleep(100);
  printf("                 :|         |o                     |:\n");
  Sleep(100);
  printf("                 :|                                |:\n");
  Sleep(100);
  printf("                 :|             \\_o               |:\n");
  Sleep(100);
  printf("                 :|               `                |:\n");
  Sleep(100);
  printf("                 :|________________________________|:\n");
  Sleep(100);
  printf("                 ::::::::::::::::::::::::::::::::::::\n");
  Sleep(500);
  system("cls");
}

// procedure pour regler un  problem dans la lecture des fichiers:
void rmvchr(char *str, char charToRemmove)
{
  int i, j;
  int len = strlen(str);
  for (i = 0; i < len; i++)
  {
    if (str[i] == charToRemmove)
    {
      for (j = i; j < len; j++)
      {
        str[j] = str[j + 1];
      }
      len--;
      i--;
    }
  }
}
// procedure pour regler un problem dans les chaines:
char *remove_white_spaces(char *str)
{
  int i = 0, j = 0;
  while (str[i])
  {
    if (str[i] != ' ')
      str[j++] = str[i];
    i++;
  }
  str[j] = '\0';
  return str;
}

//*****************************************************************************************************
//**************************** Procedure du TP*********************************************************

// proc1:
void creertabjo()
{
  // remplir tabepreuves et tabpays:
  int j = 0, i = 0, k, l = 0;
  FILE *fichier1;
  fichier1 = fopen("countries-epreuves.txt", "r");
  if (fichier1 == NULL)
    printf("erreur fichier n'existe pas ");
  char *line1 = malloc(sizeof(char) * (350));
  while (!feof(fichier1))
  {
    char ch = '\n';
    fgets(line1, 50, fichier1);
    if (i <= 150)
    {
      rmvchr(line1, ch);
      strcpy(tabpays[i], line1);
      i++;
    }
    else
    {
      rmvchr(line1, ch);
      strcpy(tabepreuve[j], line1);
      j++;
    }
  }

  fclose(fichier1);
  free(line1);
  // remplir tabjo dont chaque case contient une LLc:
  participants t, new, p;
  int n, a, x, b = 0, rd, s; // n:nombre des maillons, x:compteur ,b:pour ne
  int bol1, bol2;
  string concurrent;
  printf("\n");
  for (i = 0; i < nb_ep; i++)
  {
    bol1 = -1;
    a = strlen(tabepreuve[i]) - 2;
    while (tabepreuve[i][a] == ' ')
    {
      a -= 2;
    }
    if (tabepreuve[i][a] == ')')
      a -= 1;
    // printf("%C \n",tabepreuve[i][a]);
    if (tabepreuve[i][a] == 'H')
      bol1 = 1;
    for (j = 0; j < nb_py; j++)
    {
      bol2 = -1;
      x = 1;
      t = NULL;
      srand(l);
      n = (rand()) % 11;
      l++;
      for (k = 0; k < 19; k++)
      {
        if (strcmp(tabpays[j], paysarab[k]) == 0)
          bol2 = 1; // we are here
      }
      if (n != 0)
      {
        b = 0;
        srand(l);
        rd = (rand()) % 21;
        do
        {
          new = malloc(sizeof(maillon));

          if (bol1 == 1)
          {
            if (bol2 == 1)
            {
              strcpy((*new).name, name_boyar[b + rd]);
            }
          }
          if (bol1 == -1)
          {
            if (bol2 == 1)
            {
              strcpy((*new).name, name_girlar[b + rd]);
            }
          }
          if (bol1 == 1)
          {
            if (bol2 == -1)
            {
              strcpy((*new).name, name_boyet[b + rd]);
            }
          }
          if (bol1 == -1)
          {
            if (bol2 == -1)
            {
              strcpy((*new).name, name_girlet[b + rd]);
            }
          }
          b++;
          (*new).suiv = NULL;
          if (t == NULL)
          {
            t = new;
            p = new;
          }
          else
          {
            (*p).suiv = new;
            p = new;
          }
          x++;
        } while (x <= n);

        tabjo[i][j] = t;
      }
      else
      {
        tabjo[i][j] = NULL;
      }
    }
  }
}

// proc2:
void inserath(string nomath, int nump, int nume)
{
  int i, pos = -1;
  enum bool test = True; // pos et test le deux sont considere comme des bools
  participants t, p, q;
  int x = 0;
  if (nume > (nb_ep - nb_esup) || nume <= 0) // pour verifie que l eprueve existe
  {
    printf("\t\t\tepreuve n existe pas il ya %d epreuves\n", nb_ep - nb_esup);
    pos = -2; // pour eviter le else if
  }
  if (nump > nb_py || nump <= 0) // pour verifie que le pays existe
  {
    printf("\t\t\tpays n existe pas il ya %d pays\n", nb_py - nb_psup);
    pos = -2; // pour eviter le else if
  }
  if (strcmp(tabpays[nump - 1], "\t\t\tCe pays n'existe plus") == 0)
    pos = -2;
  if (pos != -1)
    printf("\n\t\t\ton ne peut pas inserer des athletes dans le pays de position %d car il n'existe plus", nump);

  else if (pos == -1)
  {
    t = tabjo[nume - 1][nump - 1]; //(-1) car le pays numero 1 pour l'etre humain son numero est 0 dans le tableau
    p = t;
    if (t == NULL)
    { // si la liste est vide on cree une nouvelle
      p = malloc(sizeof(maillon));
      t = p;
      strcpy((*p).name, nomath);
      (*p).suiv = NULL;
      p = NULL;
      printf("\t\t\tl'athlete est ins%cr%C\n", 130, 130);
    }
    while (p != NULL) // si la liste n est pas vide on cree un maillon , on garde la tete, et on fait le chainage
    {
      if ((*p).suiv == NULL)
        q = p;
      x++;
      if (strcmp((*p).name, nomath) == 0)
        test = False; // un test si l athlete existe deja
      p = (*p).suiv;
    }
    if (t != NULL)
    {
      if (x == 10)
        printf("\t\t\tliste des participants pleine\n"); // si la liste est pleine.
      if (x != 10)
      {
        if (test == False)
          printf("\t\t\tAthlete existe deja\n");
        if (test == True)
        {
          p = malloc(sizeof(maillon));
          strcpy((*p).name, nomath);
          (*p).suiv = NULL;
          (*q).suiv = p;
          printf("\t\t\tl'athlete est ins%cr%C", 130, 130);
        }
      }
    }

    tabjo[nume - 1][nump - 1] = t; // on recupaire la tete dans la case du tableau tabjo qui convient
  }
}

// proc3:
void listathpays(string pays)
{
  int i = 0, pos = -1;
  participants t, p;

  for (i = 0; i < nb_py; i++)
  {
    remove_white_spaces(pays);
    if (strcmp(tabpays[i], pays) == 0) // on verifie si le pays existe ou non
    {
      pos = i; // pos est utilisé pour recuperer la position et aussi comme boolean
      i = nb_py;
    }
  }
  if (pos == -1)
  {
    Textecolor(4);
    printf("\n\t\t\tle pays %s n'existe pas\n", pays);
  }
  else if (pos != -1)
  {
    Textecolor(8);
    printf("le pays :%s\n", tabpays[pos]); // on affiche le pays qui convient
    for (i = 0; i < nb_ep; i++)
    {
      t = tabjo[i][pos];
      p = t;
      Textecolor(8);
      printf("%s \n", tabepreuve[i]);

      if (p == NULL)
      {
        Textecolor(4);
        printf("y a pas de participant\n");
      }

      if (p != NULL)
      {
        Textecolor(5);
        printf("Participants:\n");
        while (p != NULL)
        {
          Textecolor(5);
          printf("-->");
          Textecolor(3);
          printf(" %s \n", (*p).name);
          p = (*p).suiv;
        }
      }
    }
  }
}

// proc4:
enum bool sansath(int ne)
{
  int i;
  enum bool res = True;
  // on peut ajouter ce test:
  /*if ((ne> nb_ep) || (ne<=0)) //pour verifie que l eprueve existe
  {
  printf("\t\t\tepreuve n existe pas il ya %d epreuves\n",nb_ep-nb_esup);
  res=False;
  }*/
  // else{
  for (i = 0; i < nb_py; i++)
  {
    if (tabjo[ne - 1][i] != NULL)
    {              // si on trouve qu'il ya un participant dans une epreuves de ce pays
      res = False; // on mets le resulat a faux et on sort de la boucle
      i = nb_py;
    }
  } 
  //} 
  return res;
}

// proc5:
void listjo()
{
  int i, j;
  participants t, p;
  for (i = 0; i < nb_ep; i++)
  {
    if (strcmp("cette epreuve n'existe plus", tabepreuve[i]) != 0)
    {
      Textecolor(8);
      printf("=======================================");
      Textecolor(5);
      printf("  l'epreuve : %s ", tabepreuve[i]); // on affiche d'abord l'epreuves
      Textecolor(8);
      printf("===================================");
      printf("\n");
      for (j = 0; j < nb_py; j++)
      {
        t = tabjo[j][i];
        p = t;
        if (p != NULL)
        {
          Textecolor(8);
          printf("* %s * \n", tabpays[j]); // pays par pays
          Textecolor(5);
          printf("Les participants :\n");
          while (p != NULL)
          {
            Textecolor(5);
            printf("-->");
            Textecolor(3);
            printf(" %s .\n", (*p).name); // on affiche les athletes
            p = (*p).suiv;
          }
        }
        Sleep(500);
        if (kbhit())
        {
          i = nb_ep;
          j = nb_py;
        } // pour conroler l'affichage
      }
    }
  }
}

// proc6:
void *suppays(string pays)
{
  int i, j, pos = -1; // pos est utiliser pour trouver la position du pays et comme bollean aussi
  participants p, supp;
  for (i = 0; i < nb_py; i++)
  {
    if (strcmp(tabpays[i], pays) == 0) // on verifie si le pays existe ou non
    {
      pos = i;
      i = nb_py;
    }
  }
  if (pos == -1)
    printf("\t\t\tCe pays n'existe plus ");
  else if (pos != -1)
  {
    strcpy(tabpays[pos], "Ce pays n'existe plus"); // on remplace le nom du pays par ce message qui va nous servir
    for (
        i = 0; i < nb_ep; i++)
    {
      p = tabjo[i][pos];
      p = supp;
      while (p != NULL)
      {
        p = (*p).suiv;
        free(supp); // on vide les listes maillons par maillosn
        supp = p;
        tabjo[i][pos] = NULL; // pour passer au maillon suivant
      }
    }
    nb_psup++; // on incremente le nombre des pays supprimer (on a besoin de ça pour un bon affichage)
  }
}
// proc7:
void *suppath(string nomath, int nump, int nume)
{
  enum bool test = False;
  int i;
  participants t, dele, sauv;
  t = tabjo[nume - 1][nump - 1];
  if (t == NULL)
  {
    printf("\t\t\tathlete n'existe pas");
    test = True;
  }
  else
  {
    if ((strcmp((*t).name, nomath) == 0))
    { // s'il est dans la tete
      if ((*t).suiv == NULL)
      {
        free(t);
        tabjo[nume - 1][nump - 1] = NULL;
        test = True;
      }
      else
      {
        dele = t; // dele ptr qui supprime et libere le maillon:
        test = True;
        t = (*t).suiv;
        free(dele);
      }
    }
    else // s'il n'est pas dans la tete
    {
      dele = t;
      if ((*dele).suiv == NULL)
        dele = NULL;
      while (dele != NULL)
      {
        sauv = dele;
        dele = (*dele).suiv;
        if (dele != NULL)
          if (strcmp((*dele).name, nomath) == 0)
          {
            test = True;
            (*sauv).suiv = (*dele).suiv;
            free(dele);
            dele = NULL;
          }
      }
    }
  } // pour afficher un message au utilisateur
  if (test == False)
    printf("\t\t\tAthlete n'existe pas");
}
// proc8:
void suplignesvides()
{
  int i;
  for (i = 0; i < nb_ep; i++)
  {
    if (sansath(i) == True) // on utilise la fonction precedente
    {
      // on vas copier un message dans tabepreuve qui nous marque que l'epreuve est supprimé
      strcpy(tabepreuve[i], "cette epreuve n'existe plus");
    }
  }
}

int main(int argc, char **argv)
{

  participants t, new, p;
  int i, j, ne, np, nump, nume, choice, pos, retour, li;
  enum bool res;
  string athletes, athletes2, pays, pays2, pays3, epreuve, epreuve2, nomath, choix;
  string blad, voice, charCommand;
  // creer un menu:
  time_t t1 = time(0);
  char *time = ctime(&t1);
  Textecolor(5);
  system("cls");
  Barrechargement();
  welcome();
  generique();
  fire_olymp();
  WelcomeJo();
  while (1)
  {
  Menu:
    system("cls");
    printf("\n");
    Textecolor(5); // la date
    printf("                                  la date d'aujourd'hui:%s", time);
    Textecolor(3);
    printf("\n\n\n");
    printf("                                                        MENU                                   \n");
    printf("                                                       ------                                  \n");
    printf("\t\t\t******************************************************************\n");
    printf("\t\t\t*                                                                *\n");
    printf("\t\t\t*               ---------------------------                      *\n");
    printf("\t\t\t*    01.Creer la matrice des participants                        *\n");
    printf("\t\t\t*    02.Lister les pays qui existe                               *\n");
    printf("\t\t\t*    03.Lister les epreuves qui existe                           *\n");
    printf("\t\t\t*    04.Avoir le num%Cro d'une epreuve donn%c                      *\n", 130, 130);
    printf("\t\t\t*    05.Avoir le num%cro d'un pays donn%c                          *\n", 130, 130);
    printf("\t\t\t*    06.Inserer un athlete                                       *\n");
    printf("\t\t\t*    07.Afficher les athletes d'un pays                          *\n");
    printf("\t\t\t*    08.Verifier si ligne est vide                               *\n");
    printf("\t\t\t*    09.Afficher la matrice des participants                     *\n");
    printf("\t\t\t*    10.Supprimer le pays et l'afficher pour la derniere fois    *\n");
    printf("\t\t\t*    11.Supprimer un athlete                                     *\n");
    printf("\t\t\t*    12.Supprimer les epreuves dont y'a pas de participants      *\n");
    printf("\t\t\t*    Any other key to quit the program                           *\n");
    printf("\t\t\t*               ---------------------------                      *\n");
    printf("\t\t\t*                                                                *\n");
    printf("\t\t\t******************************************************************\n");
    Textecolor(5);
    printf("\t\t Please you can't do any thing without creating tabjo !!! ");
    printf("Enter your choice :\n");
    gotoxy(50, 27);
    printf(" _____ ");
    gotoxy(50, 28);
    printf("|     |");
    gotoxy(50, 29);
    printf("|_____|\n");
    gotoxy(53, 28);
    scanf("%d", &choice);
    Chargement();
    switch (choice)
    {
    case 1:
      creertabjo();
      system("cls");
      Textecolor(5);
      gotoxy(30, 12);
      printf("La matrice tabjo, les tableaux tabepreuve et tabpays sont crees ");
      Textecolor(3);
      gotoxy(30, 13);
      printf("----------------------------------------------------");
      gotoxy(30, 14);
      printf("|              |                    |              |");
      gotoxy(30, 15);
      printf("| tabjo        |     tabpays        |   tabepreuve |");
      gotoxy(30, 16);
      printf("|              |                    |              |");
      gotoxy(30, 17);
      printf("----------------------------------------------------");
      gotoxy(30, 18);
      printf("|                   Are created                    |");
      gotoxy(30, 19);
      printf("----------------------------------------------------");
      gotoxy(30, 20);
      printf("Press any key to return to the menu");
      break;
    case 2:
      system("cls");
      Textecolor(8);
      printf("les pays sont: \n");
      for (i = 0; i < nb_py / 2; i++)
      {
        Textecolor(5);
        gotoxy(1, i + 1);
        printf("%d-", i + 1);
        Textecolor(3);
        gotoxy(5, i + 1);
        printf("%s", tabpays[i]);
        Textecolor(5);
        gotoxy(50, i + 1);
        printf("|  %d-", i + (nb_py / 2) + 1);
        Textecolor(3);
        gotoxy(58, i + 1);
        printf("%s", tabpays[i + (nb_py / 2)]);
        Sleep(150);
      }
      printf("\n\n\t\t\tPress any key to return to the menu");
      break;
    case 3:
      system("cls");
      Textecolor(8);
      printf("les epreuves sont: \n");
      for (i = 0; i < nb_ep / 2; i++)
      {
        Textecolor(5);
        gotoxy(1, i + 1);
        printf("%d-", i + 1);
        Textecolor(3);
        gotoxy(5, i + 1);
        printf("%s", tabepreuve[i]);
        Textecolor(5);
        gotoxy(50, i + 1);
        printf("|  %d-", i + (nb_ep / 2) + 1);
        Textecolor(3);
        gotoxy(58, i + 1);
        printf("%s", tabepreuve[i + (nb_ep / 2)]);
        Sleep(150);
      }
      printf("\n\n\t\t\tPress any key to return to the menu");
      break;
    case 4:
    label:
      system("cls");
      Textecolor(4);
      printf("\n\n\n");
      printf("\t\t\t ___________________________________________________________________________\n");
      printf("\t\t\t| Remarque !! si vous ne conaissez pas le nom exact  de l'epreuve           |\n");
      printf("\t\t\t| clicker sur <echap> pour retourner au menu et lister  les epreuves        |\n");
      printf("\t\t\t| sinon clicker sur n'importe touche                                        |\n");
      printf("\t\t\t|___________________________________________________________________________|\n");
      retour = getch();
      switch (retour)
      {
      case ESC:
        goto Menu;
        break;
      default:
        Textecolor(3);
        printf("\t\t\tDonnez l'epreuve :");
        gets(epreuve);
        remove_white_spaces(epreuve);
        pos = -1; // boolean et utiliser pour avoir la position en mm temps.
        for (i = 0; i < nb_ep; i++)
        {
          strcpy(epreuve2, tabepreuve[i]);
          remove_white_spaces(epreuve2);
          if (strcmp(epreuve2, epreuve) == 0)
          {
            pos = i;
            i = nb_ep;
          }
        }
        if (pos == -1)
        {
          goto label;
        }
        if (pos != -1)
        {
          printf("\t\t\tLe numero d'epreuve est :%d\n", pos + 1);
          printf("\t\t\tPress any key to return to the menu");
        }
      }
      break;
    case 5:
    out:
      system("cls");
      Textecolor(4);
      printf("\n\n\n");
      printf("\t\t\t ___________________________________________________________________________\n");
      printf("\t\t\t| Remarque !! si vous ne conaissez pas le nom exact  du pays                |\n");
      printf("\t\t\t| clicker sur <echap> pour retourner au menu et lister  les pays            |\n");
      printf("\t\t\t| sinon clicker sur n'importe touche                                        |\n");
      printf("\t\t\t|___________________________________________________________________________|\n");
      retour = getch();
      switch (retour)
      {
      case ESC:
        goto Menu;
        break;
      default:
        Textecolor(3);
        printf("\t\t\tDonnez le pays :");
        gets(pays3);
        remove_white_spaces(pays3);
        pos = -1; // boolean et utiliser pour avoir la position en mm temps.
        for (i = 0; i < nb_py; i++)
        {
          strcpy(pays2, tabpays[i]);
          remove_white_spaces(pays2);
          if (strcmp(pays2, pays3) == 0)
          {
            pos = i;
            i = nb_py;
          }
        }
        if (pos == -1)
        {
          goto out;
        }
        if (pos != -1)
        {
          printf("\t\t\tLe numero de pays est :%d\n", pos + 1);
          printf("\t\t\tPress any key to return to the menu");
        }
      }
      break;
    case 6:
      system("cls");
      Textecolor(5);
      printf("\n\n\n");
      printf("\t\t\tentrer le numero de pays puis l epreuve dont vous voulez  \n");
      printf("\t\t\t            inserer un athlete et donnez son nom :        \n");
      Textecolor(4);
      printf("\t\t\t ___________________________________________________________________________\n");
      printf("\t\t\t| Remarque !! si vous ne conaissez pas le numero clicker sur <echap>        |\n");
      printf("\t\t\t| pour retourner au menu et avoir le numero de pays/epreuve                 |\n");
      printf("\t\t\t| sinon clicker sur n'importe touche                                        |\n");
      printf("\t\t\t|___________________________________________________________________________|\n");
      _getch();
      switch ((retour = _getch()))
      {
      case ESC:
        goto Menu;
        break;
      default:
        Textecolor(5);
        printf("\t\t\tnumero pays: ");
        scanf("%d", &nump);
        printf("\t\t\tnumero epreuve: ");
        scanf("%d", &nume);
        printf("\t\t\tLe nom d'athlete : ");
        scanf("%s", athletes2);
        inserath(athletes2, nump, nume);
        break;
      }
      printf("\n\t\t\tPress any key to return to the menu");
      break;
    case 7:
      system("cls");
      Textecolor(3);
      printf("\t\t\tSvp entrer le nom du pays que vous voulez : ");
      scanf("%s", blad);
      listathpays(blad);
      Textecolor(5);
      printf("\n\t\t\tPress any key to return to the menu");
      break;
    case 8:
    repeat:
      system("cls");
      Textecolor(3);
      printf("\n\n\n");
      printf("\t\t\tentrer le numero de l epreuve dont vous voulez  \n");
      printf("\t\t\t   confirmer si il ya des participants ou non   \n");
      Textecolor(4);
      printf("\t\t\t ___________________________________________________________________________\n");
      printf("\t\t\t| Remarque !! si vous ne conaissez pas le numero clicker sur <echap>        |\n");
      printf("\t\t\t| pour retourner au menu et avoir le numero de l'epreuve                    |\n");
      printf("\t\t\t| sinon clicker sur n'importe touche                                        |\n");
      printf("\t\t\t|___________________________________________________________________________|\n");
      printf("\t\t\t numero epreuve: ");
      scanf("%d", &nume);
      Textecolor(8);
      if (sansath(nume) == True)
      {
        printf("\t\t\t La fonction a retourner:");
        Textecolor(2);
        printf("True\n");
      }
      else
      {
        printf("\t\t\t La fonction a retourner:");
        Textecolor(4);
        printf("False\n");
      }
      printf("\n\n");
      Textecolor(3);
      printf("\t\t\t si vous voulez videz la ligne puis r%cessayer clicker sur <oui> \n", 130);
      printf("\t\t\t  sinon ecrire n'importe quoi :");
      scanf("%s", choix);
      remove_white_spaces(choix);
      if (strcmp(choix, "oui") == 0)
      {
        for (i = 0; i < nb_py; i++)
        {
          tabjo[nume - 1][i] = NULL;
        }
        strcpy(tabepreuve[nume - 1], "cette epreuve n'existe plus");
        goto repeat;
      }
      break;
    case 9:
      system("cls");
      printf("\n\n\n");
      Textecolor(4);
      printf("\t\t\t ___________________________________________________________________________\n");
      printf("\t\t\t| Remarque !! si vous voulez stopper l'affichage clicker sur n'importe      |\n");
      printf("\t\t\t|   quelle autre touche.clicker une autre fois pour retourner au menu       |\n");
      printf("\t\t\t|___________________________________________________________________________|\n");
      printf("\t\t\tpress any key to start");
      getch();
      system("cls");
      listjo();
      printf("\t\t\tpress any key to return to the menu ");
      getch();
      break;
    case 10:
    here:
      system("cls");
      Textecolor(4);
      printf("\n\n\n");
      printf("\t\t\t ___________________________________________________________________________\n");
      printf("\t\t\t| Remarque !! si vous ne conaissez pas le nom exact  du pays                |\n");
      printf("\t\t\t| clicker sur <echap> pour retourner au menu et lister  les pays            |\n");
      printf("\t\t\t| sinon clicker sur n'importe touche                                        |\n");
      printf("\t\t\t|___________________________________________________________________________|\n");
      retour = getch();
      switch (retour)
      {
      case ESC:
        goto Menu;
        break;
      default:
        Textecolor(3);
        printf("\t\t\tDonnez le pays que vous voulez supprimer :");
        scanf("%s", blad);
        listathpays(blad);
        suppays(blad);
        Textecolor(3);
        printf("\t\t\tpress any key to return to the menu ");
      }
      break;
    case 11:
      system("cls");
      Textecolor(3);
      printf("\n\n\n");
      printf("\t\t\tSvp entrer le nom du athlete que vous voulez supprimer : ");
      scanf("%s", nomath);
      printf("\t\t\t Donner le numero du pays puis l'epreuve :\n");
      printf("\n");
      Textecolor(4);
      printf("\t\t\t ___________________________________________________________________________\n");
      printf("\t\t\t| Remarque !! si vous ne conaissez pas le numero clicker sur <echap>        |\n");
      printf("\t\t\t| pour retourner au menu et avoir le numero de pays/epreuve                 |\n");
      printf("\t\t\t| sinon clicker sur n'importe touche                                        |\n");
      printf("\t\t\t|___________________________________________________________________________|\n");
      _getch();
      switch ((retour = _getch()))
      {
      case ESC:
        goto Menu;
        break;
      default:
        Textecolor(3);
        printf("\t\t\tnumero pays:");
        scanf("%d", &np);
        printf("\t\t\tnumero epreuve:");
        scanf("%d", &ne);
        suppath(nomath, np, ne);
        printf("\n\t\t\tPress any key to return to the menu");
        break;
      }
      break;
    case 12:
      system("cls");
      Textecolor(3);
      printf("\n\n\t\t\tToutes les epreuves contient des participants \n");
      printf("\t\t\t si vous voulez videz une ligne puis r%cessayer clicker sur <oui> \n", 130);
      printf("\t\t\t  sinon ecrire n'importe quoi :");
      scanf("%s", choix);
      remove_white_spaces(choix);
      if (strcmp(choix, "oui") == 0)
      {
        printf("\t\t\t entrer le numero d'une ligne que vous voulez videz :");
        scanf("%d", &li);
        for (i = 0; i < nb_py; i++)
        {
          tabjo[li - 1][i] = NULL;
        }
      }
      suplignesvides();
      Textecolor(3);
      printf("\n\n");
      printf("\t\t\t Toutes les epreuves qui ne contient pas des participants sont supprim%c", 130);
      break;
    default:
      system("cls");
      Chargement();
      strcpy(voice, "you are quitting the program now ");
      strcpy(charCommand, "espeak \"");
      strcat(charCommand, voice);
      system(charCommand);
      Sleep(200);
      strcpy(voice, "good bye everybody");
      strcpy(charCommand, "espeak \"");
      strcat(charCommand, voice);
      system(charCommand);
      Barrechargement();
      exit(1);
      break;
    }
    
  }
    getch();
  return 0;
}