
#include <libs-klipos.h>

#include "../include/kqueue.h"


void initKQueue(KQueue* queue, void* buffer, Int32 size)
{
    queue->head = 0;
    queue->tail = 0;
    queue->size = size;
    queue->pending = buffer;
}

bool writeToKQueue(KQueue* queue, UInt32 data)
{
    if ( ((queue->tail+1) & (queue->size-1)) == ((queue->head) & (queue->size-1)) )
    {
        return false;
    }
  
    queue->pending[queue->tail & (queue->size-1)] = data;
    queue->tail++;
    
    return true;
}

bool readFromKQueue(KQueue* queue, UInt32* data)
{
    if (queue->head == queue->tail)
    {
        return false;
    }
    
    *data = queue->pending[queue->head & (queue->size-1)];
    queue->head++;
    
    return true;
}

