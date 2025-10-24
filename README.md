<<<<<<< HEAD
# QT-Snake-Game
=======
# SnakeGame

A small Qt-based Snake game (qmake project).

## Requirements

- Qt 5 or Qt 6 (Qt Widgets)
- A compatible compiler (MinGW or MSVC)
- Qt Creator (recommended) or the Qt command-line tools

## Build (Qt Creator)

1. Open `SnakeGame.pro` in Qt Creator.
2. Configure a kit (MinGW or MSVC) and build/run from the IDE.

## Build (command line, MinGW)

Open the Qt command prompt for your Qt installation, then run:

```powershell
qmake
mingw32-make
```

For MSVC (Visual Studio), you can use:

```powershell
qmake -spec win32-msvc
nmake
```

The built executable will be in your build folder (e.g. a `release` or `debug` subfolder). Run the produced `.exe` to start the game.

## Project layout

- `src/` — source files: `main.cpp`, `mainwindow.cpp/.h`, `Resources.qrc`, and the `.pro` file.

## License

Add your preferred license here.

## Notes

- This repository uses qmake (`.pro`) as the build system. If you prefer CMake, you can port the project to a `CMakeLists.txt`.
>>>>>>> a325fee (Initial commit)
