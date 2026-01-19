/*
    Name : "World map generator"
    Version: indev 0.2
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

    int landscape_num;

public:

    //Constractur of class
    Map()
    {
        bool is_valid = false;

        while(!is_valid)
        {   std::cout <<"Peleace, enter number of rows in map: ";
            std::cin >>rows;
            std::cout <<"Peleace, enter number of cols in map: ";
            std::cin >> cols;

            if(rows < 10 || cols < 10)
            {
                std::cout<<"Rows and cols must be bigger then 10\n ";
            }
            else if(rows > 50 || cols > 50)
            {
                std::cout<<"Rows and cols can't be bigger then 50\n ";
            }
            else 
            {
                is_valid = true;
            }
        }

        is_valid = false;

        while(!is_valid)
        {   
            std::cout <<"Pleace enter the number of lanscape: ";
            std::cin >> landscape_num;

            if(landscape_num <= 0)
            {
                std::cout<<"Landscape must be at least 1 \n ";
            }
            else if(landscape_num > 5)
            {
                std::cout<<"Landscape must be leas then 5\n ";
            }
            else 
            {
                is_valid = true;
            }
        }

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
        
        int max_forest_height = rows / 2;  
        int max_forest_width = cols / 2;
        
        for(int k = 0; k < landscape_num; ++k)
        {
            // Seting forest position(in futher random)
            landscape_height = rand()% max_forest_height + 1;
            landscape_leight = rand()% max_forest_width + 1;
            landscape_pos_x = rand()% (rows-4)+2;
            landscape_pos_y = rand()% (cols-4)+2;

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
        
    }
    //Generate mountain on map
    void GenerateMountain()
    {   

        int max_mountain_height = rows / 4;
        int max_mountain_width = cols / 4;

        for(int k = 0; k < landscape_num; ++k)
        {   
            landscape_height = rand()% max_mountain_height + 1;
            landscape_leight = rand()% max_mountain_width + 1;
            landscape_pos_x = rand()% (rows-4)+2;
            landscape_pos_y = rand()% (cols-4)+2;

            //Cheking corners of map
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