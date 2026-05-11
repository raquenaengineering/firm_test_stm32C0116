#ifndef MLX90614_H
#define MLX90614_H

#include "stm32c0xx_hal.h"

// MLX90614 I2C address (7-bit)
#define MLX90614_ADDR 0x5A  // Default address (0x5A or 0x5B)

// MLX90614 RAM/EEPROM addresses
#define MLX90614_TOBJ1  0x07  // Object 1 temperature
#define MLX90614_TAMB   0x06  // Ambient temperature
#define MLX90614_TOBJ2  0x08  // Object 2 temperature

// Function prototypes
HAL_StatusTypeDef MLX90614_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef MLX90614_ReadTemp(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, float *temp);
float MLX90614_GetTemp(I2C_HandleTypeDef *hi2c, uint8_t temp_type);  // temp_type: 0=TOBJ1, 1=TAMB, 2=TOBJ2

#endif // MLX90614_H
