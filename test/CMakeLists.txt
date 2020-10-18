cmake_minimum_required(VERSION 3.0.0)

add_library(utilites utilites.cpp)
target_link_libraries(utilites ${PROJECT_NAME})

add_executable(test_add_employes test_add_employes.cpp)
target_link_libraries(test_add_employes utilites)

add_executable(test_check_cache test_check_cache.cpp)
target_link_libraries(test_check_cache utilites) 

target_include_directories(${PROJECT_NAME} PUBLIC ../src)

add_test(
    NAME test_add_employes
    COMMAND test_add_employes
)

add_test(
    NAME test_check_cache
    COMMAND test_check_cache
    
)

set_property( TEST test_check_cache PROPERTY RUN_SERIAL 1)
set_property( TEST test_add_employes PROPERTY RUN_SERIAL 1)
