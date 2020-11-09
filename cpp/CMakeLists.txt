cmake_minimum_required(VERSION 3.10.2)
project("cmake_test")
set(CMAKE_BUILD_TYPE Debug)

#include_directories(../my_funcs)
#file(GLOB funcs "../my_funcs/*.cpp")
#file(GLOB m "../*cpp")
#file(GLOB source_code "../*")
#add_executable(main ../review_cpp.cc ${funcs})
#set (CMAKE_CXX_STANDARD 17)

message("CMAKE_SYSTEM: ${CMAKE_SYSTEM}")
message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SYSTEM_VERSION: ${CMAKE_SYSTEM_VERSION}")
message("CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}")

if (UNIX)
	message("\tUNIX")
else()
	message("\tNot UNIX")
endif()

if (${CMAKE_SYSTEM} MATCHES Linux)
	message("\tLINUX")
else()
	message("\tNot Linux")
endif()

if (${CMAKE_SYSTEM} MATCHES LinuxD)
	add_definitions(-Ddefined_in_cmake=1)
else()
	add_definitions(-Ddefined_in_cmake=0)
endif()

set(HAVE_NCCL xx)
if (HAVE_NCCL)
	message("here ${HAVE_NCCL}")
endif()

if (HAVE_NCCL STREQUAL "xx" AND ${HAVE_NCCL} STREQUAL "xx")
	message("strequal")
endif()

message("== ENV: $ENV{CUDA_VISIBLE_DEVICES} $ENV{CUDNN_VERSION}")

set(my_list "I;love;you")
message ("my_list: ${my_list}")

foreach(l ${my_list})
	message("\t${l}")
endforeach()

message("================")
foreach (var i love you 1 2 3 +;=;^ fun) # arguments are seperated by space or semi-colon
	message("\t${var}")
endforeach()
message("==================")
foreach(var RANGE 4)
	message("\t${var}") # 0-4
endforeach()
message("=============")
foreach(var RANGE 2 4) 
	message("\t:" ${var}) # no space will show
endforeach()
message("============")
foreach(var RANGE 2 8 3) #have to upper case
	message("\t: "${var})
endforeach()
message("============")
set(a "1;2;3;sd")
foreach (var ${a} "1;2;3;sd") # don't put them inside the quotes
	message("\t: "${var})
endforeach()
message("========== f: ${f}")
set(a "i")
set(b "love")
set(c "you")

foreach (var in ITEMS a b c d e ff)
	if (DEFINED ${var})
		message("\t${var}")
	else()
		# create new variable
		set(${var} "${var}_new")
	endif()
endforeach()

message("d: ${d}; e ${e}; ff: ${ff}")

# if a variable is set to empty, then it is not defined
set(zls_xx $ENV{HOROVOD_CPU_OPERATIONS})
message("${zls_xx}")
#message() # This should not be empty, but it can be ""
if (DEFINED zls_xx)
	message("zls_xx is defined: ${zls_xx}")
endif()

message("returning from here")
return()




#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") #message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_BINARY_DIR}")
# where to store the output file after make
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set(LIBRARY_OUTPUT_PATH "./")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./")

file(GLOB_RECURSE ALL_H "my_funcs/*.h")
message("All header files: ${ALL_H}")
file(GLOB ALL_CC "my_funcs/*.cc")
message("All cpp source files: ${ALL_CC}")

set(FILES "")
set(FILES_LIST "I LOVE YOU")
foreach(cc ${ALL_CC})
	#get_filename_component(f_name ${cc} PATH)
	#get_filename_component(f_name ${cc} NAME_WE)
	get_filename_component(f_name ${cc} NAME)
	message("\t${cc} -> ${f_name}")
	set(FILES "${FILES} ${f_name}")
	list(APPEND FILES_LIST ${f_name})
endforeach()
message("\n\t${FILES}")
message("\n\t${FILES_LIST}")
set(FILES_LIST "${FILES_LIST};${FILES_LIST}")
message("\n\t${FILES_LIST}")
list(REMOVE_DUPLICATES FILES_LIST) #remove duplicates
message("\n\t${FILES_LIST}")

add_library(my_sum SHARED "../my_funcs/my_func_1.cc")
add_executable("${PROJECT_NAME}_main" "../review_cpp.cc") # "./my_funcs/my_func_1.cc")
target_link_libraries("${PROJECT_NAME}_main" my_sum)

