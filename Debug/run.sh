# This script is used to compile project and run the debug houdini scene at the same time

#!/bin/bash

cd Build
make
cd ..
/Applications/Houdini/Houdini19.5.353/Frameworks/Houdini.framework/Versions/Current/Resources/bin/houdini ./debug.hipnc
