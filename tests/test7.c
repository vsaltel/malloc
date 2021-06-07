#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{ char *addr1; char *addr3; char *addr4;

	puts("1");
    addr1 = (char*)calloc(6*M, 3);
	puts("2");
    strcpy(addr1, "Bonjour\n");
    print(addr1);
	show_alloc_mem();
	printf("addr1 %p\n", addr1);
    addr3 = (char*)realloc(addr1, 100);
	if (!addr3)
		printf("null\n");	
	show_alloc_mem();
	puts("3");
    print(addr3);
	puts("5");
	addr4 = (char*)calloc(1000000000, 1000000000);
	if (!addr4)
		write(0, "work\n", 5);
    return (0);
}
