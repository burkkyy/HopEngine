FROM ubuntu:22.04

# Update system
RUN yes | apt update
RUN yes | apt upgrade

# Install Dependencies
RUN yes | apt install \
    build-essential \
    libvulkan-dev \
    vulkan-validationlayers-dev \
    spirv-tools \
    libglfw3-dev \
    libglm-dev \
    libxxf86vm-dev \
    libxi-dev

VOLUME /home/env
WORKDIR /home/env

CMD ["make"]
