ifeq	($(PLATFORM),HOST)
	CC=gcc
endif

ifeq	($(PLATFORM),BBB)
	CC=arm-linux-gnueabihf-gcc
endif

ifeq	($(PLATFORM),KL25Z)
	CC=arm-none-eabi-gcc
endif
	DEP=platform.h	

	CCFLAGS=	-DVERBOSE	-DPROJECT1	-Wall	-Werror	-g	-O0	-std=c99	

%.o:	%.c	$(DEPS)
	$(CC)	-c	-o	$@	$<	$(CCFLAGS)	

memory:	memory.c	memory.h
	$(CC)	-o	memory.o		$(CCFLAGS)	memory.c

conversion:	conversion.c	memory.c	memory.h	conversion.h
	$(CC)	-o	conversion.o	$(CCFLAGS)	conversion.c	memory.c		
	
debug:	debug.c		debug.h
	$(CC)	-o	debug.o	$(CCFLAGS)	debug.c		

platform:	platform.c	platform.h
	$(CC)	-o	platform.o	$(CCFLAGS)	memory.c	

.PHONY:	conversiontest.c	memory.c	debug.c		conversion.c	platform.c			

clean :
	rm	-f	*.o	
