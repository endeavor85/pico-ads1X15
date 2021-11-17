add_executable(ads1X15-comparator-example
	comparator.cpp
	../../ads1X15.cpp
)

# Pull in pico_stdlib which pulls in commonly used features
target_link_libraries(ads1X15-comparator-example pico_stdlib hardware_i2c)

# enable stdio_usb
pico_enable_stdio_usb(ads1X15-comparator-example 1) 
pico_enable_stdio_uart(ads1X15-comparator-example 0) 

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(ads1X15-comparator-example)
