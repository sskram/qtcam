/*
 * nilecam_cu30.cpp -- Handling special feature of seecamcu30 camera
 * Copyright © 2015  e-con Systems India Pvt. Limited
 *
 * This file is part of Qtcam.
 *
 * Qtcam is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Qtcam is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Qtcam. If not, see <http://www.gnu.org/licenses/>.
 */

#include "nilecam_cu30.h"

NILECAM_CU30::NILECAM_CU30(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief NILECAM_CU30::setSpecialEffectsNileCam - setting special effects to the camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::setSpecialEffectsNileCam(const specialEffects &specialEffect)
{

    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* set camera control code */
    g_out_packet_buf[2] = SET_SPECIAL_EFFECT; /* set special effect code */
    g_out_packet_buf[3] = specialEffect; /* set special effect */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_SPECIAL_EFFECT &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::setDenoiseValueNileCam - setting denoise value to the camera
 * @param deNoiseVal - denoise value
 * return true - success /false - failure
 */
bool NILECAM_CU30::setDenoiseValueNileCam(int deNoiseVal)
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* set camera control code */
    g_out_packet_buf[2] = SET_DENOISE_CONTROL; /* set denoise control code */
    g_out_packet_buf[3] = deNoiseVal; /* set denoise value */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_DENOISE_CONTROL &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::getSpecialEffectsNileCam - get effect mode set in camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getSpecialEffectsNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* set camera control code */
    g_out_packet_buf[2] = GET_SPECIAL_EFFECT; /* get special effect code */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==GET_SPECIAL_EFFECT &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit sendEffectMode(g_in_packet_buf[2]);
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::getDenoiseValueNileCam - get denoise value from camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getDenoiseValueNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* set camera control code */
    g_out_packet_buf[2] = GET_DENOISE_CONTROL; /* get denoise code */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==GET_DENOISE_CONTROL &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit sendDenoiseValue(g_in_packet_buf[2]);
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::getSceneModeNileCam - getting scene mode from the camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getSceneModeNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = GET_SCENEMODE_NILECAM_CU30; /* get scene mode command */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==GET_SCENEMODE_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit sceneModeValue(g_in_packet_buf[2]);
            return true;
        }
    }
    return false;
}


/**
 * @brief NILECAM_CU30::setSceneModeNileCam - setting scene mode to the camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::setSceneModeNileCam(const sceneModes &sceneMode)
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* Camera control id */
    g_out_packet_buf[2] = SET_SCENEMODE_NILECAM_CU30; /* Set scene mode command */
    g_out_packet_buf[3] = sceneMode; /* Scene mode to set */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_SCENEMODE_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::setExpRoiModeNileCam - Set ROI auto exposure to camera
 * @param camROIAutoExposureMode - ROI mode
 * @param vidResolnWidth - preview resolution width
 * @param vidResolnHeight - preview resolution height
 * @param xCord - mouse xCordinate from preview
 * @param yCord - mouse yCordinate from preview
 * @param winSize - ROI window size
 * return true - success /false - failure
 */
bool NILECAM_CU30::setExpRoiModeNileCam(camROIAutoExpMode see3camAutoexpROIMode, uint vidResolnWidth, uint vidResolnHeight, uint xCord, uint yCord, QString winSize)
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //((Input - InputLow) / (InputHigh - InputLow)) * (OutputHigh - OutputLow) + OutputLow // map resolution width and height -  0 to 255

    double outputLow = 0;
    double outputHigh = 255;
    double inputXLow = 0;
    double inputXHigh = vidResolnWidth-1;
    double inputXCord = xCord;
    int outputXCord = ((inputXCord - inputXLow) / (inputXHigh - inputXLow)) * (outputHigh - outputLow) + outputLow;

    double inputYLow = 0;
    double inputYHigh = vidResolnHeight-1;
    double inputYCord = yCord;
    int outputYCord = ((inputYCord - inputYLow) / (inputYHigh - inputYLow)) * (outputHigh - outputLow) + outputLow;

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = SET_EXP_ROI_MODE_NILECAM_CU30; /* set exposure ROI command */
    g_out_packet_buf[3] = see3camAutoexpROIMode; /* exposure ROI mode to set */

    if(see3camAutoexpROIMode == AutoExpManual){
        g_out_packet_buf[4] = outputXCord; // x cord
        g_out_packet_buf[5] = outputYCord; // y cord
        g_out_packet_buf[6] = winSize.toUInt(); // window size
    }

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_EXP_ROI_MODE_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {
            return true;
        }
    }
    return false;
}


