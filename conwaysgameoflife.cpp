#include <iostream>							//for output
#include <chrono>							//for delay
#include <thread>							//for delay
#include <cstdlib>							//for random
#include <ctime>							//for random

using namespace std;


const size_t delay_milliseconds = 100;		//delay 				(defautl: 100)
const size_t map_size_x = 130; 				//size of the map [x] 	(default: 130)
const size_t map_size_y = 70; 				//size of the map [x] 	(default: 70)
char map[map_size_y][map_size_x];			//the map itself
char new_map[map_size_y][map_size_x];		//the buffer for computing later


void fill_map_empty(){
	for(size_t y = 0; y < map_size_y; y++){
		for(size_t x = 0; x < map_size_x; x++){
			map[y][x] = ' ';			
		}
	}
}
//prints the map
void print_map(){
	for(size_t y = 0; y < map_size_y; y++){
		for(size_t x = 0; x < map_size_x; x++){
			cout << map[y][x];
		}
		cout << endl;
	}
}

bool check(int y, int x){ 				//checks the surroundings 
	size_t amount = 0;
	if(y != 0 && x != 0){
	if(map[y-1][x-1] == '#'){
		amount++;
	}
	if(map[y-1][x] == '#'){
		amount++;
	}
	if(map[y-1][x+1] == '#'){
		amount++;
	}

	if(map[y][x-1] == '#'){
		amount++;
	}
	if(map[y][x+1] == '#'){
		amount++;
	}

	if(map[y+1][x-1] == '#'){
		amount++;
	}
	if(map[y+1][x] == '#'){
		amount++;
	}
	if(map[y+1][x+1] == '#'){
		amount++;
	}

	if(map[y][x] == '#' && (amount == 3 || amount == 2)){
		new_map[y][x] = '#';			//changes are written into the buffer
		return true;
	}
	if(map[y][x] != '#' && amount == 3){
		new_map[y][x] = '#';			//here, too
		return true;
	}
	else{
		new_map[y][x] = ' ';			//and here
		return false;
	}

	}
}

void update_the_map(){
	for(size_t y = 0; y < map_size_y; y++){
		for(size_t x = 0; x < map_size_x; x++){
			map[y][x] = new_map[y][x];	//map gets the content of the buffer
		}
	}
}

void fill_map_random(){
	srand(time(0)); 					// use current time as seed for random generator
	int rdm;
	for(size_t y = 0; y < map_size_y; y++){
		for(size_t x = 0; x < map_size_x; x++){
			rdm = rand();
			if(rdm % 2)
				map[y][x] = ' ';
			else
				map[y][x] = '#';
		}
	}
}

int main(int argc, char const *argv[])
{
	fill_map_random();
	while(true){
		#ifdef _WIN32
		system("cls");
		#elif __linux__
		system("clear");
		#endif 
		print_map();
		for(size_t y = 0; y < map_size_y; y++){
			for(size_t x = 0; x < map_size_x; x++){
				check(y,x);
			}
		}
		update_the_map();
		this_thread::sleep_for(chrono::milliseconds(delay_milliseconds));
	}
	return 0;
}