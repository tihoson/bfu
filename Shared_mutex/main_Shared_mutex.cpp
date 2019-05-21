#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <mutex>
#include "Shared_mutex.hpp"

const int reads    = 10;
const int threads  = 20;
const int requests = 500;
const int sleep    = 10;

using namespace std::chrono;
using clock_ = high_resolution_clock;

void client(std::mutex& m) {
	for (int i = 0; i < requests; i++) {
		m.lock();
		std::this_thread::sleep_for(milliseconds(1 + rand() % sleep)); 
		m.unlock();
	}
}

void shared_client(Shared_mutex& m) {
	for (int i = 0; i < requests; i++) {
		bool read = rand() % reads == 0;
		if (read) {
			m.lock_shared();
			std::this_thread::sleep_for(milliseconds(1 + rand() % sleep)); 
			m.unlock_shared();
		} else {
			m.lock();
			std::this_thread::sleep_for(milliseconds(1 + rand() % sleep)); 
			m.unlock();
		}
	}
}

int main() {
	srand(time(nullptr));
	clock_::time_point start = clock_::now();
	{
		std::mutex m;
		std::vector<std::thread> t(threads);
		for (auto& cur : t)
			cur = std::thread(client, std::ref(m));
		for (auto& cur : t)
			cur.join();	
	}
	std::cout << "Client time: " 
			  << duration_cast<milliseconds>(clock_::now() - start).count()
			  << " ms\n";
	start = clock_::now();
	{
		Shared_mutex m;
		std::vector<std::thread> t(threads);
		for (auto& cur : t)
			cur = std::thread(shared_client, std::ref(m));
		for (auto& cur : t)
			cur.join();	
	}
	std::cout << "Shared client time: " 
			  << duration_cast<milliseconds>(clock_::now() - start).count()
	       	  << " ms\n";
	start = clock_::now();
	return 0;
}
