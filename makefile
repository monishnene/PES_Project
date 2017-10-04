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

	CCFLAGS=	-DVERBOSE	-DPROJECT1	-Wall	-Werror	-g	-O0	-std=c99	-I /home/monish/PES_project1

Project1:	main.o	memory.o	debug.o	conversion.o	project1.o
	$(CC)	-c	Project1	main.o	memory.o	debug.o	conversion.o	project1.o	$(CCFLAGS)

main.o:	main.c	project1.h	conversion.h	debug.h	memory.h	platform.h	
	$(CC)	-c	main.c	$(CCFLAGS)	

project1.o:	project1.c	conversion.h	debug.h	memory.h	platform.h
	$(CC)	-c	project1.c	$(CCFLAGS)	

conversion.o:	conversion.c	memory.h	platform.h
	$(CC)	-c	conversion.c	$(CCFLAGS)	

memory.o:	memory.c	stdlib.h	platform.h
	$(CC)	-c	memory.c	$(CCFLAGS)	

debug.o:	debug.c	platform.h
	$(CC)	-c	debug.c	$(CCFLAGS)	

.PHONY:	conversiontest.c	memory.c	debug.c		conversion.c	project1.c			

clean :
	rm	-f	*.o	
