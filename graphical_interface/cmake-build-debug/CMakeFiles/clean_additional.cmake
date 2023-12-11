# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/graphical_interface_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/graphical_interface_autogen.dir/ParseCache.txt"
  "graphical_interface_autogen"
  )
endif()
