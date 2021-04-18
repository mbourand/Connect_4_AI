cmake_minimum_required(VERSION 3.10)

project(app)

file(GLOB APP_SRC
	"srcs/*.cpp"
	"incs/*.hpp"
)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(app ${APP_SRC})
target_link_libraries(app PRIVATE
	sfml-system
	sfml-window
	sfml-graphics
)
target_include_directories(app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/incs")

set_target_properties(app PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
if (MSVC)
	target_compile_options(app PRIVATE "/Zc:__cplusplus")
	set_target_properties(app PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	string (FIND VCPKG_TARGET_TRIPLET "-windows-static" POS_TRIPLET)
	if (POS_TRIPLET EQUAL -1)
		set(MSVC_STATIC OFF CACHE BOOL "Force MSVC CRT static")
	else()
		set(MSVC_STATIC ON CACHE BOOL "Force MSVC CRT static")
	endif()
	if (MSVC_STATIC)
		set(CompilerFlags
			CMAKE_CXX_FLAGS
			CMAKE_CXX_FLAGS_DEBUG
			CMAKE_CXX_FLAGS_RELEASE
			CMAKE_C_FLAGS
			CMAKE_C_FLAGS_DEBUG
			CMAKE_C_FLAGS_RELEASE
		)
		foreach(CompilerFlag ${CompilerFlags})
			string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
		endforeach()
	endif()
endif()
