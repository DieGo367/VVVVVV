Build Dependencies
------------------
Compared to building VVVVVV natively, there are several additional tools required
at build time. These include the DS development toolchain as well as tools to
preprocess the images/sounds/music from the `data.zip` file so they can be
included in the DS rom file.

- [BlocksDS](https://blocksds.skylyrac.net/) - The toolchain used for this project.
Follow these [installation instructions](https://blocksds.skylyrac.net/docs/setup/options/).
Be sure to export the `BLOCKSDS` and `WONDERFUL_TOOLCHAIN` environment variables
as they are required when using BlocksDS with CMake.
- [ImageMagick](https://imagemagick.org/script/download.php) - Used to preprocess the
images before they can be converted to the format used on DS. Ensure it is in your `PATH`.
- [FFmpeg](https://ffmpeg.org/download.html) - Used to reencode sounds/music to lower quality
(and to WAV instead of OGG). Ensure it is in your `PATH`.
- [Python](https://www.python.org/downloads/) - Used to run a small script extracting
the music out of the binary blob in `data.zip`.

Unlike other versions, there is no longer a dependency on SDL2. All libraries are either
bundled with the VVVVVV source code or included with your BlocksDS installation.

Build Instructions
------------------
Be sure to use `git submodule update --init` after cloning this repo to get all
the submodules downloaded.

Place your `data.zip` file here in the `desktop_version` folder.
See "Including data.zip" in the original README below for where to find it.

To set up the build environment run these commands from within this folder:
```
mkdir build
cd build
cmake .. --toolchain=$BLOCKSDS/cmake/BlocksDS.cmake -DNDS_ARCH_THUMB=1
```

Now you can just run `make` to compile the game. This will also extract and
convert the assets and bundle them into the output `VVVVVV.nds` rom.

This repository makes most of its changes via `#ifdef`s and `#define`s so it should
still be possible to build the desktop native versions of VVVVVV here as well,
if you follow the original instructions.

Original README
---------------
How to Build
------------
VVVVVV's official desktop versions are built with the following environments:

- Windows: Visual Studio 2010
- macOS: Xcode CLT, currently targeting 10.9 SDK
- GNU/Linux: CentOS 7

The engine depends solely on [SDL2](https://libsdl.org/) 2.24.0+. All other dependencies
are statically linked into the engine. The development libraries for Windows can
be downloaded from SDL's website, Linux developers can find the dev libraries from their
respective repositories, and macOS developers should compile and install from source.
(If you're on Ubuntu and your Ubuntu is too old to have this SDL version, then
[see here](https://github.com/TerryCavanagh/VVVVVV/issues/618#issuecomment-968338212)
for workarounds.)

Since VVVVVV 2.4, git submodules are used for the
[third party libraries](https://github.com/TerryCavanagh/VVVVVV/tree/master/third_party).
After cloning, run `git submodule update --init` to set all of these up.
You can also use this command whenever the submodules need to be updated.

Steamworks support is included and the DLL is loaded dynamically, you do not
need the SDK headers and there is no special Steam or non-Steam version. The
current implementation has been tested with Steamworks SDK v1.46.

To build the Make and Play edition of the game, uncomment `#define MAKEANDPLAY`
in `MakeAndPlay.h`.

To generate the projects on Windows:
```
# Put your SDL2 folders somewhere nice!
mkdir build
cd build
cmake -A Win32 -G "Visual Studio 10 2010" .. -DSDL2_INCLUDE_DIRS="C:\SDL2-2.24.0\include" -DSDL2_LIBRARIES="C:\SDL2-2.24.0\lib\x86\SDL2;C:\SDL2-2.24.0\lib\x86\SDL2main"
```

Then to compile the game, open the solution and click Build.

For more detailed information and troubleshooting, see the [Compiling VVVVVV
Guide](https://vsix.dev/wiki/Guide:Compiling_VVVVVV_on_Windows_with_Visual_Studio)
on the Viki.

To generate everywhere else:
```
mkdir build
cd build
cmake ..
```

Then to compile the game, type `make`.

Including data.zip
------------
You'll need the data.zip file from VVVVVV to actually run the game! You can grab
it from your copy of the game, or you can just download it for free from the [Make
and Play](https://thelettervsixtim.es/makeandplay/) page. Put this file next to
your executable and the game should run.

This is intended for personal use only - our license doesn't allow you to
actually distribute this data.zip file with your own forks without getting
permission from us first. See [LICENSE.md](../LICENSE.md) for more details.
