cmake_minimum_required(VERSION 3.21)
project(eonsimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(eonsimulator src/main.cpp include/event/Event.h src/event/EventNewCallArrivalErlangClass.cpp include/event/EventNewCallArrivalErlangClass.h src/event/EventCallServiceTermination.cpp include/event/EventCallServiceTermination.h src/network/Network.cpp include/network/Network.h src/Simulator.cpp include/Simulator.h src/Link.cpp include/Link.h include/tools/Logger.h src/Connection.cpp include/Connection.h include/tools/Generator.h src/TrafficClassStatistics.cpp include/TrafficClassStatistics.h include/constants/Constants.h src/tools/Generator.cpp src/tools/Logger.cpp  src/network/Structure.cpp include/network/Structure.h)
