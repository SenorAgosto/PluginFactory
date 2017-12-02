#!/bin/sh
# Start Xcode
mkdir -p xcode_build && cd xcode_build && cmake -G "Xcode" .. && open PluginFactory.xcodeproj && cd ..

