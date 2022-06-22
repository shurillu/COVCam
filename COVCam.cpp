#include "COVCam.h"
#include "COVCamPreset.h"



COVCam::COVCam() {
	m_isInitialized      = false;
	m_pCameraFrameBuffer = NULL;
	m_pCameraSensor      = NULL;
	m_lastError          = ESP_OK;
	memset(&m_cameraConfig, 0, sizeof(m_cameraConfig));
}

COVCam::~COVCam() {
	if (m_pCameraFrameBuffer != NULL) {
		esp_camera_fb_return(m_pCameraFrameBuffer);
		m_pCameraFrameBuffer = NULL;
	}
	if (m_isInitialized)
		esp_camera_deinit();
}

bool COVCam::init(camera_config_t cameraConfig) {

	memset(&m_cameraConfig, 0, sizeof(m_cameraConfig));
	memcpy(&m_cameraConfig, &cameraConfig, sizeof(cameraConfig));

	m_lastError = esp_camera_init(&m_cameraConfig);
	if (m_lastError != ESP_OK) {
		Serial.printf("Unable to init the camera driver. Error code: 0x%02X\n", m_lastError); // -------------------------------------------------
		return false;
	}
	m_isInitialized = true;
	m_pCameraSensor = esp_camera_sensor_get();
	return true;
}

bool COVCam::init(COVCamPreset camera, framesize_t resolution, uint8_t jpegQuality, uint8_t frameBuffers) {
	camera_config_t cameraConfig;

	memset(&cameraConfig, 0, sizeof(cameraConfig));

	if (M5StackCameraX == camera) {
		memcpy(&cameraConfig, &M5StackCameraXConfig, sizeof(M5StackCameraXConfig));
		Serial.println("M5Stack CameraX selected.");
	}
	else if (M5StackCameraModelA == camera) {
		memcpy(&cameraConfig, &M5StackCameraModelAConfig, sizeof(M5StackCameraModelAConfig));
		Serial.println("M5Stack Camera (model A) selected.");
	}
	else if (M5StackTimerCameraX == camera) {
		memcpy(&cameraConfig, &M5StackTimerCameraXConfig, sizeof(M5StackTimerCameraXConfig));
		Serial.println("M5Stack Timer CameraX selected.");
	}
	else if (ESP32CAM == camera) {
		memcpy(&cameraConfig, &ESP32CAMConfig, sizeof(ESP32CAMConfig));
		Serial.println("ESP32-CAM selected.");
	}
	else {
		m_lastError = ESP_FAIL;
		return false;
	}

	cameraConfig.frame_size = resolution;
	cameraConfig.pixel_format = PIXFORMAT_JPEG;
	cameraConfig.jpeg_quality = jpegQuality;
	cameraConfig.fb_count = frameBuffers;
	cameraConfig.xclk_freq_hz = 20000000;
	return init(cameraConfig);
}

uint8_t* COVCam::getFrameBuffer() {
	if (NULL == m_pCameraFrameBuffer)
		return NULL;
	return m_pCameraFrameBuffer->buf;
}

uint8_t* COVCam::capture() {
	if (m_pCameraFrameBuffer != NULL) {
		esp_camera_fb_return(m_pCameraFrameBuffer);
		m_pCameraFrameBuffer = NULL;
	}
	m_pCameraFrameBuffer = esp_camera_fb_get();
	return getFrameBuffer();
}

uint32_t COVCam::getFrameBufferLength() {
	if (NULL == m_pCameraFrameBuffer)
		return 0;
	return m_pCameraFrameBuffer->len;
}

uint16_t COVCam::getFrameBufferHeight() {
	if (NULL == m_pCameraFrameBuffer)
		return 0;
	return m_pCameraFrameBuffer->height;
}

uint16_t COVCam::getFrameBufferWidth() {
	if (NULL == m_pCameraFrameBuffer)
		return 0;
	return m_pCameraFrameBuffer->width;
}

bool COVCam::flip(COVCamFlipMode flipMode) {
	if (NULL == m_pCameraSensor)
		return false;

	m_pCameraSensor->set_hmirror(m_pCameraSensor, flipMode & COVCamFlipHorizontal);
	m_pCameraSensor->set_vflip(m_pCameraSensor, (flipMode & COVCamFlipVertical) >> 1);
	return true;
}

