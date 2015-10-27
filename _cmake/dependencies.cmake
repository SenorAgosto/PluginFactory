# include our cmake extensions
include(_cmake/AddLibrary/Dependencies.cmake)

# external libraries we're going to use. 
include(_cmake/dependencies/Boost.cmake)
include(_cmake/dependencies/dl.cmake)

# external libraries used for testing. 
include(_cmake/dependencies/UnitTest++.cmake)
