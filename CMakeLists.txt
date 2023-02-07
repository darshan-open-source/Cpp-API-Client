cmake_minimum_required(VERSION 3.25.1)

project(netlibAPI)
include_directories(include/)
ADD_LIBRARY( netlibAPI STATIC
             src/api.cpp )
