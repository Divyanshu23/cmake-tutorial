add_library(adder adder.cpp adder.hpp) 

install(TARGETS adder DESTINATION lib)
install(FILES adder.hpp DESTINATION include)