/**
 * @brief NILECAM_CU30::getExpRoiModeNileCam - get ROI auto exposure mode and window size
 * return true - success /false - failure
 */
bool NILECAM_CU30::getExpRoiModeNileCam(){

    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = GET_EXP_ROI_MODE_NILECAM_CU30; /* get exposure ROI mode  */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]== GET_EXP_ROI_MODE_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {
            emit roiAutoExpModeValue(g_in_packet_buf[2], g_in_packet_buf[5]);
            return true;
        }
    }
    return false;
}

/**
 * @brief See3CAM_130::setBurstLengthNileCam - set burst length in camera
 * @param burstLength - burst length - no of images to be taken.
 * return true - success /false - failure
 */
bool NILECAM_CU30::setBurstLengthNileCam(uint burstLength){

    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = SET_BURST_LENGTH_NILECAM_CU30; /* set burst length command */
    g_out_packet_buf[3] = burstLength; /* burst length value to set */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]== SET_BURST_LENGTH_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::getBurstLengthNileCam - get burst length from camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getBurstLengthNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = GET_BURST_LENGTH_NILECAM_CU30; /* get burst length mode  */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==GET_BURST_LENGTH_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit burstLengthValue(g_in_packet_buf[2]);
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::setQFactorNileCam - set QFactor in camera
 * @param qFactor.
 * return true - success /false - failure
 */
bool NILECAM_CU30::setQFactorNileCam(uint qFactor){
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = SET_Q_FACTOR_NILECAM_CU30; /* set qfactor command */
    g_out_packet_buf[3] = qFactor; /* qfactor value */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_Q_FACTOR_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::getQFactorNileCam - get QFactor from camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getQFactorNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = GET_Q_FACTOR_NILECAM_CU30; /* get qFactor value */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]== GET_Q_FACTOR_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit qFactorValue(g_in_packet_buf[2]);
            return true;
        }
    }
    return false;
}


/**
 * @brief NILECAM_CU30::setFlipModeNileCam - Setting orientation
*/
bool NILECAM_CU30::setFlipModeNileCam(bool horzModeSel, bool vertiModeSel)
{

    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera control for see3cam_30 camera */
    g_out_packet_buf[2] = SET_ORIENTATION_NILECAM_CU30; /* set flip mode for 30 camera */
    if(horzModeSel && vertiModeSel){
        g_out_packet_buf[3] = SET_ORIENTATION_BOTHFLIP_ENABLE_NILECAM_CU30 ; /* both flip enable */
    }else if(horzModeSel && !vertiModeSel){
        g_out_packet_buf[3] = SET_ORIENTATION_HORZFLIP_NILECAM_CU30; /* horizontal flip only mode */
    }else if(!horzModeSel && vertiModeSel){
        g_out_packet_buf[3] = SET_ORIENTATION_VERTFLIP_NILECAM_CU30 ; /* vertical flip only mode */
    }else
        g_out_packet_buf[3] = SET_ORIENTATION_BOTHFLIP_DISABLE_NILECAM_CU30 ; /* both flip disable */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_ORIENTATION_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}




/**
 * @brief NILECAM_CU30::getFlipModeNileCam - getting flip mode from the camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getFlipModeNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera control id */
    g_out_packet_buf[2] = GET_ORIENTATION_NILECAM_CU30; /* Get orientation command */


    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==GET_ORIENTATION_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit flipMirrorModeChanged(g_in_packet_buf[2]);
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::setFrameRatectrlValue - setting frame rate control value
 * @param frameRate
 * @return true/false
 */
