cmake_minimum_required(VERSION 3.21)
project(eonsimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(eonsimulator src/main.cpp include/event/Event.h src/event/EventNewCallArrivalErlangClass.cpp include/event/EventNewCallArrivalErlangClass.h src/event/EventCallServiceTermination.cpp include/event/EventCallServiceTermination.h src/network/Network.cpp include/network/Network.h src/Simulator.cpp include/Simulator.h src/Link.cpp include/Link.h include/tools/Logger.h include/network/structures/Benes4x4.h include/network/structures/TestCase2.h src/Connection.cpp include/Connection.h include/network/structures/SingleLink.h include/tools/Generator.h include/network/structures/TestCase1.h src/TrafficClassStatistics.cpp include/TrafficClassStatistics.h include/constants/Constants.h src/tools/Generator.cpp src/tools/Logger.cpp include/network/structures/ThreeSections4x4.h src/network/Structure.cpp include/network/Structure.h)
