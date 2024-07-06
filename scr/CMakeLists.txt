# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(StormRotate)  # Set your project name here
enable_language(C)

# Add your source files here
set(SOURCE_FILES
    main.c
    Func_DataIO.c
    Func_Rotate.c
    Func_Raster.c
    Func_Filelist.c
)


# Add the executable target
add_executable(StormRotate ${SOURCE_FILES})
# Link against the math library
target_link_libraries(StormRotate m)


## cmake -G "MinGW Makefiles" ..
## mingw32-make