bool NILECAM_CU30::setFrameRateValueNileCam(uint frameRate)
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* set camera control code */
    g_out_packet_buf[2] = SET_FRAME_RATE_NILECAM_CU30; /* set framerate control code */
    g_out_packet_buf[3] = frameRate; /* set framerate value */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_FRAME_RATE_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::getFrameRateValueNileCam - get frameRate control value from camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getFrameRateValueNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* set camera control code */
    g_out_packet_buf[2] = GET_FRAME_RATE_NILECAM_CU30; /* get frame rate code */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==GET_FRAME_RATE_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit frameRateCtrlValueReceived(g_in_packet_buf[2]);
            return true;
        }
    }
    return false;
}


/**
 * @brief NILECAM_CU30::setExposureCompensationNileCam - setting exposure compensation
 * @param exposureCompValue - exposure compensation value
 * @return true/false
 */
bool NILECAM_CU30::setExposureCompensationNileCam(unsigned int exposureCompValue){
    if(EXPOSURECOMP_MIN > exposureCompValue || EXPOSURECOMP_MAX < exposureCompValue){
        emit indicateExposureValueRangeFailure("Failure", "Given exposure compensation value is invalid");
        return false;
    }

    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = SET_EXPOSURE_COMPENSATION_NILECAM_CU30; /* set exposure compensation command */
    g_out_packet_buf[3] = (u_int8_t)((exposureCompValue & 0xFF000000) >> 24);
    g_out_packet_buf[4] = (u_int8_t)((exposureCompValue & 0x00FF0000) >> 16);
    g_out_packet_buf[5] = (u_int8_t)((exposureCompValue & 0x0000FF00) >> 8);
    g_out_packet_buf[6] = (u_int8_t)((exposureCompValue & 0x000000FF) >> 0);

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            emit indicateCommandStatus("Failure", "Failed to set exposure compensation value");
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_EXPOSURE_COMPENSATION_NILECAM_CU30 && g_in_packet_buf[6]==SET_SUCCESS) {\
            emit indicateCommandStatus("Success", "Exposure compensation value is set successfully");
            return true;
        }
    }
    return false;
}


/**
 * @brief See3CAM_130::getExposureCompensationNileCam - getting exposure compensation
 * @return true/false
 */
bool NILECAM_CU30::getExposureCompensationNileCam(){
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* set camera control code */
    g_out_packet_buf[2] = GET_EXPOSURE_COMPENSATION_NILECAM_CU30; /* get exposure compensation code */

    unsigned int exposureCompValue;

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]== GET_EXPOSURE_COMPENSATION_NILECAM_CU30 && g_in_packet_buf[6]==GET_SUCCESS) {\
            exposureCompValue = (((u_int8_t)g_in_packet_buf[2]) << 24)
                                | (((u_int8_t)g_in_packet_buf[3]) << 16)
                                | (((u_int8_t)g_in_packet_buf[4]) << 8)
                                | (((u_int8_t)g_in_packet_buf[5]) << 0);
            emit exposureCompValueReceived(exposureCompValue);
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::setFaceDetectionRectNileCam - setting face detection rectangle
 * @param enableFaceDetectRect - enable / disable face detect rectangle
 * @param embedData - Enable / Disable embed data
 * @param overlayRect - Enable / Disable overlay Rectangle
 * @return true/false
 */
bool NILECAM_CU30::setFaceDetectionRectNileCam(bool enableFaceDetectRect, bool embedData, bool overlayRect){

    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = SET_FACE_DETECT_RECT_NILECAM_CU30; /* set face detect Rect command */

    if(enableFaceDetectRect)
        g_out_packet_buf[3] = ENABLE_FACE_RECT_NILECAM_CU30; /* enable face Rect */
    else
        g_out_packet_buf[3] = DISABLE_FACE_RECT_NILECAM_CU30; /* disable face Rect*/

    if(embedData)
        g_out_packet_buf[4] = ENABLE_EMBED_DATA_NILECAM_CU30; /* enable embed data */
    else
        g_out_packet_buf[4] = DISABLE_EMBED_DATA_NILECAM_CU30; /* disable embed data */

    if(overlayRect)
        g_out_packet_buf[5] = ENABLE_OVERLAY_RECT_NILECAM_CU30; /* enable overlay rect */
    else
        g_out_packet_buf[5] = DISABLE_OVERLAY_RECT_NILECAM_CU30; /* disable overlay rect */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_FACE_DETECT_RECT_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::getFactDetectMode - get face detect mode[ disable/enable ] from camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getFaceDetectionRectNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = GET_FACE_DETECT_RECT_NILECAM_CU30; /* get face detect mode command */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1] == GET_FACE_DETECT_RECT_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit faceDetectModeValue(g_in_packet_buf[2], g_in_packet_buf[3], g_in_packet_buf[4]);
            return true;
        }
    }
    return false;
}


