# About

lulu is MIDI-controlled granular delay. It is also released on [Gumroad](https://xinisnot.gumroad.com/l/lulu). If you like it, I would appreciate if you can leave a small tip.

# How to build

Basically, you can build along with [this way](https://github.com/Cycling74/rnbo.example.juce). So after installing the necessary tools (especially git, cmake and IDE), first you should clone this repository, and update JUCE submodule.

```
$ git clone https://github.com/xinisnot/lulu.git
$ cd lulu
$ git submodule update --init --recursive --progress
$ cd build
```

Next generate your build system. For example you want to use macOS and Xcode, you should do below.

```
$ cmake .. -G Xcode
```

If you have an error at this point, maybe there is reason in version of JUCE (git submodule adds development version). To avoid this, you may be able to use stable version. Download JUCE from [here](https://juce.com/download/) and install, and make a symbolic link to JUCE in `thirdparty` directory (assuming you are in `build`).

```
$ cd ../thirdparty
$ rmdir juce
$ ln -s PATH_TO_JUCE .
$ mv SYMBOLIC_LINK_NAME juce
$ cd ../build
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
