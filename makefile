project1:	main.c	conversion.c	debug.c		memory.c	
	gcc	-o	main.elf	main.c	debug.c	conversion.c	memory.c

conversion test:	conversion.c	memory.c
	gcc	-o	conversiontest.elf	conversion.c	memory.c		
