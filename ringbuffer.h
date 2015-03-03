/*
 * ringbuffer.h
 *
 *  Created on: 09/06/2014
 *      Author: Wellington
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

//#include "PacketInfo.h"

/**
 * ringbuffer - a template based interrupt safe circular buffer structure with functions
 */
template<typename T, int BUFFERSIZE>
class ringbuffer {
public:
	ringbuffer();
	virtual ~ringbuffer();
	bool empty();
	void push_back(T);
	T pop_front();
	void clear_buffer();
private:
	//#define BUFFERSIZE 16
	int head;
	int tail;
	T buffer[BUFFERSIZE];

	// Non-copyable, non-assignable.
	//ringbuffer(ringbuffer&);
	//ringbuffer& operator=(const ringbuffer&);


};

template<typename T, int BUFFERSIZE>
ringbuffer<T,BUFFERSIZE>::ringbuffer() {
	/*
	head = 0;
	tail = 0;
	unsigned char i = BUFFERSIZE;
	for (i = BUFFERSIZE; i > 0; i--) {
		buffer[i - 1] = 0;
	}
	// TODO Auto-generated constructor stub
	*/
	clear_buffer();
}

template<typename T, int BUFFERSIZE>
ringbuffer<T,BUFFERSIZE>::~ringbuffer() {
	// TODO Auto-generated destructor stub
}

/**
 * empty() - checks the buffer for data
 *
 * returns true if empty, false if there is data
 */
template<typename T, int BUFFERSIZE>
bool ringbuffer<T,BUFFERSIZE>::empty() {
	return head == tail;
}
template<typename T, int BUFFERSIZE>
void ringbuffer<T,BUFFERSIZE>::clear_buffer(){
		 _disable_interrupts();  // disable interrupts to protect head and tail values
	                            // This prevents the RX_ISR from modifying them
	                            // while we are trying to read and modify
		head = 0;
		tail = 0;

		_enable_interrupts();  // ok .. let everyone at them
}

/**
 * push_back() - append a byte to the buffer is possible
 *               assumed to be called from the recv interrupt
 */
template<typename T, int BUFFERSIZE>
void ringbuffer<T,BUFFERSIZE>::push_back(T c){
    //int i = (unsigned int)(head + 1) % BUFFERSIZE;

	int i = (unsigned int)(head + 1);

	if(i == BUFFERSIZE){
		i=0;
	}
    if ( i != tail ) {
        buffer[head] = c;
        head = i;
    }
}
/**
 * pop_front() - remove a value from front of ring buffer
 */
template<typename T, int BUFFERSIZE>
T ringbuffer<T,BUFFERSIZE>::pop_front() {
	    T c;

	    _disable_interrupts();  // disable interrupts to protect head and tail values
	                            // This prevents the RX_ISR from modifying them
	                            // while we are trying to read and modify

	    // if the head isn't ahead of the tail, we don't have any characters
	    if (head != tail) {
	        c = buffer[tail];
	        tail = (unsigned int)(tail + 1);
	        if(tail==BUFFERSIZE){
	        	tail=0;
	        }
	       // tail = (unsigned int)(tail + 1) % BUFFERSIZE;
	    }

	    _enable_interrupts();  // ok .. let everyone at them

	    return c;

}



#endif /* RINGBUFFER_H_ */
