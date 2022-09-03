# This script is used to compile project and run the debug houdini scene at the same time

#!/bin/bash

source ../config.env

# TODO: cmake is unnecessary in some scenarios, prevent it!

mkdir Build
cd Build
cmake ../../Source
make

${HOUDINI_BINARY_PATH} ${DEBUG_SCENE_PATH}
