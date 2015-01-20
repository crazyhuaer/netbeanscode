
#ifndef SOCKET_H
#define SOCKET_H

#include <ooc/ooc.h>
#include <ooc/exception.h>

DeclareClass( Socket, Base );

Socket socket_new( void );

void socket_methods( Socket self, int );

/* Virtual function definitions
 */

Virtuals( Socket, Base )

	void	(* socket_virtual)  ( Socket );

EndOfVirtuals;

DeclareClass( SocketException, Exception );

enum SocketExceptionTypes
{
	OK				=	0,

};

#endif  /* SOCKET_H */
