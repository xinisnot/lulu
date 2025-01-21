# lulu
**lulu** is MIDI-controlled live-granular effect. When receives MIDI note-on message, lulu starts to generate grains from a loop-recording buffer of 5 secs. According to received MIDI note number, grains can be pitch-shifted.

![gui](manual_images/gui.png)

## About GUI
By double-clicking each dials, a number box which lets you tweak values will appear. 

Two range-bars positioned in lower half are linked to the following dial.

* size1, size2
* pos1, pos2

Input sound is displayed on the oscilloscope. *Note: current version will reset oscilloscope drawing when window is closed. There's no problem in using*.

<div style="page-break-before:always"></div>

# How to use
Although lulu is an audio effect plugin, it must receive MIDI note-on message in order to sound. 


Middle C is the standard for grain pitch, and no pitch shift occurs.