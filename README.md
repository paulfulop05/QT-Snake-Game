# SnakeGame

A small Qt-based Snake game (qmake project).

# SnakeGame

A compact Snake game implemented with Qt (Widgets). This repository uses qmake and is intended to be built with Qt Creator or Qt command-line tools on Windows.

## Quick summary

- Language: C++
- Toolkit: Qt (Widgets)
- Build system: qmake (.pro)

## Requirements

- Qt 5 or Qt 6 (Qt Widgets module)
- A supported compiler: MinGW (recommended for Qt distributions bundled with MinGW) or MSVC
- Qt Creator (recommended) or the Qt command-line tools available with your Qt installation

## Build & run (recommended — Qt Creator)

1. Open `SnakeGame.pro` in Qt Creator.
2. Select/configure a kit (MinGW or MSVC) and run `Build` → `Run` from the IDE.

## Build & run (command line)

Open the Qt command prompt shipped with your Qt installation (this sets PATH and other env vars). Then from the project root run:

For MinGW:

```powershell
qmake
mingw32-make
.
```

For MSVC (Visual Studio Developer Command Prompt):

```powershell
qmake -spec win32-msvc
nmake
.
```

The produced `.exe` will typically be inside a `release` or `debug` folder under the project root or the build directory configured by your kit.

## Project structure

- `src/` — application source files (e.g. `main.cpp`, `mainwindow.cpp`, `mainwindow.h`, `Resources.qrc`)
- `SnakeGame.pro` — qmake project file

## Troubleshooting

- If qmake is not found, open the "Qt Command Prompt" for your Qt install, or ensure `qmake.exe` is on PATH.
- If you see missing Qt headers or libs, check that your selected kit matches the Qt version used to build the project.
- For MSVC builds ensure you use the corresponding Visual Studio Developer Command Prompt so the correct compiler and tools are on PATH.
