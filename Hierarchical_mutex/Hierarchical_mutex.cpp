#include "Hierarchical_mutex.hpp"

Hierarchical_mutex::Hierarchical_mutex(const int prior):
	prior_(prior) {}
	
void Hierarchical_mutex::lock() {
	std::lock_guard<std::mutex> lock(m_in_);
	std::thread::id id = std::this_thread::get_id();
	if (lckd_.find(id) == lckd_.end()) {
		lckd_.emplace(id, std::stack<int>());
		lckd_.at(id).push(prior_);
	} else {
		try {
			if (lckd_.at(id).empty() || lckd_.at(id).top() < prior_) {
				lckd_.at(id).push(prior_);
				m_.lock();
			} else  if (lckd_.at(id).top() >= prior_){
				throw "Incorrect lock!\n";
			}
		} catch (const char *error) {
			std::cout << error;
			exit(0);
		}
	}		
}

void Hierarchical_mutex::unlock() {
	std::lock_guard<std::mutex> lock(m_in_);
	std::thread::id id = std::this_thread::get_id();
	try {
		if (lckd_.find(id) == lckd_.end() || (lckd_.find(id)->second).empty()) {
			throw "Mutex with " + std::to_string(prior_) + " prior isn't locked!\n";
		} else {
			if (lckd_.at(id).top() != prior_) {
				throw std::string("Incorrect unlock!\n");
			} else {
				m_.unlock();
				lckd_.at(id).pop();
			}
		}
	} catch (std::string error) {
		std::cout << error;
		exit(0);
	}
}

std::mutex Hierarchical_mutex::m_in_ ;
std::map<std::thread::id, std::stack<int>> Hierarchical_mutex::lckd_ = std::map<std::thread::id, std::stack<int>>();
