#include <stdlib.h>

/* Changes the size of the memory block pointed to by ptr to size bytes.
The contents will be unchanged in the range from the start of the region up to the
minimum of the old and new sizes.  If the new size is larger than the old size, the  added
memory  will  not  be  initialized.   If  ptr is NULL, then the call is equivalent to mal‐
loc(size), for all values of size; if size is equal to zero, and ptr is not NULL, then the
call  is  equivalent  to  free(ptr).
Unless ptr is NULL, it must have been re turned by an earlier call to malloc(), calloc(), or realloc().*/
void	*ft_realloc(void *ptr, size_t size)
{
	size_t	i;
	void	*nptr;

	i = 0;
	nptr = (void *)malloc(size);
	if (!nptr)
		return (NULL);
	while (((char *)ptr)[i])
		{
			((char *)nptr)[i] = ((char *)ptr)[i];
			i++;
		}
	free(ptr);
	return (nptr);
}
