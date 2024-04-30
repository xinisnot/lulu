# About

lulu is MIDI-controlled granular delay. If you only want to use VST/AU plugin, you can download [here](https://xinisnot.gumroad.com/l/lulu).

# How to build

Basically, you can build along with [this way](https://github.com/Cycling74/rnbo.example.juce). So after installing the necessary tools, first you should clone this repository, and update JUCE submodule.

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

Finally, build VST/AU plugins. By default, plugins are builded as Debug-build (quick compile, but seems that perfermance is slower and file size is larger). If you want to build as Release-build, you should add `--config Release` option.

```
$ cmake --build .
```

# Note

This repository has C++ codes that RNBO generates in `export` directory. But if you want to modify original RNBO patches or export as different codes such as JavaScript, you must purchase RNBO licenses.