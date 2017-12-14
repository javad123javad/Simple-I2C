/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   I2CLib.h
 * Author: javad
 *
 * Created on July 30, 2017, 8:21 PM
 */

#ifndef I2CLIB_H
#define I2CLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include "../../MyLib/Types/MyDataTypes.h"


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif
#define CUBI2
//  #define NANO_PI
//  #define ORANGE_PI
/* I2C Protocol Constants */
#define I2C_SUCCESS     0
#define I2C_FAILURE     -1
#define I2C_NOT_CONFIGURED -2
/* I2C Bus Numbers */
#ifdef CUBI2
    #define I2C_BUS_0    0
    #define I2C_BUS_1    1
    #define I2C_BUS_2    2
#endif

#ifdef NANO_PI
    #define I2C_0    0
    #define I2C_1    1
#endif

#ifdef ORANGE_PI
    #define I2C_0    0
    #define I2C_1    1
#endif

/*******************************************************************************/
/*!
 * \brief   This function initialize  I2C protocol to communicate in addreess dev_addr
 * \param   I2C_num     [IN]    : I2C Device Number. it can be find in /dev/i2c
 * \param   dev_addr    [IN]    : Device Address   
 */
s8 I2C_Init(u8 I2C_num, u8 dev_addr);

/*!
 * \brief This function writes reg_data in reg_addr on the device address specified in dev_addr
 * \param [IN] dev_addr     :   Device Address
 * \param [IN] reg_addr     :   Register Address
 * \param [IN] reg_data     :   Data to write
 * \param [IN] data_cnt     :   Number of bytes to write
 */
s8 I2C_Write(u8 dev_addr, u8 reg_addr, u8 * reg_data, u16 data_cnt);

/*!
 * \brief This function reads reg_data in reg_addr from the address specified in dev_addr
 * \param [IN]  dev_addr    :   Device Address
 * \param [IN]  reg_addr    :   Register Address
 * \param [OUT] reg_data    :   Data is save in this variable
 * \param [In]  data_cnt    :   Number of bytes to read.
 */
s8 I2C_Read(u8 dev_addr, u8 reg_addr, u8 * reg_data,  u16 data_cnt);
/*!
 * \brief This function De-Init Specified I2C bus
 * \param [IN]  file_name    :   The file related to the opened I2C bus.
 */
s8 I2C_DeInit(s16 file_name);
#endif /* I2CLIB_H */

