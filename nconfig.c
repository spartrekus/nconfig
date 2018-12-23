
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
/*
       -----------------------
       |                     |
       |     NCONFIG         |
       |                     |
       -----------------------
*/
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

//////////////////////////////////////////
#include <stdio.h>
#if defined(__linux__) //linux
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__) 
#define MYOS 4  // freebsd
#define PATH_MAX 2500
#else
#define MYOS 0
#endif



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
//#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
//#include <sys/types.h>
#include <unistd.h>  //define getcwd
//////////////////////////////////////////
//////////////////////////////////////////


void printdir()
{
   DIR *dirp; int chr ;  
   struct dirent *dp;
   dirp = opendir( "." );
   while  ((dp = readdir( dirp )) != NULL ) 
   {
        if (  strcmp( dp->d_name, "." ) != 0 )
        if (  strcmp( dp->d_name, ".." ) != 0 )
        {
            for ( chr = 0 ;  chr <= strlen(dp->d_name) ; chr++) 
               printf( "%c" , dp->d_name[chr] );
            printf( "\n" );
        }
   }
   closedir( dirp );
}



void nsystem( char *mycmd )
{
   printf( "<CMD: %s>\n", mycmd );
   system( mycmd );
   printf( " Defunc CMD: %s>\n", mycmd );
}


void npkg( char *mycmd )
{
           char cmdi[PATH_MAX];
           printf( "< npkg (start) (OS: %d)\n" , MYOS );
           if      ( MYOS == 1 )
             strncpy( cmdi , " apt-get install -y  " , PATH_MAX );
           else if ( MYOS == 4 )
             strncpy( cmdi , " pkg install -y  " , PATH_MAX );
             //strncpy( cmdi , " pkg install  " , PATH_MAX );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , mycmd , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           if ( strcmp( mycmd, "" ) != 0 ) 
              nsystem( cmdi ); 
           printf( "  npkg (completed) (OS: %d)\n" , MYOS );
}


///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}








