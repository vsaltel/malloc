#include "malloc.h"

void	malloc_init(void)
{
	struct rlimit	rlp;
	size_t			n;

	n = 0;
	while (n < NB_AREA)
		g_malloc.area[n++].type = empty;

	getrlimit(RLIMIT_DATA, &rlp);
	g_malloc.data_limit = rlp.rlim_cur;
	g_malloc.page_size = (size_t)getpagesize();
	g_malloc.init = 1;
}
