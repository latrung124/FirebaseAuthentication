cmake_minimum_required(VERSION 3.27.7)

project(Login-Module VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Set tool chains
set(VCPKG_EXECUTABLE $ENV{VCPKG_DIR}/vcpkg)

# Enable or disable log info
option(ENABLE_LOG_INFO "Enable log info" ON)

if(ENABLE_LOG_INFO)
    add_definitions(-DLOG_INFO_ENABLED)
endif()

# Define the source directory as a macro
if(DEFINED ENV{FIREBASE_CONFIG_PATH})
    add_definitions(-DFIREBASE_CONFIG_PATH="$ENV{FIREBASE_CONFIG_PATH}")
else()
    add_definitions(-DFIREBASE_CONFIG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/config")
endif()

set(ZLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows/include")
set(ZLIB_LIBRARY "${CMAKE_SOURCE_DIR}/vcpkg_installed/vcpkg/pkgs/lib_x64-windows/bin")

# Define the base path for vcpkg installations
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/vcpkg/pkgs/curl_x64-windows/share/curl")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/vcpkg/pkgs/curl_x64-windows/share/curl")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/vcpkg/pkgs/nlohmann-json_x64-windows/share/nlohmann_json")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/vcpkg/pkgs/cpp-httplib_x64-windows/share/httplib")

# Find required libraries
find_package(ZLIB REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(httplib CONFIG REQUIRED)

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

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Interface/IFirebaseCloud.h

    ${CMAKE_CURRENT_SOURCE_DIR}/App/FirebaseApp.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/FirebaseCloudImpl.h

    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AppAuthStateListener.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AppAuthentication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/Utils/AuthUtils.h

    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AuthProvider/GoogleOauth.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AuthProvider/AbstractExternalAuthProvider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AuthProvider/AbstractInternalAuthProvider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AuthProvider/EmailPwAuthProvider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AuthProvider/GoogleAuthProvider.h)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/App/FirebaseApp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App/FirebaseCloudImpl.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AppAuthStateListener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AppAuthentication.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AuthProvider/GoogleOauth.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AuthProvider/EmailPwAuthProvider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Authentication/AuthProvider/GoogleAuthProvider.cpp)

add_executable(Login-Module
    ${HEADER_FILES}
    ${SOURCE_FILES}
    main.cpp)

# Target include directories
target_include_directories(Login-Module PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/App
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Interface
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/firebase_cpp_sdk/include
    ${CMAKE_CURRENT_BINARY_DIR}/res/values
    ${ZLIB_INCLUDE_DIR}
    ${CURL_INCLUDE_DIRS}
    ${nlohmann_json_INCLUDE_DIRS})

# Set link directories
set(FIREBASE_LIB_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/firebase_cpp_sdk/libs/Release)

# Link the Firebase C++ SDK
target_link_libraries(Login-Module PUBLIC 
    ${FIREBASE_LIB_DIR}/firebase_auth.lib
    ${FIREBASE_LIB_DIR}/firebase_app.lib
    ${REQUIRED_LIBS}
    CURL::libcurl
    nlohmann_json nlohmann_json::nlohmann_json
    httplib::httplib)

# Set the path to your google-services.json
set(SOURCE_GOOGLE_SERVICES_JSON "${CMAKE_CURRENT_SOURCE_DIR}/Resources/config/google-services.json")
set(DES_GOOGLE_SERVICES_JSON "${CMAKE_CURRENT_BINARY_DIR}/Resources/config/google-services.json")

if(NOT EXISTS ${SOURCE_GOOGLE_SERVICES_JSON})
    message(FATAL_ERROR "Missing ${GOOGLE_SERVICES_JSON}")
endif()

# Define a custom target to run vcpkg install
add_custom_target(run_vcpkg_install
    COMMAND ${VCPKG_EXECUTABLE} install
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running vcpkg install to ensure dependencies are installed"
)

# Define a custom target to copy google-services.json to the binary directory
add_custom_command(
    OUTPUT ${DES_GOOGLE_SERVICES_JSON}
    COMMAND ${CMAKE_COMMAND} -E copy
            ${SOURCE_GOOGLE_SERVICES_JSON}
            ${DES_GOOGLE_SERVICES_JSON}
    DEPENDS ${SOURCE_GOOGLE_SERVICES_JSON}
    COMMENT "Copying config.json to binary directory"
)