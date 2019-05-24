#include <fstream>
#include <list>
#include <algorithm>
#include <future>
#include <chrono>
#include <cmath>

using namespace std::chrono;
using clock_ = high_resolution_clock;

int max_deep = log2(std::thread::hardware_concurrency());

std::list<int> quick_sort(std::list<int> list, int deep = 0) {
    if (list.empty()) 
		return list;
		
    int mid = list.front();
    
    auto left_it = std::partition(list.begin(), list.end(), [mid](int cur){return cur < mid;});
    auto right_it = std::partition(left_it, list.end(), [mid](int cur){return cur <= mid;});

    std::list<int> l, m;

    l.splice(l.end(), list, list.begin(), left_it);
    m.splice(m.end(), list, left_it, right_it);

    
    std::launch type = std::launch::deferred;
    
    if (deep < max_deep)
        type = std::launch::async; 

    std::future<std::list<int>> async_part = std::async(type, quick_sort, std::move(l), deep + 1);
    list = quick_sort(std::move(list), deep + 1);
    
    list.splice(list.begin(), std::move(m));
    list.splice(list.begin(), async_part.get());

    return std::move(list);
}

int main(){
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    
    std::list<int> list;
    int cur;
    while (in >> cur)
    	list.push_back(cur);
    
    clock_::time_point start = clock_::now();
    
    list = quick_sort(std::move(list));
        
    out << "Time: " 
		<< duration_cast<milliseconds>(clock_::now() - start).count() 
		<< "ms.\n"; 

    for (int cur: list) 
		out << cur << '\n';

    return 0;
}
