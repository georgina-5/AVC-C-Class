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
int check_red = 0;


	while(true){
		//THIS "FOR LOOP" READS PIXELS AND DECIDES IF IT IS BLACK OR WHITE
		for (Count_X = 4; Count_X < 317; Count_X = Count_X + 26){
			sample_array[Count] = (int)get_pixel(Count_Y, Count_X, 3);
			check_red += (int)get_pixel(Count_Y, Count_X, 0);
			Count++;
		}
		for(int i = 0; i < 14; i++){
			cout<<"Pixel value = "<<sample_array[i]<<endl;		//can comment this line out if needed
			}							//so check red can be tested
		
		cout<<"Red value = "<<check_red<<endl;
		//sleep(1);		//put a sleep in just in case it needs to be slowed down
		Count = 0;
		take_picture();
		update_screen();
	}
}
