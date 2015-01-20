
/* This is a Socket class implementation file
 */

#include "socket.h"
#include "implement/socket.h"

#include <ooc/exception.h>
#include <ooc/signal.h>

/** @class Socket
 *  @brief Socket class - brief description.
 * 	@see socket.h
 */

/** @file socket.h 
 *  @brief Socket class - brief description.
 * Socket is a .....
 */ 

/* Allocating the class description table and the vtable
 */

AllocateClass( Socket, Base );

/* Class virtual function prototypes
 */

static
void
_socket_virtual( Socket self )
{
	return;
}


/* Class initializing
 */

static
void
Socket_initialize( Class this )
{
	SocketVtable vtab = & SocketVtableInstance;
	
	vtab->socket_virtual	= 	_socket_virtual;

	ooc_init_class( SocketException );
	ooc_init_class( Signal );
	
	/* Allocate global resources here */
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
Socket_finalize( Class this )
{
	/* Release global resources! */
}
#endif


/* Constructor
 */

static
void
Socket_constructor( Socket self, const void * params )
{
	assert( ooc_isInitialized( Socket ) );
	
	chain_constructor( Socket, self, NULL );

}

/* Destructor
 */

static
void
Socket_destructor( Socket self, SocketVtable vtab )
{
}

/* Copy constuctor
 */

static
int
Socket_copy( Socket self, const Socket from )
{
	/* makes the default object copying (bit-by-bit) */
	return OOC_COPY_DEFAULT;
	
	/* Copies data by hand */
	self->data = from->data;
	...
	return OOC_COPY_DONE;
	
	/* Prevent object duplication */
	return OOC_NO_COPY;
}

/*	=====================================================
	Class member functions
 */


Socket
socket_new( void )
{
	ooc_init_class( Socket ); !!! TODO !!! You may want to remove the initialization from here ...
		
	return (Socket) ooc_new( Socket, NULL );
}


void
socket_methods( Socket self, int )
{
	
}

/* This is a SocketException class implementation
 */

/** @class SocketException
 *  @brief SocketException class - brief description.
 * 	@see socketexception.h
 */

/** @file socketexception.h 
 *  @brief SocketException class - brief description.
 * SocketException is a .....
 */ 

#include <ooc/implement/exception.h>

ClassMembers( SocketException, Exception )
EndOfClassMembers;

Virtuals( SocketException, Exception )
EndOfVirtuals;

AllocateClass( SocketException, Exception );

static	void	SocketException_initialize( Class this ) {}
static	void	SocketException_finalize( Class this ) {}

static	void	SocketException_constructor( SocketException self, const void * params )
{
	assert( ooc_isInitialized( SocketException ) );
	
	chain_constructor( SocketException, self, NULL );

    if( params )
        self->Exception.user_code = * ( (int*) params );
}

static	void	SocketException_destructor( SocketException self, SocketExceptionVtable vtab ) {}
static	int		SocketException_copy( SocketException self, const SocketException from ) { return OOC_COPY_DEFAULT; }

Exception
socket_exception_new( enum SocketExceptionTypes error_code )
{
       ooc_init_class( SocketException );
       return (Exception) ooc_new( SocketException, & error_code );
}
