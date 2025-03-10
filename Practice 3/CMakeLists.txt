add_executable(task3
    src/main.cpp
    src/SimpleFifo.h
)

target_include_directories(task3
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(task3
    PRIVATE ${SYSTEMC_LIBRARY}
)