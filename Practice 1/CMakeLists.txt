add_executable(task1
    src/main.cpp
    src/RSLatch.h
)

target_include_directories(task1
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(task1
    PRIVATE ${SYSTEMC_LIBRARY}
)