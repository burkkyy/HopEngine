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

DOCKER_IMAGE_NAME = 'hophopengine-build'
DOCKER_IMAGE_PATH = 'buildenv/'

def check_env():
    p = platform.system().lower()

    try:
        subprocess.check_output(['docker', 'ps'])
    except:
        ERROR("Docker not found on system, or permissions to get docker denied. Try running as root.\nSee doc/buildenv/build.md for more")
        exit(1)

def build_docker_image(image_path: str, image_name: str):
    INFO(f"Building docker image \"{image_name}\"...")
    
    if os.system(f'docker build {image_path} -t {image_name}'):
        ERROR(f"Failed to build docker image: {image_name}", "DOCKER")
        exit(1)
    
    INFO(f"Built docker image \"{image_name}\"!")

def run_docker_image(image_name: str):
    docker_command = f'docker run --rm -it -v .:/root/env {image_name} make'
    
    UPDATE(f"Going into \"{image_name}\" buildenv...", "DOCKER")
    print(docker_command)
    if os.system(docker_command):
        ERROR(f"Failded building source in image: {image_name}", "BUILD")
        return False

    return True

def make(docker_path, docker_image_name):
    build_docker_image(docker_path, docker_image_name)
    if not run_docker_image(docker_image_name):
        exit() # Error has occured in docker

if __name__ == '__main__':
    check_env()
    
    if len(sys.argv) == 1:
        UPDATE("Building for linux target system...", "BUILD")
        make(DOCKER_IMAGE_PATH, DOCKER_IMAGE_NAME)
        exit()
    
    arg = sys.argv[1].lower()

    if arg == 'dev':
        UPDATE("Build library for linux dev env", "BUILD")
        make(DOCKER_IMAGE_PATH, DOCKER_IMAGE_NAME)
        INFO("Make sure you have validation layers installed on your system")
