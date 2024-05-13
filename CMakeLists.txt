cmake_minimum_required(VERSION 3.28)
project(BusSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(BusSystem main.cpp
        Route.cpp
        Stop.cpp
        Passenger.cpp
        People.cpp
        Bus.hpp
        Bus.cpp
        MetroPass.cpp
        MetroPass.hpp
        Transaction.cpp
        Transaction.hpp)
