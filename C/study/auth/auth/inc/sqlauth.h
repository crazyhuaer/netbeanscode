/*
 *file name:sqlauth.h
 *description:header file of libsqlauth
 */

#ifndef		__SQLAUTH__
#define		__SQLAUTH__

/**
 *  *description:connect to the mysql server
 *   *return value int:0 successfully,other value are failed
 *    */

int lib_mysql_connect(char *ip_addr,int port,char *username,char *password,char *dataname);


/**
 *  *description:insert username and password into tables;
 *   *return value int:0 successfully,other value are failed
 *    */

int lib_mysql_insuser(char *username,char *password);




/**
 *  *description:delete username and password in tables;
 *   *return value int:0 successfully,other value are failed
 *    */

int lib_mysql_deluser(char *username);



/**
 *  *description:Search username and password in tables;
 *   *return value int:0 successfully,other value are failed
 *    */

int lib_mysql_searchuser(char *username);




/**
 *  *description:Show all username and password in tables;
 *   *return value int:0 successfully,other value are failed
 *    */

int lib_mysql_showuser();



#endif
