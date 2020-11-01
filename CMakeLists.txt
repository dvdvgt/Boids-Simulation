cmake_minimum_required(VERSION 3.17)
project(ParticleSystem)

find_package(SFML COMPONENTS graphics window system REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(include)

add_executable(ParticleSystem src/main.cpp include/Flock.h include/Particle.h include/Utils.h src/Particle.cpp src/Flock.cpp src/Utils.cpp include/Rule.h src/Rule.cpp)

target_link_libraries(ParticleSystem sfml-window sfml-graphics sfml-system)


