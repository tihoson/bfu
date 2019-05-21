#include "Shared_mutex.hpp"

void Shared_mutex::lock() {
	unlock_shared();
	m_.lock();
}

void Shared_mutex::unlock() {
	m_.unlock();
}

void Shared_mutex::lock_shared() {
	std::lock_guard<std::mutex> lock(shared_m_);
	if (shared_.empty())
		m_.lock();
	shared_.emplace(std::this_thread::get_id());
}

void Shared_mutex::unlock_shared() {
	std::lock_guard<std::mutex> lock(shared_m_);
	shared_.erase(std::this_thread::get_id());
	if (shared_.empty())
		m_.unlock();
}
