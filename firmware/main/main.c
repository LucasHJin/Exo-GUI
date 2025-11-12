/*
TWAI == CAN. esp just refers CAN as TWAI.
refer this official doc: https://docs.espressif.com/projects/esp-idf/en/release-v4.3/esp32/api-reference/peripherals/twai.html

Also, you must open 'this' projct in vs code, not via Exo_GUI. Otherwie vs code does not recognize the esp libraries.
*/

#include <stdio.h>
#include <stdbool.h>
#include <driver/twai.h>
#include <driver/gpio.h>

//TODO: configure gpio
#define tx_gpio GPIO_NUM_0
#define rx_gpio GPIO_NUM_1

void send_msg(uint32_t id, uint8_t *data, uint8_t length, bool extended, uint32_t timeout_ms);
twai_message_t* receive_msg(uint32_t timeout_ms);
void stop_driver();
void uninstall_driver();

void app_main(void)
{
    //init configs
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(tx_gpio, rx_gpio, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    //install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
        printf("Driver istalled\n");
    } else {
        printf("Failed to install driver\n");
        return;
    }

    //start driver
    if (twai_start() == ESP_OK) {
        printf("Driver started\n");
    } else {
        printf("Failed to start driver\n");
        return;
    }

    //TODO: send data in a loop or so
}

/**
 * @brief Send a CAN message via TWAI
 * 
 * @param id       CAN ID (standard 11-bit or extended 29-bit)
 * @param data     Pointer to data bytes to send
 * @param length   Number of bytes in data (0-8)
 * @param extended  0 = standard frame, 1 = extended frame
 * @param timeout_ms Timeout in milliseconds for sending
 */
void send_msg(uint32_t id, uint8_t *data, uint8_t length, bool extended, uint32_t timeout_ms) {
    //configure message to transmit
    twai_message_t msg;
    msg.identifier = id;
    msg.extd = extended;
    msg.data_length_code = length;

    for (int i = 0; i < length; i ++) {
        msg.data[i] = data[i];
    }

    //queue message for transmission
    esp_err_t res = twai_transmit(&msg, pdMS_TO_TICKS(timeout_ms));
    if (res == ESP_OK) {
        ESP_LOGI("CAN message sent (ID: 0x%03X, DLC: %d)", id, length);
    } else {
        ESP_LOGE("Failed to send CAN message (ID: 0x%03X)", id);
    }
}

twai_message_t* receive_msg(uint32_t timeout_ms) {
    //wait for message to be received
    twai_message_t msg;
    esp_err_t res = twai_receive(&msg, pdMS_TO_TICKS(timeout_ms));
        
    if (res != ESP_OK) {
        printf("Failed to receive message\n");
        return NULL;
    }

    return &msg;
}

void stop_driver() {
    if (twai_stop() == ESP_OK) {
        printf("Driver stopped\n");
    } else {
        printf("Failed to stop driver\n");
    }
}

void uninstall_driver() {
    if (twai_driver_uninstall() == ESP_OK) {
        printf("Driver uninstalled\n");
    } else {
        printf("Failed to uninstall driver\n");
    }
}