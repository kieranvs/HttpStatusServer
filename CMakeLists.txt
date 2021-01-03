cmake_minimum_required(VERSION 3.12)
project(HttpStatusServer VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ======== SimpleWebServer ========
add_subdirectory(dependencies/Simple-Web-Server)

# ======== Server ========
add_executable(
	HttpStatusServer
	src/server.cpp
)
target_include_directories(HttpStatusServer PRIVATE . dependencies)
target_link_libraries(HttpStatusServer PRIVATE simple-web-server)

# ======== Client ========
add_executable(
	HttpStatusClient
	src/client.cpp
)
target_include_directories(HttpStatusClient PRIVATE . dependencies)
target_link_libraries(HttpStatusClient PRIVATE simple-web-server)