#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */

void** top_k(size_t k, void** datos, size_t tam_datos, cmp_func_t cmp);