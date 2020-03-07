#include "allocator.hpp"
#include <stdlib.h>


static void* mem_start_ptr = nullptr;
static size_t using_size = 0;
static size_t max_size = 0;

void makeAllocator(size_t maxSize)
{
    if (mem_start_ptr != nullptr)
        free(mem_start_ptr);
        
    max_size = maxSize;
    mem_start_ptr = malloc(max_size);
    using_size = 0;

}
char* alloc(size_t size)
{

   void* ret = nullptr;

   if(max_size >= using_size+ size)
   {
       ret = mem_start_ptr + using_size;
       using_size += size;
       return (char*)ret;
   }
   else return nullptr;

}


void reset()
{

    using_size = 0;
    
}