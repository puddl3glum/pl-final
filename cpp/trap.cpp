
#include <iostream>
#include <mutex>
#include <stack>
#include <string>
#include <stdlib.h>
#include <thread>
#include <vector>

using namespace std;

template<typename Function, typename D>
D integrate(Function f, pair<D, D> range, D tol) {
    stack<pair<D, D>> S;
    mutex mut;

    // push starting range onto the stack
    S.push(range);

    // Declare val for returning later
    auto int_val = make_shared<D>(0);

    // declare lambda for threading
    auto calc_segment = [&](){
        // D a, b;
        mut.lock();
            auto [a, b] = S.top();
            S.pop();
        mut.unlock();

        // trapezoid rule
        auto I_1 = ((b - a) / 2) * (f(a) + f(b));
        // get midpoint
        auto m = (a + b) / 2;
        // composite trapezoid rule w/ 2 subintervals
        auto I_2 = ((b - a) / 4) * (f(a) + 2 * f(m) + f(b));

        mut.lock();
            if (abs(I_1 - I_2) < 3 * (b - a) * tol) {
                *int_val += I_2;
            } else {
                S.push(pair<D, D> (a, m));
                S.push(pair<D, D> (m, b));
            }
        mut.unlock();
    };

    vector<thread> threads;

    while (S.size()) {
        
        for (auto x = 0; x < S.size(); x++) {
            threads.push_back(thread(calc_segment));
        }

        for (auto x = 0; x < threads.size(); x++) {
            threads.at(x).join();
        }
        
        threads.clear();
    }

    // cout << S.size() << "\n";

    return *int_val;
}

int main(int argc, char * argv[]) {

    if (argc < 4) {
        cout << "Too few arguments. Expected: a b tolerance\n";
        return 1;
    }

    auto a = atof(argv[1]);
    auto b = atof(argv[2]);
    auto tol = atof(argv[3]);

    pair<double, double> range(a, b);
    // declare the lambda to pass to integrate
    // template<typename D>
    auto f = [](auto x){ return x*x;};

    // cout << f(b) << "\n";

    auto val = integrate(f, range, tol);

    cout << val << "\n";
    return 0;
}
