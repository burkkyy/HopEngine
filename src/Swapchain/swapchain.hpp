#pragma once

namespace bun {

class SwapChain {
public:
    SwapChain();
    ~SwapChain();

    SwapChain(const SwapChain&) = delete;
    SwapChain& operator=(const SwapChain&) = delete;
};

}
