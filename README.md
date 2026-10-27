# qtmir

qtmir allows a shell written in Qt to function as a window manager by running a Mir server and implementing the Qt Platform Abstraction (QPA) API. It is currently compatible with both Mir 1 and Mir 2 (see the `-DWITH_MIR2` build option).

[src/platforms/mirserver](src/platforms/mirserver) is the central part, running the Mir server and bridging between Mir and Qt (e.g. screens, input events). It allows the shell to interact with Mir, for example by configuring a window management policy.

[src/platforms/mirserver/qpa](src/platforms/mirserver/qpa) builds a small plugin that makes Qt load qtmir as a QPA.

[src/modules/QtMir/Application](src/modules/QtMir/Application) exposes Mir concepts as QML elements (e.g. a Mir surface as a MirSurfaceItem). It implements the interface described by the [include/lomiri/shell/application](include/lomiri/shell/application) headers.

## Build

See [debian/control](debian/control) for a complete list of build dependencies on Debian. The project is built with CMake:

```sh
cmake -B build
cmake --build build -j $(nproc)
ctest --test-dir build
```
