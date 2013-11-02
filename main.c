#include <stdio.h>
#include "sorted-list.h"
#include <string.h>

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

int main(int argc, char **argv) {
	SortedListPtr list = SLCreate(compareInts);
	int *a = malloc(sizeof(int)), *b = malloc(sizeof(int)), *c = malloc(sizeof(int)), *d = malloc(sizeof(int)), *e = malloc(sizeof(int)),*f = malloc(sizeof(int));
	SortedListIteratorPtr iter= SLCreateIterator(list);
	void *ptr;
	int data;
	/* adding other stuff */
	*a = 7;
	*b = 5;
    *c = 3;
    *d = 6;
	SLInsert(list, a);
	SLInsert(list, b);
	SLInsert(list, c);
	ptr = SLNextItem(iter);
	ptr = SLNextItem(iter);
	SLRemove(list,b);
	SLInsert(list, d);
	printf("%d\n", *(int *)SLNextItem(iter));
	SLDestroy(list);
	free(a);
	free(b);
	free(c);
    free(d);
    free(e);
    free(f);
    return 1;
}
