#include <thread>
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using vector_type = std::complex<long double>;

const unsigned NUM_THREADS = 5;
const unsigned VEC_SIZE = static_cast<unsigned>(2 * std::pow(10, 7));

void work(const std::vector<vector_type> & v, unsigned chunk,
          vector_type & result) {
    auto work_size = v.size() / NUM_THREADS;
    auto beg = chunk * work_size, end = (chunk + 1) * work_size;
    
    for (unsigned i = beg; i < end; ++i)
        result += std::exp(-
                           std::pow(
                                    std::tanh(v[i]), std::acos(-1.0L) / 12.3456L
                                    )
                           );
     std::cout << "Thread " << result << std::endl;
}  

int main() {
    auto num_threads = std::thread::hardware_concurrency();
    std::cout << "Hardware threads: " << num_threads << "\t";
    std::cout << "Number of threads: " << NUM_THREADS << std::endl;
    
    std::vector<vector_type> iv(VEC_SIZE);
    for (unsigned i = 0; i < iv.size(); ++i) iv[i] = vector_type(i,i);
    
    std::vector<std::thread> th;
    std::vector<vector_type> res(NUM_THREADS);
    
    for (unsigned n = 0; n < NUM_THREADS; n++)
        th.push_back(std::thread(work, std::ref(iv), n, std::ref(res[n])));
    
    for (unsigned n = 0; n < NUM_THREADS; n++)
        th[n].join();
    
    vector_type sol = 0;
    for (unsigned n = 0; n < NUM_THREADS; n++) sol += res[n];
    std::cout << "Solution: " << sol << std::endl;
    
    return 0;
}
