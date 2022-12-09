#!/bin/bash

source ./config.env

mkdir Build
cd Build
cmake ../../Source
make

${HOUDINI_BINARY_PATH} ${DEBUG_SCENE_PATH}
