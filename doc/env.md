# How to setup the development environment

1. Download/Install docker

2. Build the docker image
`docker build buildenv/ -t hophopengine-build`
**NOTE:** On linux run this as root

3. Run the docker image
Linux / Mac: `docker run --rm -it -v $(pwd):/root/env hophopengine-build`
Windows: `docker run --rm -it -v %cd%:/root/env hophopengine-build`
