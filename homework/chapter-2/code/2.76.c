#include <string.h>

/*
 * @note 分配 nmemb 个元素的数组，每个元素大小为 size
 */
void *calloc(size_t nmemb, size_t size)
{
    if(!nmemb && !size)
    {
        return NULL;
    }

    void *p = malloc(size * nmemb);

    if(p)
        memset(p, 0, size * nmemb);

    return p;
}
