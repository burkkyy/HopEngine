# How to build the engine

## How to set up build enviroment
1. Download and Install [Python 3.11](https://www.python.org/downloads/release/python-3115/)\
**NOTE** During installation on windows, make sure to click 'add to path'

2. Download and Install [Docker](https://www.docker.com/products/docker-desktop/)

## How to run the build script
To build HopHopEngine, you have to run build.py.

> Ex.\
> `python build.py`

The build script will create the build environment for you and handle all of the compiliation process. All files created during compiliation are dumped in `engine/build/`.

## Build script options

`python build.py` will only build the library.
To make the examples: `python build.py examples`.
To make the demos: `python build.py demos`.
