#pragma once
#ifndef COVCAM_H
#define COVCAM_H

#include <Arduino.h>
#include <esp_camera.h>



enum COVCamPreset {
	M5StackCameraX      = 0,
	M5StackTimerCameraX = 1
};


enum COVCamFlipMode {
	COVCamNoFlip         = 0,
	COVCamFlipHorizontal = 1, 
	COVCamFlipVertical   = 2,
	COVCamFlipBoth       = 3
};

enum COVCamSpecialEffect {
	COVCamEffectNone      = 0,
	COVCamEffectNegative  = 1,
	COVCamEffectGrayscale = 2,
	COVCamEffectRedTint   = 3,
	COVCamEffectGreenTint = 4,
	COVCamEffectBlueTint  = 5,
	COVCamEffectSepia     = 6
};

enum COVCamWhiteBalanceMode {
	COVCamWhiteBalanceAuto   = 0,
	COVCamWhiteBalanceSunny  = 1,
	COVCamWhiteBalanceCloudy = 2,
	COVCamWhiteBalanceOffice = 3,
	COVCamWhiteBalanceHome   = 4
};

class COVCam {
public:
	COVCam();
	~COVCam();

	bool init(camera_config_t config);

	bool init(COVCamPreset camera,
		framesize_t resolution = FRAMESIZE_QVGA,
		uint8_t jpegQuality = 6);

	uint8_t* getFrameBuffer();
	uint8_t* capture();

	uint32_t getFrameBufferLength();
	uint16_t getFrameBufferHeight();
	uint16_t getFrameBufferWidth();
	
	bool flip(COVCamFlipMode flipMode);


	bool setContrast(int8_t level);          // -2 : 2
	int  getContrast();

	bool setBrightness(int8_t level);        // -2 : 2
	int  getBrightness();

	bool setSaturation(int8_t level);        // -2 : 2
	int  getSaturation();

	bool setSharpness(int8_t level);         // -2 : 2
	int  getSharpness();

	bool setAutoExposure(int8_t level);      // -2 : 2
	int  getAutoExposure();

	bool setDenoise(uint8_t level);
	uint8_t getDenoise();

	bool setJPEGQuality(uint8_t quality);        // 0 : 63
	uint8_t getJPEGQuality();

	bool setWhiteBalanceMode(COVCamWhiteBalanceMode mode); // 0 : 4
	COVCamWhiteBalanceMode getWhiteBalanceMode();

	bool setSpecialEffect(COVCamSpecialEffect effect);   // 0 : 6
	COVCamSpecialEffect getSpecialEffect();

	bool setWhiteBalance(bool enable);
	bool getWhiteBalance();

	bool setColorBar(bool enable);
	bool getColorBar();

	bool setLensCorrection(bool enable);
	bool getLensCorrection();

	bool setResolution(framesize_t resolution);
	framesize_t getResolution();


/*
	bool setGainceiling(gainceiling_t gainceiling); // 0 - 511

	bool setGainControl(bool enable);
	bool setExposureControl(bool enable);
	bool setAutomaticExposureControl2(bool enable);
	bool setAutomaticWhiteBalance(bool enable);
	bool setAutomatiGainControl(int value);
	bool setAutomaticExposureControl(int value);
	bool setDCW(bool enable);
	bool setBPC(bool enable);
	bool setWPC(bool enable);
	bool setRawGMA(bool enable);
*/



private:
	sensor_t*       m_pCameraSensor;
	camera_fb_t*    m_pCameraFrameBuffer;
	bool            m_isInitialized;
	esp_err_t       m_lastError;
	camera_config_t m_cameraConfig;

};

#endif
