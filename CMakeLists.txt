cmake_minimum_required(VERSION 3.14)

project(toxiproxy)

if (POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
endif ()

set(TOXIPROXY_HEADER_DIR ${PROJECT_SOURCE_DIR}/include/toxiproxy)
set(TOXIPROXY_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source/)
set(TOXIPROXY_SRCS ${TOXIPROXY_SOURCE_DIR}/toxiproxy_client.cc ${TOXIPROXY_SOURCE_DIR}/toxiproxy_http_client.cc ${TOXIPROXY_SOURCE_DIR}/toxic.cc
  ${TOXIPROXY_SOURCE_DIR}/toxic_type.cc ${TOXIPROXY_SOURCE_DIR}/toxic_list.cc ${TOXIPROXY_SOURCE_DIR}/timeout.cc ${TOXIPROXY_SOURCE_DIR}/slow_close.cc ${TOXIPROXY_SOURCE_DIR}/slicer.cc
  ${TOXIPROXY_SOURCE_DIR}/reset_peer.cc ${TOXIPROXY_SOURCE_DIR}/proxy.cc ${TOXIPROXY_SOURCE_DIR}/limit_data.cc ${TOXIPROXY_SOURCE_DIR}/latency.cc ${TOXIPROXY_SOURCE_DIR}/bandwidth.cc)
set(TOXIPROXY_HEADERS ${TOXIPROXY_HEADER_DIR}/toxiproxy_client.h ${TOXIPROXY_HEADER_DIR}/toxiproxy_http_client.h ${TOXIPROXY_HEADER_DIR}/toxic.h
  ${TOXIPROXY_HEADER_DIR}/toxic_type.h ${TOXIPROXY_HEADER_DIR}/toxic_list.h ${TOXIPROXY_HEADER_DIR}/timeout.h ${TOXIPROXY_HEADER_DIR}/slow_close.h ${TOXIPROXY_HEADER_DIR}/slicer.h
  ${TOXIPROXY_HEADER_DIR}/reset_peer.h ${TOXIPROXY_HEADER_DIR}/proxy.h ${TOXIPROXY_HEADER_DIR}/limit_data.h ${TOXIPROXY_HEADER_DIR}/latency.h ${TOXIPROXY_HEADER_DIR}/bandwidth.h)

include(FetchContent)

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)

FetchContent_Declare(
  httplib
  URL https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.10.2.zip
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
option(BUILD_TOXIPROXY_AS_SHARED  "Build the Toxiproxy client library as a shared libary." OFF)

if (WIN32)
  set(TOXIPROXY_SRCS ${TOXIPROXY_SRCS} ${TOXIPROXY_HEADERS})
endif (WIN32)

FetchContent_MakeAvailable(httplib json)

if (BUILD_TOXIPROXY_AS_SHARED)
  add_library(toxiproxy SHARED ${TOXIPROXY_SRCS})
else ()
  add_library(toxiproxy STATIC ${TOXIPROXY_SRCS})
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC
  ${httplib_SOURCE_DIR}
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include>
  )

target_link_libraries(
  toxiproxy
  nlohmann_json::nlohmann_json
)

install(FILES ${TOXIPROXY_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/toxiproxy)
