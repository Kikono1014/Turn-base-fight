cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(TBFight)


option(USE_STATIC "Use static library" ON)
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")


add_executable(TBFight
    main.cpp
    lib/Key/Key.cpp
    Controller/Controller.cpp
    Spell/Spell.cpp
    Unit/Unit.cpp
    Squad/Squad.cpp
) 


add_subdirectory(lib/nlohmann_json)

target_link_libraries(TBFight PRIVATE nlohmann_json)

