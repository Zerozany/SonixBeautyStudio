find_package(Qt6 REQUIRED
    COMPONENTS
    Quick
    Qml
    Core
    QuickControls2
)

qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0002 NEW)
qt_policy(SET QTP0001 NEW)

qt_standard_project_setup(
    REQUIRES 6.3
)

qt_add_library(${PROJECT_NAME} STATIC)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Core
    Qt6::QuickControls2
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE "$<$<CONFIG:Release>:TRUE>$<$<NOT:$<CONFIG:Release>>:FALSE>"
    WIN32_EXECUTABLE "$<$<CONFIG:Debug>:FALSE>$<$<NOT:$<CONFIG:Debug>>:TRUE>"
)
