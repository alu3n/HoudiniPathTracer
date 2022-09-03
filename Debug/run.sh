# This script is used to compile project and run the debug houdini scene at the same time

#!/bin/bash

source ../config.env

cd Build
make
cd ..
${HOUDINI_BINARY_PATH} ${DEBUG_SCENE_PATH}
