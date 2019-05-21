#include <mutex>
#include <stack>
#include <thread>
#include <fstream>
#include <string>
#include <memory>
#include <iostream>
#include <vector>

class safe_thread : public std::thread {
	public:
		using std::thread::thread;
		~safe_thread() {
			if (joinable())
				join();
		}
		safe_thread& operator = (safe_thread&& other) = default;
};

template <typename T>
class safe_stack {
	public:
		void push(T);
		std::shared_ptr<T> pop_top();
		size_t size();
		bool empty();
	private:
		std::mutex m_;
		std::stack<T> st_;
};

template <typename T>
void safe_stack<T>::push(T new_elem) {
	std::lock_guard<std::mutex> lock(m_);
	st_.push(new_elem);
}

template <typename T>
std::shared_ptr<T> safe_stack<T>::pop_top() {
	std::lock_guard<std::mutex> lock(m_);
	if (st_.empty())
		return nullptr;
	std::shared_ptr<T> top = std::make_shared<T>(st_.top());
	st_.pop();
	return top;
}

template <typename T>
size_t safe_stack<T>::size() {
	std::lock_guard<std::mutex> lock(m_);
	return st_.size();
}

template <typename T>
bool safe_stack<T>::empty() {
	std::lock_guard<std::mutex> lock(m_);
	return st_.empty();
}

void operations(safe_stack<std::string>& st, int id) {
	std::string file_id(std::to_string(id));
	
	std::ifstream in("commands" + file_id + ".txt");
	std::ofstream out("log" + file_id + ".txt");
	
	std::string command;
	try {
		while (in >> command) {
			std::cout << std::this_thread::get_id() << std::endl;
			if (command == "push") {
				std::string arg;
				in >> arg;
				st.push(arg);
				out << arg << " pushed" << std::endl;
				continue;
			}
			if (command == "pop_top") {
				std::shared_ptr<std::string> top = st.pop_top();
				if (top != nullptr) {
					out << "pop_top: " << *top << std::endl;
				} else {
					out << "pop_top returned nullptr: empty stack" << std::endl;
				}
				continue;
			}
			if (command == "size") {
				out << "size " << st.size() << std::endl;
				continue;
			}
			if (command ==  "empty") {
				if (st.empty()) {
					out << "stack is empty" << std::endl;
				} else {
					out << "stack isn't empty" << std::endl;
				}
				continue;
			}
			throw command;
		}
	} catch (std::string error) {
		out << error << " invalid command";
		return;
	}
}

int main() {
	safe_stack<std::string> st;
	std::vector<safe_thread> t(3);
	for (int i = 0; i < 3; i++)
		t[i] = safe_thread(operations, std::ref(st), i);
	return 0;
}
