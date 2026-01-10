

#include <stdint.h>
#include <stdbool.h>
#define QUEUE_DEPTH 900

typedef struct {int16_t head; int16_t load; int32_t buffer[QUEUE_DEPTH+3];} Queue;


void init_queue(Queue* this);

bool enqueue(Queue* this, int32_t data);

bool dequeue(Queue* this, int32_t* data);

void monitor_queues();

void init_all_queues();
