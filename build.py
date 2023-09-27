import os
import platform

def check_docker():
    if not os.system('docker -v'):
        print("Please install docker on your system")
        exit(1)

def check_platform():
    p = platform.system.lower()
    if p == 'windows':
        return False
    else if p == 'linux':
        return True
    else:
        print("Build env does not support this platform")
        exit(1)

if __name__ == '__main__':
    check_docker()

    if check_platform():
        # linux build env
        ...
    else:
        # Windows build env
        ...
