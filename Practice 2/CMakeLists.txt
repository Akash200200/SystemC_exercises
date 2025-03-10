add_executable(task2
    src/main.cpp
    src/MovingAverage.h
)

target_include_directories(task2
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(task2
    PRIVATE ${SYSTEMC_LIBRARY}
)