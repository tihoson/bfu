#ifndef __HIERARCHICAL_MUTEX__
#define __HIERARCHICAL_MUTEX__

#include <iostream>
#include <mutex>
#include <map>
#include <thread>
#include <stack>
#include <string>

class Hierarchical_mutex {
	private:
		static std::mutex m_in_;
		static std::map<std::thread::id, std::stack<int>> lckd_;
		std::mutex m_;
		int prior_;
	public:
		Hierarchical_mutex(const int); 
		static void init();
		void lock();
		void unlock();
};

#endif //__Hierarchical_MUTEX__
