cmake_minimum_required(VERSION 2.6)

set(location_suffix "")

project(tracer)

find_package(DynamoRIO 7.0)
if (NOT DynamoRIO_FOUND)
  message(FATAL_ERROR "DynamoRIO package required to build")
endif(NOT DynamoRIO_FOUND)

function (add_client name source_file_list extension_list)
  add_library(${name} SHARED ${source_file_list})
  configure_DynamoRIO_client(${name})
  foreach (ext ${extension_list})
    use_DynamoRIO_extension(${name} ${ext})
  endforeach (ext)

  # Provide a hint for how to use the client
  if (NOT DynamoRIO_INTERNAL OR NOT "${CMAKE_GENERATOR}" MATCHES "Ninja")
    get_target_property(path ${name} LOCATION${location_suffix})
    add_custom_command(TARGET ${name}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND}
      ARGS -E echo "Usage: pass to drconfig or drrun: -c ${path}"
      VERBATIM)
  endif ()
endfunction (add_client)

configure_DynamoRIO_global(OFF ON)

add_client(tracer "tracer.c" "drmgr;drreg;drutil;drx")
