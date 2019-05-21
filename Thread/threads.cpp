#include <vector>
#include <thread>
#include <iostream>
#include <numeric>
#include <thread>

class def_thread : public std::thread {
	public:
		using std::thread::thread;
		~def_thread() {
			if (this->joinable())
				this->join();
		}
		def_thread& operator=(def_thread&& t) {
			std::thread::operator=(std::forward<std::thread>(t));
		}//= default;
};

void get_data(std::vector<int>& a, std::vector<int>& b) {
	int n;
	std::cout << "Enter vector size\n";
	std::cin >> n;
	a.resize(n), b.resize(n);
	std::cout << "Enter elements of first vector\n";
	for (int& cur : a)
		std::cin >> cur;
	std::cout << "Enter elements of second vector\n";
	for (int& cur : b)
		std::cin >> cur;
}

void worker(std::vector<int>& a, std::vector<int>& b, size_t l, size_t r, int& ans) {
	for (size_t i = l; i < r && i < a.size(); i++)
		ans += a[i] * b[i];
}

int find_scolar(std::vector<int> a, std::vector<int> b) {
	size_t n = std::max(std::thread::hardware_concurrency(), 2u);
	size_t k = a.size();
	size_t block_size = (n + k - 1) / n;
	std::vector<def_thread> d_t(n);
	std::vector<int> t_ans(n);
	for (size_t i = 0; i < n; i++)
		d_t[i] = def_thread([&, i](int l, int r) {
				for (size_t j = l; j < r && j < a.size(); j++)
					t_ans[i] += a[j] * b[j];
			} , block_size * i, block_size * (i + 1));
	for (size_t i = 0; i < n; i++)
		d_t[i].join();
	return std::accumulate(t_ans.begin(), t_ans.end(), 0);
}

int main() {
	std::vector<int> a, b;
	get_data(a, b);
	std::cout << find_scolar(std::move(a), std::move(b));	
	return 0;
}
