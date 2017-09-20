cmake_minimum_required(VERSION 3.6)
project(Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    cl.command.1.tlog
    CL.read.1.tlog
    CL.write.1.tlog
    link-cvtres.read.1.tlog
    link-cvtres.write.1.tlog
    link-rc.read.1.tlog
    link-rc.write.1.tlog
    link.command.1.tlog
    link.read.1.tlog
    link.write.1.tlog
    sort_array_puz.lastbuildstate
    sort_array_puz.log
    sort_array_puz.obj
    stdafx.obj
    vc110.pdb)

add_executable(Release ${SOURCE_FILES})