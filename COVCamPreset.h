#pragma once
#ifndef COVCAMPRESET_H
#define COVCAMPRESET_H

#include <esp_camera.h>

// -----IMPORTANT ----- When adding new cameras, KEEP THE FIELD ORDER (otherwise errors!)

// M5 Stack Camera X
// URL: https://docs.m5stack.com/#/en/unit/m5camera_x
const camera_config_t M5StackCameraXConfig = {
	.pin_pwdn = -1,
	.pin_reset = 15,

	.pin_xclk = 27,

	.pin_sscb_sda = 22,
	.pin_sscb_scl = 23,

	.pin_d7 = 19,
	.pin_d6 = 36,
	.pin_d5 = 18,
	.pin_d4 = 39,
	.pin_d3 = 5,
	.pin_d2 = 34,
	.pin_d1 = 35,
	.pin_d0 = 32,
	.pin_vsync = 25,
	.pin_href = 26,
	.pin_pclk = 21,

	.xclk_freq_hz = 20000000,

	.ledc_timer = LEDC_TIMER_0,
	.ledc_channel = LEDC_CHANNEL_0,

	.pixel_format = PIXFORMAT_JPEG,
	.frame_size = FRAMESIZE_QVGA,
	.jpeg_quality = 6,
	.fb_count = 1
};



// M5 Stack Timer Camera X
// URL: https://docs.m5stack.com/#/en/unit/timercam_x
const camera_config_t M5StackTimerCameraXConfig = {
	.pin_pwdn = -1,
	.pin_reset = 15,

	.pin_xclk = 27,

	.pin_sscb_sda = 25,
	.pin_sscb_scl = 23,

	.pin_d7 = 19,
	.pin_d6 = 36,
	.pin_d5 = 18,
	.pin_d4 = 39,
	.pin_d3 = 5,
	.pin_d2 = 34,
	.pin_d1 = 35,
	.pin_d0 = 32,
	.pin_vsync = 22,
	.pin_href = 26,
	.pin_pclk = 21,

	.xclk_freq_hz = 20000000,

	.ledc_timer = LEDC_TIMER_0,
	.ledc_channel = LEDC_CHANNEL_0,

	.pixel_format = PIXFORMAT_JPEG,
	.frame_size = FRAMESIZE_QVGA,
	.jpeg_quality = 6,
	.fb_count = 1
};



// ESP32-CAM
// URL: https://randomnerdtutorials.com/esp32-cam-camera-pin-gpios/
const camera_config_t ESP32CAMConfig = {
	.pin_pwdn = 32,
	.pin_reset = -1,

	.pin_xclk = 0,

	.pin_sscb_sda = 26,
	.pin_sscb_scl = 27,

	.pin_d7 = 35,
	.pin_d6 = 34,
	.pin_d5 = 39,
	.pin_d4 = 36,
	.pin_d3 = 21,
	.pin_d2 = 19,
	.pin_d1 = 18,
	.pin_d0 = 5,
	.pin_vsync = 25,
	.pin_href = 23,
	.pin_pclk = 22,

	.xclk_freq_hz = 20000000,

	.ledc_timer = LEDC_TIMER_0,
	.ledc_channel = LEDC_CHANNEL_0,

	.pixel_format = PIXFORMAT_JPEG,
	.frame_size = FRAMESIZE_QVGA,
	.jpeg_quality = 6,
	.fb_count = 1
};




#endif
