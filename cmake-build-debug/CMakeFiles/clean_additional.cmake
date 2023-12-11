# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "app_interfaces/graphical_interface/CMakeFiles/graphical_interface_autogen.dir/AutogenUsed.txt"
  "app_interfaces/graphical_interface/CMakeFiles/graphical_interface_autogen.dir/ParseCache.txt"
  "app_interfaces/graphical_interface/graphical_interface_autogen"
  )
endif()
