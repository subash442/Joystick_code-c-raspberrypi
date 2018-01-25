/*
****************Author : subash Timilsina************
*/

#include "ttlcomm.h"
#include <linux/joystick.h>


#define JOY_EVENTDEV  "/dev/input/js0"


const char STARTBYTE = 127;

char GamebuttonA , GamebuttonB;
signed char Righttrigger , Lefttrigger;
signed char LeftstickY , RightstickY , LeftstickX , RightstickX;

char init_joystick(int *fd)
{
    *fd = open(JOY_EVENTDEV,O_RDONLY,O_NONBLOCK);
    if (*fd < 0) return 1;
    else
    return 0;
}

void display_device_info(int fd,int *noofaxes,int *noofbuttons)
{
    char nameofdevice[80];
    ioctl(fd,JSIOCGAXES,noofaxes);
    ioctl(fd,JSIOCGBUTTONS,noofbuttons);
    ioctl(fd,JSIOCGNAME(sizeof(nameofdevice)),nameofdevice);
    printf("%s \n\n%d Axes\n%d Buttons\n",nameofdevice,*noofaxes,*noofbuttons);
}

char read_data(int fd,struct js_event *jse)
{
    int data_size;
    data_size = read(fd,jse,sizeof(*jse));
    if (data_size == sizeof(*jse))
    {
        return 1;
    }
    printf("Data is invalid.\n");
    return 0;
}

signed char Compute(long int x)
{
   return ((32767-x)/65534.0)*100
   ;
}

/*void check_button_pressed(struct js_event joyevent,int noaxes,int nobutton)
{
    int i;
    int *axis = (int *) calloc(noaxes , sizeof(int));
    int *button = (int *) calloc(nobutton,sizeof(int));
    switch(joyevent.type & ~ JS_EVENT_INIT)
		{
			case JS_EVENT_AXIS :

				axis [ joyevent.number ] = joyevent.value;
				break;

			case JS_EVENT_BUTTON :

				button [joyevent.number ] = joyevent.value;
				break;

        }

        for(i=0;i<noaxes;i++)
            printf("\nAxes%d : %d\n",i,axis[i]);
        for(i=0;i<nobutton;i++)
            printf("\n\nButton%d : %d\n\n",i,button[i]);
        free(axis);
        free(button);
 }*/

 void send_data()
{


    write_data(STARTBYTE);
    usleep(1000);
    write_data(GamebuttonA);
    usleep(1000);
    write_data(GamebuttonB);
    usleep(1000);
    write_data(LeftstickX);
    usleep(1000);
    write_data(LeftstickY);
    usleep(1000);
    write_data(RightstickX);
    usleep(1000);
    write_data(RightstickY);
    usleep(1000);
    write_data(Lefttrigger);
    usleep(1000);
    write_data(Righttrigger);
    usleep(1000);

}



void check_button_pressed(struct js_event joyevent)
{

    GamebuttonA = 0 , GamebuttonB = 0 , Righttrigger = 0 , Lefttrigger = 0 ,
     LeftstickY=0 , RightstickY=0 , LeftstickX=0 , RightstickX=0 ;
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 0)
    {
                printf("Button A\n");
                GamebuttonA |= (1<<0);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 1)
    {
               printf("Button B\n");
                GamebuttonA |= (1<<1);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 2)
    {
                printf("Button X\n");
                GamebuttonA |= (1<<2);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 3)
    {
                printf("Button Y\n");
                GamebuttonA |= (1<<3);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 4)
    {
               printf("Button Left\n");
                GamebuttonB |= (1<<0);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 5)
    {
                printf("Button Right\n");
                GamebuttonA |= (1<<4);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 6)
    {
               printf("Button Back\n");
                GamebuttonB |= (1<<1);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 7)
    {
               printf("Button Start\n");
                GamebuttonA |= (1<<5);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 8)
    {
               printf("Button Xbox\n");
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 9)
    {
               printf("Button leftstick pressed\n");
                GamebuttonB |= (1<<2);
    }
    if (joyevent.type == 1 && joyevent.value == 0 && joyevent.number == 10)
    {
               printf("Button rightstick pressed\n");
                GamebuttonA |= (1<<6);
    }
    if (joyevent.type == 2 && joyevent.number == 0)
    {
        printf("Button Leftstick left or right\n");
        LeftstickX = Compute(joyevent.value);
        printf("Value : %d\n",LeftstickX);
    }
    if (joyevent.type == 2 && joyevent.number == 1)
    {
         printf("Button Leftstick up or down.\n");
         LeftstickY = Compute(joyevent.value);
         printf("Value : %d\n",LeftstickY);
    }
    if (joyevent.type == 2 && joyevent.number == 2)
    {
            printf("Button Left trigger\n");
                Lefttrigger = Compute(joyevent.value);
                printf("Value : %d\n",Lefttrigger);
    }
    if (joyevent.type == 2 && joyevent.number == 3)
    {
        printf("Button Rightstick left or right\n");
                RightstickX = Compute(joyevent.value);
                printf("Value : %d\n",RightstickX);
    }
    if (joyevent.type == 2 && joyevent.number == 4)
    {
        printf("Button Rightstick up or down\n");
                RightstickY = Compute(joyevent.value);
                printf("Value : %d\n",RightstickY);
    }
    if (joyevent.type == 2 && joyevent.number == 5)
    {
        printf("Button Right trigger\n");
                Righttrigger = Compute(joyevent.value);
                printf("Value : %d\n",Righttrigger);
    }
    if (joyevent.type == 2 && joyevent.number == 6)
    {
         if (joyevent.value<0)
                {
                    printf("Button Plus_Left trigger\n");
                    GamebuttonB |= (1<<3);
                }
                else if (joyevent.value>0)
                {
                    printf("Button Plus_Right trigger\n");
                    GamebuttonB |= (1<<4);
                }

    }
    if (joyevent.type == 2 && joyevent.number == 7)
    {
        if (joyevent.value>0)
                {
                    printf("Button Plus_Down trigger\n");
                    GamebuttonB |= (1<<5);
                }
                else if (joyevent.value<0)
                {
                    printf("Button Plus_Up trigger\n");
                    GamebuttonB |= (1<<6);
                }



    }


}

int main()
{

    int noofaxes = 0;
    int noofbuttons = 0;
    int filedescriptor = -1;
    struct termios sp;
    struct js_event jse;
    if (init_joystick(&filedescriptor))
    {
        printf("Joystick Not Connected.\n");
        return 1;
    }
    if (init_serialport(SERIAL_PORT1))
    {
        printf("No serial communication device found on usb0.\n");
        //if (init_serialport(SERIAL_PORT2))
          //  printf("No serial communication device found on usb1.\n");
            return 1;
    }
    printf("Communication device and joystick found.\n\n");
    setting_serialport(&sp);
    display_device_info(filedescriptor,&noofaxes,&noofbuttons);
    while(1)
    {
        while(read_data(filedescriptor,&jse))
        {

                check_button_pressed(jse);  // check_button_pressed(jse,noofaxes,noofbuttons);
                send_data();
        }


    }

     close(filed);
    close(filedescriptor);
    return 0;
}
