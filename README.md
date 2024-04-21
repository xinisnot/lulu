# About

lulu is polyphonic granular delay. If you only want to use VST/AU plugin, you can download here.

# How does lulu work

Maybe the main components of lulu is a audio buffer, midi buffer and grain generators. Audio buffer has 2 channels and length of each channels is 10 seconds, and input audio signal is always recorded to buffer. Midi buffer manages choosen pitch and velocity according with receiving note-on and note-off. Periodically generated trigger is sent to any one of 1500 grain generators, scheduling generation of grain. At that time one of pitch in Midi buffer is chosen, used as playback speed of grain. So grain generators work like voices of polyphonic synthesizer, and sound of cloud makes polyphonic texture.

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