//////////////////////////////////////////
//////////////////////////////////////////
int main( int argc, char *argv[])
{

   int i; 
   int foundcmd = 0;
   int ch = 0;
   char cmdi[PATH_MAX];

   if ( MYOS == 1 )
     printf( "OS: Linux (Keep going OpenSource)\n" );
   else if ( MYOS == 2 )
     printf( "OS: Win (Could be much better choice, have a try in free Opensource for your freedom)\n" );
   else if ( MYOS == 3 )
     printf( "OS: Win (Could be much better choice, have a try in free Opensource for your freedom)\n" );
   else if ( MYOS == 4 )
     printf( "OS: BSD/OpenBSD/FreeBSD (Good choice)\n" );



    ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "os" ) ==  0 ) 
     {
       printf( "< what is my os? (os cmd) (OS: %d)\n" , MYOS );
       return 0;
     }
     if ( MYOS == 2 ) return 0;  // right, so let's keep opensource
     if ( MYOS == 3 ) return 0;  // right, so let's keep opensource





    ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "ip" ) ==  0 ) 
     {
       if      ( MYOS == 1 ) nsystem( " ip addr " );
       else if ( MYOS == 4 ) nsystem( " ifconfig " );
       return 0;
     }

    ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "df" ) ==  0 ) 
     {
       if      ( MYOS == 1 ) nsystem( " df -h " );
       else if ( MYOS == 4 ) nsystem( " df -h  " );
       return 0;
     }





    ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( ( strcmp( argv[1] , "nfont" ) ==  0 ) || ( strcmp( argv[1] , "vidfont" ) ==  0 ) )
     {
       if ( MYOS == 1 )
         nsystem( " setfont  /usr/share/consolefonts/Lat15-TerminusBold32x16.psf.gz    " );
       else if ( MYOS == 4 )
         nsystem( " vidfont " );
       return 0;
     }


     ////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( ( strcmp( argv[1] , "nconfig" ) ==  0 ) || ( strcmp( argv[1] , "update" ) ==  0 )  )
     {
       //nsystem( " mkdir git ; cd git ; git clone https://github.com/spartrekus/nconfig nconfig  " );  <-- takes too much resource 
       nsystem( "  wget tinyurl.com/nconfig1 -O nconfig.c ; gcc nconfig.c -o nconfig " );
       return 0;
     }





     ////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "termedit" ) ==  0 ) 
     {
           nsystem( " wget https://raw.githubusercontent.com/spartrekus/davedit/master/termedit.c  -O termedit.c " );
           nsystem( " wget https://raw.githubusercontent.com/spartrekus/davedit/master/termedit.h  -O termedit.h " );
           nsystem( " wget https://raw.githubusercontent.com/spartrekus/davedit/master/structs.h  -O structs.h " );
           nsystem( "     gcc -lncurses termedit.c -o termedit  " );
           return 0;
     }





    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    if ( argc >= 3)
      if ( strcmp( argv[1] , "pkg" ) ==  0 )  // it is like in BSD
      if ( strcmp( argv[2] , "" ) !=  0 ) 
      {
           if ( MYOS == 1 )
              strncpy( cmdi , " apt-get update ; apt-get install -y " , PATH_MAX );
           else if ( MYOS == 4 )
              strncpy( cmdi , " pkg install -y " , PATH_MAX );

           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           for( i = 2 ; i < argc ; i++) 
           {
              printf( "=> %d/%d %s \n", i , argc , argv[ i ] );
              strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
              strncat( cmdi , argv[ i ] , PATH_MAX - strlen( cmdi ) -1 );
              strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           }
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           nsystem( cmdi );
           return 0; 
      }
    /////////////////////////////////////////////////////////////




      ////////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "c" ) ==  0 ) || ( strcmp( argv[2] , "C" ) ==  0 ) )
      {
         if ( MYOS == 1 ) nsystem( " apt-get update " );
         if ( MYOS == 1 ) 
           nsystem( " apt-get install -y  vim make tcc gcc ncurses-dev gcc make vim  subversion  " );
         else if ( MYOS == 4 ) 
           npkg( " vim gcc make " );
         return 0;
      }


    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "desktop" ) ==  0 ) 
      {
          printf( "\n" );
          printf( "======\n" );
          printf( "=MENU=\n" );
          printf( "======\n" );
          printf( "1. Blackbox\n" );
          printf( "2. Icewm\n" );
          printf( "3. Other (just free)\n" );
          printf( "<Enter Your Choice and Press Return to Continue>\n" ); 
          ch = getchar();
          printf( "<Keypress: %c>\n", ch ); 

          if           ( ch == '1') 
            printf( "=> blackbox \n" );
          else if      ( ch == '2') 
            printf( "=> icewm\n" );

         if ( MYOS == 1 ) nsystem( " apt-get update " );
         npkg( " tcc  " );
         npkg( " links  " );
         npkg( " ssh  " );

         if      ( MYOS == 1 ) npkg( " ncurses-dev xinit xterm " );
         else if ( MYOS == 4 ) npkg( " ncurses Xorg " );

         if           ( ch == '1') 
         {
            npkg( " blackbox " ); 
         }
         else if      ( ch == '2') 
         {
            npkg( " icewm " ); 
            npkg( " menu " ); 
         }

         npkg( " less  " );
         npkg( " wget  " );
         npkg( " bash  " );
         npkg( " xinit xterm " );

         npkg( " sshfs  " );
         npkg( " i3lock  " );
         npkg( " vim  " );

         npkg( " wmctrl " );
         npkg( " xdotool " );
         npkg( " feh " );
         npkg( " zip " );

         npkg( " xclip " );

         npkg( " dillo " );
         npkg( " links " );
         ////////////////////////////////////////////////////////

         if ( MYOS == 1 )
         {
	 nsystem( " apt-get install  -y  console-setup " ); // very first, the keyboard
         nsystem( " apt-get install  -y links " );
         nsystem( " apt-get install  -y ssh " );
         nsystem( " apt-get install  -y xz-utils " );
         nsystem( " apt-get install  -y xinit xterm " );
         nsystem( " apt-get install  -y xbindkeys  " );
         nsystem( " apt-get install  -y wmctrl   " );
         nsystem( " apt-get install  -y xdotool   " );
         ////////////////////////////////////////////////////////
         nsystem( " apt-get install  -y tcc  " ); //always there
         nsystem( " apt-get install  -y tcc  " ); //always there
         nsystem( " apt-get install  -y screen  " ); //always there
         ////////////////////////////////////////////////////////
         //nsystem( " apt-get install  -y x11-xserver-utils ");
         //nsystem( " apt-get install  -y xserver-xorg ");
         nsystem( " apt-get install  -y libx11-dev  " );
         // xserver-xorg-legacy  " ); 
         nsystem( " apt-get install  -y feh  " );
         nsystem( " apt-get install  -y xterm  " );
         nsystem( " apt-get install  -y xbindkeys  " );
         nsystem( " apt-get install  -y i3lock  " );
         nsystem( " apt-get install  -y scrot  " );
         nsystem( " apt-get install  -y fspanel  " );
         nsystem( " apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y xclip  scrot feh  " );
         nsystem( " apt-get install  -y xdotool   " );
         ////////////////////////////////////////////////////////
         nsystem( " apt-get install -y screen  " );
         nsystem( " apt-get install -y sshfs  " );

         nsystem( " apt-get install  -y fbpanel  " );

         nsystem( " apt-get install  -y links " );
         nsystem( " apt-get install  -y ssh " );
         nsystem( " apt-get install  -y xinit xterm " );

         ////////////////////////////////////////////////////////
         //if ( strcmp( argv[2] , "desk+" ) ==  0 ) 
            nsystem( " apt-get install  -y nedit  " ); //it works
            nsystem( " apt-get install  -y fbpanel  " );
            nsystem( " apt-get install  -y xpaint  " );

         nsystem( " apt-get install  -y less  " ); 
         nsystem( " apt-get install  -y calcurse  " ); 
         nsystem( " apt-get install  -y abook  " ); 
         }

         ////////////////////////////////////////////////////////
         return 0;
      }






    ///////////////////////////////////////////////////////
    // BSD Rocks
    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( strcmp( argv[1] , "wheel" ) ==  0 ) 
      {
         printf( " you may enter this : pw user mod username -G wheel \n" );
         printf( " or : nconfig set wheel \n" );
         return 0;
      }
    ///////////////////////////////////////////////////////
    // BSD Rocks
    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( strcmp( argv[1] , "de" ) ==  0 )  // BSD
      {
         nsystem( " kbdcontrol -l /usr/share/syscons/keymaps/german.iso.kbd " );
         return 0;
      }







    ////////////////////////////////////////////////////////
    if ( argc == 2)
     if ( ( strcmp( argv[1] , "nfont" ) ==  0 ) || ( strcmp( argv[1] , "font" ) ==  0 ) 
     || ( strcmp( argv[1] , "setfont" ) ==  0 ) || ( strcmp( argv[1] , "ft" ) ==  0 ) )
     {
       if ( MYOS == 1 )
         nsystem( " setfont  /usr/share/consolefonts/Lat15-TerminusBold32x16.psf.gz    " );
       else if ( MYOS == 4 )
         nsystem( " vidfont " );
       return 0;
     }





     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "linux" ) ==  0 ) 
     {
       nsystem( " wget  https://raw.githubusercontent.com/spartrekus/linux-logo/master/linux.png -O linux.png  " );
       return 0;
     }



    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "set" ) ==  0 ) 
      if ( strcmp( argv[2] , "pc" ) ==  0 ) 
      if ( MYOS == 1 )
      {
	  nsystem( " apt-get install -y console-data console-setup " );
          nsystem( " apt-get install -f -y console-data locales" );
          nsystem( " dpkg-reconfigure tzdata " );
          nsystem( " dpkg-reconfigure console-data " );
          nsystem( " dpkg-reconfigure console-setup " );
          nsystem( " dpkg-reconfigure keyboard-configuration " );
          nsystem( " dpkg-reconfigure locales " );
          nsystem( " echo LANG=C.UTF-8 > /etc/default/locale  " );
          return 0;
      }




     ////////////////////////////////////////////////////////
     if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "games" ) ==  0 ) 
      {
         if ( MYOS == 1 ) nsystem( " apt-get update " );
         // xmahjongg - tile-based solitaire game
         npkg( " xdemineur xmahjongg " );
         return 0;
      }




     ////////////////////////////////////////////////////////
     if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "mutt" ) ==  0 ) 
      {
         if ( MYOS == 1 ) nsystem( " apt-get update " );
         npkg( " mutt  " );
         return 0;
      }








     ////////////////////////////////////////////////////////
     if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "xinit" ) ==  0 ) 
      {
         if ( MYOS == 1 ) nsystem( " apt-get update " );
         npkg( " xinit xterm  " );
         return 0;
      }


    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "svn" ) ==  0 ) 
      || ( strcmp( argv[2] ,  "subversion" ) ==  0 ) )
      {
          if ( MYOS == 1 ) 
	    nsystem( " apt-get update ; apt-get install -y subversion tcc make ncurses-dev  " );
          else if ( MYOS == 4 ) 
          {
            npkg( " subversion gcc " );
            npkg( " make " );
            npkg( " ncurses " );
          }

         if ( MYOS == 1 ) nsystem( " apt-get update " );
         if ( MYOS == 1 ) 
           nsystem( " apt-get install -y  vim make tcc gcc ncurses-dev gcc make vim  subversion  " );
         else if ( MYOS == 4 ) 
           npkg( " vim gcc make " );

         return 0;
      }



      if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "sddm" ) ==  0 ) 
      {
         nsystem( " apt-get update " );
         nsystem( "  apt-get install -y  --no-install-recommends sddm " );
         return 0;
      }









   ////////////////////////////////////////////////////////
   if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "sys" ) ==  0 ) 
     {
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y tcc " );
         return 0;
     }

    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] ,   "system" ) ==  0 ) 
        || ( strcmp( argv[2] ,   "standard" ) ==  0 ) 
        || ( strcmp( argv[2] ,   "base" ) ==  0 ) 
        )
      {
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y tcc " ); 
         nsystem( " apt-get install  -y debootstrap " );
         nsystem( " apt-get install  -y ssh " ); 
         nsystem( " apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y debootstrap " );
         nsystem( " apt-get install  -y links " ); 
         nsystem( " apt-get install  -y ncurses-dev  " ); 
         nsystem( " apt-get install  -y ncurses-dev screen " ); 
         nsystem( " apt-get install  -y ncurses-dev tcc " ); 
         nsystem( " apt-get install  -y ncurses-dev " );
         nsystem( " apt-get install  -y ncurses-dev  " ); 
         nsystem( " apt-get install  -y ncurses-dev make " ); 
         nsystem( " apt-get install  -y ncurses-dev less " ); 
         nsystem( " apt-get update " );
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y alsa-base " );
         nsystem( " apt-get install  -y alsa-utils " );
         nsystem( " apt-get install  -y vim  " );
         nsystem( " apt-get install  -y tcc  " );
         return 0;
      }




















   ////////////////////////////////////////////////////////
   if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "xbase" ) ==  0 ) 
     {
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y debootstrap " );
         nsystem( " apt-get install  -y xterm " );
         nsystem( " apt-get install  -y xinit xterm " );
         nsystem( " apt-get install  -y xbindkeys  wmctrl    xterm xinit  " );
         nsystem( " apt-get install  -y xinit wmctrl  " );
         nsystem( " apt-get install  -y xinit xdotool  " );
         nsystem( " apt-get install  -y xterm " );
         nsystem( " apt-get install  -y xclip " );
         nsystem( " apt-get install  -y fspanel  " );
         nsystem( " apt-get install  -y xterm " );
         nsystem( " apt-get install  -y x11-xserver-utils  " ); 
         nsystem( " apt-get install  -y x11-xserver-utils xserver-xorg-legacy  " ); 
         nsystem( " apt-get install  -y libx11-dev  " );  //really useful and really small
         return 0;
     }


    ////////////////////////////////////////////////////////
    if ( argc == 3)
    if ( strcmp( argv[1] , "install" ) ==  0 ) 
    if ( strcmp( argv[2] , "libx11+" ) ==  0 ) 
    {
         nsystem( " apt-get update ; apt-get install  -y libx11-dev  " );  
         nsystem( " apt-get install  -y ncurses-dev libx11-dev " ); 
         nsystem( " apt-get install  -y ncurses-dev libxaw7-dev " ); 
         nsystem( "   apt-get install -y lesstif2-dev  " );
         return 0;
    }







    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "mypc" ) ==  0 ) 
         || ( strcmp( argv[2] , "pc" ) ==  0 ) )
      {
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y debootstrap " );
         nsystem( " apt-get install  -y sshfs  " );
         nsystem( " apt-get install  -y tcc  " );
    ////////////////////////////////////////////////////////
         nsystem( " apt-get install  -y screen " );
         nsystem( " apt-get install  -y dillo " );

	 nsystem( " apt-get update  " );
         ////////////////////////////////////////////////////////
         nsystem( " apt-get install  -y tcc  " ); //always there
         ////////////////////////////////////////////////////////
         nsystem( " apt-get install  -y xinit xterm " );
         nsystem( " apt-get install  -y libx11-dev  " );

         ////////////////////////////////////////////////////////
         nsystem( " apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y xinit xterm " );
         nsystem( " apt-get install  -y x11-xserver-utils ");
         nsystem( " apt-get install  -y libx11-dev  " );
         // xserver-xorg-legacy  " ); 

         nsystem( " apt-get install  -y feh  " );
         nsystem( " apt-get install  -y xpaint  " );
         nsystem( " apt-get install  -y xterm  " );
         nsystem( " apt-get install  -y xbindkeys  " );
         nsystem( " apt-get install  -y scrot  " );
         ////////////////////////////////////////////////////////

         nsystem( " apt-get install  -y fbpanel  " );  // <- small and clean?
         nsystem( " apt-get update ; apt-get install -y doublecmd-gtk --no-install-recommends  " );
         nsystem( " apt-get install  -y i3lock scrot " );
         nsystem( " apt-get install  -y less  " );
         nsystem( " apt-get install  -y ssh  " );
         nsystem( " apt-get install  -y wget  " );
         nsystem( " apt-get install  -y make  " );
         nsystem( " apt-get install  -y vim  " );
         ///////// working efficiently with double cmd 
         nsystem( " apt-get install  -y vim  " );
         return 0;
      }








    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "min" ) ==  0 ) 
      {
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y ncurses-dev screen " ); 
         nsystem( " apt-get install  -y ncurses-dev tcc " ); 
         return 0;
      }







     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] ,   "pwd" ) ==  0 ) 
     {
         printf( "%s\n", getcwd( cmdi , PATH_MAX ));
         return 0;
     }
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] ,   "USER" ) ==  0 ) 
     {
         printf( "%s\n", getenv( "USER") );
         return 0;
     }
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] ,   "TERM" ) ==  0 ) 
     {
         printf( "%s\n", getenv( "TERM") );
         return 0;
     }
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] ,   "HOME" ) ==  0 ) 
     {
         printf( "%s\n", getenv( "HOME") );
         return 0;
     }
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] ,   "ls" ) ==  0 ) 
     {
         printdir();
         return 0;
     }
     ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "ls" ) ==  0 ) 
     {
         chdir( argv[ 2 ] );
         printdir();
         return 0;
     }





   ////////////////////////////////////////////////////////
   if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "tiny" ) ==  0 ) 
     {
         nsystem( " apt-get update " );
         nsystem("  apt-get install  -y xinit xterm netsurf vim ssh sshfs ncurses-dev tcc " ); 
         nsystem( " apt-get install  -y xbindkeys wmctrl xdotool " );
         nsystem( " apt-get install  -y libx11-dev ");
         return 0;
     }








   ////////////////////////////////////////////////////////
   if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "x11" ) ==  0 ) 
     {
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y  xinit xterm " );
         nsystem( " apt-get install  -y xbindkeys wmctrl " );
         nsystem( " apt-get install  -y libx11-dev ");
         nsystem( " apt-get install  -y x11-xserver-utils xserver-xorg-legacy  " ); 
         return 0;
     }








    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 )  
     if ( ( strcmp( argv[2] , "work" ) ==  0 )
     || ( strcmp( argv[2] , "xwork" ) ==  0 ) )
     {
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y debootstrap " );
       nsystem( " apt-get install  -y ncurses-dev " ); 
       nsystem( " apt-get install  -y tcc " );
         nsystem( " apt-get install  -y links " );
       nsystem( " apt-get install  -y screen " );
       nsystem( " apt-get install  -y vim " );
       nsystem( " apt-get install  -y links " );
       nsystem( " apt-get install  -y zip " );
       nsystem( " apt-get install  -y ssh " );
       nsystem( " apt-get install  -y sshfs " );
       nsystem( " apt-get install  -y zip " );
         nsystem( " apt-get install  -y x11-xserver-utils  " ); 
         nsystem( " apt-get install  -y x11-xserver-utils xserver-xorg-legacy  " ); 
         nsystem( " apt-get install  -y xterm " );
         nsystem( " apt-get install  -y   xinit xterm " );
         nsystem( " apt-get install  -y xinit xbindkeys  wmctrl  xclip fspanel xterm xinit  " );
         nsystem( " apt-get install  -y  wmctrl  " );
         nsystem( " apt-get install  -y xterm " );
         nsystem( " apt-get install  -y subversion " );
         nsystem( " apt-get install  -y  xdotool  " );
         nsystem( " apt-get install  -y   xinit xterm " );
         nsystem( " apt-get install  -y xterm " );
         nsystem( " apt-get install  -y subversion " );
         ////nsystem( " apt-get update ; apt-get install -y doublecmd-gtk --no-install-recommends  " );
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y tcc " ); 
         nsystem( " apt-get install  -y ssh " ); 
         nsystem( " apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y links " ); 
         nsystem( " apt-get install  -y ncurses-dev  " ); 
         nsystem( " apt-get install  -y ncurses-dev screen " ); 
         nsystem( " apt-get install  -y ncurses-dev tcc " ); 
         nsystem( " apt-get install  -y ncurses-dev subversion " ); 
         nsystem( " apt-get install  -y ncurses-dev make " ); 
         nsystem( " apt-get install  -y ncurses-dev less " ); 
         nsystem( " apt-get update " );
	 nsystem( " apt-get update ; apt-get install -y subversion tcc make ncurses-dev  " );
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y alsa-base " );
         nsystem( " apt-get install  -y alsa-utils " );
         nsystem( " apt-get install  -y vim  " );
         nsystem( " apt-get install  -y tcc  " );
         nsystem( " apt-get install  -y ssh screen subversion tcc " );
         nsystem( " apt-get install  -y ssh screen subversion tcc " );
         nsystem( " apt-get install  -y mupdf  feh  " );
         nsystem( " apt-get install  -y i3lock    " );
         nsystem( " apt-get install  -y gcc     " );

         /// new
	 nsystem( " apt-get update ; apt-get install --no-install-recommends  -y texlive mupdf  " );
	 nsystem( " apt-get install --no-install-recommends  -y texlive-latex-extra    " );  // for enumitem with resume !! (enumitem.sty)

         /// surely
	 nsystem( " apt-get install -y screen " );
	 nsystem( " apt-get install -y tcc " );
	 nsystem( " apt-get install -y links " );
	 nsystem( " apt-get install -y ncurses-dev " );
	 nsystem( " apt-get install -y libx11-dev " );
       return 0;
     }
    ////////////////////////////////////////////////////////









    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    if ( argc >= 3)
      if ( strcmp( argv[1] , "search" ) ==  0 )  // it is like in BSD
      if ( strcmp( argv[2] , "" ) !=  0 ) 
      {
           strncpy( cmdi , " apt-get update ; apt-cache search " , PATH_MAX );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           for( i = 2 ; i < argc ; i++) 
           {
              printf( "=> %d/%d %s \n", i , argc , argv[ i ] );
              strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
              strncat( cmdi , argv[ i ] , PATH_MAX - strlen( cmdi ) -1 );
              strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           }
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           nsystem( cmdi );
           return 0; 
      }
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////




    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////



    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    if ( argc >= 3)
      if ( strcmp( argv[1] , "search" ) ==  0 )  // it is like in BSD
      if ( strcmp( argv[2] , "" ) !=  0 ) 
      {
           strncpy( cmdi , " apt-cache search " , PATH_MAX );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           for( i = 2 ; i < argc ; i++) 
           {
              printf( "=> %d/%d %s \n", i , argc , argv[ i ] );
              strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
              strncat( cmdi , argv[ i ] , PATH_MAX - strlen( cmdi ) -1 );
              strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           }
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           nsystem( cmdi );
           return 0; 
      }
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////








    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 2)  // default
     if ( ( strcmp( argv[1] , "asoundrc" ) ==  0 ) 
     || ( strcmp( argv[1] , "asoundrc0" ) ==  0 ) 
     || ( strcmp( argv[1] , "asound" ) ==  0 ) 
     || ( strcmp( argv[1] , "sound" ) ==  0 ) 
     || ( strcmp( argv[1] , "asoundrc-0" ) ==  0 ) )
     {
       nsystem( "  wget    \"https://raw.githubusercontent.com/spartrekus/asoundrc/master/asoundrc-0\" -O ~/.asoundrc " );
       return 0;
     }
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 2)
     if ( ( strcmp( argv[1] , "asoundrc-1" ) ==  0 ) 
     || ( strcmp( argv[1] , "asoundrc1" ) ==  0 ) )
     {
       nsystem( "  wget    \"https://raw.githubusercontent.com/spartrekus/asoundrc/master/asoundrc-1\" -O ~/.asoundrc " );
       return 0;
     }







    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "fetch" ) ==  0 ) 
     if ( strcmp( argv[2] , "screenrc" ) ==  0 ) 
     {
       nsystem( " wget  \"https://raw.githubusercontent.com/spartrekus/screenrc/master/screenrc\"  -O ~/.screenrc "  );
       return 0;
     }










    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "set" ) ==  0 ) 
      if ( strcmp( argv[2] , "time" ) ==  0 ) 
      {
          nsystem( " dpkg-reconfigure tzdata " );
          return 0;
      }




    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "set" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "keyboard" ) ==  0 ) 
      || ( strcmp( argv[2] , "key" ) ==  0 ) 
      || ( strcmp( argv[2] , "keys" ) ==  0 ) )
      {
          npkg( " keyboard-configuration " );
          nsystem( " dpkg-reconfigure keyboard-configuration " ); //for gal
          npkg( " console-setup " );
          //nsystem( " dpkg-reconfigure console-setup " );  //for console
          // on bsd, /etc/rc.conf  with keymap=us   or keymap=de or keymap=fr
          return 0;
      }



    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "set" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "locales" ) ==  0 ) 
      || ( strcmp( argv[2] , "locale" ) ==  0 ) )
      {
          // select de de utf8 utf8, and then put C.UTF8
          system( " apt-get install -f -y console-data locales" );
          system( " dpkg-reconfigure locales " );
          nsystem( " echo LANG=C.UTF-8 > /etc/default/locale  " );
          return 0;
      }




     if ( argc == 2)
     if ( strcmp( argv[1] , "kwin95" ) ==  0 ) 
     {
       nsystem( " cd ; wget  https://raw.githubusercontent.com/spartrekus/kwin95/master/wallpaper-win.jpg  -O .wallpaper.jpg " );
       nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/icons.zip  -O icons.zip  ; unzip -o icons.zip  " );
       nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/xkey.ini   -O .xbindkeysrc  " );
       nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/xinitrc.txt -O .xinitrc  " );
       return 0;
     }


     if ( argc == 2)
     if ( strcmp( argv[1] , "xinitrc" ) ==  0 ) 
     {
       nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/xinitrc.txt -O .xinitrc  " );
       return 0;
     }




     ////////////////////////////////////////////////////////
     // for a stable system without systemD (D for de-installing ), devuan live desktop
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "devuan" ) ==  0 ) 
     {
          printf( "\n" );
          printf( "======\n" );
          printf( "=MENU=\n" );
          printf( "======\n" );
          printf( "1. Raspberry\n" );
          printf( "2. i386\n" );
          printf( "3. Cancel\n" );
          printf( "<Enter Your Choice and Press Return to Continue>\n" ); 
          ch = getchar();
          printf( "<Keypress: %c>\n", ch ); 
          if      ( ch == '1') 

             nsystem( " wget https://mirror.leaseweb.com/devuan/devuan_ascii/embedded/devuan_ascii_2.0.0_arm64_raspi3.img.xz " );
          else if ( ch == '2') 
          {
             nsystem( " wget https://files.devuan.org/devuan_ascii/desktop-live/devuan_ascii_2.0.0_i386_desktop-live.iso" );
             nsystem( " md5sum devuan_ascii_2.0.0_i386_desktop-live.iso" );
             printf( " have a quick check 62bd2d1faa502dab8abd8ae67254024b  devuan_ascii_2.0.0_i386_desktop-live.iso\n " );
             nsystem( " md5sum devuan_ascii_2.0.0_i386_desktop-live.iso" );
          }
          else if ( ch == '3') 
          {
             printf( " Choice: 3\n" );
          }
          printf( " Have a good day \n" );
          return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "raspbian" ) ==  0 ) 
     {
          nsystem(  " wget http://director.downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2018-11-15/2018-11-13-raspbian-stretch-lite.zip " );
          // https://downloads.raspberrypi.org/raspbian_lite_latest
          return 0;
     }
       




      ///////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if (  ( strcmp( argv[2] , "libreoffice" ) ==  0 ) 
         || ( strcmp( argv[2] , "lbo" ) ==  0 ) )
      {
	  nsystem( " apt-get update ; apt-get install --no-install-recommends  -y libreoffice    " );
	  nsystem( "  apt-get install -y nedit  " );
	  nsystem( "  apt-get install -y gnumeric  " );
          return 0;
      }




    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "beamer" ) ==  0 ) 
      {
	  nsystem( " apt-get update " );
	  nsystem( " apt-get install --no-install-recommends  -y texlive mupdf  " );
	  nsystem( " apt-get install -y sshfs " );
	  nsystem( " apt-get install -y screen " );
	  nsystem( " apt-get install -y --no-install-recommends mupdf texlive texlive-latex-extra   texlive-font-utils " );
          return 0;
      }




    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "mupdf" ) ==  0 ) 
      {
	  nsystem( " apt-get update " );
	  nsystem( " apt-get install mupdf " );
	  nsystem( " apt-get install screen " );
          return 0;
      }




    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "claw" ) ==  0 ) 
      || ( strcmp( argv[2] , "claws" ) ==  0 ) 
      || ( strcmp( argv[2] , "email" ) ==  0 ) 
      || ( strcmp( argv[2] , "xemail" ) ==  0 ) )
      {
          nsystem( " apt-get update ; apt-get install -y mutt claws-mail  msmtp " );
          return 0;
      }







    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "office"  ) ==  0 ) 
      || ( strcmp( argv[2] ,   "calligra"  ) ==  0 ) )
      {
          nsystem( " apt-get update ; apt-get install -y mutt   karbon    calligrasheets calligrawords calligrastage  calligraplan  " );
          nsystem( " apt-get install  -y libx11-dev  " );  //really useful and really small
          nsystem("   apt-get install  -y      karbon    calligrasheets  calligrawords  calligrastage     ");

          nsystem("     apt-get install  -y  kfourinline kmahjongg kmines knights ksudoku                 tuxmath  xdemineur    ");
          nsystem("    apt-get install  -y              calligraplan      ");
          nsystem("    apt-get install  -y         feh xpaint scrot    ");
         nsystem( "    apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y alsa-base " );
         nsystem( " apt-get install  -y alsa-utils " );
         nsystem( " apt-get install  -y vim  " );
         nsystem( " apt-get install  -y tcc  " );
          return 0;
      }




    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "printer" ) ==  0 ) 
      || ( strcmp( argv[2] , "cups" ) ==  0 ) )
      {
          nsystem( " apt-get update ; apt-get install  -y cups   " ); 
          nsystem( " apt-get install  -y cups-bsd  " ); 
          return 0;
      }


    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "scanner" ) ==  0 ) 
      {
          nsystem( " apt-get update ; apt-get install  -y sane  " ); 
          return 0;
      }







    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    // xterm has bugs
    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "kde" ) ==  0 ) 
      {
	  nsystem( " apt-get update  " );
          nsystem( " dpkg-reconfigure keyboard-configuration " );

          nsystem( " apt-get install  -y tcc links debootstrap " ); 
	  nsystem( " apt-get update ; apt-get install -y kde-standard " );

          nsystem( " apt-get install  -y zip ssh ncurses-dev " );
         nsystem( " apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y debootstrap " );

         nsystem( " apt-get install  -y rxvt " ); // rxvt has no (less) display bug, like xterm or Eterm.

	  nsystem( " apt-get update ; apt-get install -y kde-standard " );
          //nsystem( " dpkg-reconfigure tzdata " );
	  nsystem( " apt-get install -y feh scrot " );
          nsystem( " apt-get install -y kmahjongg  " ); // ma
	  nsystem( " apt-get install -y vim " );

          nsystem( " apt-get install  -y rxvt  " );
	  nsystem( " apt-get install -y fledit " ); //let's hope that one day in there with fltk 
	  nsystem( " apt-get install -y leafpad " ); //leafpad for pa

	  nsystem( " apt-get install -y xterm " );
	  nsystem( " apt-get install -y vim " );
	  nsystem( " apt-get install -y chromium " );
	  nsystem( " apt-get install -y chromium-browser " );
         nsystem( " apt-get update ; apt-get install -y doublecmd-gtk --no-install-recommends  " );

         nsystem( " apt-get install  -y ssh " ); 
         nsystem( " apt-get install  -y links " ); 
         nsystem( " apt-get install  -y ncurses-dev  " ); 
          nsystem( " apt-get install  -y subversion   " ); 
          nsystem( " apt-get install  -y make   " ); 
          nsystem( " apt-get install  -y libx11-dev   " ); 
          nsystem( " apt-get install  -y ncurses-dev screen " ); 

          nsystem("    apt-get install  -y         feh xpaint scrot    ");
         nsystem( "    apt-get install  -y ncurses-dev " ); 
         nsystem( " apt-get install  -y alsa-base " );
         nsystem( " apt-get install  -y alsa-utils " );
         nsystem( " apt-get install  -y vim  " );
         nsystem( " apt-get install  -y tcc  " );

          nsystem( " apt-get install  -y ekiga  " ); // to chat and voice video  over ip in intranet // why not

          npkg( " xdemineur xmahjongg " );

          nsystem( " apt-get update ; apt-get install -y mutt claws-mail  msmtp " );
          nsystem( " apt-get install  -y gcc   " ); 
          nsystem( " apt-get install  -y tcc   " ); 
          nsystem( " apt-get install  -y libx11-dev  " );  //really useful and really small
	  nsystem( " apt-get install -y kde-standard " );
          nsystem( " apt-get install  -y libx11-dev  " );  //really useful and really small

         nsystem( " apt-get install  -y i3lock scrot " );
         nsystem( " apt-get install  -y less  " );
         nsystem( " apt-get install  -y ssh  " );
         nsystem( " apt-get install  -y wget  " );
         nsystem( " apt-get install  -y make  " );
         nsystem( " apt-get install  -y vim  " );
         nsystem( " apt-get install  -y xpaint  " );
         nsystem( " apt-get install  -y nedit  " ); //it works

         nsystem( " apt-get install  -y feh  " );
         nsystem( " apt-get install  -y xterm  " );
         nsystem( " apt-get install  -y xbindkeys  " );
         nsystem( " apt-get install  -y scrot  " );
         nsystem( " apt-get update ; apt-get install  -y cups  " ); 
         nsystem( " apt-get update ; apt-get install  -y cups-bsd   " ); 
         nsystem( " apt-get install  -y vim  " );

         nsystem( " apt-get install  -y xpenguins  " );
         nsystem( " apt-get install  -y xdemineur  " );
         nsystem( " apt-get install  -y xedit  " );
         nsystem( " apt-get install  -y nedit  " );

        nsystem( " apt-get install  -y mtpfs  " );
        nsystem( " apt-get install  -y go-mtpfs  " );
        nsystem( " apt-get install  -y jmtpfs  " );
        /*
         go-mtpfs - Mount MTP devices over FUSE
         golang-github-hanwen-usb-dev - CGO bindings for libusb.
         jmtpfs - FUSE based filesystem for accessing MTP devices
         mtpfs - FUSE filesystem for Media Transfer Protocol devices
        */


         return 0;
      }







    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "ssh" ) ==  0 ) 
      {
	  nsystem( " echo install useful ssh packages ; apt-get update " );
	  nsystem( " apt-get install ssh " );
	  nsystem( " apt-get install sshfs " );
          return 0;
      }







    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "gcc" ) ==  0 ) || ( strcmp( argv[2] , "gcc" ) ==  0 ) )
      {
	  nsystem( " apt-get update ; apt-get install -y subversion gcc make ncurses-dev  " );
          return 0;
      }



    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 2)
     if ( ( strcmp( argv[1] , "nfont" ) ==  0 ) || ( strcmp( argv[1] , "font" ) ==  0 ) 
     || ( strcmp( argv[1] , "setfont" ) ==  0 ) || ( strcmp( argv[1] , "ft" ) ==  0 ) )
     {
       if ( MYOS == 1 )
         nsystem( " setfont  /usr/share/consolefonts/Lat15-TerminusBold32x16.psf.gz    " );
       else if ( MYOS == 4 )
         nsystem( " vidfont " );
       return 0;
     }



    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 2)
     if ( ( strcmp( argv[1] , "nfont" ) ==  0 ) || ( strcmp( argv[1] , "font" ) ==  0 ) )
     {
       if ( MYOS == 1 )
         nsystem( " setfont  /usr/share/consolefonts/Lat15-TerminusBold32x16.psf.gz    " );
       else if ( MYOS == 4 )
         nsystem( " vidfont " );
       return 0;
     }




    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( ( strcmp( argv[1] , "wlan0" ) ==  0 ) 
      || ( strcmp( argv[1] , "wlan" ) ==  0 ) )
      {
          //nsystem( "  ifdown --force wlan0 ; sleep 1s ; ifup wlan0 " );
          nsystem( "  while : ; do   dhclient -v wlan0 ; sleep 5s ; done " );
          return 0;
      }




     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "msx" ) ==  0 ) 
     {
       nsystem( " xterm -bg black -fg green -fa 33 " );
       return 0;
     }


    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "chromium" ) ==  0 ) 
         || ( strcmp( argv[2] , "chromium-browser" ) ==  0 ) 
         || ( strcmp( argv[2] , "cr" ) ==  0 ) )
      {
	  nsystem( " apt-get update ; apt-get install -y --no-install-recommends   chromium-browser " );
	  nsystem( " apt-get install -y --no-install-recommends   chromium " );
	  nsystem( " apt-get install -y --no-install-recommends   chromium-browser " );
	  nsystem( " apt-get install -y --no-install-recommends   chromium " );
          return 0;
      }



      ////////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "midori" ) ==  0 ) 
      {
	  if ( MYOS == 1 ) nsystem( " apt-get update " );
	  npkg( " midori  ");
          return 0;
      }




    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "words" ) ==  0 ) || ( strcmp( argv[2] , "calligra" ) ==  0 ) )
      {
	  nsystem( " apt-get update " );
	  nsystem( " apt-get install -y calligrawords " );
          return 0;
      }




      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "arec" ) ==  0 ) 
      {
          if ( fexist( "/usr/bin/mencoder" ) != 1 ) 
                 nsystem( "apt-get update ; apt-get install -y alsa-utils  "); 
          nsystem( "  arecord -V stereo -t wav -f cd -D plughw:0,0 $(ntimestamp )-arec.wav  ");
          return 0;
      }
      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "vrec" ) ==  0 ) 
      {
          if ( fexist( "/usr/bin/mencoder" ) != 1 ) 
                 nsystem( "apt-get update ; apt-get install -y mencoder  "); 
          nsystem( " mencoder tv:// -tv driver=v4l2:device=/dev/video0 -ovc lavc -nosound -o $( ntimestamp )-video.avi  ");
          return 0;
      }
      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////







    ////////////////////////////////////////////////////////
    if ( argc == 2)
    if ( strcmp( argv[1] , "x48" ) ==  0 ) 
    {
      nsystem( " xlsfonts ; x48 -connFont -misc-fixed-medium-r-semicondensed--0-0-75-75-c-0-iso8859-1     -smallFont -misc-fixed-medium-r-semicondensed--0-0-75-75-c-0-iso8859-1   -mediumFont -misc-fixed-medium-r-semicondensed--13-100-100-100-c-60-iso8859-1  -largeFont -misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-1     " );
      return 0;
    }
    ////////////////////////////////////////////////////////
    if ( argc == 2)
    if ( strcmp( argv[1] , "hl" ) ==  0 ) 
    {
       nsystem( " cd ; cd  SIERRA/Half-Life ; sleep 1 ; xterm -e wine hl.exe  ");
       return 0;
    }



    ////////////////////////////////////////////////////////
    if ( argc == 2)
    if ( strcmp( argv[1] , "webcam" ) ==  0 ) 
    {
       nsystem( " mplayer -fs -zoom tv://  ");
       return 0;
    }



    ////////////////////////////
    if ( argc >= 2)
    if ( strcmp( argv[ 1 ] , "--args"  ) == 0  ) 
    {
          for( i = 1 ; i < argc ; i++) 
          {
	    printf( "> Argument: %d/%d: %s\n", i-1 , argc-2 ,  argv[ i ] );
            if ( fexist( argv[ i ] ) == 1 ) 
            printf( "  - File found: %s\n" , argv[ i ] );
          }
          return 0;
    }




    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "tex" ) ==  0 ) 
      || ( strcmp( argv[2] , "texlive" ) ==  0 ) 
      || ( strcmp( argv[2] , "latex" ) ==  0 ) )
      {
          //system( " apt-get install --no-install-recommends texlive-font-utils  " );
	  nsystem( " apt-get update ; apt-get install --no-install-recommends  -y texlive mupdf  " );
	  nsystem( " apt-get install --no-install-recommends  -y texlive-latex-extra    " );  // for enumitem with resume !! (enumitem.sty)
	  nsystem( " apt-get install -y screen " );
          return 0;
      }


    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "libx11" ) ==  0 )
      {
         nsystem( " apt-get update " );
         nsystem( " apt-get install  -y ncurses-dev libx11-dev " ); 
         return 0;
      }


    /////
    if ( argc == 3)
      if ( strcmp( argv[1] , "fetch" ) ==  0 ) 
      if  ( strcmp( argv[2] , "vimrc" ) ==  0 ) 
      {
         printf ( "  Get vimrc from net! \n" );
         nsystem( " wget 'https://raw.githubusercontent.com/spartrekus/Config-Xbindkeys/master/vimrc.txt' -O ~/.vimrc  " );
         return 0;
      }

    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 ) 
     if ( strcmp( argv[2] , "markdown" ) ==  0 ) 
     {
       nsystem( " apt-get update ; apt-get install -y markdown " );
       return 0;
     }

    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 ) 
     if ( strcmp( argv[2] , "dbview" ) ==  0 ) 
     {
       nsystem( " apt-get update ; apt-get install -y dbview " );
       return 0;
     }


    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 ) 
     if ( ( strcmp( argv[2] , "squashfs" ) ==  0 ) || ( strcmp( argv[2] , "squash" ) ==  0 ) )
     {
       nsystem( " apt-get update ; apt-get install -y squashfs-tools " );
       return 0;
     }









     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "nexplorer" ) ==  0 ) 
     {
       nsystem( " wget https://raw.githubusercontent.com/spartrekus/nexplorer/master/nexplorer.c -O nexplorer.c ; tcc -lncurses nexplorer.c -o nexplorer ; chmod  +x  nexplorer ; ls nexplorer  -ltra " );
       return 0;
     }





     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "markdown4c" ) ==  0 ) 
     {
       printf( "Prg to come soon.... \n" );
       return 0;
     }
    

     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "markdown" ) ==  0 ) 
     {
       nsystem( " wget https://raw.githubusercontent.com/spartrekus/markdown-examples/master/README.md -O markdown.md " );
       nsystem( " markdown markdown.md > markdown.html " );
       return 0;
     }



     ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] , "mount" ) ==  0 ) 
     {
         printf( "diskls found: %s\n", argv[1] ); 
         strncpy( cmdi , "  mkdir /media/pendrive ;  cd ;  umount /media/pendrive ; mount  " , PATH_MAX );
         strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , argv[2] , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , " /media/pendrive ; nexplorer /media/pendrive ; cd ; umount /media/pendrive " , PATH_MAX - strlen( cmdi ) -1 );
         nsystem( cmdi );
         nsystem( " mount " );
       return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 )  
     if ( ( strcmp( argv[2] , "fbi" ) ==  0 ) || ( strcmp( argv[2] , "fbg" ) ==  0 ))
     {
       /// fbi and fbgv ! //gs?
       /// fbi images
       /// fbgv for pdfs
       nsystem( " apt-get update ; apt-get install -y fbi  " );
       nsystem( "  apt-get install -y fbi  " );
       nsystem( " apt-get install -y ghostscript " );
       return 0;
     }



     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "pi" ) ==  0 )
     {
         nsystem( " cd   ; sshfs pi@192.168.50.7:/home/pi sshfs " );
         return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 )
     if ( strcmp( argv[2] , "kde-games" ) ==  0 )
     {
         nsystem( " apt-get update ; apt-get  install -y kolf  kmahjongg katomic  kmines granatier kgoldrunner ");
         nsystem( " apt-get update ; apt-get  install -y kpat  " ); //freecell cards
         return 0;
     }

     ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 )
     if ( strcmp( argv[2] , "kde-pacman" ) ==  0 )
     {
         nsystem( " apt-get update ; apt-get  install -y kapman  kblocks " ); //tetris and pacman
         return 0;
     }





    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "x11-apps" ) ==  0 ) 
      {
         nsystem( " apt-get update ; apt-get install -y x11-apps " ); 
         return 0;
      }


    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "fltk" ) ==  0 ) 
      {
         nsystem( " apt-get update ; apt-get install -y g++ libfltk1.3-dev " ); 
         nsystem( "  apt-get install -y libx11-dev " ); 
         return 0;
      }

    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "fetch" ) ==  0 ) 
     if ( strcmp( argv[2] , "screenrc" ) ==  0 ) 
     {
       nsystem( " wget  \"https://raw.githubusercontent.com/spartrekus/screenrc/master/screenrc\"  -O ~/.screenrc "  );
       return 0;
     }














    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "fetch" ) ==  0 ) 
     if ( strcmp( argv[2] , "config" ) ==  0 ) 
     {
         nsystem( " wget  \"https://raw.githubusercontent.com/spartrekus/screenrc/master/screenrc\"  -O ~/.screenrc "  );

         nsystem( " wget 'https://raw.githubusercontent.com/spartrekus/Config-Xbindkeys/master/vimrc.txt' -O ~/.vimrc  " );

         nsystem( " wget tinyurl.com/nconfig1 -O /tmp/nconfig.c " );

         nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/xkey.ini   -O .xbindkeysrc  " );


         nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/xinitrc.txt -O .xinitrc  " );


         nsystem( " cd ; wget    \"https://raw.githubusercontent.com/spartrekus/asoundrc/master/asoundrc-0\" -O ~/.asoundrc " );

         chdir( getenv( "HOME" ));
         if ( fexist( ".wallpaper.jpg" ) == 0 ) 
            nsystem( " cd ; wget \"https://raw.githubusercontent.com/spartrekus/Totally-Libre-Free-GNU-Matrix-Wallpaper-1920x1080/master/cmatrix-free-gnu-wallpaper-unix-1920x1080.png\" -O .wallpaper.jpg   " );

         printf( " chdir HOME. \n " );
         chdir( getenv( "HOME" ));

         return 0;
     }









    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "fltk" ) ==  0 ) 
      {
         nsystem( " apt-get update ; apt-get install -y g++ libfltk1.3-dev " ); 
         nsystem( "  apt-get install -y libx11-dev " ); 
         return 0;
      }

    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "libfltk" ) ==  0 ) 
      {
         nsystem( " apt-get update ; apt-get install -y libfltk1.3-dev " ); 
         return 0;
      }





    //////////////////////////////////////
    if ( argc >= 3)
      if ( strcmp( argv[1] , "ssh" ) ==  0 ) 
      {
         strncpy( cmdi, "", PATH_MAX );
         strncat( cmdi , " ssh  " , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , " -C " , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , "192.168.1." , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , argv[2] , PATH_MAX - strlen( cmdi ) -1 );
         if ( argc == 4 )
         {
           strncat( cmdi , " -l " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , argv[3] , PATH_MAX - strlen( cmdi ) -1 );
         }
         strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
         printf( "<CMD: %s>\n", cmdi );
         nsystem( cmdi );
         return 0;
      }
    //////////////////////////////////////
    if ( argc >= 3)
      if ( strcmp( argv[1] , "nssh" ) ==  0 ) 
      {
         strncpy( cmdi, "", PATH_MAX );
         strncat( cmdi , " ssh  " , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , " -C " , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , "192.168.52." , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , argv[2] , PATH_MAX - strlen( cmdi ) -1 );
         if ( argc == 4 )
         {
           strncat( cmdi , " -l " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , argv[3] , PATH_MAX - strlen( cmdi ) -1 );
         }
         strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
         printf( "<CMD: %s>\n", cmdi );
         nsystem( cmdi );
         return 0;
      }






   ////////////////////////////////////////////////////////
   if ( argc == 2)
     if ( strcmp( argv[1] ,   "pi" ) ==  0 ) 
     {
        nsystem( " ssh pi@192.168.50.7 "  );
        return 0;
     }


     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "gnumeric" ) ==  0 ) 
     {
        nsystem( " apt-get update ; apt-get install -y --no-install-recommends          gnumeric " );
        return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "myip" ) ==  0 ) 
     {
         nsystem( " wget http://checkip.dyndns.com/ -O /tmp/extip ; cat /tmp/extip " ); 
         return 0;
     }
     ////////////////////////////////////////////////////////



     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "xwrapper" ) ==  0 ) 
     {
         nsystem( " dpkg-reconfigure xserver-xorg-legacy " );
         return 0;
     }


    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "fluid" ) ==  0 ) 
      {
         nsystem( " apt-get update ; apt-get install -y g++ libfltk1.3-dev " ); 
         nsystem( "  apt-get install -y libx11-dev " ); 
         nsystem( "  apt-get install -y fluid  " ); 
         return 0;
      }




      // setxkbmap
      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "xp" ) ==  0 ) 
      {
         nsystem( " cd ; mkdir .icewm " );
         nsystem( " cd ; mkdir .icewm/themes " );
         nsystem( " cd ; cd .icewm ; cd themes ; wget https://raw.githubusercontent.com/spartrekus/icewm-xp/master/WindowsXP.zip -O winxp.zip " );
         nsystem( " cd ; cd .icewm ; cd themes ; unzip -o winxp.zip " );
         nsystem( " cd ; cd .icewm ; wget https://raw.githubusercontent.com/spartrekus/icewm-xp/master/keys -O         keys   " );
         nsystem( " cd ; cd .icewm ; echo 'Theme=WindowsXP/default.theme'  >  theme " );
         nsystem( " cd ; echo setxkbmap de >  .xinitrc  " );
         nsystem( " cd ; echo icewm        >> .xinitrc  " );
         return 0;
      }




      ////////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "icewm" ) ==  0 ) 
      {
           if      ( MYOS == 1 ) npkg( " ncurses-dev icewm xinit xterm " );
           else if ( MYOS == 4 ) npkg( " ncurses Xorg feh vim icewm menu " );
           return 0; 
      }




     // chat: nconfig  pkg jabberd2  
     // calendar: calcurse
     // abook: contacts

     return 0; 
} 






