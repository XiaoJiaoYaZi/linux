cmake_minimum_required(VERSION 2.8)

project(linux_7)

link_libraries(gdbm)
link_libraries(mysqlclient)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(gdbm_compat)
target_link_libraries(gdbm)
target_link_libraries(mysqlclient)

