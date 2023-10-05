## Enviroment variables for a windows target build.
# Read doc/buildenv/build.md for more

ARCH = win64
OUT = build/win64/bin/app.exe
CC = x86_64-w64-mingw32-g++
AR = x86_64-w64-mingw32-gcc-ar
CFLAGS = -std=c++17 -O2 -Wall -Wextra -I src/ -I /usr/local/include -L /usr/local/lib -I /usr/local/include/vulkan/Include -L /usr/local/include/vulkan/Lib/
LDFLAGS = -lglfw3 -lgdi32 -luser32 -lkernel32 -lwinmm -limm32 -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -lws2_32 -lntdll
