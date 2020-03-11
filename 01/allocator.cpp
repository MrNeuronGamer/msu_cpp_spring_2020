#include "allocator.hpp"
#include <stdlib.h>


static void* mem_start_ptr = nullptr;
static size_t using_size = 0;
static size_t max_size = 0;

void makeAllocator(size_t maxSize)
{
    using_size = 0;
    max_size = 0;
    // проверяем, нет ли уже аллоцированный памяти, если есть -- возвращаем её ОС
    if (mem_start_ptr != nullptr)
        free(mem_start_ptr);
        
    // берём у ОС памяти
    max_size = maxSize;
    mem_start_ptr = malloc(max_size);
    if (!mem_start_ptr) max_size = 0;

    using_size = 0;

}
char* alloc(size_t size)
{
    // Выдаём указатель пользователю
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
    // откатываемся на начало аллоцированный памяти

    using_size = 0;
    
}