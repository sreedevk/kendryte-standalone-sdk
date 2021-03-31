# Kendryte K210 standalone SDK

This is a fork of the official `kendryte-standalone-sdk` repository with a bunch of peripheral drivers & utililities.
The following is a list of additional Drivers Available in this fork.

1. U8G2 Kendryte K210 HAL   - https://github.com/sreedevk/u8g2-kendryte-sdk-hal
2. LCD1602 Driver for K210  - https://github.com/sreedevk/lcd-1602-kendryte-sdk
3. TM1638 Driver for K210   - https://github.com/sreedevk/tm1638-driver-kendryte-sdk

More drivers are being added & will be available in future.

## Usage

### Creating a New Project

If you want to start a new project, for instance, `hello_world`, you only need to:

- Linux and OSX

`mkdir` your project in `src/`, `cd src && mkdir hello_world`, then put your codes in it, enter SDK root directory and build it.

```bash
mkdir build && cd build
cmake .. -DPROJ=<ProjectName> -DTOOLCHAIN=/opt/riscv-toolchain/bin && make
```

- Windows

Download and install latest CMake.

[Download cmake-3.14.1-win64-x64.msi](https://github.com/Kitware/CMake/releases/download/v3.14.1/cmake-3.14.1-win64-x64.msi)

Download and install latest toolchain.

[Download kendryte-toolchain-win-i386-8.2.0-20190409.tar.xz](https://github.com/kendryte/kendryte-gnu-toolchain/releases/download/v8.2.0-20190409/kendryte-toolchain-win-i386-8.2.0-20190409.tar.xz)

Open a Windows Powershell, cd to Project directory.

`mkdir` your project in `src/`, `cd src && mkdir hello_world`, then put your codes in it, and build it.

```powershell
$env:Path="E:\kendryte-toolchain\bin;C:\Program Files\CMak
e\bin" +  $env:Path

mkdir build && cd build
cmake -G "MinGW Makefiles" ../../../..
make
```
You will get 2 key files, `hello_world` and `hello_world.bin`.

1. If you are using JLink to run or debug your program, use `hello_world`
2. If you want to flash it in UOG, using `hello_world.bin`, then using flash-tool(s) burn <ProjectName>.bin to your flash.

This is very important, don't make a mistake in files.

### Creating & adding a Third Party Library
If you are interested in developing third party libraries to be used with fork of kendryte-standalone-sdk, 
you can use this template repository:  
[KENDRYTE SDK THIRD PARTY MODULE TEMPLATE](https://github.com/sreedevk/kendryte-sdk-library-template)

or you can add the CMakeLists.third_party.example.txt as `CMakeLists.txt` in the root of your library directory. make sure to add all the header files in an `include folder`

Once you have the third party library ready, you can add it to this repository by simply running:  
```bash
git submodule add {your-lib-repo-link} third_party/{your-lib-name}/
```

and recompiling your code.
