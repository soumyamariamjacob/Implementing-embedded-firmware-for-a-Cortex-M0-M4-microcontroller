//Here’s an example where an LED blinks using a FreeRTOS task:

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

void vLEDTask(void *pvParameters) {
    // Configure LED GPIO pin (Assuming pin PC13)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER |= GPIO_MODER_MODER13_0; // Output mode

    while (1) {
        // Toggle LED
        GPIOC->ODR ^= GPIO_ODR_ODR13;
        
        // Delay for 500 ms
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void) {
    // Initialize system
    SystemInit();
    
    // Create FreeRTOS task
    xTaskCreate(vLEDTask, "LED Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    
    // Start scheduler
    vTaskStartScheduler();
    
    // Main loop should not be reached
    while (1);
}
