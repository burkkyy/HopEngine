FROM ubuntu:22.04

# Update system
RUN apt update && apt upgrade

# Install Dependencies
RUN apt install \
    build-essential \
    libvulkan-dev \
    vulkan-validationlayers-dev \
    spirv-tools \
    libglfw3-dev \
    libglm-dev \
    libxxf86vm-dev \
    libxi-dev

# Install glslc
RUN wget https://storage.googleapis.com/shaderc/artifacts/prod/graphics_shader_compiler/shaderc/linux/continuous_gcc_release/436/20230921-084032/install.tgz \
    tar -xf install.tgz

VOLUME /root/env
WORKDIR /root/env

CMD ["make"]
