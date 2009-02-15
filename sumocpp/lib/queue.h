#ifndef QUEUE_H_
#define QUEUE_H_

struct Move{
	char left, right, pri;
	int time;
};

class Queue{
public:	 
	Queue();
	~Queue();
	void push(Move move);
	void push(char m1, char m2, int time);
	void push(char m1, char m2, int time, int priority);
	void clear();
	Move* front();
	Move dec(int time);
	Move pop();
};

#endif


