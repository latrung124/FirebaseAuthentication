cmake_minimum_required(VERSION 3.27.7)

project(Login-Module VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# SET(HEADER_FILES
# )

# SET(SOURCE_FILES
# )

# Define platform-specific required libraries
if(WIN32)
    set(REQUIRED_LIBS
        advapi32.lib
        ws2_32.lib
        crypt32.lib
    )
elseif(APPLE)
    # For macOS libraries, we still need to use find_library
    set(REQUIRED_LIBS
        pthread
        CoreFoundation
        Foundation
        Security
        GSS
        Kerberos
    )
    
    # Find macOS libraries
    foreach(LIB ${REQUIRED_LIBS})
        find_library(${LIB}_LIB ${LIB})
        if(NOT ${LIB}_LIB)
            message(FATAL_ERROR "Failed to find ${LIB}")
        endif()
    endforeach()
    
    # Update REQUIRED_LIBS to use the found library paths
    set(REQUIRED_LIBS
        ${pthread_LIB}
        ${CoreFoundation_LIB}
        ${Foundation_LIB}
        ${Security_LIB}
        ${GSS_LIB}
        ${Kerberos_LIB}
    )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

add_executable(Login-Module main.cpp)

add_subdirectory(third_party/firebase_cpp_sdk)

# Link the dependencies libraries

# Link the Firebase C++ SDK
target_link_libraries(Login-Module PUBLIC 
    firebase_auth 
    firebase_app
    ${REQUIRED_LIBS})

# Set the path to your google-services.json
set(GOOGLE_SERVICES_JSON "${CMAKE_CURRENT_SOURCE_DIR}/Resources/google-services.json")

# Verify the file exists
if(NOT EXISTS ${GOOGLE_SERVICES_JSON})
    message(FATAL_ERROR "Missing ${GOOGLE_SERVICES_JSON}")
endif()

# Generate the resource xml from google-services.json
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/res/values/google-services.xml"
    COMMAND ${PYTHON_EXECUTABLE}
            "${CMAKE_CURRENT_SOURCE_DIR}/third_party/firebase_cpp_sdk/generate_xml_from_google_services_json.py"
            --input="${GOOGLE_SERVICES_JSON}"
            --output="${CMAKE_CURRENT_BINARY_DIR}/res/values/google-services.xml"
    DEPENDS ${GOOGLE_SERVICES_JSON}
    COMMENT "Generating google-services.xml from google-services.json"
)