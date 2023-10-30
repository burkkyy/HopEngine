FROM ubuntu:22.04

# Update system
RUN apt update && apt install -y

# Install build dependencies
RUN yes | apt install \
    build-essential \
    git \
    cmake \
    mingw-w64 \
    wget \
    p7zip-full \
    p7zip-rar

# Download and Install GLFW
RUN git clone https://github.com/glfw/glfw.git
RUN cd glfw && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_TOOLCHAIN_FILE=../CMake/x86_64-w64-mingw32.cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF .. && \
    make && \
    make install

# Download and Install glm
RUN wget https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.7z
RUN 7z x glm-0.9.9.8.7z
RUN cp -r glm/glm/ /usr/local/include/glm

# Download and Install the vulkan sdk
RUN wget https://sdk.lunarg.com/sdk/download/latest/windows/vulkan-sdk.exe
RUN 7z x -ovulkan-sdk vulkan-sdk.exe
RUN cp -r vulkan-sdk/ /usr/local/include/vulkan

VOLUME /root/env
WORKDIR /root/env

CMD ["make"]
