#!/bin/sh
# Start Xcode
mkdir -p build && cd build && cmake -G "Xcode" .. && open PluginFactory.xcodeproj && cd ..

