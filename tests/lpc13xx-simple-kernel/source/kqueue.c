
#include <libs-klipos.h>

#include "../include/kqueue.h"


void initKQueue(KQueue* queue, void* buffer, int32_t size)
{
    queue->head = 0;
    queue->tail = 0;
    queue->size = size;
    queue->pending = buffer;
}

bool writeToKQueue(KQueue* queue, uint32_t data)
{
    uint32_t size = queue->size-1;
    if ( ((queue->tail+1) & (size)) == ((queue->head) & (size)) )
    {
        printf("writeToKQueue failed!\r\n");
        return false;
    }
  
    queue->pending[queue->tail & (size)] = data;
    queue->tail++;
    
    return true;
}

bool readFromKQueue(KQueue* queue, uint32_t* data)
{
    if (queue->head == queue->tail)
    {
        return false;
    }
    
    *data = queue->pending[queue->head & (queue->size-1)];
    queue->head++;
    
    return true;
}

