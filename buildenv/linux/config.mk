# Enviroment variables for a linux target build. 
# Read doc/buildenv/build.md for more

ARCH = linux
OUT = build/linux/bin/app.bin
CC = g++
AR = ar
CFLAGS = -std=c++17 -O2 -Wall -Wextra -I src/
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
