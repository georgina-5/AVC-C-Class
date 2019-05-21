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
int check_red = 0;
int Neutral_Speed = 48;
int Left_Speed = 52;				///min 31, base 48, max 59
int Right_Speed = 44;
set_motors(1,Left_Speed);
set_motors(5,Right_Speed);
hardware_exchange();

	while(true){																//quadrant 2 ends at red square, 160 is just a test value		check_red < 160
		
		for (Count = 0; Count < 14; Count++){									//puts values from a[0] to a[12]
			
			for (Count_X = 0; Count_X < 240; Count_X = Count_X + 20){
				sample_array[Count] = (int)get_pixel(Count_Y, Count_X, 3);
				if (sample_array[Count] > 100){									//if light is above a certain value, 100 is just a test value
					sample_array[Count] = 1;									//then that pixel will be determined to be "white"
				}
				else{															//else that pixel will be determined to be "black"
					sample_array[Count] = 0;
				}
				check_red = (int)get_pixel(Count_Y, Count_X, 0);
				cout<<"Red = "<<check_red<<endl;
				
				//cout<<"Count = "<<Count<<endl;
				//cout<<"Count X = "<<Count_X<<endl;
			}
		}
		
		Count = 0;
		Count_X = 0;

		cout<<"Count = "<<Count<<endl;
		cout<<"Count X = "<<Count_X<<endl;
		
		for(int sample_number = 0; sample_number < 14; sample_number++){
			if (sample_array[sample_number] == 1){
				error += ((sample_number) - 6);
				cout<<"error = "<<error<<endl;
			}
		}
					
		//UPDATING MOTOR SPEEDS
		if (error < 0){										//if the error is on the left 
			Left_Speed = (Neutral_Speed)-((error)/2);				
			Right_Speed = (Neutral_Speed)+((error)/2);		//turn right
		}
		else if (error > 0){								//if the error is on the right
			Left_Speed = (Neutral_Speed)+((error)/2);		//turn left
			Right_Speed = (Neutral_Speed)-((error)/2);
		}
		else if (error == 0){								//if there is no error
			Left_Speed = Neutral_Speed;						//both motors go the same speed
			Right_Speed = Neutral_Speed;
		}													///THE SPEEDS THAT THE MOTOR ARE BEING UPDATE AS
															///e.g (+/-(ERROR/2)) ARE JUST TEST VALUES AND CAN BE CHANGED
		set_motors(1,Left_Speed);
		set_motors(5,Right_Speed);
		hardware_exchange();								//update motor speed values
		
		error = 0;
		
		take_picture();
		update_screen();
	}
}
