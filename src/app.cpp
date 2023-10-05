#include <iostream>

#include "Window/window.hpp"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    bun::Window w(500, 800);

    std::cout << "Hello world!" << std::endl;

    return 0;
}
