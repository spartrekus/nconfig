
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









// new
#include <time.h>




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
	char cmdi[PATH_MAX];
	char charo[PATH_MAX];
	int i; 




	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "freebsd" ) ==  0 ) 
		{
			printf(  "Timestamp: %d\n", (int)time(NULL));
			nsystem( " wget https://download.freebsd.org/ftp/snapshots/i386/i386/ISO-IMAGES/13.0/FreeBSD-13.0-CURRENT-i386-20181213-r342020-memstick.img.xz " );
			return 0;
		}
	////////////////////////////////////////////////////////
	if ( argc == 4)
		if ( strcmp( argv[1] , "fetch" ) ==  0 ) 
			if ( strcmp( argv[2] , "base" ) ==  0 ) 
				if ( strcmp( argv[3] , "11.2" ) ==  0 ) 
				{
					nsystem( " mkdir 11.2 " );
					chdir( "11.2" );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/11.2-RELEASE/MANIFEST " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/11.2-RELEASE/base-dbg.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/11.2-RELEASE/base.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/11.2-RELEASE/kernel-dbg.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/11.2-RELEASE/kernel.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/11.2-RELEASE/ports.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/11.2-RELEASE/src.txz " );
					return 0;
				}
	////////////////////////////////////////////////////////
	if ( argc == 4)
		if ( strcmp( argv[1] , "fetch" ) ==  0 ) 
			if ( strcmp( argv[2] , "base" ) ==  0 ) 
				if ( strcmp( argv[3] , "12.0" ) ==  0 ) 
				{
					nsystem( " mkdir 12.0 " );
					chdir( "12.0" );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/12.0-RELEASE/MANIFEST " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/12.0-RELEASE/base-dbg.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/12.0-RELEASE/base.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/12.0-RELEASE/kernel-dbg.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/12.0-RELEASE/kernel.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/12.0-RELEASE/ports.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/12.0-RELEASE/src.txz " );
					return 0;
				}
	////////////////////////////////////////////////////////
	if ( argc == 4)
		if ( strcmp( argv[1] , "fetch" ) ==  0 ) 
			if ( strcmp( argv[2] , "base" ) ==  0 ) 
				if ( strcmp( argv[3] , "13.0" ) ==  0 ) 
				{
					nsystem( " mkdir 13.0 " );
					chdir( "13.0" );
					//nsystem( " wget -r -l 5  http://ftp.freebsd.org/pub/FreeBSD/releases/i386/13.0-RELEASE/ " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/13.0-RELEASE/MANIFEST " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/13.0-RELEASE/base-dbg.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/13.0-RELEASE/base.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/13.0-RELEASE/kernel-dbg.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/13.0-RELEASE/kernel.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/13.0-RELEASE/ports.txz " );
					nsystem( " wget http://ftp.freebsd.org/pub/FreeBSD/releases/i386/13.0-RELEASE/src.txz " );
					return 0;
				}









	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( ( strcmp( argv[1] , "time" ) ==  0 ) 
				|| ( strcmp( argv[1] , "--time" ) ==  0 ) 
				|| ( strcmp( argv[1] , "--ntimestamp" ) ==  0 ) 
		   )
		{
			//printf("Timestamp: %d\n",(int)time(NULL));
			printf("%d\n", (int)time(NULL));
			return 0;
		}
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "timeh" ) ==  0 ) 
		{
			time_t clk = time(NULL);
			printf("%s", ctime( &clk ));
			return 0;
		}


	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "timec" ) ==  0 ) 
		{
			i = snprintf( cmdi, 50 , "%d",  (int)time(NULL) );
			printf("%s\n", cmdi );
			return 0;
		}


	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] ,   "size" ) ==  0 ) 
		{
			if ( fexist( argv[ 2 ] ) == 1 ) 
				fseek_filesize( argv[ 2 ] );
			return 0;
		}

	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( ( strcmp( argv[1] , "ld" ) ==  0 ) 
				|| ( strcmp( argv[1] ,   "nfind" ) ==  0 ) )
		{
			listdir( ".", 0 , argv[ 2 ] ) ;
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
		if ( strcmp( argv[1] ,   "VARUSER" ) ==  0 ) 
		{
			nsystem( " echo SYSTEM VAR $USER " );
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










	if ( MYOS == 1 )
		printf( "OS: Linux (Keep going OpenSource)\n" );
	else if ( MYOS == 2 )
		printf( "OS: Win (Could be much better choice, have a try in free Opensource for your freedom)\n" );
	else if ( MYOS == 3 )
		printf( "OS: Win (Could be much better choice, have a try in free Opensource for your freedom)\n" );
	else if ( MYOS == 4 )
		printf( "OS: BSD/OpenBSD/FreeBSD (Good choice)\n" );





	if ( argc == 2)
		if ( strcmp( argv[1] , "times" ) ==  0 ) 
		{
			time_t clk = time(NULL);
			printf("%s", ctime(&clk));
			return 0;
		}
	//long t;
	//struct tm *ltime;
	//time(&t);
	//ltime=localtime(&t);
	//char charo[50];  int fooi ; 
	//fooi = snprintf( charo, 50 , "%04d%02d%02d%02d%02d%02d", 1900 + ltime->tm_year, ltime->tm_mon +1 , ltime->tm_mday, ltime->tm_hour, ltime->tm_min, ltime->tm_sec );





	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "pciconf" ) ==  0 ) 
		{
			if      ( MYOS == 1 ) nsystem( " lspci " );
			else if ( MYOS == 4 ) nsystem( " pciconfig -lv  " );
			return 0;
		}

	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "geom" ) ==  0 ) 
		{
			if      ( MYOS == 1 ) nsystem( " /sbin/blkid " );
			//else if ( MYOS == 4 ) nsystem( " gpart list | grep name " );
			else if ( MYOS == 4 ) nsystem( " gpart list | grep da " );
			return 0;
		}
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "gpart" ) ==  0 ) 
		{
			if ( MYOS == 1 )      nsystem( " /sbin/fdisk -l  | less " );
			else if ( MYOS == 4 ) nsystem( " gpart list      | less " );
			return 0;
		}
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "ip" ) ==  0 ) 
		{
			if ( MYOS == 1 ) 
			{
				nsystem( " ip addr " );
				nsystem( " ifconfig " );
			}
			else if ( MYOS == 4 ) nsystem( " ifconfig " );
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
	if ( argc == 3)
		if ( strcmp( argv[1] , "fexist" ) ==  0 ) 
		{
			printf( "CMD: fexist %d\n", fexist( argv[ 2 ] ) );
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
				printf( "\n" );

				if ( MYOS == 1 ) nsystem( " apt-get update " );
				npkg( " tcc  " );
				npkg( " links  " );
				npkg( " ssh  " );

				if      ( MYOS == 1 ) npkg( " ncurses-dev xinit xterm " );
				else if ( MYOS == 4 ) npkg( " ncurses Xorg " );

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
				npkg( " links " );      // links -g for graphics

				npkg( " dillo " );   
				npkg( " links " );      // very useful
				npkg( " ssh " );   

				npkg( " icewm " );   // stable, 17 Mb, larger but comfort. 
				//npkg( " xfe " );     // for icons and likely it may work., with xfw and xfi. 
				npkg( " links ");
				npkg( " links2 ");
				npkg( " unzip " );


				if ( MYOS == 4 )
				{
					npkg(  " ntp " ); 
					npkg(  " xlockmore " );  // xlock daisy, cool no?
					npkg(  " nedit " );      // stable and good
					npkg(  " unzip " );      // still unseful today
					npkg(  " alsa-utils " ); // might help to avoid pulseaudio, locking users like other Operating Systems.
					npkg(  " fusefs-sshfs "); // great to mount a drive over the seas with X11 forward and usage. ;)
					npkg(  " fusefs-ext2 ");  // for ext2, and likely ext3.
				}
				////////////////////////////////////////////////////////


				if ( MYOS == 1 )
				{
					nsystem( " apt-get install  -y  console-setup " ); // very first, the keyboard
					npkg(  "  ssh ");
					npkg(  "  sshfs ");
					nsystem( " apt-get install  -y links " );
					nsystem( " apt-get install  -y ssh " );
					nsystem( " apt-get install  -y xz-utils " );  //why?

					nsystem( " apt-get install  -y xinit xterm " );
					nsystem( " apt-get install  -y xbindkeys  " );

					nsystem( " apt-get install  -y x11-xserver-utils   " ); //xrdb might help for sddm

					nsystem( " apt-get install  -y wmctrl   " );   
					nsystem( " apt-get install  -y xdotool   " ); 
					nsystem( " apt-get install  -y alsa-utils   " );
					////////////////////////////////////////////////////////
					nsystem( " apt-get install  -y tcc  " ); //always there, on some systems
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
					//nsystem( " apt-get install  -y fbpanel  " );

					nsystem( " apt-get install  -y links " );
					nsystem( " apt-get install  -y ssh " );
					nsystem( " apt-get install  -y xinit xterm " );

					////////////////////////////////////////////////////////
					//if ( strcmp( argv[2] , "desk+" ) ==  0 ) 
					nsystem( " apt-get install  -y nedit  " ); //it works
					nsystem( " apt-get install  -y fbpanel  " );
					nsystem( " apt-get install  -y xpaint  " );
					nsystem( " apt-get install  -y less  " ); 

				}

				////////////////////////////////////////////////////////
				return 0;
			}















	if ( argc == 3)
		if ( strcmp( argv[1] , "watch" ) ==  0 ) 
			if ( strcmp( argv[2] , "df" ) ==  0 ) 
			{
				printf( "> watch df.\n" );
				while ( 1 ) 
				{ 
					printf( "===============\n");
					printf(" Timestamp: %d\n",(int)time(NULL));
					time_t clk = time(NULL);
					printf(" %s", ctime( &clk ));
					printf( "===============\n");
					nsystem( " df -h " ); 
					usleep( 5 * 1000000 ); 
				}
				return 0;
			}





	if ( argc == 3)
		if ( strcmp( argv[1] , "watch" ) ==  0 ) 
			if ( strcmp( argv[2] , "ls" ) ==  0 ) 
			{
				printf( "> watch ls.\n" );
				while ( 1 ) 
				{ 
					printf( "===============\n");
					printf(" Timestamp: %d\n",(int)time(NULL));
					time_t clk = time(NULL);
					printf(" %s", ctime( &clk ));
					printf( "===============\n");
					printdir(); 
					usleep( 5 * 1000000 ); 
				}
				return 0;
			}

	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "ls" ) ==  0 ) 
		{
			nls();
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




	if ( argc == 3)
		if ( strcmp( argv[1] , "watch" ) ==  0 ) 
			if ( ( strcmp( argv[2] , "sd" ) ==  0 ) 
					|| ( strcmp( argv[2] ,   "da" ) ==  0 ) )
			{
				printf( "> watch ls.\n" );
				while ( 1 ) 
				{ 
					printf( "===============\n");
					printf(" Timestamp: %d\n",(int)time(NULL));
					time_t clk = time(NULL);
					printf(" %s", ctime( &clk ));
					printf( "===============\n");

					if ( MYOS == 1 ) 
						nsystem( "  ls -ltra /dev/sd* " );
					else if ( MYOS == 1 ) 
						nsystem( "  ls -ltra /dev/da* " );

					usleep( 5 * 1000000 ); 
				}
				return 0;
			}










	if ( argc == 2)
		if ( strcmp( argv[1] , "eject" ) ==  0 ) 
		{
			printf( "> Eject cdrom.\n" );
			if      ( MYOS == 1 ) 
				nsystem( " eject " );
			else if ( MYOS == 4 ) 
				nsystem( " eject cd0 " );
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
	if ( argc == 2)
		if ( strcmp( argv[1] , "pkg-update" ) ==  0 ) 
		{
			printf( " pkg clean ; pkg bootstrap -f ; pkg update -f \n" );
			return 0;
		}






	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "us" ) ==  0 )  // BSD
		{
			printf( "> Set keyboard layout.\n" );
			nsystem( " kbdcontrol -l /usr/share/syscons/keymaps/us.iso.kbd " );
			nsystem( " setxkbmap us " );
			return 0;
		}
	///////////////////////////////////////////////////////
	// BSD Rocks
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "de" ) ==  0 )  // BSD
		{
			printf( "> Set keyboard layout.\n" );
			nsystem( " kbdcontrol -l /usr/share/syscons/keymaps/german.iso.kbd " );
			nsystem( " setxkbmap de " );
			return 0;
		}
	///////////////////////////////////////////////////////
	// BSD Rocks
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "fr" ) ==  0 )  // BSD
		{
			printf( "> Set keyboard layout.\n" );
			nsystem( " kbdcontrol -l /usr/share/syscons/keymaps/fr.iso.kbd " );
			nsystem( " setxkbmap fr " );
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
				if ( MYOS == 1 ) npkg( "  ninvaders " );
				return 0;
			}





	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
			if ( strcmp( argv[2] ,   "dos" ) ==  0 ) 
			{
				if ( MYOS == 1 ) nsystem( " apt-get update " );
				npkg( " dosfstools  " );
				return 0;
			}














	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "tiger" ) ==  0 ) 
		{
			//nsystem( "  /usr/bin/Xtigervnc :1 -desktop :1 -depth 32 -SecurityTypes None -AlwaysShared -geometry 1680x1050   "   );
			nsystem( "  /usr/bin/Xtigervnc :1 -desktop :1 -depth 32 -SecurityTypes None -AlwaysShared -geometry 1280x720   "   );
			// ok, but you need too on vnc server:
			// xtightvncviewer :1
			// export DISPLAY=:1 
			// icewm 
			return 0;
		}
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "vnc" ) ==  0 ) 
		{
			nsystem( " x2vnc 192.168.52.14:1 ");
			return 0;
		}




	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
			if ( strcmp( argv[2] ,   "wincmd" ) ==  0 ) 
			{
				// retro
				if ( MYOS == 1 ) nsystem( " apt-get update " );
				npkg( " doublecmd-qt  " );
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
			if ( ( strcmp( argv[2] ,    "prboom" ) ==  0 ) 
					|| ( strcmp( argv[2] ,   "boom" ) ==  0 ) )
			{
				if ( MYOS == 1 ) nsystem( " apt-get update " );
				npkg( " prboom-plus   " );
				return 0;
			}
	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
			if ( strcmp( argv[2] ,    "boom-server" ) ==  0 ) 
			{
				if ( MYOS == 1 ) nsystem( " apt-get update " );
				npkg( " prboom-plus-game-server  " );
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
					nsystem( " apt-get update " );

				npkg( "  tcc  " );

				if ( MYOS == 1 ) 
				{
					nsystem( "  apt-get install -y subversion tcc make ncurses-dev  " );
					npkg( "  tcc  " );
					npkg( "  make  " );
					npkg( "  ncurses-dev  " );
				}


				else if ( MYOS == 4 ) 
				{
					npkg( " subversion  " );
					npkg( " make " );
					npkg( " ncurses " );
				}

				npkg( "  gcc  " );

				npkg( " vim " );  // or emacs, up to you.

				npkg( " gcc  " );
				npkg( " subversion  " );
				npkg( " make  " );
				npkg( " ncurses-dev  " );
				npkg( " tcc  " );

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
			if ( strcmp( argv[2] ,   "icewm" ) ==  0 ) 
			{
				if      ( MYOS == 1 ) npkg( " ncurses-dev icewm xinit xterm " );
				else if ( MYOS == 4 ) npkg( " ncurses Xorg feh vim icewm menu " );
				npkg( " unzip " );
				return 0; 
			}








	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "install" ) ==  0 ) 
			if ( strcmp( argv[2] , "all" ) ==  0 ) 
			{
				if ( MYOS == 1 ) nsystem( " apt-get update  " );
				npkg( " ssh   " );
				npkg( " links " );
				npkg( "  wget  " );
				npkg( "  less  " );
				npkg( "  vim  " );
				npkg( "  links  " );
				npkg( "  screen  " );
				npkg( " subversion gcc " );
				nsystem( "  nconfig install apps ");
				nsystem( "  nconfig install xapps ");
				npkg( "  alsa-utils " );
				if ( MYOS == 1 ) 
					nsystem( " apt-get install  -y xinit xterm " );
				return 0;
			}


	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] ,    "install" ) ==  0 ) 
			if ( ( strcmp( argv[2] ,  "apps" ) ==  0 ) 
					|| ( strcmp( argv[2] , "app" ) ==  0 ) )
			{
				npkg( "  tcc  " );
				npkg( "  subversion  " );
				npkg( "  wget  " );
				npkg( "  gcc  " );
				npkg( "  less  " );
				npkg( "  unzip  " );
				npkg( "  zip  " );
				npkg( "  vim  " );
				npkg( "  subversion  " );
				npkg( "  make  " );
				npkg( "  ncurses  " );
				npkg( "  ncurses-dev " );
				npkg( "  links  " );
				npkg( "  screen  " );
				npkg( "  wget  " );
				npkg( "  less  " );
				npkg( "  xz-utils  " );
				npkg( "  ncurses-dev " );
				npkg( "  fusefs-ext2  " );
				npkg( "  fusefs-ext2  " );
				npkg( "  fusefs-sshfs  " );
				npkg( "  e2fsprogs  " );
				return 0;
			}




	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "install" ) ==  0 ) 
			if ( ( strcmp( argv[2] , "xapps" ) ==  0 ) 
					|| ( strcmp( argv[2] , "xapp" ) ==  0 ) )
			{
				//nsystem( " apt-get update ; apt-get install -y x11vnc nedit tcc links xclip feh rox-filer scrot nedit  xbindkeys xterm rxvt  " );
				npkg( "  xdotool  " );
				npkg( "  wmctrl  " );
				npkg( "  xterm  " );
				npkg( "  vim  " );
				npkg( "  xinit  " );
				npkg( "  xdotool  " );
				npkg( "  wmctrl  " );
				npkg( "  feh  " );
				npkg( "  links  " );
				npkg( "  ncurses  " );
				npkg( "  xclip  " );
				if ( MYOS == 4 ) 
					npkg( "  xlockmore  " );
				else 
					npkg( "  i3lock  " );
				npkg( "  links  " );
				npkg( "  scrot  " );
				npkg( " links ");
				npkg( " links2 ");
				npkg( "  xpaint  " );
				npkg( "  nedit  " );
				npkg( "  rox-filer  " );
				return 0;
			}




	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
			if ( strcmp( argv[2] ,   "ssh" ) ==  0 ) 
			{
				npkg( " ssh " );
				npkg( " sshfs " );
				return 0;
			}






	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
			if ( strcmp( argv[2] ,   "x11" ) ==  0 ) 
			{
				nsystem( " apt-get update ; apt-get install  -y xinit xterm icewm " );
				////nsystem( " apt-get install  -y libx11-dev ");
				//nsystem( " apt-get install  -y xbindkeys wmctrl xdotool " );
				nsystem( " apt-get install  -y icewm " );
				nsystem( " apt-get install  -y unzip " ); //for the x11 icons
				npkg( " icewm ");
				npkg( " xterm ");
				npkg( " xinit ");
				npkg( " xserver-xorg " );
				//nsystem( " apt-get install  -y x11-xserver-utils xserver-xorg-legacy  " ); 
				return 0;
			}




	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
			if ( ( strcmp( argv[2] ,   "xutils" ) ==  0 ) 
					|| ( strcmp( argv[2] ,   "xutil" ) ==  0 ) )
			{
				if ( MYOS == 1 )
				{
					nsystem( " apt-get update ; apt-get install  -y xinit xterm icewm " );
					////nsystem( " apt-get install  -y libx11-dev ");
					//nsystem( " apt-get install  -y xbindkeys wmctrl xdotool " );
					nsystem( " apt-get install  -y icewm " );
					nsystem( " apt-get install  -y unzip " ); //for the x11 icons
					npkg( " xserver-xorg " );
				}
				else if ( MYOS == 4 )
				{
					npkg( " Xorg ");
				}

				npkg( " icewm ");
				npkg( " xterm ");
				npkg( " xinit ");
				npkg( " xclip ");
				npkg( " xclock ");
				npkg( " xlockmore ");
				npkg( " i3lock ");
				npkg( " icewm ");
				npkg( " wmctrl ");
				npkg( " xdotool ");
				npkg( " links ");
				npkg( " links2 ");
				npkg( " xserver-xorg " );
				npkg( " xterm ");
				//nsystem( " apt-get install  -y x11-xserver-utils xserver-xorg-legacy  " ); 
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

			if ( fexist( "/usr/bin/unzip" ) == 1 ) 
				nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/icons.zip  -O kwin95icons.zip  ; unzip -o kwin95icons.zip  ; rm kwin95icons.zip " );
			nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/xkey.ini   -O .xbindkeysrc  " );
			nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/xinitrc.txt -O .xinitrc  " );


			return 0;
		}




	if ( argc == 2)
		if ( strcmp( argv[1] , "freebsd" ) ==  0 ) 
		{
			nsystem( " wget https://download.freebsd.org/ftp/releases/i386/i386/ISO-IMAGES/12.0/FreeBSD-12.0-RELEASE-i386-disc1.iso.xz " );
			return 0;
		}



	///////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "install" ) ==  0 ) 
			if ( strcmp( argv[2] , "sshfs" ) ==  0 ) 
			{
				npkg(  " fusefs-sshfs "); // great to mount a drive over the seas with X11 forward and usage. ;)
				npkg(  " fusefs-ext2 ");  // for ext2, and likely ext3.
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





	if ( argc == 3)
		if ( strcmp( argv[1] , "install" ) ==  0 ) 
			if ( strcmp( argv[2] , "xfce" ) ==  0 ) 
			{
				npkg( " xfce4 " );
				npkg( " xfwm4 " );
				npkg( " thunar " );
				npkg( " wicd " );
				npkg( " xfe " );
				return 0;
			}





	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	// xterm has bugs
	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "install" ) ==  0 ) 
			if ( ( strcmp( argv[2] , "kde" ) ==  0 ) 
					|| ( strcmp( argv[2] , "kde-standard" ) ==  0 ) )
			{
				nsystem( " apt-get update  " );
				////nsystem( " dpkg-reconfigure keyboard-configuration " );
				npkg( " ssh " );
				npkg( " links " );
				npkg( " ncurses-dev " );
				npkg( " wget " );
				npkg( " less " );

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
			if ( ( strcmp( argv[2] , "gcc" ) ==  0 ) || ( strcmp( argv[2] , "gcc" ) ==  0 ) )
			{
				//nsystem( " apt-get update ; apt-get install -y subversion gcc make ncurses-dev  " );
				npkg( " gcc  " );
				npkg( " subversion  " );
				npkg( " make  " );
				npkg( " ncurses-dev  " );
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
		if ( strcmp( argv[1] , "wlan0" ) ==  0 )   
		{
			if ( MYOS == 1 )
				nsystem( " pkill wpa_supplicant ; ifdown --force wlan0 ; sleep 1 ; ifup wlan0 ; dhclient -v wlan0 " );
			else if ( MYOS == 4 )
				nsystem( " pkill wpa_supplicant ; kldload rtwn0 ; kldstat ; ifconfig wlan0 create wlandev rtwn0 ; ifconfig wlan0 up scan ;  wpa_supplicant -B -i wlan0 -c /etc/mywifi.conf ; dhclient wlan0 ; ifconfig   " );
			return 0;
		}

	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "wlan1" ) ==  0 )   
		{
			if ( MYOS == 1 )
				nsystem( "  ifdown --force wlan1 ; sleep 1 ; ifup wlan1 ; dhclient -v wlan1 " );
			else if ( MYOS == 4 )
				nsystem( "  kldload rtwn0 ;  kldstat ; ifconfig wlan1 create wlandev rtwn0 ; ifconfig wlan1 up scan ;  wpa_supplicant -B -i wlan1 -c /etc/mywifi.conf ; dhclient wlan1 ; ifconfig   " );
			return 0;
		}







	/// just burn a dvd
	if ( argc == 3)
		if ( strcmp( argv[1] , "--burn" ) ==  0 ) 
			if ( strcmp( argv[2] , "" ) !=  0 ) 
			{
				// growisofs -dvd-compat -Z /dev/sr0=/home/user_name/Downloads/LinuxMint.iso
				printf("Burn of file ISO (Linux): %s\n", argv[ 2 ] );
				npkg( " growisofs " );
				strncpy( cmdi, "", PATH_MAX );
				strncat( cmdi , "  growisofs -dvd-compat -Z /dev/sr0=" , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , argv[2] , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , "\" " , PATH_MAX - strlen( cmdi ) -1 );
				printf( "<CMD: %s>\n", cmdi );
				nsystem( cmdi );
				return 0;
			}






	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "chromium" ) ==  0 ) 
		{
			if      ( MYOS == 1 ) 
			{
				if ( fexist( "/etc/rpi" ) == 1 ) 
					nsystem( " chromium-browser google.com " ); 
				else 
					nsystem( " chromium google.com " ); 
			}
			else if ( MYOS == 4 ) 
				nsystem( " chrome google.com " ); 
			return 0;
		}




	////////////////////////////////////////////////////////
	if  ( argc == 2)
		if ( strcmp( argv[1] , "dpms" ) ==  0 )
		{
			nsystem( " export DISPLAY=:0 ; xset s off ;  xset -dpms ;  xset s noblank  ; setterm -blank 0  " );
			return 0;
		}

	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "xip" ) ==  0 ) 
		{
			nsystem( " cd ; nconfig ip > ip.log  ;  xmessage -file ip.log  " );
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
		if ( strcmp( argv[1] , "msx2" ) ==  0 ) 
		{
			nsystem( "xterm -bg black -fg green  -fn DejaVuMono -fa 50 -fs 12 -e bash " );
			return 0;
		}


	//////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "big" ) ==  0 ) 
		{
			nsystem( "  xterm -bg black -fg green  -fn DejaVuMono -fa 50 -fs 35 " );
			return 0;
		}

	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "reboot" ) ==  0 ) 
		{
			nsystem( " reboot " ); 
			return 0;
		}


	///////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "big" ) ==  0 ) 
		{
			strncpy( cmdi , "  xterm -bg black -fg green  -fn DejaVuMono -fa 50 -fs  ",  PATH_MAX );
			strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
			strncat( cmdi , argv[ 2 ] , PATH_MAX - strlen( cmdi ) -1 );
			strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
			nsystem(  cmdi  ); 
			return 0;
		}



	////////////////////////////////////////////////////////
	if ( argc == 4 )
		if ( strcmp( argv[1] ,   "install" ) ==  0 ) 
			if ( strcmp( argv[2] ,   "devuan" ) ==  0 ) 
			{
				strncpy( cmdi , "   date ; mount ; umount /target ;  umount /target ; fdisk -l ;  ls /target ;  mount ; echo mkfs ;  mkfs.ext3  -F  ",  PATH_MAX );
				strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , argv[ 3 ] , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , "  ; mount  " , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , argv[ 3 ] , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , " /target ;  " , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , "   bash /root/debootstrap-devuan.sh  ; umount /target   ; umount  /target  ; date ; sleep 3  ; echo mission completed " , PATH_MAX - strlen( cmdi ) -1 );
				nsystem(  cmdi  ); 
				//nsystem( "   date ; mount ;  umount /target ; fdisk -l ;  ls /target ;  mount ; echo mkfs ;  mkfs.ext3 /dev/sda2  ; mount /dev/sda2 /target/ ;   bash /root/debootstrap-devuan.sh     ; umount  /target  ; date  " );
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
	if ( argc == 2)
		if ( strcmp( argv[1] , "sound" ) ==  0 ) 
		{
			nsystem( " aplay  /usr/share/sounds/alsa/Rear_Center.wav  " );
			return 0;
		}

	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "mylene" ) ==  0 ) 
		{
			printf(  "> Testing Application (mplayer, http connection for audio, and audio) \n" );
			nsystem( " mplayer http://listen.radionomy.com/mylenefarmerwebradio " );  //stable for testing sound 
			nsystem( " mpg123 http://listen.radionomy.com/mylenefarmerwebradio " );  //stable for testing sound 
			return 0;
		}
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "bigbunny" ) ==  0 ) 
		{
			printf(  "> Testing Application (mplayer, http connection for video, and video) \n" );
			nsystem( " mplayer -loop 0 http://ia800201.us.archive.org/12/items/BigBuckBunny_328/BigBuckBunny.ogv" );
			return 0;
		}



	////////////////////////////////////////////////////////
	if ( argc == 3)
		if (( strcmp( argv[1] , "fetch" ) ==  0 ) || ( strcmp( argv[1] , "play" ) ==  0 ))
			if ( strcmp( argv[2] , "hal" ) ==  0 )
			{
				printf(  "> Testing Application (mplayer, http connection for video, and video) \n" );
				printf(  "> Why HP 9000, do you think? \n" );
				if ( strcmp( argv[1] , "fetch" ) ==  0 ) 
					nsystem( " wget https://ia800402.us.archive.org/22/items/video_20160419/video.mp4 ");
				else
					nsystem( "   mplayer  -af volume=30.1:0  -fs -zoom -loop 0 https://ia800402.us.archive.org/22/items/video_20160419/video.mp4 ");
				return 0;
			}





	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "--mp-3" ) ==  0 ) 
		{
			ncmdwith( "    mplayer  -af volume=30.1:0  -fs -zoom -loop 0  " ,  argv[ 2 ] );
			return 0;
		}
	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "--mp" ) ==  0 ) 
		{
			ncmdwith( "    mplayer  -fs -zoom -loop 0  " ,  argv[ 2 ] );
			return 0;
		}



	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "install" ) ==  0 ) 
			if ( strcmp( argv[2] , "hal" ) ==  0 ) 
			{
				npkg( " mplayer vim links alsa-utils mpg123 screen " );
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
			if ( MYOS == 1 )   nsystem( " apt-get update  " );
			npkg( " mencoder  " );
			npkg( " alsa-utils  " );

			if ( fexist( "/usr/bin/mencoder" ) != 1 ) 
				nsystem( "apt-get update ; apt-get install -y alsa-utils  "); 

			i = snprintf( charo , 50 , "%d",  (int)time(NULL) );
			strncpy( cmdi , "  arecord -V stereo -t wav -f cd -D plughw:0,0    " , PATH_MAX );
			strncat( cmdi , charo , PATH_MAX - strlen( cmdi ) -1 );
			strncat( cmdi , "-arec.wav" , PATH_MAX - strlen( cmdi ) -1 );
			strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
			printf( ">cmdi: %s\n", cmdi );

			nsystem( cmdi );
			return 0;
		}




	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "vrec" ) ==  0 ) 
		{
			if ( fexist( "/usr/bin/mencoder" ) != 1 ) 
				nsystem( "apt-get update ; apt-get install -y mencoder  "); 
			nsystem( " mencoder tv:// -tv driver=v4l2:device=/dev/video0 -ovc lavc -nosound -o $( nconfig --ntimestamp )-video.avi  ");
			return 0;
		}






	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "x48" ) ==  0 ) 
		{
			if ( MYOS == 1 ) 
				nsystem( " xlsfonts ; x48 -connFont -misc-fixed-medium-r-semicondensed--0-0-75-75-c-0-iso8859-1     -smallFont -misc-fixed-medium-r-semicondensed--0-0-75-75-c-0-iso8859-1   -mediumFont -misc-fixed-medium-r-semicondensed--13-100-100-100-c-60-iso8859-1  -largeFont -misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-1     " );
			else 
				nsystem( " x48 " );
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



	/////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "install" ) ==  0 ) 
			if ( strcmp( argv[2] , "qemu" ) ==  0 ) 
			{
				npkg( " qemu-system-i386  " );
				return 0;
			}


	///////////////////////////////////////////////////////
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
			if ( ( strcmp( argv[2] , "squashfs" ) ==  0 ) 
					|| ( strcmp( argv[2] , "sqfs" ) ==  0 )
					|| ( strcmp( argv[2] , "squash" ) ==  0 ) )
			{
				nsystem( " apt-get update ; apt-get install -y squashfs-tools " );
				return 0;
			}








	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "nexplorer" ) ==  0 ) 
		{
			if ( MYOS == 1 ) 
				npkg( "ncurses-dev" );
			else if ( MYOS == 4 ) 
				npkg( "ncurses" );

			if ( fexist( "/usr/bin/tcc" ) == 1 ) 
				nsystem( " wget https://raw.githubusercontent.com/spartrekus/nexplorer/master/nexplorer.c -O nexplorer.c ; tcc -lncurses nexplorer.c -o nexplorer ; chmod  +x  nexplorer ; ls nexplorer  -ltra " );

			else if ( fexist( "/usr/bin/gcc" ) == 1 ) 
				nsystem( " wget https://raw.githubusercontent.com/spartrekus/nexplorer/master/nexplorer.c -O nexplorer.c ; gcc -lncurses nexplorer.c -o nexplorer ; chmod  +x  nexplorer ; ls nexplorer  -ltra " );

			else 
				nsystem( " wget https://raw.githubusercontent.com/spartrekus/nexplorer/master/nexplorer.c -O nexplorer.c " );

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
			if ( strcmp( argv[2] , "xfce-terminal" ) ==  0 ) 
			{
				npkg( " xfce4-terminal " );
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


	////////////////////////////////////////////////////////
	// useful sometimes
	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "max" ) ==  0 ) 
		{
			nsystem( "  wmctrl -r :ACTIVE: -b toggle,maximized_vert,maximized_horz   " );
			return 0;
		}
	if ( argc == 3)
		if ( strcmp( argv[1] , "key" ) ==  0 ) 
			if ( strcmp( argv[2] , "right" ) ==  0 ) 
			{
				nsystem( " xdotool key Right " );
				return 0;
			}
	if ( argc == 3)
		if ( strcmp( argv[1] , "key" ) ==  0 ) 
			if ( strcmp( argv[2] , "left" ) ==  0 ) 
			{
				nsystem( " xdotool key Left " );
				return 0;
			}




	////////////////////////////////////////////////////////
	// mnount ufs : mount -r -t ufs -o ufstype=ufs2   /dev/sdb1 /home/<your_username>/ufs_mount
	////////////////////////////////////////////////////////
	if ( argc == 4)
		if ( strcmp( argv[1] , "mount" ) ==  0 ) 
			if ( strcmp( argv[2] , "ufs" ) ==  0 ) 
			{
				strncpy( cmdi , " mkdir /media/ufs_mount ; mount -r -t ufs -o  ufstype=ufs2  " , PATH_MAX );
				strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , argv[3] , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
				strncat( cmdi , " /media/ufs_mount  " , PATH_MAX - strlen( cmdi ) -1 );
				nsystem( cmdi );
				return 0;
			}



	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "xp" ) ==  0 ) 
		{
			nsystem( " cd ; mkdir .icewm " );
			nsystem( " cd ; mkdir .icewm/themes " );
			nsystem( " cd ; cd .icewm ; cd themes ; wget https://raw.githubusercontent.com/spartrekus/icewm-xp/master/WindowsXP.zip -O winxp.zip ; unzip -o winxp.zip  " );

			nsystem( " cd ; cd .icewm ; wget https://raw.githubusercontent.com/spartrekus/icewm-xp/master/keys -O         keys   " );
			nsystem( " cd ; cd .icewm ; wget https://raw.githubusercontent.com/spartrekus/icewm-xp/master/menu -O         menu   " );

			nsystem( " cd ; cd .icewm ; echo 'Theme=WindowsXP/default.theme'  >  theme " );

			nsystem( " cd ; echo  >       .xinitrc  " );
			nsystem( " cd ; echo  rox -p desktop   >>  .xinitrc  " );
			nsystem( " cd ; echo setxkbmap de >>  .xinitrc  " );
			nsystem( " cd ; echo        >>  .xinitrc  " );
			nsystem( " cd ; echo icewm        >>  .xinitrc  " );

			chdir( getenv( "HOME" ));
			if ( fexist( ".icons" ) == 0 ) 
				if ( fexist( ".icons" ) != 2 ) 
					if ( fexist( "/usr/bin/unzip" ) == 1 ) 
						nsystem( " cd ; wget https://raw.githubusercontent.com/spartrekus/kwin95/master/icons.zip  -O kwin95icons.zip  ; unzip -o kwin95icons.zip  ; rm kwin95icons.zip " );

			/// wallpaper for i3lock
			chdir( getenv( "HOME" ));
			if ( fexist( ".wallpaper.png" ) == 0 ) 
				nsystem( " cd ; wget \"https://raw.githubusercontent.com/spartrekus/Totally-Libre-Free-GNU-Matrix-Wallpaper-1920x1080/master/cmatrix-free-gnu-wallpaper-unix-1920x1080.png\" -O .wallpaper.png   " );

			return 0;
		}


	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] , "fswebcam" ) == 0)
		{
			npkg( " fswebcam " );
			nsystem( "  cd $USER/webserver/var/www/html/webcam/  ;  while : ; do  fswebcam  fswebcam.png ;     cp fswebcam.png    auto.jpg  ;  sleep 4 ;   done " );
			return 0;
		}



	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "xterm" ) ==  0 ) 
			if ( strcmp( argv[2] , "yellow" ) ==  0 ) 
			{
				nsystem( " echo yellow xterm  ; xterm  -bg black -fg yellow   -e  bash " );
				return 0;
			}
	////////////////////////////////////////////////////////
	if ( argc == 3)
		if ( strcmp( argv[1] , "xterm" ) ==  0 ) 
			if ( strcmp( argv[2] , "green" ) ==  0 ) 
			{
				nsystem( " echo green xterm  ; xterm  -bg black -fg green   -e  bash " );
				return 0;
			}









	////////////////////////////////////////////
	if ( argc == 4)
		if ( strcmp( argv[1] , "gpart" ) ==  0 ) 
			if ( strcmp( argv[2] , "destroy" ) ==  0 ) 
				if ( strcmp( argv[3] , "disk" ) ==  0 ) 
					if ( MYOS == 4 )
					{
						nsystem( " dd if=/dev/zero of=/dev/da0 bs=2m  count=1 " );
						return 0;
					}
	////////////////////////////////////////////
	if ( argc == 4)
		if ( strcmp( argv[1] , "gpart" ) ==  0 ) 
			if ( strcmp( argv[2] , "create" ) ==  0 ) 
				if ( strcmp( argv[3] , "fat32" ) ==  0 ) 
					if ( MYOS == 4 )
					{
						nsystem( " dd if=/dev/zero of=/dev/da0 bs=2m  count=1 " );
						nsystem( " gpart create -s mbr da0 " );
						nsystem( " gpart add -t fat32  da0 " );
						nsystem( " newfs_msdos -F32 /dev/da0s1 " );
						return 0;
					}
	////////////////////////////////////////////
	// mounting on freebsd
	// mount ... <- direct for ufs2
	// -t msdosfs 
	// -t ext2fs 
	////////////////////////////////////////////
	if ( argc == 4)
		if ( strcmp( argv[1] , "gpart" ) ==  0 ) 
			if ( strcmp( argv[2] , "create" ) ==  0 ) 
				if ( strcmp( argv[3] , "ufs" ) ==  0 ) 
					if ( MYOS == 4 )
					{
						nsystem( " dd if=/dev/zero of=/dev/da0 bs=2m  count=1 " );
						nsystem( " gpart create -s mbr da0 " );
						nsystem( " gpart add -t freebsd  da0 " );
						nsystem( " gpart set -a active -i 1 da0 " );
						nsystem( " gpart create -s bsd da0s1 " );
						nsystem( " gpart show -p  da0 " );
						nsystem( " newfs /dev/da0s1 " );
						nsystem( " gpart show -p  da0 " );
						//install bootloader, da0s1a, da0s1b
						//nsystem( " gpart bootcode -b /boot/boot da0s1 ");
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
			strncat( cmdi , " /media/pendrive  " , PATH_MAX - strlen( cmdi ) -1 );
			nsystem( cmdi );
			nsystem( " bash " );
			nsystem( " umount /media/pendrive ; mount " );
			nsystem( " ls /media/pendrive " );
			return 0;
		}









	////////////////////////////////////////////////////////
	if ( argc == 2)
		if ( strcmp( argv[1] ,   "xlock" ) ==  0 ) 
		{
			nsystem( " xlock -mode random +inwindow -duration 3  ");
			return 0;
		}



	return 0; 
} 




// ext2fs    mount -t ext2fs /dev/da0s1 /media/disk1


/*
   go-mtpfs - Mount MTP devices over FUSE
   golang-github-hanwen-usb-dev - CGO bindings for libusb.
   jmtpfs - FUSE based filesystem for accessing MTP devices
   mtpfs - FUSE filesystem for Media Transfer Protocol devices
 */

// mnount ufs : mount -r -t ufs -o ufstype=ufs2 /dev/sdb1 /home/<your_username>/ufs_mount

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

