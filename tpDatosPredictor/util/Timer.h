/*
 * Timer.h
 *
 *  Created on: 08/11/2014
 *      Author: lucas
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <iostream>
#include <time.h>

namespace std {

class Timer {
	public:
		Timer();
		virtual ~Timer();
		void           start();
		void           stop();
		void           reset();
		bool           isRunning();
		unsigned long  getTime();
		bool           isOver(unsigned long seconds);
	private:
		bool           resetted;
		bool           running;
		unsigned long  beg;
		unsigned long  end;
};

} /* namespace std */

#endif /* TIMER_H_ */