bool COVCam::setContrast(int8_t level) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_contrast(m_pCameraSensor, level);
	return true;
}
int COVCam::getContrast() {	
	if (NULL == m_pCameraSensor)
		return 0;
	return m_pCameraSensor->status.contrast;
}

bool COVCam::setBrightness(int8_t level) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_brightness(m_pCameraSensor, level);
	return true;
}
int COVCam::getBrightness() {
	if (NULL == m_pCameraSensor)
		return 0;
	return m_pCameraSensor->status.brightness;
}

bool COVCam::setSaturation(int8_t level) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_saturation(m_pCameraSensor, level);
	return true;
}
int COVCam::getSaturation() {
	if (NULL == m_pCameraSensor)
		return 0;
	return m_pCameraSensor->status.saturation;
}

bool COVCam::setSharpness(int8_t level) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_sharpness(m_pCameraSensor, level);
	return true;
}
int COVCam::getSharpness() {
	if (NULL == m_pCameraSensor)
		return 0;
	return m_pCameraSensor->status.sharpness;
}

bool COVCam::setAutoExposure(int8_t level) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_ae_level(m_pCameraSensor, level);
	return true;
}
int COVCam::getAutoExposure() {
	if (NULL == m_pCameraSensor)
		return 0;
	return m_pCameraSensor->status.ae_level;
}

bool COVCam::setDenoise(uint8_t level) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_denoise(m_pCameraSensor, level);
	return true;
}
uint8_t COVCam::getDenoise() {
	if (NULL == m_pCameraSensor)
		return 0;
	return m_pCameraSensor->status.denoise;
}

bool COVCam::setJPEGQuality(uint8_t quality) {
	if (NULL == m_pCameraSensor)
		return false;
	if (quality > 63)
		quality = 63;
	else if (quality < m_cameraConfig.jpeg_quality)
		quality = m_cameraConfig.jpeg_quality;
	m_pCameraSensor->set_quality(m_pCameraSensor, quality);
	return true;;
}
uint8_t COVCam::getJPEGQuality() {
	if (NULL == m_pCameraSensor)
		return 0;
	return m_pCameraSensor->status.quality;
}

bool COVCam::setWhiteBalanceMode(COVCamWhiteBalanceMode mode) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_wb_mode(m_pCameraSensor, (int)mode);
	return true;
}
COVCamWhiteBalanceMode COVCam::getWhiteBalanceMode() {
	if (NULL == m_pCameraSensor)
		return COVCamWhiteBalanceAuto;
	return (COVCamWhiteBalanceMode)m_pCameraSensor->status.wb_mode;
}

bool COVCam::setSpecialEffect(COVCamSpecialEffect effect) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_special_effect(m_pCameraSensor, (int)effect);
	return true;
}
COVCamSpecialEffect COVCam::getSpecialEffect() {
	if (NULL == m_pCameraSensor)
		return COVCamEffectNone;
	return (COVCamSpecialEffect)m_pCameraSensor->status.special_effect;
}

bool COVCam::setWhiteBalance(bool enable) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_whitebal(m_pCameraSensor, enable);
	return true;
}
bool COVCam::getWhiteBalance() {
	if (NULL == m_pCameraSensor)
		return false;
	return m_pCameraSensor->status.awb;
}

bool COVCam::setColorBar(bool enable) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_colorbar(m_pCameraSensor, enable);
	return true;
}
bool COVCam::getColorBar() {
	if (NULL == m_pCameraSensor)
		return false;
	return m_pCameraSensor->status.colorbar;
}

bool COVCam::setLensCorrection(bool enable) {
	if (NULL == m_pCameraSensor)
		return false;
	m_pCameraSensor->set_lenc(m_pCameraSensor, enable);
	return true;
}
bool COVCam::getLensCorrection() {
	if (NULL == m_pCameraSensor)
		return false;
	return m_pCameraSensor->status.lenc;
}

bool COVCam::setResolution(framesize_t resolution) {
	if (NULL == m_pCameraSensor)
		return false;
	if (resolution > m_cameraConfig.frame_size)
		resolution = m_cameraConfig.frame_size;
	else if (resolution < 0)
		resolution = (framesize_t)0;
	m_pCameraSensor->set_framesize(m_pCameraSensor, resolution);
	return true;
}
framesize_t COVCam::getResolution() {
	if (NULL == m_pCameraSensor)
		return FRAMESIZE_INVALID;
	return m_pCameraSensor->status.framesize;
}


