import os
import platform

DEPENDENCIES = './requirements.txt'
BUILD_IMAGE_NAME = 'hophopengine-build'
UNIX_ENV = True

def check_env():
    p = platform.system().lower()

    if os.system('docker -v >/dev/null 2>&1'):
        print("Docker not found. See doc/buildenv/build.md for more")
        exit(1)

    if p == 'windows':
        UNIX_ENV = False
        return False
    elif p == 'linux' or p == 'darwin':
        UNIX_ENV = True
        return True
    else:
        print("Build env does not support this platform")
        exit(1)

def is_image_built():
    if not os.system(f'sudo docker image inspect {BUILD_IMAGE_NAME} > /dev/null 2>&1'):
        return True
    return False

def build_image():
    if UNIX_ENV:
        os.system(f'sudo docker build buildenv/ -t {BUILD_IMAGE_NAME}')
    else:
        os.system(f'docker build buildenv/ -t {BUILD_IMAGE_NAME}')

def build():
    if UNIX_ENV:
        os.system(f'sudo docker run --rm -it -v $(pwd):/root/env {BUILD_IMAGE_NAME}')
    else:
        os.system(f'docker run --rm -it -v %cd%:/root/env {BUILD_IMAGE_NAME}')
    
if __name__ == '__main__':
    check_env()
    
    try:
        if not is_image_built():
            build_image()
        
        build()
    except:
        print("Some build error has occured, see doc/buildenv/build.md for more") 
