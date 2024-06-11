project("sonarcloud-test")

add_executable(${PROJECT_NAME}
    main.cpp
    misra_rules.cpp
    misra_rules.h
    sonar_rules.cpp
    sonar_rules.h
)

#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_OPTIONS "-Wsign-conversion")
