Thank you for downloading! Plugins can be installed using the old-fashioned way.

# MacOS

## [1] Put plugins in the correct folder
It’s recommended to put them in your system folder. System folders are…

* `/Library/Audio/Plug-Ins/VST3` for VST
* `/Library/Audio/Plug-Ins/Components` for AU

## [2] Make plugins available (Catalina or later)
Plugins are not certified because I’m not a member of the Apple Developer Program.   Therefore macOS won’t let you launch them by default. But you can let them launch by following steps.

1. Open **Terminal.app**. This is in `/Applications/Utility`
2. Enter or copy-and-paste below command, and hit Enter-key. If you put plugins in a folder other than the system folder, rewrite the path.
3. Enter the password of your Mac if the prompt requests to do so, and hit Enter-key. *Note that the * mark does not appear*.

### [2-1] for VST
```
sudo xattr -rd com.apple.quarantine "/Library/Audio/Plug-Ins/VST3/lulu.vst3"
```

### [2-2] for AU
```
sudo xattr -rd com.apple.quarantine "/Library/Audio/Plug-Ins/Components/lulu.component"
```

## [3] Finish
Now you can launch plugins from the host. If necessary, scan plugins from the host.


<div style="page-break-before:always"></div>

# Windows

## [1] Put plugins in the correct folder
It’s recommended to put them in your system folder. System folder is…

* `C:/Program Files/Common Files/VST3`

## [2] Finish
Now you can launch plugins from the host. If necessary, scan plugins from the host.
