#Makefile of 


#main target
target = authtest

#
objects = main.o

#subdirs
SUBDIRS = libsqlauth

CC 	=	gcc
CFLAGS 	=	-I./inc  -L./libsqlauth
LFLAGS 	=       -L/usr/lib64/mysql/	-lmysqlclient -lsqlauth -L./libsqlauth 

$(target):$(objects)
	$(call make_subdir) 
	$(CC)	$(CFLAGS)	-o $(target)	$^ $(LFLAGS)

define make_subdir
 @for subdir in $(SUBDIRS) ; do \
 ( cd $$subdir && make $1) \
 done;
endef

.PHONY:clean

clean:
	rm -f $(objects) $(target)
	$(call make_subdir,clean) 
