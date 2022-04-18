cmake_minimum_required(VERSION 3.21)
project(eonsimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(eonsimulator src/main.cpp src/event/Event.cpp include/event/Event.h src/event/EventNewCallArrival.cpp include/event/EventNewCallArrival.h src/event/EventCallServiceTermination.cpp include/event/EventCallServiceTermination.h src/network/Network.cpp include/network/Network.h src/Simulator.cpp include/Simulator.h src/Link.cpp include/Link.h src/tools/EventComparator.cpp include/tools/EventComparator.h src/tools/Logger.cpp include/tools/Logger.h src/network/Benes4x4.cpp include/network/Benes4x4.h src/network/TestCase2.cpp include/network/TestCase2.h src/Connection.cpp include/Connection.h)
