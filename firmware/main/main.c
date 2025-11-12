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
twai_message_t receive_msg(uint32_t timeout_ms);
void stop_driver();
void uninstall_driver();
void set_pos(float pos, float vel, float torq, float vel_scale, float torq_scale, uint32_t timeout_ms);
void set_pos_default(float pos, float vel, float torq, uint32_t timeout_ms);
void set_vel(float vel, float torq, uint32_t timeout_ms);
void set_torque(float torq, uint32_t timeout_ms);
float get_pos_estimate(uint32_t timeout_ms);
float get_vel_estimate(uint32_t timeout_ms);

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

    //TODO: send command in a loop
    while (1) {
        
    }
}

/**
 * @brief Send a CAN message via TWAI
 * 
 * @param id       CAN ID (standard 11-bit or extended 29-bit)
 * @param data     Pointer to data bytes to send
 * @param length   Number of bytes in data (0-8) (size of data)
 * @param extended  0 = standard frame, 1 = extended frame
 * @param timeout_ms Timeout in milliseconds for sending
 */
void send_msg(uint32_t id, uint8_t *data, uint8_t length, bool extended, uint32_t timeout_ms) {
    //configure message to transmit
    twai_message_t msg;
    msg.identifier = id;
    msg.extd = extended;
    msg.data_length_code = length;
    memcpy(msg.data, data, length);

    //queue message for transmission
    esp_err_t res = twai_transmit(&msg, pdMS_TO_TICKS(timeout_ms));
    if (res == ESP_OK) {
        printf("CAN message sent (ID: %d, len: %d)", id, length);
    } else {
        printf("Failed to send CAN message (ID: %d)", id);
    }
}

twai_message_t receive_msg(uint32_t timeout_ms) {
    //wait for message to be received
    twai_message_t msg;
    esp_err_t res = twai_receive(&msg, pdMS_TO_TICKS(timeout_ms));
        
    if (res != ESP_OK) {
        printf("Failed to receive message\n");
        msg.identifier = -1;
    }

    return msg;
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

void set_pos(float pos, float vel, float torq, float vel_scale, float torq_scale, uint32_t timeout_ms) {
    uint8_t data[8]; //always send 8 bytes data

    //allocate pos float into first 4 bytes of data (float is 4 bytes)
    memcpy(&data[0], &pos, 4);

    //desired feedforward velocity
    int16_t vel_ff = (int16_t) (vel * vel_scale);
    //split 16 bits into 8 bits
    data[4] = vel_ff & 0xFF; //store the lower 8 bits
    data[5] = (vel_ff >> 8) & 0xFF; //shift 8 bits to the right and store the upper 8 bits

    //desired feedforward torque
    int16_t torq_ff = (int16_t) (torq * torq_scale);
    data[6] = torq_ff & 0xFF;
    data[7] = (torq_ff >> 8) & 0xFF;

    send_msg(0x0c, data, 8, false, timeout_ms);
}

void set_pos_default(float pos, float vel, float torq, uint32_t timeout_ms) {
    set_pos(pos, vel, torq, 1.0, 1.0, timeout_ms);
}

void set_vel(float vel, float torq, uint32_t timeout_ms) {
    uint8_t data[8]; 
    memcpy(&data[0], &vel, 4); //float is 4 bytes
    memcpy(&data[4], &torq, 4);
    send_msg(0x0d, data, 8, false, timeout_ms);
}

void set_torque(float torq, uint32_t timeout_ms) {
    uint8_t data[8];
    memcpy(&data[0], torq, 4);
    send_msg(0x0e, data, 8, false, timeout_ms);
}

float get_pos_estimate(uint32_t timeout_ms) {
    //send reqeust for estimated encoder pos value
    send_msg(0x09, NULL, 0, false, timeout_ms);

    //receive message
    twai_message_t rx = receive_msg(timeout_ms);
    if (rx.identifier == -1) return 0.0;

    float pos;
    memcpy(&pos, rx.data, 4);
    return pos;
}

float get_vel_estimate(uint32_t timeout_ms) {
    send_msg(0x09, NULL, 0, false, timeout_ms);

    twai_message_t rx = receive_msg(timeout_ms);
    if (rx.identifier == -1) return 0.0;

    float vel;
    memcpy(&vel, rx.data, 4);
    return vel;
}