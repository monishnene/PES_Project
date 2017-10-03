/* Define compiler for the platform*/
#ifdef PLATFORM==HOST
CC= gcc
#endif

#ifdef PLATFORM==BBB
CC= arm-linux-gnueabihf-gcc
#endif


#ifdef PLATFORM==KL25Z
CC= arm-none-eabi-gcc
#endif


CCFLAGS = -DVERBOSE -DPROJECT1

conversion test:	conversiontest.c	memory.c
	$(CC)	-o	$(CCFLAGS)	conversiontest.elf conversiontest.c	memory.c		

clean :
	rm -f *.o 
