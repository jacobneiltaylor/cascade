Cascade
=======

**A C++11 Thread Management Library**

Introduction
------------

Cascade is a library designed to streamline and automate the usage of threads in a high-level fashion, allowing multithreaded applications to scale automatically on supported platforms. The library is designed to allow developers to focus on their actual business logic, instead of also having to worry about the low-level details of writing multithreaded code.

Supported Features
------------------

* Cross-platform: this library is designed to work across Windows, MacOSX and Linux. If it doesn't work on your platform, we want to hear about it!
* Limited dependencies: This library only depends on C++11 and the STL. No boost, pthreads or WinAPI required! 
* High-level interface: The library is completely object oriented, and the threadManager class (the main entry point to the libraries functionality) is coded as a singleton. No need to play hot potato with pointers (and debug the associated memory access violations)!
* Automatic resource management: Threads are spun up when new work is assigned and released when complete, so your application automatically uses only as much system resources as absolutely necessary.

Future Features
---------------

In the future, we hope to add advanced features including reserved threads, persistent (service) threads, integrated message passing, dynamically registered mutexes and more.

Licensing
---------

This code is registered under the GNU LGPL. This allows you to use this library in proprietary software, provided you return any modifications back to the community. If you would like to use our software, but the license is incompatible with your business requirements or policies, we offer supported, proprietary licensing on request.
