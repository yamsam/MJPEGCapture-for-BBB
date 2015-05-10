cmake_minimum_required (VERSION 2.8)

project (mjpeg_capture)

# find OpenCV
find_package(OpenCV REQUIRED)
include_directories(OpenCV_INCLUDE_DIRS)

# find V4L2
find_path(V4L_INCLUDE_DIR NAMES libv4l2.h)
include_directories(V4L_INCLUDE_DIR)
find_library(V4L_LIB NAMES v4l2)

# Our sources
get_filename_component (my_folder . ABSOLUTE)
include_directories (${my_folder})

set (camera_sources
${my_folder}/camera.cpp
${my_folder}/MJPEGCapture.cpp)

set (test_sources
${my_folder}/test_opencv.cpp
)

set (face_sources
${my_folder}/facetrack.cpp
${my_folder}/MJPEGCapture.cpp
)

set (face_bench_sources
${my_folder}/facetrack_benchmark.cpp
${my_folder}/MJPEGCapture.cpp
)

set (bench_src
${my_folder}/mjpeg_benchmark.cpp
${my_folder}/MJPEGCapture.cpp)


add_executable(camera
	${camera_sources})

add_executable(test_opencv
${test_sources})

add_executable(face
${face_sources})

add_executable(face_bench
${face_bench_sources})

add_executable(bench
${bench_src})

target_link_libraries(camera
	${OpenCV_LIBS}
	${V4L_LIB})

target_link_libraries(test_opencv
	${OpenCV_LIBS})

target_link_libraries(face
	${OpenCV_LIBS}
	${V4L_LIB}
)

target_link_libraries(face_bench
	${OpenCV_LIBS}
	${V4L_LIB}
)

target_link_libraries(bench
	${OpenCV_LIBS}	${V4L_LIB} )

