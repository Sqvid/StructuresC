#ifndef QUEUE_H
#define QUEUE_H

#include "../list.h"

typedef List Queue;
typedef ListElement QueueElement;


#define queueCreate listCreate
#define getQueueSize getListSize
#define queueDestroy listDestroy
#define queuePeek(queue) ((queue)->head->data == NULL ? NULL : (queue)->head->data)

int enqueue(Queue* queue, const void* data);
int dequeue(Queue* queue, void** data);


// Function definitions:

int enqueue(Queue* queue, const void* data){
	return listAddNext(queue, queue->tail, data);
}

int dequeue(Queue* queue, void** data){
	return listDelNext(queue, NULL, data);
}

#endif
