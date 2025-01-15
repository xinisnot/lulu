# About

lulu is MIDI-controlled live granular. It is also released on [Gumroad](https://xinisnot.gumroad.com/l/lulu). If you like it, I would appreciate if you can leave a small tip.

# How to build

Basically, you can build in [this way](https://github.com/Cycling74/rnbo.example.juce), but I've made some changes because I want to use the stable version of JUCE (the development version, which `git submodule` adds, gave me an error while working with CMake). So after installing the necessary tools (especially git, cmake and IDE) and JUCE (download from [here](https://juce.com/download/)),

```
$ git clone https://github.com/xinisnot/lulu.git
$ cd lulu/thirdparty
$ ln -s PATH_TO_JUCE .
$ mv SYMBOLIC_LINK_NAME juce
$ cd ../build
$ cd build
```
Next generate your build system. For example you want to use macOS and Xcode, you should do below.

```
$ cmake .. -G Xcode
```

Finally, build VST/AU plugins in `build` directory.

 ```
$ cmake --build .
```

By default, plugins are builded as Debug-build (quick compile, convenient for debug, but perfermance is slower and file size is larger). If you want to build for your sound/music creation, you should build as Release-build.

 ```
$ cmake --build . --config Release
```

# Note

This repository has C++ codes that RNBO generates in `export` directory. But if you want to modify original RNBO patches or export as different codes such as JavaScript, you must purchase RNBO licenses.
