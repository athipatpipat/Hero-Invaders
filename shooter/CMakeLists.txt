cmake_minimum_required(VERSION 3.3)
project(shooter CXX)
include(.eecs211/cmake/CMakeLists.txt)

# Defines a variable to stand for the two .cpp files that implement
# the model.
set(MODEL_COMMON
        src/geometry.cpp
        src/laser.cpp
        src/model.cpp)


# Adds a program named `brick_out` built from src/brick_out.cpp and
# the common model files.
add_program(shooter
        src/main.cpp
        src/ui.cpp
        ${MODEL_COMMON})
target_link_libraries(shooter ge211)

# Adds a test program named `model_test` built from test/model_test.cpp
# and the common model files.
add_test_program(model_test
        test/model_test.cpp
        ${MODEL_COMMON})
target_link_libraries(model_test ge211)
