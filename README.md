# Task System Tray
This app shows an icon in the system tray while another program executes

## Building

```
qmake
make
```

This produces a binary `TaskSystemTray`

## Using

```
/path/to/TaskSystemTray <some long-running command>
```

The system tray icon will appear until the long-running command terminates.

