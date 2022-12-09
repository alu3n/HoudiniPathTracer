#!/bin/bash

source ./config.env

mkdir Build
cd Build
cmake ../../Source
make