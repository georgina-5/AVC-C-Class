/* AVC Project: Team 8
Quadrant 2 */
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "E101.h"
#include <time.h>
using namespace std;
//CHANGE CODING FORMATING, USE CLASSES NOT JUST IN ONE MAIN
int main()
{
init(0);
open_screen_stream();
int Count = 0;
int Count_Y = 120;
int Count_X = 0;
int sample_array[13];
int error = 0;
int backwards_check = 0;
int check_red = 0;
int Neutral_Speed = 48;
int Left_Speed = 52;				///min 31, base 48, max 59
int Right_Speed = 52;
set_motors(1,Left_Speed);			//LEFT MOTOR
set_motors(5,Right_Speed);			//RIGHT MOTOR
set_motors(3, 48);					//CAMERA
hardware_exchange();

	while(true){																//quadrant 2 ends at red square, 160 is just a test value		check_red < 160
		//THIS "FOR LOOP" READS PIXELS AND DECIDES IF IT IS BLACK OR WHITE
		for (Count_X = 4; Count_X < 317; Count_X = Count_X + 26){			//puts values from a[0] to a[12]
			sample_array[Count] = (int)get_pixel(Count_Y, Count_X, 3);
			if (sample_array[Count] > 80){									//if light is above a certain value, 100 is just a test value
				sample_array[Count] = 1;									//then that pixel will be determined to be "white"
			}
			else{															//else that pixel will be determined to be "black"
				sample_array[Count] = 0;
			}
			//cout<<"Count = "<<Count<<endl;
			//cout<<"X = "<<Count_X<<endl;
			check_red += (int)get_pixel(Count_Y, Count_X, 0);
			//cout<<"Red = "<<check_red<<endl;
			Count++;
		}
		Count = 0;

		//THIS "FOR LOOP" READS THE ARRAY: CALCULATES THE ERROR, AND ADJUSTS THE MOTOR SPEEDS 
		for(int sample_number = 0; sample_number < 14; sample_number++){
			if (sample_array[sample_number] == 1){
				error += ((sample_number) - 6);
			}
		}
		
		//CHECKS IF IT SHOULD GO BACKWARDS
		for(int sample_number = 0; sample_number < 14; sample_number++){
			if (sample_array[sample_number] == 1){
				backwards_check ++;
			}
		}
		
		cout<<"Error = "<<error<<endl;
		sleep(1);
		//UPDATING MOTOR SPEEDS
		if (error < 0){										//if the error is on the left 
			Left_Speed = (Neutral_Speed)-((error)/2);				
			Right_Speed = (Neutral_Speed)+((error)/2);		//turn right
			cout<<"RIGHT"<<endl;
		}
		else if (error > 0){										//if the error is on the right
			Left_Speed = (Neutral_Speed)+((error)/2);		//turn left
			Right_Speed = (Neutral_Speed)-((error)/2);
			cout<<"LEFT"<<endl;
		}
		else if (error == 0){									//if there is no error
			Left_Speed = 45;								//both motors go the same speed
			Right_Speed = 51;
			cout<<"STRAIGHT"<<endl;
		}													///THE SPEEDS THAT THE MOTOR ARE BEING UPDATE AS
															///e.g (+/-(ERROR/2)) ARE JUST TEST VALUES AND CAN BE CHANGED
		
		else if (backwards_check == 13){
			Left_Speed = 51;
			Right_Speed = 45;
		}												
		
		set_motors(1,Left_Speed);
		set_motors(5,Right_Speed);
		hardware_exchange();								//update motor speed values	

		//cout<<"error = "<<error<<endl;
		//cout<<"Left = "<<Left_Speed<<endl;
		//cout<<"Right = "<<Right_Speed<<endl;
		error = 0;
		check_red = 0;
		take_picture();
		update_screen();
	}
}
