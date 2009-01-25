#ifndef QUEUE_H_
#define QUEUE_H_

class Move
{
  public:
  int m1, m2, time;
};

class Queue
{
  public:
    struct Item
    {
      Move move;
      Item* next;
    } *head, *tail;
    
    Queue();
    ~Queue();
    void push(Move move);
    void push(char m1, char m2, int time);
    void clear();
    Move pop(int time);
    Move pop();
};

#endif


