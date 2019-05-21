#ifndef __SHARED_MUTEX__
#define __SHARED_MUTEX__

#include <thread>
#include <mutex>
#include <set>

class Shared_mutex {
	private:
		std::mutex m_, shared_m_;
		std::set<std::thread::id> shared_; 
	public:
		void lock();
		void unlock();
		void lock_shared();
		void unlock_shared();
};

#endif //__SHARED_MUTEX__
