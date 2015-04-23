#Makefile of libsqlauth

objects  = libsqlauth.o

target 	 = libsqlauth.a

AR = ar
AFLAGS = rc

$(target):$(objects)
	$(AR)	-$(AFLAGS)	$@	$^		




.PHONY:clean
clean:
	rm -f $(objects)	$(target)
 
