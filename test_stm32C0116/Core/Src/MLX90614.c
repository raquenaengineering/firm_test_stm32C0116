#include "mlx90614.h"

// Initialize MLX90614 (check if device is responsive)
HAL_StatusTypeDef MLX90614_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t dummy;
    return HAL_I2C_Mem_Read(hi2c, MLX90614_ADDR << 1, MLX90614_TOBJ1, 1, &dummy, 1, HAL_MAX_DELAY);
}

// Read temperature from a specific register (returns in °C)
HAL_StatusTypeDef MLX90614_ReadTemp(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, float *temp) {
    uint8_t data[2];
    int16_t raw_temp;
    HAL_StatusTypeDef status;

    status = HAL_I2C_Mem_Read(hi2c, MLX90614_ADDR << 1, reg_addr, 1, data, 2, HAL_MAX_DELAY);
    if (status != HAL_OK) {
        return status;
    }

    raw_temp = (data[1] << 8) | data[0];
    *temp = raw_temp * 0.02f - 273.15f;  // Convert to °C
    return HAL_OK;
}

// Get temperature (simplified wrapper)
float MLX90614_GetTemp(I2C_HandleTypeDef *hi2c, uint8_t temp_type) {
    float temp = 0.0f;
    uint8_t reg;

    switch (temp_type) {
        case 0: reg = MLX90614_TOBJ1; break;  // Object 1
        case 1: reg = MLX90614_TAMB;  break;  // Ambient
        case 2: reg = MLX90614_TOBJ2; break;  // Object 2
        default: return -273.15f;             // Invalid
    }

    if (MLX90614_ReadTemp(hi2c, reg, &temp) != HAL_OK) {
        return -273.15f;  // Error
    }
    return temp;
}
