ifeq	($(PLATFORM),HOST)
	CC=gcc
	flags=	
endif

ifeq	($(PLATFORM),BBB)
	CC=arm-linux-gnueabihf-gcc
	flags=	-mcpu=cortex-a8	-mthumb	-mfloat-abi=hard			
endif

ifeq	($(PLATFORM),KL25Z)
	CC=arm-none-eabi-gcc
	flags=	-mthumb	-mfpu=fpv4-sp-d16	-specs=nosys.specs	-mcpu=cortex-m0	-march=armv6-m	-mfloat-abi=soft		
endif	
	PROJECT=	PROJECT1	PROJECT2  

	objects=	main.o	memory.o	debug.o	conversion.o	project1.o

	cfiles=	main.c	project1.c	conversion.c	debug.c	memory.c	
	
	basedir=/home/monish/PES_Project

	objdir=$(basedir)/object
	srcdir=$(basedir)/src
	bindir=$(basedir)/bin
	asmdir=$(basedir)/asm
	depdir=$(basedir)/dep
	headdir=$(basedir)/header

	CCFLAGS=	$(flags)	-D$(PROJECT)	-Wall	-Werror	-g	-O0	-std=c99	-DVERBOSE  -lc	


.PHONY:	compile-all	clean	build		

$(srcdir)/%.i:$(srcdir)/%.c	$(headdir)/%.h
	$(CC)	$(CCFLAGS)	-E	$<	-o	$@

$(asmdir)/%.asm:$(srcdir)/%.c	$(headdir)/%.h
	$(CC)	$(CCFLAGS)	-S	$<	-o	$@

$(objdir)/%.o:$(srcdir)/%.c	$(headdir)/%.h
	$(CC)	$(CCFLAGS)	-c	$<	-o	$@

$(objdir)/%.o:$(asmdir)/%.s	$(headdir)/%.h
	$(CC)	$(CCFLAGS)	-c	$<	-o	$@

$(depdir)%.d:$(srcdir)%.c	$(headdir)/%.h
	$(CC)	$(CCFLAGS)	-M	$<	-o	$@

$(depdir)%.d:$(srcdir)%.s	$(headdir)/%.h
	$(CC)	$(CCFLAGS)	-M	$<	-o	$@

build:	$(objects)	$(headdir)/%.h
	$(CC)	-o	$(bindir)/project1.elf	$(CCFLAGS)	-Xlinker	

compile-all:	$(cfiles)	$(headdir)/%.h	
	$(CC)	-c	$(cfiles)	$(CCFLAGS)

clean :
	rm	-f	*.o	*.s	*.e	*.elf
