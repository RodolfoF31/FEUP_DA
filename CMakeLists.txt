cmake_minimum_required(VERSION 3.24)
project(ProjetoDA)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjetoDA src/main.cpp src/Utils/MenuMan.cpp src/Utils/MenuMan.h src/Utils/FileMan.cpp src/Utils/FileMan.h src/Models/Network.cpp src/Models/Network.h src/Models/Station.cpp src/Models/Station.h)
