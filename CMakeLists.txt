project("sonarcloud-test")

add_executable(${PROJECT_NAME}
    main.cpp
    misra_rules.cpp
    misra_rules.h
    sonar_rules.cpp
    sonar_rules.h
)
