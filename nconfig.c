
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   //chdir
#include <dirent.h>


// new
#include <time.h>

///  norm
#define KRED  "\x1B[31m"
#define KGRE  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KNRM  "\x1B[0m"
///  bright
#define KBGRE  "\x1B[92m"
#define KBYEL  "\x1B[93m"


void lscount()
{
   double mycount = 0;
   DIR *dirp;
   struct dirent *dp;
   dirp = opendir( "." );
   while  ((dp = readdir( dirp )) != NULL ) 
   {    //  printf( "%s\n", dp->d_name );
         mycount++;
   }
   printf( "nlscount: %g\n", mycount );
   closedir( dirp );
}




///////////////////////////////////////////
void readfile( char *filesource )
{
   FILE *source; 
   int ch ; 
   source = fopen( filesource , "r");
   if ( source == NULL ) { printf( "File not found.\n" ); } else {
   while( ( ch = fgetc(source) ) != EOF )
   {
         printf( "%c", ch );
   }
   fclose(source);
   }
}
   





///////////////////////////////////////////
void grepfile( char *filesource , char *sstring)
{
   FILE *source; 
   int c,j ;
   char lline[PATH_MAX]; 
   char mysstring[PATH_MAX]; 
   strncpy( mysstring, sstring,  PATH_MAX); int pcc=0;
   int begin;
   j = 0;
   source = fopen( filesource , "r");
   if ( source == NULL ) { printf( "File not found.\n" ); } 
   else {
   {    c = fgetc(source);
        while( c != EOF )
        {
           //printf( ">%c", c );
           lline[j++] = c;
           begin = 0;
           if ( c == '\n' )
           {  
             begin = 1;
             lline[j]='\0';
             if ( strstr( lline, mysstring ) != 0 )
                 printf( "%s", lline );
             j = 0;
             lline[j]='\0';
           }
           c = fgetc(source);
        }
   fclose(source);
  }
  }
}



void nls()
{ 
   DIR *dirp;
   struct dirent *dp;
   dirp = opendir( "." );
   while  ((dp = readdir( dirp )) != NULL ) 
   {
         if (  strcmp( dp->d_name, "." ) != 0 )
         if (  strcmp( dp->d_name, ".." ) != 0 )
             printf( "%s\n", dp->d_name );
   }
   closedir( dirp );
}





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




///////////////
void listdir(const char *name, int indent, const char *searchitem )
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
	{
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf( path, sizeof(path), "%s/%s", name, entry->d_name);

            listdir( path, indent + 2, searchitem );
        } 
	else 
	{
	    if ( strstr( entry->d_name , searchitem ) != 0 ) 
	    {
              printf("%s/%s\n", name , entry->d_name );
	    }
        }
    }
    closedir(dir);
}




void fseek_filesize(const char *filename)
{
    FILE *fp = NULL;
    long off;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("failed to fopen %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fseek(fp, 0, SEEK_END) == -1)
    {
        printf("failed to fseek %s\n", filename);
        exit(EXIT_FAILURE);
    }

    off = ftell( fp );
    if (off == (long)-1)
    {
        printf("failed to ftell %s\n", filename);
        exit(EXIT_FAILURE);
    }

    //printf("[*] fseek_filesize - file: %s, size: %ld\n", filename, off);
    printf("%ld\n", off);

    if (fclose(fp) != 0)
    {
        printf("failed to fclose %s\n", filename);
        exit(EXIT_FAILURE);
    }
}













void nsystem( char *mycmd )
{
   printf( "<CMD: %s>\n", mycmd );
   system( mycmd );
   printf( " Defunc CMD: %s>\n", mycmd );
}


void ncmdwith( char *mycmd, char *myfile )
{
           char cmdi[PATH_MAX];
           printf( "** CMD (start) (OS: %d)\n" , MYOS );
           strncpy( cmdi , mycmd , PATH_MAX );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " \""  , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , myfile , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , "\" "  , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           nsystem( cmdi ); 
           printf( "** CMD (completed) (OS: %d)\n" , MYOS );
}


void npkg_update( )
{
    if ( MYOS == 1 ) 
      nsystem( "  apt-get update " );
}




////////////
void npkg( char *mycmd )
{
           char cmdi[PATH_MAX];
           printf( "< npkg (start) (OS: %d)\n" , MYOS );
           if      ( MYOS == 1 ) strncpy( cmdi , " apt-get install -y  " , PATH_MAX );
           else if ( MYOS == 4 ) strncpy( cmdi , " pkg install -y  " , PATH_MAX );

           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , mycmd , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );

           if ( strcmp( mycmd, "" ) != 0 ) nsystem( cmdi ); 
           printf( "  npkg (completed) (OS: %d)\n" , MYOS );
}


