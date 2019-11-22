cmake_minimum_required(VERSION 2.8)

# Use (slightly) modern C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# By default build in release - less waiting!
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


# For OS X need X11 and PNG libraries
if (APPLE)
  # General flags - warnings should be heeded
  set(CMAKE_CXX_FLAGS "-Wall -Wextra")
  # Debug flags, assuming g++/clang++
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  # Release flags - optimise for speed
  message(STATUS "Compiling for OS X")
  add_definitions(-Dcimg_use_png=1)
  include_directories(AFTER "/opt/X11/include")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

  
  endif()

project( RayTracer )

add_executable( rayTracer 
    AmbientLightSource.cpp
    AmbientLightSource.h
    Camera.cpp
    Camera.h
    CImg.h
    Colour.cpp
    Colour.h
    Cube.cpp
    Cube.h
    Cylinder.cpp
    Cylinder.h
    Direction.cpp
    Direction.h
    DirectionalLightSource.cpp
    DirectionalLightSource.h
    ImageDisplay.cpp
    ImageDisplay.h
    LightSource.cpp
    LightSource.h
    Material.h
    Matrix.cpp
    Matrix.h
    NonCopyable.h
    Normal.cpp
    Normal.h
    Object.cpp
    Object.h
    PinholeCamera.cpp
    PinholeCamera.h
    Plane.cpp
    Plane.h
    Point.cpp
    Point.h
    PointLightSource.cpp
    PointLightSource.h
    Ray.h
    RayIntersection.h
    Scene.cpp
    Scene.h
    SceneReader.cpp
    SceneReader.h
    Sphere.cpp
    Sphere.h
    SpotLightSource.cpp
    SpotLightSource.h
    Transform.cpp
    Transform.h
    Vector.cpp
    Vector.h
    rayTracerMain.cpp
    utility.h
)

# For OS X need X11 and PNG libraries
if (APPLE)
  message(STATUS "LINKING for OS X")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/X11/lib -lX11 -lpng")
  message(STATUS "Linker flags = ${CMAKE_EXE_LINKER_FLAGS}")
endif()

