# PES_Project1
Monish Nene and Sanika Dongre PES FALL 17
/*
 * conversion.c
Long description:-

 The conversion.c is used for making different conversions like:-
1) Integer to Ascii
2) Ascii to integer 
3) big to little endian and little to big endian
Integer to Ascii uses my_itoa function that handles cases for base 2 to base 16. For base2, if the data is negative, it converts int to char and then converts the negative number into a positive number.The function i2a is then called on which converts the integer to binary values and then reverse function is being called upon to reverse the bits for proper representation of the bits. The compli function is then called which takes the 2's complement of the number and the final answer we get are the binary values for int number. Incase, the number is positive the same logic is applied except that the 2's complement is not required to be taken. For base 8, the binary values for number has been found out and arranged in groups of 3 and for each group respective powers of 2 have been multiplied to get the final answer. For base 10, incrementing the pointer so that it points to the signed bit in case of negative number.The negative number is converted to positive and then converted into bits which are then represented properly. For positive values, the same logic has been used as above.For base 16, the binary values for number has been found out and arranged in groups of 4 and for each group respective power of 2 has been multiplied to get the final answer.

Ascii to integer uses my_atoi function that handles cases for base 2 to base 16. If msb is 1, flag is set to 1 and then negative number is first converted into positive. A function call is used to find the numvalue and then loop would be used for adjusting the value into integer. Similar logic is used for positive number. For base 8, if MSB is 4 or above flag is set to 1. Then, function call is used to find the numvalue and then loop is used for adjusting the value into integer. For base 10, if it has a negative sign, if flag =1, convert negative to positive.Then, the function call numvalue is used to find the numvalue.For, base 16, if MSB is 8 or above, then use the functioncall to find the numvalue. Loop for adjusting the value into integer is used. For all other cases the default condition is that the base is invalid.

For  converting big to little endian, Remainder of data with 16 (for hex) is taken and is being multiplied by 16 for each iteration.After this operation, the MSB and LSB is being swapped  and the middle bytes remain the same. The little to big endian conversion uses the same logic the MSB gets stored first and then the middle bytes and LSB at the last.


 * memory.c
Long Description:-

It has various memory functions like:-
1)my_memmove:- memmove takes 1 byte pointers source and destination and copies a length of bytes from source to destination location without any overalp. If flag =1 , if end of destination adresses intersects at start of source address then we start copying from the begining to handle overlap condition and if the start of destination location intersects at the end of source location then we start copying from the end to handle the overlap condition. If there is no overlap, then flag is zero. Destination is being returned.

2)my_memcpy:- It is used to copy a length of bytes from source to destination. THe copy function may or maynot corrupt the data. Destination is being returned.

3)my memset:- It is used to set all the locations of the source to a given value. It performs the same function as the set_all() function. Source is being returned.

4)my_memzero:- It is used to zero out all the memory.It performs the same function as the clear_all() function. Source is being returned.

5)my_reverse:- It is used for reversing the bytes in a memory. If the length of string is even ( tested by mod operator) the length is divided by 2 to carry out the iterations in the for loop (for reversing) upto half of the length. In case, the length is odd, it is first reduced by 1 and then divided by 2 and then reversing logic is performed. In the reverse for loop, the temp variable stores the source location for every iteration. THen, destination is stored in source and the temp which contains the source is stored back in destination. The function returns source.

6)reserve_words:- Malloc function that contatins the size of operator is used to reserve words in the source. This function returns source. 

7)free_words:-  It is used to free dynamic memory location.

 debug.c
This creates a print_memory() function that enables/disables debug printing with a compile time switch. -DVERBOSE is the flag that is used to enable the compile time switch.
Long description for makefile:-

For platform host the compiler used is gcc and the flags used is -DVERBOSE
For platform BBB the  arm-linux-gnueabihf-gcc compiler is used and the flag is -DVERBOSE
For platform  KL25Z the compiler used is  arm-none-eabi-gcc and the flags used are:- -mthumb, -mfpu=fpv4-sp-d16, -specs=nosys.specs, -mcpu=cortex-m0, -march=armv6-m, -mfloat-abi=soft.

cfiles used are main.c --> it consists of all header files, project1.c, conversion.c, debug.c and memory.c
The ccflags used are $(flags), -DPROJECT1 , -Wall, -Werror, -g, -o0, -std=c99 and the path using -I/path for executable file -lc

Build creates the .elf file.
compile-all creates all the object files.
main.o,project1.o,conversion.o,memory.o,debug.o-->can be used to create individual object files.
main.i,project1.i,conversion.i,memory.i,debug.i-->can be used to create individual .e files.
main.asm,project1.asm,conversion.asm,memory.asm,debug.asm-->can be used to create individual .s files.
clean is used to delete intermediate files

