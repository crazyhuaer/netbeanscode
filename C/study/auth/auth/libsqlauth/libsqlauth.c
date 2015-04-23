/**---------------------------------------------------------------------
 *file name:libsqlauth.c
 *description:lib of sql auth
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <string.h>

MYSQL 		my_connection;
MYSQL_RES	*result;	
MYSQL_ROW	sql_row;
MYSQL_FIELD	*field;


/**
 *description:connect to the mysql server
 *return value int:0 successfully,other value are failed
 */

int lib_mysql_connect(char *ip_addr,int port,char *username,char *password,char *dataname)
{
	int ret = -1;
	
	mysql_init(&my_connection);	

	if(mysql_real_connect(&my_connection,ip_addr,username,password,dataname,port,NULL,0))
	{
		perror("connect..");
		ret = 0;
	}
	else
	{
		perror("connect..");
	}

	return ret;
}


/**
 *description:insert username and password into tables;
 *return value int:0 successfully,other value are failed
 */

int lib_mysql_insuser(char *username,char *password)
{
	int ret = -1;
	char sql[100];
	sprintf(sql,"insert into persons value(\"%s\",\"%s\")",username,password);
	//printf("sql:%s\n",sql);
	ret = mysql_query(&my_connection,sql);			
	if(!ret)
	{
		printf("Insert succesfully.\n");
	}
	else
	{
		perror("Insert");
	}

	return ret;
}


/**
 *description:delete username and password in tables;
 *return value int:0 successfully,other value are failed
 */

int lib_mysql_deluser(char *username)
{
	int ret = -1;
	char sql[100];
	sprintf(sql,"delete from persons where user_name=\'%s\'",username);
	//printf("sql:%s\n",sql);
	ret = mysql_query(&my_connection,sql);			
	if(!ret)
	{
		printf("Delete succesfully.\n");
	}
	else
	{
		perror("Insert");
	}

	return ret;
}



/**
 *description:Search username and password in tables;
 *return value int:0 successfully,other value are failed
 */

int lib_mysql_searchuser(char *username)
{
	int ret = -1;
	char sql[100];
	int i,j;

	sprintf(sql,"select * from persons where user_name=\'%s\'",username);
	//printf("sql:%s\n",sql);
	ret = mysql_query(&my_connection,sql);			
	if(!ret)
	{
		printf("Search succesfully,result is:\n");
		result = mysql_store_result(&my_connection);
		if(result)
		{
			j=mysql_num_fields(result);
			while(sql_row=mysql_fetch_row(result))
			{
				for(i=0;i<j;i++)
				{
					printf("%s\t",sql_row[i]);
				}
				printf("\n");
			}
		}
	}
	else
	{
		perror("Insert");
	}

	return ret;
}


/**
 *description:Show all username and password in tables;
 *return value int:0 successfully,other value are failed
 */

int lib_mysql_showuser()
{
	int ret = -1;
	char sql[100];
	int i,j;

	sprintf(sql,"select * from persons");
	//printf("sql:%s\n",sql);
	ret = mysql_query(&my_connection,sql);			
	if(!ret)
	{
		printf("Query succesfully,result is:\n");
		result = mysql_store_result(&my_connection);
		if(result)
		{
			j=mysql_num_fields(result);
			while(sql_row=mysql_fetch_row(result))
			{
				for(i=0;i<j;i++)
				{
					printf("%s\t",sql_row[i]);
				}
				printf("\n");
			}
		}
	}
	else
	{
		perror("Insert");
	}

	return ret;
}
