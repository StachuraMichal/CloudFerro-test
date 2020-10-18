cmake_minimum_required(VERSION 3.0.0)
project(EmployeesManager VERSION 0.1.0)

include(CTest)
enable_testing()



#add_executable(sample src/sample.cpp)
add_library(${PROJECT_NAME} src/server.cpp src/server.h)
#target_link_libraries(sample ${PROJECT_NAME} )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# <------------ add hiredis dependency --------------->
find_path(HIREDIS_HEADER hiredis)
target_include_directories(${PROJECT_NAME} PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(${PROJECT_NAME} ${HIREDIS_LIB})

# <------------ add redis-plus-plus dependency -------------->
# NOTE: this should be *sw* NOT *redis++*
find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(${PROJECT_NAME} PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(${PROJECT_NAME} ${REDIS_PLUS_PLUS_LIB})

# <------------ add pqlib dependency -------------->
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}  ${PQXX_LIB} ${PQ_LIB})




add_subdirectory(test)

