cmake_minimum_required(VERSION 3.5.0)

project(path_tracing)

add_executable(path_tracing)

set(HEADERS
    source/Core/Assert.h

    source/Image/Image.h
    source/Image/stb_image.h
    source/Image/stb_image_write.h

    source/Math/Color.h
    source/Math/Intersect.h
    source/Math/Math.h
    source/Math/Numbers.h
    source/Math/Ray.h
    source/Math/Tri.h
    source/Math/Vector.h

    source/BVH.h
    source/Util.h
)

set(SOURCES
    source/Image/Image.cpp

    source/BVH.cpp
    source/Util.cpp

    source/main.cpp
)

target_sources(path_tracing PRIVATE ${SOURCES} ${HEADERS})

target_compile_features(path_tracing PUBLIC cxx_std_20)
