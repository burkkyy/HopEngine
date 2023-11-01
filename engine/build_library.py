import os
import subprocess
import sys
import shutil
import platform

class CompilieError(Exception):
    pass

def ERROR(s: str, t: str = 'ERROR'):
    print(f"\033[91m[{t}]\033[00m {s}")

def UPDATE(s: str, t: str = 'UPDATE'):
    print(f"\033[92m[{t}]\033[00m {s}")

def INFO(s: str, t: str = 'INFO'):
    print(f"\033[94m[{t}]\033[00m {s}")

WINDOWS_TARGET = 'win64'
LINUX_TARGET = 'linux'
ALL_TARGET = 'all'
DOCKER_IMAGE_WIN64 = 'hophopengine-win64-build'
DOCKER_IMAGE_LINUX = 'hophopengine-linux-build'
DOCKER_IMAGE_PATH_WIN64 = 'buildenv/win64/'
DOCKER_IMAGE_PATH_LINUX = 'buildenv/linux/'

def check_env():
    p = platform.system().lower()

    if not subprocess.check_output(['docker', 'ps']):
        ERROR("Docker not found on system, or permissions to get docker denied. Try running as root.\nSee doc/buildenv/build.md for more")
        exit(1)

    if p == 'windows':
        return False
    elif p == 'linux':
        return True
    else:
        ERROR("This script does not support the host platform")
        exit(1)

def is_docker_image_built(image_name: str):
    return subprocess.check_output(['docker', 'image', 'inspect', f'{image_name}'])

def build_docker_image(image_path: str, image_name: str):
    INFO(f"Building docker image \"{image_name}\"...")
    
    if os.system(f'docker build {image_path} -t {image_name}'):
        ERROR(f"Failed to build docker image: {image_name}", "DOCKER")
        exit(1)
    
    INFO(f"Built docker image \"{image_name}\"!")

def run_docker_image(image_name: str):
    # Set up config.mk or else makefile fails
    if image_name == DOCKER_IMAGE_LINUX:
        try:
            os.remove("buildenv/config.mk")
        except FileNotFoundError:
            pass
        shutil.copyfile("buildenv/linux/config.mk", "buildenv/config.mk")
    elif image_name == DOCKER_IMAGE_WIN64:
        try:
            os.remove("buildenv/config.mk")
        except FileNotFoundError:
            pass
        shutil.copyfile("buildenv/win64/config.mk", "buildenv/config.mk")
    else:
        ERROR(f"Can't run image: \"{image_name}\"", "DOCKER")
        exit(1)
    
    UPDATE(f"Going into \"{image_name}\" buildenv...", "DOCKER")
    
    docker_command = f'docker run --rm -it -v .:/root/env {image_name} make'
    
    print(docker_command)
    if os.system(docker_command):
        ERROR(f"Failded building source in image: {image_name}", "BUILD")
        return False

    # Remove config.mk after compilation
    try:
        os.remove("buildenv/config.mk")
    except FileNotFoundError:
        pass

    return True

def make(docker_path, docker_image_name):
    if not is_docker_image_built(docker_image_name):
        build_docker_image(docker_path, docker_image_name)
    if not run_docker_image(docker_image_name):
        exit() # Error has occured in docker

if __name__ == '__main__':
    is_linux = check_env()

    if len(sys.argv) == 1:
        if is_linux:
            UPDATE("Building for linux target system...", "BUILD")
            make(DOCKER_IMAGE_PATH_LINUX, DOCKER_IMAGE_LINUX)
        else:
            UPDATE("Building for windows target system...", "BUILD")
            make(DOCKER_IMAGE_PATH_WIN64, DOCKER_IMAGE_WIN64)
        exit()
    
    arg = sys.argv[1].lower()
    if arg == 'linux':
        UPDATE("Building for linux target system...", "BUILD")
        make(DOCKER_IMAGE_PATH_LINUX, DOCKER_IMAGE_LINUX)
    elif arg == 'win64':
        UPDATE("Building for windows target system...", "BUILD")
        make(DOCKER_IMAGE_PATH_WIN64, DOCKER_IMAGE_WIN64)
    elif arg == 'all':
        UPDATE("Building for linux and windows system...", "BUILD")
        make(DOCKER_IMAGE_PATH_LINUX, DOCKER_IMAGE_LINUX)
        make(DOCKER_IMAGE_PATH_WIN64, DOCKER_IMAGE_WIN64)
    elif arg == 'dev':
        if is_linux:
            UPDATE("Build library for linux dev env", "BUILD")
            make(DOCKER_IMAGE_PATH_LINUX, DOCKER_IMAGE_LINUX)
            INFO("Make sure you have validation layers installed on your system")
        else:
            UPDATE("Build library for windows dev env", "BUILD")
            make(DOCKER_IMAGE_PATH_WIN64, DOCKER_IMAGE_WIN64)
            INFO("Make sure you have validation layers installed on your system")
    elif arg == 'help':
        INFO('Available build targets:', 'HELP')
        print("\n\tlinux\twin64\tall\tdev")
        print("\n\tEx. python build.py linux\n")
        INFO('Other available args:', 'HELP')
        print("\n\thelp\n")
        exit()
    else:
        ERROR('Invalid args. For available build targets and help run:\n')
        print('\tpython build.py help\n')
        exit(1)