/**
 * @brief NILECAM_CU30::setSmileDetectionStateNileCam - setting smile detection rectangle
 * @param enableSmileDetect - enable / disable smile detect
 * @param embedData - Enable / Disable embed data
 * @param thresholdValue - smile threshold value
 * @return true/false
 */
bool NILECAM_CU30::setSmileDetectionStateNileCam(bool enableSmileDetect, bool embedData, uint thresholdValue,  bool smileTrigger){
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }
    if((SMILE_THRESHOLD_MIN > thresholdValue || SMILE_THRESHOLD_MAX < thresholdValue) && enableSmileDetect){
        emit indicateSmileThresholdRangeFailure("Failure", "Given smile detection threshold value is invalid.");
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = SET_SMILE_DETECTION_NILECAM_CU30; /* set face detect Rect command */

    if(enableSmileDetect)
        g_out_packet_buf[3] = ENABLE_SMILE_DETECT_NILECAM_CU30; /* enable smile detect */
    else
        g_out_packet_buf[3] = DISABLE_SMILE_DETECT_NILECAM_CU30; /* disable smile detect */

    g_out_packet_buf[4] = thresholdValue; // Setting threshold value

    if(embedData)
        g_out_packet_buf[5] = ENABLE_EMBED_DATA_NILECAM_CU30; /* enable embed data */
    else
        g_out_packet_buf[5] = DISABLE_EMBED_DATA_NILECAM_CU30; /* disable embed data */

    if(smileTrigger)
        g_out_packet_buf[6] = ENABLE_SMILE_TRIGGER_NILECAM_CU30; /* enable smile trigger  */
    else
        g_out_packet_buf[6] = DISABLE_SMILE_TRIGGER_NILECAM_CU30; /* disable smile trigger */
    
    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            emit indicateCommandStatus("Failure", "Failed to set smile detection threshold");
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_SMILE_DETECTION_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            emit indicateCommandStatus("Success", "Smile detection threshold is set successfully");
            return true;
        }
    }
    return false;
}


/**
 * @brief NILECAM_CU30::getSmileDetectionStateNileCam - get smile detect mode[ disable/enable ] from camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getSmileDetectionStateNileCam()
{
    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* Camera control id */
    g_out_packet_buf[2] = GET_SMILE_DETECTION_NILECAM_CU30; /* Get smile detection */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==GET_SMILE_DETECTION_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {\
            emit smileDetectModeValue(g_in_packet_buf[2], g_in_packet_buf[3], g_in_packet_buf[4], g_in_packet_buf[5]);
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::restoreDefaultNileCam - set all the values to default in camera
 * @return true/false
 */
bool NILECAM_CU30::restoreDefaultNileCam(){

    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = SET_TO_DEFAULT_NILECAM_CU30; /* set to default command */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SET_TO_DEFAULT_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}


/**
 * @brief NILECAM_CU30::enableDisableFaceRectangle - disable RF rectangle before capture image and enable back after capturing image
 * and disable before recording video and enable back.
 * @param enableRFRect - true / false
 * @return true/false
 */
bool NILECAM_CU30::enableDisableFaceRectangle(bool enableFaceRect){

    // hid validation
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize buffers
    initializeBuffers();

    // fill buffer values
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera id */
    g_out_packet_buf[2] = ENABLE_DISABLE_MODE_FACE_RECTANGLE_NILECAM_CU30; /* pass enable/disable command */
    if(enableFaceRect)
        g_out_packet_buf[3] = ENABLE_FACE_RECTANGLE_NILECAM_CU30; /* enable auto focus rect */
    else
        g_out_packet_buf[3] = DISABLE_FACE_RECTANGLE_NILECAM_CU30; /* disable auto focus rect */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==ENABLE_DISABLE_MODE_FACE_RECTANGLE_NILECAM_CU30 &&
            g_in_packet_buf[6]==SET_SUCCESS) {\
            return true;
        }
    }
    return false;
}

