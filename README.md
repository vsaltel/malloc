# malloc

My version of the standard malloc C library.
The library is thread safe.

Function included :
- malloc
- calloc
- realloc
- reallocf
- free

42 Paris school system project.

## Build

Compilation :
```
make
```

Clean objects files :
```
make clean
```

Clean entire project :
```
make fclean
```

## Usage

After build you get a dynamic library "libft_malloc_$HOSTTYPE.so"

Now you can start any program with the library with those scripts:
> The system need to know the library location

### Linux
```
./run_linux.sh your_program
```
### MacOs
```
./run_mac.sh your_program
```

Instead indicate the location of the library to your system, you can also compile your program directly with the library :

Copy the dynamic library and includes/malloc.h to your C project

Now you can compile your project with the library

>with gcc add those options : "-L. -lft_malloc"
