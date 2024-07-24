# Wallpepora
Wallpepora is a C++ desktop application to make grid squares collages of images creation easier. It works on Linux OS but if you want it to works on
others OS you need to compile it yourself.

# Install and run 
To install the application, you just need to decompress the tar.gz archive where you want.
Then run the executable inside the wallpepora directory :

    ./wallpepora

You may need to give the permissions to run the executable, you can do it by running the command :

    chmod a+x wallpepora

# Depedencies

* [wxWidgets 3.2.5 - to create the GUI](https://github.com/wxWidgets/wxWidgets)

* [OpenCV 4.9.0 - for the images processing and collages creation](https://github.com/opencv/opencv)

* [Google Test - for writing application's tests](https://github.com/google/googletest)

# Compilation

To compile the project, use CMake, there is already a CMakeLists.txt to compile the project in the source code.

    mkdir build
    cd build
    cmake ..
