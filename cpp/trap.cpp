
#include <iostream>
#include <string>
#include <stdlib.h>

//using namespace std;

int main(int argc, char * argv[]) {

    if (argc < 4) {
        std::cout << "Too few arguments. Expected: a b tolerance\n";
        return 1;
    }

    auto a = atof(argv[1]);
    auto b = atof(argv[2]);

    auto tol = atof(argv[3]);

    std::cout << a;
    std::cout << b;

    return 0;

}