#pragma once

class Map
{
private:

   // parameters of map

    int rows; // Maps rows 

    int cols; // Maps collums

    int** map; // Map array

    // parameters of landscape
    int landscape_leight;   
                        
    int landscape_height;

    int landscape_pos_x;

    int landscape_pos_y;

    int landscape_num;

public:

    Map();

    ~Map();

    void MapDraw();

    void GenerateSea();

    void GenerateForest();

    void GenerateMountain();

    void GenerateMap();

};