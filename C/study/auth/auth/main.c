/*--------------------------------------------------------------
 * file name:main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sqlauth.h"





int main(int argc,char *argv[])
{
	int ret=0;
	char function;
	int loop=1;
	char userbuff[50];
	char passbuff[50];
	char bufftmp[50];

	if(lib_mysql_connect("127.0.0.1",3306,"root","","test")	!= 0)
	{
		
		printf("Connect to server failed..\n");
		return -1;
	}
	
	while(loop)
	{
				
		//Clear buff
		memset(userbuff,0,50);
		memset(passbuff,0,50);

		printf("-------------------------------------------------------------------\n");
		printf("-------------------------------------------------------------------\n");
		printf("---Please select function.--\n");
		printf("i:Insert user..\n");
		printf("s:Search user..\n");
		printf("d:Delete user..\n");
		printf("a:Show all user..\n");
		printf("q:Quit..\n");
		printf("-------------------------------------------------------------------\n");
		printf("-------------------------------------------------------------------\n");
		
		function = getchar();
		fgets(bufftmp,50,stdin);
		switch(function)
		{	
			case 'i':
				printf("Please input user:");
				scanf("%s",userbuff);
				printf("Please input password:");
				scanf("%s",passbuff);
				lib_mysql_insuser(userbuff,passbuff);
				break;
			case 's':
				printf("Please input user:");
				scanf("%s",userbuff);
				lib_mysql_searchuser(userbuff);
				break;
			case 'd':
				printf("Please input user:");
				scanf("%s",userbuff);
				lib_mysql_deluser(userbuff);
				break;
			case 'a':
				lib_mysql_showuser();
				break;
			case 'q':
				loop=0;
				break;
			default:
				break;
		}
		fgets(bufftmp,50,stdin);
	}

	return 0;	
}
