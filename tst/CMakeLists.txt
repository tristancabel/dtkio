### CMakeLists.txt --- 
## 
## Version: 
## 
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkIoDataModelTests)


## ###################################################################
## Build tree setup
## ###################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkIoDataModelTest.h
  dtkIoDataModelHdf5Test.h
  )

set(${PROJECT_NAME}_SOURCES
  dtkIoDataModelTest.cpp
  dtkIoDataModelHdf5Test.cpp)


if(DTK_BUILD_DISTRIBUTED)
  set(${PROJECT_NAME}_HEADERS
    ${${PROJECT_NAME}_HEADERS}
    dtkIoDataModelPHdf5Test.h
    dtkIoDataModelPHdf5Runnable.h
    )

  set(${PROJECT_NAME}_SOURCES
    ${${PROJECT_NAME}_SOURCES}
    dtkIoDataModelPHdf5Test.cpp
    )
endif()


## ###################################################################
## Input - introspected
## ###################################################################

create_test_sourcelist(
    ${PROJECT_NAME}_SOURCES_TST
    ${PROJECT_NAME}.cpp
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Build rules
## ###################################################################

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES_TST}
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Test)
qt5_use_modules(${PROJECT_NAME} Xml)

target_link_libraries(${PROJECT_NAME}
  dtkIo
  dtkLog)

if(DTK_BUILD_DISTRIBUTED)
  target_link_libraries(${PROJECT_NAME} dtkDistributed)
  target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})
endif(DTK_BUILD_DISTRIBUTED)

## ###################################################################
## Test rules
## ###################################################################

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.h5"  "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

add_test(dtkIoDataModelTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkIoDataModelTest)
add_test(dtkIoDataModelHdf5Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkIoDataModelHdf5Test)

if(DTK_BUILD_DISTRIBUTED)
  add_test(dtkIoDataModelPHdf5Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkIoDataModelPHdf5Test)
endif()
######################################################################
### CMakeLists.txt ends here
