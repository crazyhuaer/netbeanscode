
#ifndef IMPL_SOCKET_H
#define IMPL_SOCKET_H

#ifndef SOCKET_H
#error Do #include "socket.h" right before doing #include "implement/socket.h"
#endif


ClassMembers( Socket, Base )

	struct addrinfo *ai_next;      // linked list, next node

EndOfClassMembers;


Exception	socket_exception_new( enum SocketExceptionTypes error_code );


#endif /* IMPL_SOCKET_H */
