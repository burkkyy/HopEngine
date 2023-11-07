# Enviroment variables for a linux target build. 
# Read doc/buildenv/build.md for more

CC = g++
AR = ar
CFLAGS = -std=c++17 -O2 -Wall -Wextra -I src/ -I /usr/local/include -L /usr/local/lib
LDFLAGS = -lglfw3 -lvulkan -ldl
