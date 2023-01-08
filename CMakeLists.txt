cmake_minimum_required(VERSION 3.21)
project(eonsimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(eonsimulator src/main.cpp include/event/Event.h src/event/EventNewCallArrivalErlangClass.cpp include/event/EventNewCallArrivalErlangClass.h src/event/EventCallServiceTermination.cpp include/event/EventCallServiceTermination.h src/network/Network.cpp include/network/Network.h src/Simulator.cpp include/Simulator.h src/network/Link.cpp include/network/Link.h include/tools/Logger.h src/Connection.cpp include/Connection.h include/tools/Generator.h src/stats/TrafficClassStatistics.cpp include/stats/TrafficClassStatistics.h src/tools/Generator.cpp src/tools/Logger.cpp  src/network/Structure.cpp include/network/Structure.h src/tools/SimulationSettings.cpp include/tools/SimulationSettings.h src/stats/SingleSimulationResults.cpp include/stats/SingleSimulationResults.h src/stats/TrafficClassResultRatios.cpp include/stats/TrafficClassResultRatios.h src/stats/SimulationSetResults.cpp include/stats/SimulationSetResults.h src/stats/TrafficClassResults.cpp include/stats/TrafficClassResults.h include/tools/SeedsProvider.h src/tools/SeedsProvider.cpp)