/**
 * @brief NILECAM_CU30::setFlashNileCam - setting flash mode to the camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::setFlashNileCam(flashStateValues flashMode)
{
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize the buffer
    memset(g_out_packet_buf, 0x00, sizeof(g_out_packet_buf));

    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* set camera control code */
    g_out_packet_buf[2] = SETFLASH_STATUS_NILECAM_CU30 ; /* set flash status command code */
    g_out_packet_buf[3] = flashMode; /* set flash state [off/torch/storbe] */

    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==SET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==SETFLASH_STATUS_NILECAM_CU30  &&
            g_in_packet_buf[6]==SET_SUCCESS) {
            return true;
        }
    }
    return false;
}


/**
 * @brief NILECAM_CU30::getFlashNileCam - getting flash state from the camera
 * return true - success /false - failure
 */
bool NILECAM_CU30::getFlashNileCam()
{
    if(uvccamera::hid_fd < 0)
    {
        return false;
    }

    //Initialize the buffer
    memset(g_out_packet_buf, 0x00, sizeof(g_out_packet_buf));
    memset(g_in_packet_buf, 0x00, sizeof(g_in_packet_buf));

    //Set the Report Number
    g_out_packet_buf[1] = CAMERA_CONTROL_NILECAM_CU30; /* camera control id */
    g_out_packet_buf[2] = GETFLASH_STATUS_NILECAM_CU30; /* get strobe mode */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if (g_in_packet_buf[6]==GET_FAIL) {
            return false;
        } else if(g_in_packet_buf[0] == CAMERA_CONTROL_NILECAM_CU30 &&
            g_in_packet_buf[1]==GETFLASH_STATUS_NILECAM_CU30 &&
            g_in_packet_buf[6]==GET_SUCCESS) {
            emit flashModeValue(g_in_packet_buf[2]);
            return true;
        }
    }
    return false;
}

bool NILECAM_CU30::readMCUFirmwareVersion(){
    QString mcuFwVersion;

    if(uvccamera::hid_fd < 0)
    {
        return false;
    }
	
    //Initialize the buffer
    memset(g_out_packet_buf, 0x00, sizeof(g_out_packet_buf));
    memset(g_in_packet_buf, 0x00, sizeof(g_in_packet_buf));

    //Set the Report Number
    g_out_packet_buf[1] = CAMERA_MCUFWVERSION_NILECAM_CU30; /* get mcu fw version */

    // send request and get reply from camera
    if(uvc.sendHidCmd(g_out_packet_buf, g_in_packet_buf, BUFFER_LENGTH)){
        if(g_in_packet_buf[0] == CAMERA_MCUFWVERSION_NILECAM_CU30){
	    mcuFwVersion.append(g_in_packet_buf[1]);	    
	    mcuFwVersion.append(g_in_packet_buf[2]);
	    mcuFwVersion.append(g_in_packet_buf[3]);
	    mcuFwVersion.append(g_in_packet_buf[4]);
	    mcuFwVersion.append(g_in_packet_buf[5]);
	    mcuFwVersion.append(g_in_packet_buf[6]);
	    mcuFwVersion.append(g_in_packet_buf[7]);
	    emit mcuFirmwareVersionReceived(mcuFwVersion);	   
            return true;
        }
    }
    return false;
}

void NILECAM_CU30::setStillSkipCount(){
    uint frameToSkip;    

    frameToSkip = 1;

    // send frame to skip values to qtcam.qml
    emit updateFrameToSkipfromCam(frameToSkip);
}



/**
 * @brief NILECAM_CU30::initializeBuffers - Initialize input and output buffers
 */
void NILECAM_CU30::initializeBuffers(){

    //Initialize input and output buffers
    memset(g_out_packet_buf, 0x00, sizeof(g_out_packet_buf));
    memset(g_in_packet_buf, 0x00, sizeof(g_in_packet_buf));
}
