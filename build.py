import os
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

try:
    import docker
except:
    ERROR("Docker not found. See\033[94m https://pypi.org/project/docker/\033[00m or install with pip:\n")
    print("\tpip install docker\n")

WINDOWS_TARGET = 'win64'
LINUX_TARGET = 'linux'
ALL_TARGET = 'all'
DOCKER_IMAGE_WIN64 = 'hophopengine-win64-build'
DOCKER_IMAGE_LINUX = 'hophopengine-linux-build'
DOCKER_IMAGE_PATH_WIN64 = 'buildenv/win64/'
DOCKER_IMAGE_PATH_LINUX = 'buildenv/linux/'

def check_env():
    p = platform.system().lower()

    try:
        client = docker.from_env()
    except docker.errors.DockerException as e:
        ERROR("Permission to get docker env denied, try running as root.\nSee doc/buildenv/build.md for more")
        exit(1)

    if p == 'windows':
        return False
    elif p == 'linux':
        return True
    else:
        ERROR("This script does not support the host platform")
        exit(1)

def is_docker_image_built(client: docker.client.DockerClient, image_name: str):
    return True if len(client.images.list(filters={'reference': image_name})) > 0 else False

def build_docker_image(client: docker.client.DockerClient, image_path: str, image_name: str):
    INFO(f"Building docker image \"{image_name}\"...")
    
    if os.system(f'docker build {image_path} -t {image_name}'):
        ERROR(f"Failed to build docker image: {image_name}", "DOCKER")
        exit(1)
    
    ''' This doesn't print out anything usefull
    client.images.build(
        path=image_path, 
        tag=image_name,
        quiet=False,
    )
    '''
    INFO(f"Built docker image \"{image_name}\"!")

def run_docker_image(client: docker.client.DockerClient, image_name: str):
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
    
    # Handle any build errors
    UPDATE(f"Going into \"{image_name}\" buildenv...", "DOCKER")

    ''' Idk this just never worked, fix later
    c = client.containers.run(
            image=image_name,
            volumes=[f"{os.getcwd()}:/root/env"],
            stdout=True,
            stderr=True,
            remove=True,
            detach=True,
        )
    try:
        exit_code = c.wait()['StatusCode']
        logs = c.logs(stdout=True, stderr=True, stream=False, timestamps=False)
        print(logs.decode('utf-8'))
        if exit_code != 0:
            raise docker.errors.ContainerError('', exit_code, 'make', image_name, '')
        INFO(f"Successfully ran \"{image_name}\"!", "BUILD")
    except docker.errors.ContainerError:
        ERROR("Some error has occured in the Makefile...", "BUILD")
        exit(1)
    ''' # Use the following instead:
    print(f'docker run --rm -it -v .:/root/env {image_name}')
    if os.system(f'docker run --rm -it -v .:/root/env {image_name}'):
        # docker returned error code (not 0)
        ERROR(f"Failded building source in image: {image_name}", "BUILD")
        return False

    # Remove config.mk after compilation
    try:
        os.remove("buildenv/config.mk")
    except FileNotFoundError:
        pass

    return True

def make_win64(client: docker.client.DockerClient):
    if not is_docker_image_built(client, DOCKER_IMAGE_WIN64):
        build_docker_image(
            client,
            DOCKER_IMAGE_PATH_WIN64,
            DOCKER_IMAGE_WIN64
        )
    if run_docker_image(client, DOCKER_IMAGE_WIN64):
        UPDATE("Binaries for win64 build in build/win64/", "BUILD")
    else:
        exit()

def make_linux(client: docker.client.DockerClient):
    if not is_docker_image_built(client, DOCKER_IMAGE_LINUX):
        build_docker_image(
            client,
            DOCKER_IMAGE_PATH_LINUX,
            DOCKER_IMAGE_LINUX
        )
    if run_docker_image(client, DOCKER_IMAGE_LINUX):
        UPDATE("Binaries for linux build in build/linux/", "BUILD")
    else:
        exit()

def make(target_arch: str):
    client = docker.from_env()
    
    if target_arch == WINDOWS_TARGET:
        make_win64(client)
    elif target_arch == LINUX_TARGET:
        make_linux(client)
    elif target_arch == ALL_TARGET:
        make_win64(client)
        make_linux(client)
        INFO("Successfully built all targets!", "BUILD")
    else:
        ERROR(f'Target system "{target_arch}" not supported', 'BUILD')
        exit(1)

if __name__ == '__main__':
    is_linux_host = check_env()
    target = None

    if len(sys.argv) == 1:
        if is_linux_host:
            UPDATE("Building for linux target system...", "BUILD")
            target = LINUX_TARGET
        else:
            UPDATE("Building for windows target system...", "BUILD")
            target = WINDOWS_TARGET
    else:
        arg = sys.argv[1].lower()
        if arg == 'linux':
            UPDATE("Building for linux target system...", "BUILD")
            target = LINUX_TARGET
        elif arg == 'win64':
            UPDATE("Building for windows target system...", "BUILD")
            target = WINDOWS_TARGET
        elif arg == 'all':
            UPDATE("Building for linux and windows system...", "BUILD")
            target = ALL_TARGET
        elif arg == 'help':
            INFO('Available build targets:', 'HELP')
            print("\n\tlinux\twin64\tall")
            print("\n\tEx. python build.py linux\n")
            INFO('Other available args:', 'HELP')
            print("\n\thelp\n")
            exit()
        else:
            ERROR('Invalid args. For available build targets and help run:\n')
            print('\tpython build.py help\n')
            exit(1)

    make(target)
