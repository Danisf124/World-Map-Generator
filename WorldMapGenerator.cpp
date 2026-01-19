/*
    Name : "World map generator"
    Version: 1.3.1
    Last update: 19.01.26
    Date of start: 16.01.25
    Author: Danisf
    GitHub: https://github.com/Danisf124/World-Map-Generator
*/


#include <iostream>
#include <string>
#include <random>
#include "Map/Map.h"


int main()
{

    std::srand(time(NULL));

    Map map;

    map.GenerateMap();
   
    map.MapDraw();

    return 0;
}