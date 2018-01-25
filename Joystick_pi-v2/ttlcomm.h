/*
****************Author : subash Timilsina************
*/

#ifndef TTLCOMM_INCLUDED
#define TTLCOMM_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define SERIAL_PORT1  "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0"
//"/dev/ttyUSB0"
//#define SERIAL_PORT1  "/dev/ttyUSB0"



int filed;

int init_serialport(char *port_name)
{
    filed = open(port_name,O_RDWR| O_NOCTTY | O_NDELAY);//read and write | no terminal will ctrl opening of port
    if (filed < 0) return 1;
    else return 0;
}

void setting_serialport(struct termios *serport)
{
    fcntl(filed, F_SETFL, FNDELAY);
    tcgetattr(filed,serport);//to get current settings
    tcflush(filed, TCIOFLUSH);
    cfsetispeed(serport,B9600);//input baudrate
    cfsetospeed(serport,B9600);//output baudrate
    serport->c_cflag &= ~PARENB;//for 0 parity bit
    serport->c_cflag &= ~CSTOPB;//for 1 stop bit
    serport->c_cflag &= ~CSIZE;//for masking size of data
    serport->c_cflag |=  CS8;//no. of data bits
    //serport->c_cflag &= ~CRTSCTS;//turn off hardware based flow control
    serport->c_cflag |=  (CLOCAL | CREAD);//turn on the receiver
    //serport->c_cflag &= ~(IXON | IXOFF | IXANY);//turn off software based flow control
    //serport->c_cflag &= ~(ICANON|ECHO|ECHOE|ISIG);//for non canonical ..means communication with avr
    tcsetattr(filed,TCSANOW,serport);//tell to make changes now
    tcflush(filed, TCIOFLUSH);
}

void write_data(char str)
{
    int data_bytessend = 0;
    int countl=0;
    do
    {
       data_bytessend = write(filed,&str,sizeof(str));
       countl++;
       if(countl>20)
       {
          //if(init_serialport(SERIAL_PORT2))
                init_serialport(SERIAL_PORT1);

       }
    }
    while(data_bytessend<0);//retry until the data write successfully
}




#endif // TTLCOMM_INCLUDED

