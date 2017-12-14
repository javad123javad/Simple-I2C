/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "I2CLib.h"

#define I2C_DEBUG_EN
int file = -1;


/*!
 * \brief   This function initialize  I2C protocol to communicate in addreess dev_addr
 * \param   dev_addr    [IN]    : Device Address   
 */
s8 I2C_Init(u8 I2C_num, u8 dev_addr) {
#ifdef CUBI2
    if (I2C_num > 2)
    {
        fprintf(stderr, "There is at most 2 I2C bus in Cubieboard 2");
    }
#endif
    char fileName[20];
    int res = 0;
    
    snprintf(fileName, 19, "/dev/i2c-%d", I2C_num);
    
    file = open(fileName, O_RDWR);
    if (file < 0)
    {
        /* ERROR HANDLING; you can check errno to see what went wrong */
#ifdef I2C_DEBUG_EN
        perror("Open Problem ");
#endif
        return I2C_FAILURE;
    }

    res = ioctl(file, I2C_SLAVE, dev_addr);
    if (res < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
#ifdef I2C_DEBUG_EN
        perror("ioctl problem ");
#endif
        return I2C_FAILURE;
    }
    
    return I2C_SUCCESS;
}

/*!
 * \brief This function writes reg_data in reg_addr on the device address specified in dev_addr
 * \param [IN] dev_addr     :   Device Address
 * \param [IN] reg_addr     :   Register Address
 * \param [IN] reg_data     :   Data to write
 * \param [IN] data_cnt     :   Number of bytes to write
 */
s8 I2C_Write(u8 dev_addr, u8 reg_addr, u8 * reg_data, u16 data_cnt)
{
    u8 buf[data_cnt];
    s8 result=0;
    buf[0] = reg_addr;
    if(file<0)
    {
        printf("File err\n");
        return I2C_NOT_CONFIGURED;
    }
    for(u8 i = 1; i < data_cnt; i++)
    {
        //puts("Im Not there\n");
        buf[i] = *(reg_data + i);
    }
    result = write(file, buf, data_cnt);
    if ( result != data_cnt)
    {
#ifdef I2C_DEBUG_EN
        perror("write problem in I2C_Write: ");
        printf("Number of Writes: %hhd\n", result);

#endif
        return I2C_FAILURE;
    }
    return I2C_SUCCESS;

}

/*!
 * \brief This function reads reg_data in reg_addr from the address specified in dev_addr
 * \param [IN]  dev_addr    :   Device Address
 * \param [IN]  reg_addr    :   Register Address
 * \param [OUT] reg_data    :   Data is save in this variable
 * \param [In]  data_cnt    :   Number of bytes to read.
 */
s8 I2C_Read(u8 dev_addr, u8 reg_addr, u8 * reg_data, u16 data_cnt)
{
    //printf("I'm Calling from read:\n");
    //printf("dev:%x\treg:%x\tdata0:%x\n",dev_addr, reg_addr, reg_data[0]);
    u8 buf[data_cnt] ;
    s8 result = 0;
    if(file<0)
    {
        printf("Not Configured file");
        return I2C_NOT_CONFIGURED;
    }
    buf[0] = reg_addr;

    /* First write a dummy value in specified data register */
    result = I2C_Write(dev_addr, reg_addr, reg_data, 1);
    //result = write(file, buf, 1);
    //printf("Result %d\n", result);
    if(result != I2C_SUCCESS)
    {
#ifdef I2C_DEBUG_EN
        perror("Write Problem (read)");
#endif
        return I2C_FAILURE;
    }
    buf[0] = reg_addr;
    result = read(file, buf, data_cnt);
    
    if(result != data_cnt)
    {
#ifdef I2C_DEBUG_EN
        perror("Read Problem");
        printf("Number of Reads %hhd\n", result);
#endif
        return I2C_FAILURE;
    }
    for(u8 i=0; i < data_cnt; i++)
    {
        *(reg_data + i) = buf[i];
        //printf("I've Read:%x\n",buf[i]);
    }
    return I2C_SUCCESS;
    //close(file);
}

/*!
 * \brief This function De-Init Specified I2C bus
 * \param [IN]  file_name    :   The file related to the opened I2C bus.
 * \return close result
 */
s8 I2C_DeInit(s16 file_name)
{
    if (close(file_name) == I2C_SUCCESS)
        return I2C_SUCCESS;
    else
        return I2C_FAILURE;
}