cmake_minimum_required(VERSION 3.8.2)


################################
##  CONFIGURE THIS FILE HERE  ##
################################

set(EXTERNAL_DEPENDS
  Qt5Widgets
  Qt5PrintSupport
  #OpenCV
  )

set(EXTERNAL_DEPENDS_LIB
  Qt5::Widgets
  Qt5::PrintSupport
  Qt5::Core
  #${OpenCV_LIBS}
  )

set(INCLUDE_DIRECTORIES
  #${OpenCV_LIBS}
  )


###
### Define Macros
###
macro(resolve_pkg_name RESULT)
  FILE(GLOB INCLUDE_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
  get_filename_component(INCLUDE_NAME ${INCLUDE_DIR} NAME)
  SET(${RESULT} ${INCLUDE_NAME})
endmacro()

###
###Set Package Name
###
resolve_pkg_name(PACKAGE_NAME)
project(${PACKAGE_NAME})
message("Creating Package: ${PACKAGE_NAME}")

add_compile_options(-std=c++17)


## need this for qt auto generated headers to include!
set(CMAKE_INCLUDE_CURRENT_DIR ON)

foreach(DEPEND ${EXTERNAL_DEPENDS})
  find_package(${DEPEND} REQUIRED)
endforeach(DEPEND)

include_directories(
  include
  ${INCLUDE_DIRECTORIES}
)

###########
## Build ##
###########

file(GLOB HDRS
  "include/${PROJECT_NAME}/*.h"
)
file(GLOB SRCS
  "src/*.cpp"
  "src/*.hpp"
)
file(GLOB NODES
  "nodes/*.cpp"
)

###
### QT stuff
###
set(CMAKE_AUTOMOC ON)  #This will autogenerate qt gui stuff
set(CMAKE_AUTORCC ON)  #this needs to be on so cmake will know what to do with QT resource Files

#find all the qt UI stuff
file(GLOB_RECURSE UI
  "include/${PROJECT_NAME}/*.ui"
)

#make them into headers
qt5_wrap_ui (UI_HDRS  ${UI})

# find all resource files
file(GLOB QRC
  "rc/*.qrc"
)

###
### compile
###

message("buliding ${PROJECT_NAME} node: ")
foreach(NODE_FILE ${NODES})
  get_filename_component(NODE_NAME ${NODE_FILE} NAME_WE)
  message("  - " ${NODE_NAME})

  add_executable(${NODE_NAME} ${NODE_FILE} ${HDRS} ${SRCS} ${UI} ${QRC})
  target_link_libraries (${NODE_NAME} ${catkin_LIBRARIES} ${EXTERNAL_DEPENDS_LIB})
  target_include_directories(${NODE_NAME} PRIVATE "include/${PROJECT_NAME}/")

  list(APPEND NODE_LIST ${NODE_NAME})

endforeach(NODE_FILE)


###
### install
###

install(TARGETS ${NODE_LIST} DESTINATION bin)
