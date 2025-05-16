#pragma once

// Reads from potmeter when button is pushed, updates globalValue
void Task_ReadValue(void* pvParameters);

// Creates the task
void Init_Task_ReadValue();