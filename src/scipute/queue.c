#include "queue.h"
#include <stdlib.h>

struct Queue* create_queue() {
  struct Queue* queue = malloc(sizeof(struct Queue));
  queue->head = NULL;
  queue->tail = NULL;

  return queue;
}

int is_empty(struct Queue *queue) {
  return queue->tail == NULL && queue->head == NULL;
}

void enqueue(struct Queue* queue, double upperBound, double lowerBound) {
  struct QueueNode* item = malloc(sizeof(struct QueueNode));

  item->upperBound = upperBound;
  item->lowerBound = lowerBound;
  item->next = NULL;

  if(queue->head == NULL && queue->tail == NULL) {
    queue->head = item;
    queue->tail = item;
  } else {
    queue->tail->next = item;
    queue->tail = item;
  }
}

struct QueueNode* dequeue(struct Queue* queue) {
  struct QueueNode* thing = queue->head;
  if(queue->head->next == NULL) {
    queue->head = NULL;
    queue->tail = NULL;
  } else {
    queue->head = queue->head->next;
  }

  return thing;
}
