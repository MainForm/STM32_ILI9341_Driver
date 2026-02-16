# STM32 ILI9341 Driver

ILI9341 TFT LCD driver for the **STM32F429I-DISC1** onboard display.

This project is intended for the display wiring used on STM32F429I-DISC1.
If you use another board, verify the schematic and pin mapping first.

## Requirements

- STM32 HAL / CubeMX generated target (`stm32cubemx`)
- CMake 3.22+
- C++20

## Add Driver With CMake

In your top-level `CMakeLists.txt`:

```cmake
# CubeMX-generated target first
add_subdirectory(cmake/stm32cubemx)

# Driver
add_subdirectory(Drivers/ILI9341)

# Your application target
target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
    ili9341
)
```

`Drivers/ILI9341/CMakeLists.txt` creates the static library target:

- `ili9341`

and links it against:

- `stm32cubemx`

## Header Include

```cpp
#include "ILI9341.hpp"
```

## Note

On STM32F429I-DISC1, MISO is not connected to the onboard ILI9341, so read operations are not available in the same way as fully wired SPI displays.
