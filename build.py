import os
import subprocess as sp
import sys
import platform

def ERROR(s: str, t: str = 'ERROR'):
    print(f"\033[91m[{t}]\033[00m {s}")

def UPDATE(s: str, t: str = 'UPDATE'):
    print(f"\033[92m[{t}]\033[00m {s}")

def INFO(s: str, t: str = 'INFO'):
    print(f"\033[94m[{t}]\033[00m {s}")

DOCKER_IMAGE_NAME = 'hophopengine-build'
DOCKER_IMAGE_PATH = 'buildenv/'

def check_env():
    try:
        sp.check_output(['docker', 'ps'])
    except:
        ERROR("Docker not found on system, or permissions to get docker denied. Try running as root.\nSee doc/buildenv/build.md for more")
        exit(1)

def is_docker_image_build():
    try:
        sp.run(["docker", "image", "inspect", DOCKER_IMAGE_NAME], check=True, stdout=sp.DEVNULL)
        return True
    except:
        return False

def build_docker_image():
    INFO(f"Building docker image \"{DOCKER_IMAGE_NAME}\"...")
    
    if os.system(f'docker build {DOCKER_IMAGE_PATH} -t {DOCKER_IMAGE_NAME}'):
        ERROR(f"Failed to build docker image: {DOCKER_IMAGE_NAME}", "DOCKER")
        exit(1)
    
    INFO(f"Built docker image \"{DOCKER_IMAGE_NAME}\"!")

def run_docker_image(path: str, command: str):
    docker_command = f'docker run --rm -it -v {path}:/root/env {DOCKER_IMAGE_NAME} {command}'
    
    UPDATE(f"Going into \"{DOCKER_IMAGE_NAME}\" buildenv...", "DOCKER")
    #print(docker_command)

    if os.system(docker_command):
        ERROR(f"Error in image: {DOCKER_IMAGE_NAME}", "DOCKER")
        return False

    return True

def make(path: str, command: str = 'make'):
    if not is_docker_image_build():
        build_docker_image()
        
    if not run_docker_image(path, command):
        exit() # Error has occured in docker

def make_examples():
    examples = [f.path for f in os.scandir('./example') if f.is_dir()]
    commands = []

    for example in examples:
        commands.append(f"make -s -C {example} ")

    if not is_docker_image_build():
        build_docker_image()

    for command in commands:
        run_docker_image('.', command)

if __name__ == '__main__':
    check_env()

    if len(sys.argv) == 1:
        UPDATE("Building engine...", "BUILD")
        make('./engine')
        exit()
    
    arg = sys.argv[1].lower()

    if arg == 'dev':
        UPDATE("Build library for linux dev env", "BUILD")
        #make()
        INFO("Make sure you have validation layers installed on your system")
    elif arg == 'examples':
        UPDATE("Building examples...", "BUILD")
        make_examples()
        INFO("All examples built!", "BUILD")
    elif arg == 'demo':
        UPDATE("Building demo...")
        make('.', 'make -s -C demo/')
        INFO("Demo built!")
    else:
        print("command not found, doing nothing")
