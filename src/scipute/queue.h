#ifndef LIB_SCI_PUTE_QUEUE
#define LIB_SCI_PUTE_QUEUE

struct Queue {
  struct QueueNode* head;
  struct QueueNode* tail;
};

struct QueueNode {
  double upperBound;
  double lowerBound;
  struct QueueNode* next;
};

struct Queue* create_queue();
int is_empty(struct Queue* queue);
void enqueue(struct Queue* queue, double upperBound, double lowerBound);
struct QueueNode* dequeue(struct Queue* queue);

#endif
