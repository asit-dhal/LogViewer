set(PROJECT_MANAGER_SRCS
    newprojecwizardpage.cpp
    project.cpp
    projectwizard.cpp
    projectattributeswizardpage.cpp
    remoteendwizardpage.cpp
    field.cpp
    fielddelegate.cpp
    fieldmodel.cpp
    fieldview.cpp
)

set(PROJECT_MANAGER_UIS
    newprojecwizardpage.ui
    projectattributeswizardpage.ui
    remoteendwizardpage.ui
)

add_library(projectmanager ${PROJECT_MANAGER_SRCS} ${PROJECT_MANAGER_UIS})
target_include_directories(projectmanager PRIVATE helper)

target_link_libraries(projectmanager
                    helper
                    Qt5::Widgets
                    Qt5::Core
                    Qt5::Gui
                    Qt5::Network
                    Qt5::Xml
)

include (CMakePrintHelpers)
cmake_print_properties(TARGETS projectmanager PROPERTIES INTERFACE_INCLUDE_DIRECTORIES IMPORTED_LOCATION)
cmake_print_properties(TARGETS projectmanager PROPERTIES INCLUDE_DIRECTORIES IMPORTED_LOCATION)