/*
go-mtpfs - Mount MTP devices over FUSE
golang-github-hanwen-usb-dev - CGO bindings for libusb.
jmtpfs - FUSE based filesystem for accessing MTP devices
mtpfs - FUSE filesystem for Media Transfer Protocol devices
*/

/*
Better not to install fluid: 

The following NEW packages will be installed:
  fltk1.3-doc fluid libdrm-dev libdrm-exynos1 libdrm-omap1 libdrm-tegra0 libfltk-cairo1.3 libfltk-forms1.3
  libfltk-gl1.3 libfltk-images1.3 libfltk1.3-dev libgl1-mesa-dev libglu1-mesa libglu1-mesa-dev
  libpthread-stubs0-dev libx11-dev libx11-doc libx11-xcb-dev libxau-dev libxcb-dri2-0-dev libxcb-dri3-dev
  libxcb-glx0-dev libxcb-present-dev libxcb-randr0 libxcb-randr0-dev libxcb-render0-dev libxcb-shape0-dev
  libxcb-sync-dev libxcb-xfixes0-dev libxcb1-dev libxdamage-dev libxdmcp-dev libxext-dev libxfixes-dev
  libxshmfence-dev libxxf86vm-dev mesa-common-dev x11proto-core-dev x11proto-damage-dev x11proto-dri2-dev
  x11proto-fixes-dev x11proto-gl-dev x11proto-input-dev x11proto-kb-dev x11proto-xext-dev
  x11proto-xf86vidmode-dev xorg-sgml-doctools 
*/


