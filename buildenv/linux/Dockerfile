FROM ubuntu:22.04

# Update system
RUN apt update && apt install -y

# Install build dependencies
RUN yes | apt install \
    build-essential \
    libvulkan-dev \
    vulkan-validationlayers-dev \
    spirv-tools \
    libglfw3-dev \
    libglm-dev \
    libxxf86vm-dev \
    libxi-dev

# Install the vulkan sdk
RUN yes | apt install wget
RUN wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | tee /etc/apt/trusted.gpg.d/lunarg.asc
RUN wget -qO /etc/apt/sources.list.d/lunarg-vulkan-jammy.list http://packages.lunarg.com/vulkan/lunarg-vulkan-jammy.list
RUN apt update
RUN yes | apt install vulkan-sdk

VOLUME /root/env
WORKDIR /root/env

CMD ["make"]
