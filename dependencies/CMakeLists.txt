message("-- Linking dependencies")

add_library(opencv_world451 SHARED IMPORTED GLOBAL)

set_property(TARGET opencv_world451 PROPERTY IMPORTED_LOCATION_RELEASE "${PROJECT_SOURCE_DIR}/dependencies/opencv/opencv_world451.dll")
set_property(TARGET opencv_world451 PROPERTY IMPORTED_LOCATION_DEBUG "${PROJECT_SOURCE_DIR}/dependencies/opencv/opencv_world451d.dll")

set_target_properties(opencv_world451 PROPERTIES LINKER_LANGUAGE CXX)