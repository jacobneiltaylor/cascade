Cascade
=======

**A C++11 Thread Management Library**

Introduction
------------

Cascade is a library designed to streamline and automate the usage of threads in a high-level fashion, allowing multithreaded applications to scale automatically on supported platforms. The library is designed to allow developers to focus on their actual business logic, instead of also having to worry about the low-level details of writing multithreaded code.

Supported Features
------------------

* Cross-platform: this library is designed to work across Windows, MacOSX and Linux. If it doesn't work on your platform, we want to hear about it!
* Limited dependencies: This library only depends on C++11 and the STL. No boost or other 3rd party dependancies!
* High-level interface: The library is completely object oriented, and the threadManager class (the main entry point to the libraries functionality) is coded as a singleton. No need to play hot potato with pointers (and debug the associated memory access violations)!
* Automatic resource management: Threads are spun up when new work is assigned and released when complete, so your application automatically uses only as much system resources as absolutely necessary.
* Registerable mutexes: Mutexes can be created by registering them with the threadManager, which means they are then easily accessible in all workers, automatically.

Future Features
---------------

Currently, we are working on making the build process straightforward. We are in the process of writing makefiles and ensuring the library builds smoothly across all supported platforms (Windows, Mac OSX, Linux). See the "Compiling" section for more details on building the library now. Once this process is complete, focus will shift back to feature development.

In the future, we hope to add advanced features including reserved threads, persistent (service) threads, integrated message passing, automatic mutex release on thread completion and more.

Compiling
---------

The library has been successfully built on the following platform releases and compilers at this early stage:

* Windows: Windows 10 (compiler: MSVC14, runtime: MSVC14)
* Linux: CentOS 7 (compiler: LLVM Clang 3.4.2, runtime: GCC 4.8.5), Fedora 23 (compiler: LLVM Clang 3.7.0, runtime: GCC 5.3.1)

Tests on other platform releases and compilers are forthcoming.

In the long term, the targeted compilers for each platform will be as follows:

* Windows: Microsoft Visual C++ Compiler
* Mac OSX: LLVM Clang
* Linux: LLVM Clang, GNU Compiler Collection

Currently, if building on Linux, we highly recommend using LLVM Clang as that is what the development team is using at this early stage. An important "gotcha" to keep in mind is that on Linux the std::thread class is implemented using pthread and requires the pthread library explicitly linked in.

Licensing
---------

This code is registered under the GNU LGPL. This allows you to use this library in proprietary software, provided you return any modifications back to the community. If you would like to use our software, but the license is incompatible with your business requirements or policies, we offer supported, proprietary licensing on request.
