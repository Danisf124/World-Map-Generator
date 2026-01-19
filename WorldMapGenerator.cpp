/*
    Name : "World map generator"
    Version: 1.1
    Last update: -
    Date of start: 16.01.25
    Author: Danisf
    Email: danasahno54@gmail.com
    GitHub: -
*/

//% g++ -Wall -g WorldMapGenerator.cpp -o bin/map

#include <iostream>
#include <string>
#include <random>

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

public:

    //Constractur of class
    Map()
    {

        rows = 15;

        cols = 15;

        map = new int* [rows]; //Init row of map

        for(int i = 0; i < rows; i++)
        {
            map[i] = new int[cols]; //Init colums of map
            for(int j = 0; j < cols; j++)
            {
                map[i][j] = 0; // Seting lanscape type fild, for first layer of map generation
            }
        }
    }
    //Destractur of class
    ~Map()
    {
        for(int i = 0; i < rows; i++)
        {
            delete[] map[i];//Deliting all rows of map
        }
        delete[] map; // Deleat map
        map = 0; // Set pointer to 0s
    }
    //Drawin map in consol
    void MapDraw()
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
               if(map[i][j] == 0)
               {
                    std::cout << "\e[0;32m"<< map[i][j] <<" ";
               }
               else if(map[i][j] == 8)
               {
                    std::cout << "\e[1;94m"<< map[i][j] <<" ";
               }
               else if (map[i][j] == 7)
               {
                    std::cout << "\e[0;92m" << map[i][j] << " ";
               }
               else if (map[i][j] == 3)
               {
                    std::cout << "\x1B[0m" << map[i][j] << " ";
               }
               
               
            }
            std::cout<<"\n";
        }
        
    }
    // Genrate sea on map
    void GenerateSea()
    {
        for(int i = 0; i < rows; ++i)
        {

            for(int j = 0; j < cols; ++j)
            {
                int flip_coin = rand()% 2; // Fliping coin: if 1, change 0 to 8 

                // In futher Add user diatanse set
                if(i < 2 || i > (rows - 3) ) //If we on sides of map
                {
                    map[i][j] = 8;
                    

                }
                else if(j < 2 || j > (cols - 3)) // If we on up or down of map
                {
                    map[i][j] = 8;
                }
                
                if((flip_coin == 1 && i == 2) || (flip_coin == 1 && i == (rows - 3)) )
                {
                    //If we on a top of map change 0 to 8
                    map[i][j] = 8;
                }
                else if((flip_coin == 1 && j == 2)||(flip_coin == 1 && j == (cols - 3)))
                {
                    //If we on a corner of map change 0 to 8
                    map[i][j] = 8;
                }
               
            }
            
        }
    }
    //Generate forest on map
    void GenerateForest()
    {   
        // Seting forest position(in futher random)
        landscape_height = rand()% 4+3;
        landscape_leight = rand()% 4+3;
        landscape_pos_x = rand()% 10+1;
        landscape_pos_y = rand()% 10+1;
        
        // Cheking if fores is out of map
        if(landscape_height + landscape_pos_x >= (rows - 1))
        {
            landscape_height = rows - landscape_pos_x;
        }
        else if(landscape_leight + landscape_pos_y >= (cols - 1))
        {
            landscape_leight = cols - landscape_pos_y;
        }
        
        
        for(int i = 0; i < landscape_height; ++i)
        {
            for(int j = 0; j < landscape_leight; ++j)
            {
                //Fliping coin to random lanscape
                int flip_coin = rand()% 2; 

                if(map[i + landscape_pos_x][j + landscape_pos_y] == 8)
                {
                   continue;
                }
                
                if(flip_coin == 1)
                {
                    continue;
                }

                map[i + landscape_pos_x][j + landscape_pos_y] = 7;
            }
        }

    }
    //Generate mountain on map
    void GenerateMountain()
    {
        landscape_height = rand()% 3+2;
        landscape_leight = rand()% 3+2;
        landscape_pos_x = rand()% 8+1;
        landscape_pos_y = rand()% 8+1;

        if(landscape_height + landscape_pos_x >= (rows - 1))
        {
            landscape_height = rows - landscape_pos_x;
        }
        else if(landscape_leight + landscape_pos_y >= (cols - 1))
        {
            landscape_leight = cols - landscape_pos_y;
        }   

        for(int i = 0; i < landscape_height; ++i)
        {
            for(int j = 0; j < landscape_leight; ++j)
            {
                if(map[i + landscape_pos_x][j + landscape_pos_y] == 8)
                {
                   continue;
                }

                map[i + landscape_pos_x][j + landscape_pos_y] = 3;
            }
        }

    }
    // Generating all bioms
    void GenerateMap()
    {
        GenerateSea();
        GenerateForest();
        GenerateMountain();
    }

};

int main()
{

    std::srand(time(NULL));

    Map map;

    map.GenerateMap();
   
    map.MapDraw();

    return 0;
}