///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
//void fseek_filesize(const char *filename)
//int fexist(char *a_option)
int fexist(const char *a_option)
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

     ////////////////////////////////////////////////////////
     if ( argc == 2 )
     if ( strcmp( argv[1] , "yel" ) ==  0 )
     {
       printf("%s", KBYEL);
       printf("Hello Yellow Terminal (bright)\n");
       return 0;
     }

     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "fsck" ) ==  0 ) 
     {
        printf( "fsck_y_enable=\"YES\"  \n" );
        return 0;
     }

     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "rc" ) ==  0 ) 
     {
//growfs_enable="YES"
//keymap="de.kbd"
        printf( "#hostname=\"generic\"\n" );
        printf( "keymap=de\n" );
        printf( "keymap=\"de.kbd\"\n" );
        printf( "growfs_enable=\"YES\"\n" );
        printf( "fsck_y_enable=\"YES\"  \n" );
        printf( "ifconfig_DEFAULT=\"DHCP\"\n" );
        printf( "sshd_enable=\"YES\"\n" );
        printf( "fusefs_enable=\"YES\"  \n" );
        printf( "wlans_rtwn0=\"wlan0\"\n" );
        printf( "ifconfig_wlan0=\"WPA DHCP\"\n" );
        printf( "ifconfig_wlan0_ipv6=\"inet6 accept_rtadv\"\n" );
        printf( "create_args_wlan0=\"country AT regdomain FCC4\"\n" );
        printf( "allscreens_flags=\"-f terminus-b32\"  \n");
        printf( "sendmail_enable=\"NONE\"\n" );
        printf( "sendmail_submit_enable=\"NO\"\n" );
        printf( "sendmail_outbound_enable=\"NO\"\n" );
        printf( "sendmail_msp_queue_enable=\"NO\"\n" );
        printf( "#apache24_enable=\"YES\"  \n" );
        printf( "#proftpd_enable=\"YES\"  \n" );
        printf( "#dumpdev=\"AUTO\"\n" );
        return 0;
     }



     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "rc" ) ==  0 ) 
     {
         printf( "keymap=de \n" );
         printf( "fsck_y_enable=\"YES\"  \n" );
         printf( "sshd_enable=\"YES\"  \n" );
         printf( "ntpd_enable=\"YES\"  \n" );
         printf( "ntpd_sync_on_start=\"YES\"  \n" );
         printf( "fsck_y_enable=\"YES\"  \n" );
         printf( "ifconfig_wlan0=\"-ht WPA SYNCDHCP\"\n" );
         printf( "fusefs_enable=\"YES\"  \n" );
         printf( "allscreens_flags=\"-f terminus-b32\"  \n");
         printf( "#apache24_enable=\"YES\"  \n" );
         printf( "#fsck_y_enable=\"YES\"  \n" );
         printf( "#ifconfig_wlan0=\"-ht WPA SYNCDHCP\"\n" );
         return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "proftpd" ) ==  0 ) 
     {
         printf( "#apache24_enable=\"YES\"  \n" );
         printf( "proftpd_enable=\"YES\"  \n" );
         printf( "ntpd_enable=\"YES\"  \n" );
         printf( "ntpd_sync_on_start=\"YES\"  \n" );
         printf( "fsck_y_enable=\"YES\"  \n" );
         printf( "ifconfig_wlan0=\"-ht WPA SYNCDHCP\"\n" );
         return 0;
     }


    ////////////////////////////////////////////////////////
    if ( argc == 2)
    if ( strcmp( argv[1] , "-red" ) ==  0 ) 
    {
       printf("%sred\n", KRED);
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


     ////////////////////////////////////////////////////////
     if ( argc == 2 )
     if ( ( strcmp( argv[1] , "byellow" ) ==  0 ) || ( strcmp( argv[1] , "--byellow" ) ==  0 ) )
     {
       printf("%s", KBYEL);
       printf("Hello Yellow Terminal (bright)\n");
       return 0;
     }

      ////////////////////////////////////////////////////////
      // useful sometimes
      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "max" ) ==  0 ) 
      {
        nsystem( "  wmctrl -r :ACTIVE: -b toggle,maximized_vert,maximized_horz   " );
        return 0;
      }



     ////////////////////////////////////////////////////////
     if ( argc == 2 )
     if ( ( strcmp( argv[1] , "yellow" ) ==  0 ) || ( strcmp( argv[1] , "--yellow" ) ==  0 ) )
     {
       printf("%s", KYEL);
       printf("Hello Yellow Terminal\n");
       return 0;
     }


     char cmdi[PATH_MAX];
     char charo[PATH_MAX];
     int i; 

     ////////////////////////////////////////////////////////
     if ( argc == 2 )
     if ( strcmp( argv[1] , "hello" ) ==  0 ) 
     {
       printf("Hello Terminal\n");
       return 0;
     }

   ////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "mana" ) ==  0 ) 
     {
            npkg( "  manaplus " );
            return 0;
     }






     ///////////////////////////////////////
     ///////////////////////////////////////
     //// Right, portable apps
     ///////////////////////////////////////
     ///////////////////////////////////////
     if ( argc == 3 )
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( ( strcmp( argv[2] ,   "xapp" ) ==  0 ) 
     || ( strcmp( argv[2] ,     "xapps" ) ==  0 ) 
     || ( strcmp( argv[2] ,     "xutil" ) ==  0 ) 
     || ( strcmp( argv[2] ,     "xutils" ) ==  0 ) )
     {
            if ( MYOS == 1 )   nsystem( " apt-get update " );
            npkg( " screen   " );  
            npkg( " mutt   " );  
            npkg( " i3lock " );   
            npkg( " mpg123 " );   
            npkg( " feh  "  );
            npkg( " nedit  "  ); // motif
            npkg( " scrot " );   
            npkg( " xdotool  " );  
            npkg( " wmctrl  " );  
            npkg( " xclip  " );  
            npkg( " xterm   " );  
            if ( MYOS == 1 ) nsystem( " apt-get install -y --no-install-recommends mupdf " );
            if ( MYOS == 1 ) nsystem( " apt-get install -y  sshfs " );
            ///npkg( " claws-mail "  );
            return 0;
     }




   ////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "xbase" ) ==  0 ) 
     {
            if ( MYOS == 1 ) 
            {
                nsystem( " dpkg-reconfigure locales " );
                nsystem( " echo LANG=C.UTF-8 > /etc/default/locale  " );
                nsystem( " locale " );
            }

            nsystem( "  kldload fuse ; chmod 777 /dev/fuse " ); 
            nsystem( " mkdir /usr/local/bin " );
            //npkg( " icewm  " );

            if ( MYOS == 1 ) nsystem( " apt-get update " );
            if ( MYOS == 1 ) npkg( "    xserver-xorg " );
            else npkg( " Xorg " );
            npkg( " xterm xinit " );
            npkg( " xinit xterm " );
            npkg( " xclip  " );
            npkg( " scrot  " );
            return 0;
     }




   ////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "base" ) ==  0 ) 
     {
            npkg( "  screen " );
            npkg( "  mpg123 " );
            //if      ( MYOS == 1 ) 
            //   npkg( "  vim " );
            //else if ( MYOS == 4 ) 
            //   npkg( "  vim-console " );
            //else 
            //   npkg( "  vim " );
            npkg( "  subversion " ); 
            npkg( "  ncurses " );
            return 0;
     }
   ////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////






    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "fltk" ) ==  0 ) 
      {
         //nsystem( " apt-get update ; apt-get install -y g++ libfltk1.3-dev " ); 
         //nsystem( " apt-get update ; apt-get install -y libfltk1.3-dev " ); 
         //nsystem( "  apt-get install -y libx11-dev " ); 
         nsystem( " apt-get update ; apt-get install -y libfltk1.3 " ); 
         return 0;
      }

    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "fltk" ) ==  0 ) 
      {
         //fltk-1.3.5                     Cross-platform C++ graphical user interface toolkit
         if ( MYOS == 1 ) 
         nsystem( " apt-get update ; apt-get install -y g++ libfltk1.3-dev " ); 
         if ( MYOS == 1 ) 
         nsystem( "  apt-get install -y libx11-dev " ); 
         npkg( " fltk-1.3.5 " );
         return 0;
      }


     ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0      )  
     if ( strcmp( argv[2] , "sshfs" ) ==  0    ) 
     {
            if ( MYOS == 1 )  npkg( " sshfs  " );
            else              npkg( " fusefs-sshfs  " );
            return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0      )  
     if ( strcmp( argv[2] , "svn" ) ==  0    ) 
     {
            if ( MYOS == 1 )  npkg( " subversion   " );
            else              npkg( " subversion   " );
            return 0;
     }









    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( ( strcmp( argv[1] , "install" ) ==  0 )  || ( strcmp( argv[1] , "--install" ) ==  0 ))
     if ( ( strcmp( argv[2] , "pdftotext" ) ==  0 )
     || ( strcmp( argv[2] ,   "pdf2txt" ) ==  0 )
     || ( strcmp( argv[2] ,   "2txt" ) ==  0 ))
     {
       if ( MYOS == 1 ) nsystem( " apt-get update ; apt-get install -y poppler-utils   " );
       /////if ( MYOS == 1 ) nsystem( " apt-get install -y antiword docx2txt "  );
       if ( MYOS == 4 ) 
          npkg( " poppler-utils " );
       return 0;
     }

    ////////////////////////////////////////////////////////
    if  ( argc == 2)
     if ( strcmp( argv[1] , "dpms" ) ==  0 )
     {
         nsystem( " export DISPLAY=:0 ; xset s off ;  xset -dpms ;  xset s noblank  ; setterm -blank 0  " );
         return 0;
     }





    ///////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if  ( strcmp( argv[2] , "gnuplot" ) ==  0 )
      {
         if ( MYOS == 1 )   nsystem( "  apt-get update " );
         npkg( " gnuplot-x11 " ); //x11/gt, care because -qt has no zoom
         return 0; 
      }












      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "mylene" ) ==  0 ) 
      {
          printf(  "> Testing Application (mpg123,mplayer, http connection for audio, and audio) \n" );
          nsystem( " mpg123 http://listen.radionomy.com/mylenefarmerwebradio " );  //stable for testing sound 
          nsystem( " mplayer http://listen.radionomy.com/mylenefarmerwebradio " );  //stable for testing sound 
          return 0;
      }
      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( ( strcmp( argv[1] , "house" ) ==  0 ) || ( strcmp( argv[1] , "houseradio" ) ==  0 ) )
      {
          printf(  "> Testing Application (mpg123,mplayer, http connection for audio, and audio) \n" );
          nsystem( " mpg123 http://streaming.radionomy.com/Retro-House-Belgium " );
          nsystem( " mplayer http://streaming.radionomy.com/Retro-House-Belgium " );
          return 0;
      }









   ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "tex" ) ==  0 ) 
     {
            if ( MYOS == 1 ) nsystem( " apt-get update " );
            if ( MYOS == 1 ) 
              nsystem( " apt-get install -y --no-install-recommends texlive " );
            return 0;
     }









   ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( ( strcmp( argv[2] ,   "docx" ) ==  0 ) 
     || ( strcmp( argv[2] ,   "antiword" ) ==  0   ) 
     || ( strcmp( argv[2] ,   "catx" ) ==  0 ) )
     {
            npkg( "  docx2txt " );
            npkg( "  antiword " );
            npkg( "  antiword " );
            npkg( "  docx2txt  " );
            npkg( "  antiword  " );
            npkg( "  catdoc  " );
            npkg( " antiword docx2txt "  );
            if ( MYOS == 1 ) 
                npkg( " catdoc " );  // to conv from xls to txt
            return 0;
     }



     ///////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "perm" ) ==  0 )  // root access
     {
         nsystem("   mkdir /media/pendrive "  );

         if ( MYOS == 1 ) 
             nsystem("   chmod 777 /dev/fb0  " );

         nsystem("   mkdir /usr/local/bin/  "  );
         nsystem( "  chmod 777 /dev/ttyv0 " ); 
         nsystem( "  chmod 777 /dev/tty0 " ); 
         nsystem( "  kldload fuse ; chmod 777 /dev/fuse " ); 
         nsystem( "  chmod 777 /dev/ttyv0 " ); 
         nsystem( "  chmod 777 /dev/fb0 " ); // for fbi and fbgs  
         nsystem( "  kldload fuse ; chmod 777 /dev/fuse " ); 
         nsystem( "  kldload fuse ; chmod 777 /dev/fuse " ); 
         nsystem("   sysctl vfs.usermount " );
         nsystem("   sysctl vfs.usermount=1 " );
         nsystem("   sysctl vfs.usermount  " );
         return 0;
     }





    ////////////////////////////////////////////////////////
    if ( argc == 2)
    if ( strcmp( argv[1] , "ue0" ) ==  0 ) 
    {
       printf(  "\n" );
       printf( "ifconfig_ue0=\"dhcp\"\n" );
       printf(  "\n" );
       return 0;
    }
    ////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////
    if ( argc == 2)
    if ( strcmp( argv[1] , "adhoc" ) ==  0 ) 
    {
       printf(  "\n" );
       printf( "ifconfig_ue0=\"inet 192.168.123.100 255.255.255.0\"\n" );
       printf(  "\n" );
       return 0;
    }
    ////////////////////////////////////////////////////////




     ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 ) 
     if ( ( strcmp( argv[2] , "claw" ) ==  0 )  || ( strcmp( argv[2] , "claws" ) ==  0 ) )
     {
       npkg( "  claws-mail "  );
       return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "claw" ) ==  0 ) 
     {
       printf( " Search bin   claw %d\n", fexist( "/usr/bin/claws-mail" ));
       printf( " Search local claw %d\n", fexist( "/usr/local/bin/claws-mail" ));
       nsystem( " export DISPLAY=:0 ;  claws-mail "  );
       return 0;
     }



     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( ( strcmp( argv[1] , "scrot" ) ==  0 ) || ( strcmp( argv[1] , "shot" ) ==  0 ) )
     {
         chdir( getenv( "HOME") );
         printf( "%s\n", getenv( "HOME") );
         if ( fexist( "pics" ) != 2 )       nsystem( " mkdir pics " );
         nsystem( " cd ; cd pics ;  scrot -s '\%Y\%m\%d\%H\%M\%S-screenshot.png'   " );
         nsystem( " ls -1 ~/pics/ | sort  > ~/.clipboard " );
         return 0;
     }




     if ( argc == 2)  // default
     if ( strcmp( argv[1] , "asoundrc1" ) ==  0 ) 
     {
              printf( "pcm.!default { \n" );
              printf( "          type asym \n" );
              printf( "          playback.pcm { \n" );
              printf( "                  type plug \n" );
              printf( "                  slave.pcm \"hw:1,0\" \n" );
              printf( "          } \n" );
              printf( "          capture.pcm { \n" );
              printf( "                  type plug \n" );
              printf( "                  slave.pcm \"hw:1,0\" \n" );
              printf( "          }  \n" );
              printf( " } \n" );
              return 0;
     }




     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "lsc" ) ==  0 ) 
     {
       lscount();
       return 0;
     }




      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "entropy" ) ==  0 )
      {
               nsystem( "   fetch -R https://raw.githubusercontent.com/spartrekus/freebsd-13-entropyfix/master/libssl.so.111  "  );
               nsystem( "   fetch  -R https://raw.githubusercontent.com/spartrekus/freebsd-13-entropyfix/master/libcrypto.so.111 " );

               nsystem( "   wget  --no-check-certificate     https://raw.githubusercontent.com/spartrekus/freebsd-13-entropyfix/master/libssl.so.111  "  );
               nsystem( "   wget  --no-check-certificate     https://raw.githubusercontent.com/spartrekus/freebsd-13-entropyfix/master/libcrypto.so.111 " );
               return 0;
      }



      ////////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] ,   "ext2" ) ==  0 ) || ( strcmp( argv[2] ,   "e2fs" ) ==  0 )  )
      {
         npkg( " e2fsprogs  " );
         return 0;
      }




     ////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////
     if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "wutil" ) ==  0 ) 
      {
         if ( MYOS == 1 ) nsystem( " apt-get update " );
         npkg( " wireless-tools   " );
         return 0;
      }







     ////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////
     if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "quake" ) ==  0 ) 
      {
         if ( MYOS == 1 ) nsystem( " apt-get update " );
         npkg( " ioquake3   " );
         return 0;
      }






     ////////////////////////////////////////////////////////
     if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] ,    "prboom" ) ==  0 ) 
         || ( strcmp( argv[2] ,   "doom" ) ==  0 ) 
         || ( strcmp( argv[2] ,   "boom" ) ==  0 ) )
      {
         if ( MYOS == 1 ) 
           nsystem( " apt-get update " );
         npkg( " prboom-plus   " );
         npkg( " prboom-plus-game-server   " );  // on linux, please use lkdoom 
         return 0;
      }



      ////////////////////////////////////////////////////////
      // useful sometimes
      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "max" ) ==  0 ) 
      {
        nsystem( "  wmctrl -r :ACTIVE: -b toggle,maximized_vert,maximized_horz   " );
        return 0;
      }



   ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "gcc" ) ==  0 ) 
     {
            npkg( " gcc5-libs gcc5 " );
            return 0;
     }
   ////////////////////////////////////////////////////////






   ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "mupdf" ) ==  0 ) 
     {
            nsystem( " apt-get install -y --no-install-recommends mupdf " );
            return 0;
     }
   ////////////////////////////////////////////////////////


    
   ////////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
     if ( strcmp( argv[2] ,   "gs" ) ==  0 ) 
     {
            npkg( " ghostscript " );
            return 0;
     }
   ////////////////////////////////////////////////////////









    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    // xterm has bugs
    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "kde" ) ==  0 ) 
      || ( strcmp( argv[2] , "notebook" ) ==  0 ) 
      || ( strcmp( argv[2] , "kde-standard" ) ==  0 ) )
      {
	  nsystem( " apt-get update  " );

          npkg( " kbd " );
          npkg( " keyboard-configuration " );

          npkg( " gcc " );
          npkg( " subversion " );

          nsystem( " dpkg-reconfigure keyboard-configuration " ); //for gal
          npkg( " console-setup " );

	  npkg( " gcc " );
	  npkg( " nano " );
	  npkg( " screen " );
          nsystem( " apt-get install  -y subversion   " ); 
          ////nsystem( " dpkg-reconfigure keyboard-configuration " );
	  npkg( " ssh " );
	  npkg( " links " );
	  npkg( " wget " );
	  npkg( " less " );
	  npkg( " screen " );
	  npkg( " links " );

          npkg( " dosfstools  " );
	  if ( MYOS == 1 ) npkg( " ntfs-3g " );

	  //npkg( " ncurses-dev " );
	  npkg( " mplayer " );
          nsystem( " apt-get install  -y links debootstrap " ); 
	  nsystem( " apt-get update ; apt-get install -y kde-standard " );
          if ( MYOS == 1 )
          {
	    nsystem( " apt-get update ; apt-get install --no-install-recommends  -y libreoffice    " );
	    nsystem( "  apt-get install -y nedit  " );
	    nsystem( "  apt-get install -y gnumeric  " );
	    nsystem( "  apt-get install -y ssh  " );
	    nsystem( "  apt-get install -y sshfs  " );
	    npkg( " wmctrl " );
	    npkg( " xdotool " );
          }
	  npkg( " mpg123 " );
          nsystem( " apt-get install  -y zip ssh ncurses-dev " );
          nsystem( " apt-get install  -y ncurses-dev " ); 
          nsystem( " apt-get install  -y debootstrap " );
          nsystem( " apt-get install  -y gcc " );
          nsystem( " apt-get install  -y xinit xterm " );
         //nsystem( " apt-get install  -y rxvt " ); // rxvt has no (less) display bug, like xterm or Eterm.
	  nsystem( " apt-get update ; apt-get install -y kde-standard " );
          //nsystem( " dpkg-reconfigure tzdata " );

	  nsystem( " apt-get install -y feh scrot " );
	  nsystem( " apt-get install -y vim " );
	  nsystem( " apt-get install -y xterm " );

          npkg( " ghostscript " );

	  npkg( " xpaint " );
	  npkg( " mutt " );

	  npkg( " less " );
	  npkg( " tilem " );
	  npkg( " audacious " );
	  npkg( " pcsxr " );

	  npkg( " mupdf " );
	  npkg( " mpg123 " );
	  npkg( " xterm " );
	  npkg( " xinit " );
	  npkg( " scrot " );
	  npkg( " feh " );
	  npkg( " xz-utils " );

	  nsystem( " apt-get install -y leafpad " ); //leafpad for pa

	  npkg( " kate " );       // top editor
	  npkg( " audacious " );  // winamp like 
	  npkg( " leafpad " );       // top editor
	  npkg( " gnumeric " );       // top editor

          if ( MYOS == 1 )  
             npkg( " ntpdate " );

	 nsystem( " apt-get install -y xterm " );
	 nsystem( " apt-get install -y vim " );
	 nsystem( " apt-get install -y chromium " );
	 nsystem( " apt-get install -y chromium-browser " );
          ///nsystem( " apt-get update ; apt-get install -y doublecmd-gtk --no-install-recommends  " );

         npkg( " gnuplot-x11 " ); //x11/gt, care because -qt has no zoom
         nsystem( " apt-get install  -y rox-filer " ); 
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

          //nsystem( " apt-get install  -y ekiga  " ); // to chat and voice video  over ip in intranet // why not

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

            if ( MYOS == 1 ) 
              nsystem( " apt-get install -y --no-install-recommends texlive " );
              /////nsystem( " apt-get install --no-install-recommends texlive " );

         nsystem( " apt-get install  -y feh  " );
         nsystem( " apt-get install  -y make  " );
         nsystem( " apt-get install  -y gcc  " );
         nsystem( " apt-get install  -y clang  " );


         nsystem( " apt-get install  -y feh  " );
         nsystem( " apt-get install  -y xterm  " );
         nsystem( " apt-get install  -y xbindkeys  " );
         nsystem( " apt-get install  -y scrot  " );
         nsystem( " apt-get update ; apt-get install  -y cups  " ); 
         nsystem( " apt-get update ; apt-get install  -y cups-bsd   " ); 
         nsystem( " apt-get install  -y vim  " );

         //nsystem( " apt-get install  -y xpenguins  " );
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
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "dos" ) ==  0 ) 
      {
         npkg( " dosfstools  "  ); 
         return 0;
      }





     ////////////////////////////////////////////////////////
     if ( argc == 3)
      if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
      if ( strcmp( argv[2] ,   "vnc" ) ==  0 ) 
      {
         npkg( " x11vnc " );
         npkg( " xtightvncviewer  "  ); 
         return 0;
      }



      ///////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "settime" ) ==  0 ) 
      {
           nsystem( "  pkg install -y openntpd ; tzsetup ; service ntpd restart  " );
           return 0;
      }

      ////////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "set" ) ==  0 ) 
      if ( strcmp( argv[2] , "time" ) ==  0 ) 
      {
          if ( MYOS == 4 ) 
            nsystem( "  pkg install -y openntpd ; tzsetup ; service ntpd restart  " );
          else 
            nsystem( " dpkg-reconfigure tzdata " );
          if ( MYOS == 1 )  
             npkg( " ntpdate " );
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





     ///////////////////////////////////////////////////////
     if ( argc == 3)
     if ( strcmp( argv[1] , "install" ) ==  0 )  // root access
     if ( strcmp( argv[2] , "sshfs" ) ==  0 )    // root access
     {
         nsystem("    mkdir /media/pendrive "  );
         nsystem( "   kldload fuse ; chmod 777 /dev/fuse " ); 
         nsystem("    mkdir /media/pendrive " );
         nsystem( "    kldload fuse ; chmod 777 /dev/fuse " ); 
         nsystem("      sysctl vfs.usermount " );
         nsystem("      sysctl vfs.usermount=1 " );
         nsystem("      sysctl vfs.usermount  " );
         npkg( " fusefs-sshfs  " );
        return 0;
     }




    ////////////////////////////////////////////////////////
    if ( argc == 2)
    if ( strcmp( argv[1] , "-y" ) ==  0 ) 
    {
       printf("%syellow\n", KYEL);
       return 0;
    }


     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( ( strcmp( argv[1] , "-time" ) ==  0 ) || ( strcmp( argv[1] , "--time" ) ==  0 ) )
     {
       printf("%d\n", (int)time(NULL));
       return 0;
     }
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "-t" ) ==  0 ) 
     {
       printf("%d\n", (int)time(NULL));
       return 0;
     }

     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "da1" ) ==  0 ) 
     {
         nsystem( " mkdir /media/pendrive " );
         nsystem( " mount -t msdos /dev/da1s1 /media/pendrive " );
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




     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "fstab" ) ==  0 ) 
     {
             printf( "/dev/sda1  /media/pendrive  vfat  rw,user,exec,umask=000 0 0 \n" );
             printf( "/dev/da0s1a     /               ufs     rw      1       1" );
             printf( "/dev/ada0s2a     /               ufs     rw      1       1" );
             printf( "/dev/da0s1b     none            swap    sw      0       0" );
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
     if ( argc == 2)
     if ( strcmp( argv[1] , "xinitrc" ) ==  0 ) 
     {
             printf(" setxkbmap de \n" );
             printf("icewm\n" );
             return 0;
     }
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "screenrc" ) ==  0 ) 
     {
             printf("bindkey -k F1 prev\n" );
             printf("bindkey -k F2 next\n" );
             printf("vbell off\n" );
             return 0;
     }






      ////////////////////////////////////////////////////////
      if ( argc == 2)
      if ( strcmp( argv[1] , "xp" ) ==  0 ) 
      {
         nsystem( " cd ; mkdir .icewm " );
         nsystem( " cd ; mkdir .icewm/themes " );

         nsystem( " cd ; cd .icewm ; cd themes ; wget https://raw.githubusercontent.com/spartrekus/icewm-xp/master/WindowsXP.zip -O winxp.zip ; unzip -o winxp.zip  " );
         nsystem( " cd ; cd .icewm ; cd themes ; fetch -R https://raw.githubusercontent.com/spartrekus/icewm-xp/master/WindowsXP.zip ; unzip -o winxp.zip  " );


         nsystem( " cd ; cd .icewm ; wget --no-check-certificate https://raw.githubusercontent.com/spartrekus/icewm-xp/master/applications    -O  applications  " );
         nsystem( " cd ; cd .icewm ; wget  https://raw.githubusercontent.com/spartrekus/icewm-xp/master/applications    -O  applications  " );

         nsystem( " cd ; cd .icewm ; wget  --no-check-certificate   https://raw.githubusercontent.com/spartrekus/icewm-xp/master/accessories    -O  accessories  " );
         nsystem( " cd ; cd .icewm ; wget  https://raw.githubusercontent.com/spartrekus/icewm-xp/master/accessories   -O  accessories  " );

         nsystem( " cd ; cd .icewm ; wget --no-check-certificate https://raw.githubusercontent.com/spartrekus/icewm-xp/master/games    -O  games  " );
         nsystem( " cd ; cd .icewm ; wget  https://raw.githubusercontent.com/spartrekus/icewm-xp/master/games   -O  games  " );

         nsystem( " cd ; cd .icewm ; wget https://raw.githubusercontent.com/spartrekus/icewm-xp/master/keys -O         keys   " );

         nsystem( " cd ; cd .icewm ; fetch -R https://raw.githubusercontent.com/spartrekus/icewm-xp/master/keys   " );


         nsystem( " cd ; cd .icewm ; wget https://raw.githubusercontent.com/spartrekus/icewm-xp/master/menu -O         menu   " );




         nsystem( " cd ; cd .icewm ; fetch -R https://raw.githubusercontent.com/spartrekus/icewm-xp/master/menu        " );

         nsystem( " cd ; cd .icewm ; echo 'Theme=WindowsXP/default.theme'  >  theme " );

         nsystem( " cd ; echo  >       .xinitrc  " );

         nsystem( " cd ; echo  rox -p desktop   >>  .xinitrc  " );
         nsystem( " cd ; echo setxkbmap de >>  .xinitrc  " );
         nsystem( " cd ; echo        >>  .xinitrc  " );
         nsystem( " cd ; echo icewm        >>  .xinitrc  " );


         //chdir( getenv( "HOME" ));
         //if ( fexist( ".wallpaper.png" ) == 0 ) 
         //   nsystem( " cd ; wget \"https://raw.githubusercontent.com/spartrekus/Totally-Libre-Free-GNU-Matrix-Wallpaper-1920x1080/master/cmatrix-free-gnu-wallpaper-unix-1920x1080.png\" -O .wallpaper.png   " );
         return 0;
      }



    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "set" ) ==  0 ) 
      if ( ( strcmp( argv[2] , "locales" ) ==  0 ) 
      || ( strcmp( argv[2] , "locale" ) ==  0 ) 
      || ( strcmp( argv[2] , "utf8" ) ==  0 ) 
      || ( strcmp( argv[2] , "utf" ) ==  0 ) )
      if ( MYOS == 1 )
      {
          // select de de utf8 utf8, and then put C.UTF8
          nsystem( " apt-get install -f -y console-data locales" );
          nsystem( " dpkg-reconfigure locales " );
          nsystem( " echo LANG=C.UTF-8 > /etc/default/locale  " );
          nsystem( " locale " );
          return 0;
      }



    ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( ( strcmp( argv[1] , "nfont" ) ==  0 ) || ( strcmp( argv[1] , "vidfont" ) ==  0 ) 
     || ( strcmp( argv[1] , "nfont" ) ==  0 ) || ( strcmp( argv[1] , "font" ) ==  0 ) )
     {
       if ( MYOS == 1 )
         nsystem( " setfont  /usr/share/consolefonts/Lat15-TerminusBold32x16.psf.gz    " );
       else if ( MYOS == 4 )
         nsystem( " vidfont " );
       return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "links" ) ==  0 ) 
     {
        if ( MYOS == 1 ) 
           nsystem( "  wget --no-check-certificate https://raw.githubusercontent.com/spartrekus/links2-portable/master/links-2.14-portable.tar.gz " );
        else 
           nsystem( " fetch -R     https://raw.githubusercontent.com/spartrekus/links2-portable/master/links-2.14-portable.tar.gz " );
        return 0;
     }






     ////////////////////////////////////////////////////////
     ///split -b 900M var-cache-pkg.tar.gz 
     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "split" ) ==  0 ) 
     {
        nsystem( "    split -b 900M file.tar.gz   " );
        return 0;
     }



     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "big" ) ==  0 ) 
     {
       nsystem( " xterm -fn DejaVuMono -bg black -fg yellow  -fa 80 -fs 20 " );
       return 0;
     }


     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "ht" ) ==  0 ) 
     {
         printf( "ifconfig_wlan0=\"-ht WPA SYNCDHCP\"\n" );
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
     if ( argc == 2)
     if ( strcmp( argv[1] , "xterm" ) ==  0 ) 
     {
       nsystem( " export DISPLAY=:0 ; xterm -bg black -fg green -fa 33 " );
       return 0;
     }





   ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( ( strcmp( argv[1] ,   "sutil" ) ==  0 ) 
     || ( strcmp( argv[1] ,     "sutils" ) ==  0 ) )
     {
         npkg( " fusefs-sshfs  " );
         npkg( " alsa-utils " );
         npkg( " mpg123 " );
         return 0;
      }



    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( ( strcmp( argv[1] , "commit" ) ==  0 ) 
      || ( strcmp( argv[1] , "com" ) ==  0 ) 
      || ( strcmp( argv[1] , "--commit" ) ==  0 ) )
      {
            printf("- SVN - \n");
            nsystem( " svn commit -m v20  ;  svn add * --force  " );
            nsystem( " svn commit -m v20  ;  svn add * --force  " );
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



      ///////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if (  ( strcmp( argv[2] , "libreoffice" ) ==  0 ) 
         || ( strcmp( argv[2] , "lbo" ) ==  0 ) )
      {
          if ( MYOS == 1 )
          {
	    nsystem( " apt-get update ; apt-get install --no-install-recommends  -y libreoffice    " );
	    nsystem( "  apt-get install -y nedit  " );
	    nsystem( "  apt-get install -y gnumeric  " );
          }
          return 0;
      }



    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "beamer" ) ==  0 ) 
      {
          if ( MYOS == 4 ) 
          {
            // regular stuffs, very large on BSD
            printf( "  Pass Mupdf \n");
            printf( "  Pass1/2 \n");
            npkg( "  texlive-base  " );
            npkg( "  texlive-texmf texlive-tlmgr " );
            printf( "  Pass2/2 \n");
            npkg( "  tex-formats tex-basic-engines   ");
            printf( "  Completed. \n");
          }
          else
          {
	    nsystem( " apt-get update " );
	    nsystem( " apt-get install --no-install-recommends  -y texlive   " );
	    nsystem( " apt-get install -y --no-install-recommends  texlive texlive-latex-extra texlive-font-utils " );
          }
          return 0;
      }




     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "cr" ) ==  0 ) 
     {
       if ( MYOS == 1 ) 
         nsystem( " chromium-browser " );
       else
         nsystem( " chromium " );
       return 0;
     }


   ////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( ( strcmp( argv[1] , "install" ) ==  0 ) || ( strcmp( argv[1] , "ninstall" ) ==  0 ) )
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
     if ( argc == 2)
     if ( ( strcmp( argv[1] , "xwrapper" ) ==  0 ) 
       || ( strcmp( argv[1] , "wrapper" ) ==  0 ) )
     {
         nsystem( " dpkg-reconfigure xserver-xorg-legacy " );
         return 0;
     }


      ////////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "fbi" ) ==  0 ) 
      {
         npkg_update( );
         npkg( "  fbi " );
         return 0;
     }

      ////////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "kodi" ) ==  0 ) 
      {
         npkg_update( );
         npkg( "  kodi " );
         return 0;
     }

      ///////////////////////////////////////////////////////
      if  ( argc == 2)
      if (  strcmp( argv[1] , "compile" ) ==  0 ) 
      {
            system( " ./configure ; make  " );
            return 0;
      }
      ///////////////////////////////////////////////////////
      if  ( argc == 2)
      if (  ( strcmp( argv[1] , "scr" ) ==  0 ) ||  ( strcmp( argv[1] , "screen" ) ==  0 ) )
      {
            system( "  screen -x " );
            return 0;
      }



      ///////////////////////////////////////////////////////
      if ( argc == 3)
      if ( strcmp( argv[1] , "install" ) ==  0 ) 
      if ( strcmp( argv[2] , "gnumeric" ) ==  0 ) 
      {
	  nsystem( " apt-get update ; apt-get install --no-install-recommends  -y gnumeric    " );
          return 0;
      }

     printf( "EOF NCONFIG\n" );
     return 0;
     // antibug
}












