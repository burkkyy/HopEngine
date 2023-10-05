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

VOLUME /root/env
WORKDIR /root/env

CMD ["make"]
