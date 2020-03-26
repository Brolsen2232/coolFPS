#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <sstream>

#define mapWidth 24
#define mapHeight 24

std::string ConvertToString(int number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}

int worldMap[mapWidth][mapHeight]=
{
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main()
{
        
        int w = 1024, h = 576;
        
        double posX = 22, posY = 12; 
        double dirX = -1, dirY = 0; 
        double planeX = 0, planeY = 0.66; 
        double time = 0; 
        double oldTime = 0; 

    sf::RenderWindow window(sf::VideoMode(w, h), "SFML window");
        
        window.setFramerateLimit(60);
        sf::Clock clock = sf::Clock();
        sf::Time fps;
        
  
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
                        
            
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }
                
                window.clear();
                
                for(int x = 0; x < w; x++)
                {
                        
                        double cameraX = 2 * x / double(w) - 1; 
                        double rayPosX = posX;
                        double rayPosY = posY;
                        double rayDirX = dirX + planeX * cameraX;
                        double rayDirY = dirY + planeY * cameraX;
                        
                        
                        int mapX = int(rayPosX);
                        int mapY = int(rayPosY);
                        
                        
                        double sideDistX;
                        double sideDistY;
                        
                        
                        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
                        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
                        double perpWallDist;
                        
                        
                        int stepX;
                        int stepY;
                        
                        int hit = 0;
                        int side; 
                        if (rayDirX < 0)
                        {
                                stepX = -1;
                                sideDistX = (rayPosX - mapX) * deltaDistX;
                        }
                        else
                        {
                                stepX = 1;
                                sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
                        }
                        if (rayDirY < 0)
                        {
                                stepY = -1;
                                sideDistY = (rayPosY - mapY) * deltaDistY;
                        }
                        else
                        {
                                stepY = 1;
                                sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
                        }
                        
                        while (hit == 0)
                        {
                                if (sideDistX < sideDistY)
                                {
                                        sideDistX += deltaDistX;
                                        mapX += stepX;
                                        side = 0;
                                }
                                else
                                {
                                        sideDistY += deltaDistY;
                                        mapY += stepY;
                                        side = 1;
                                }
                                if (worldMap[mapX][mapY] > 0) hit = 1;
                        }
                        
                        if (side == 0)
                                perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
                        else
                                perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
                        
                        int lineHeight = abs(int(h / perpWallDist));
                        
                        int drawStart = -lineHeight / 2 + h / 2;
                        if(drawStart < 0)drawStart = 0;
                        int drawEnd = lineHeight / 2 + h / 2;
                        if(drawEnd >= h)drawEnd = h - 1;
                        

                        sf::Color color;
                        
                        
                        switch(worldMap[mapX][mapY])
                        {
                                case 1:
                                    color = sf::Color::Red;   
                                    if (perpWallDist<= 23 / 4.0f)			
                                        color.r = 255;	
			                        else if (perpWallDist< 23 / 3.0f)		
                                        color.r = 200;
                                        
			                        else if (perpWallDist< 23 / 2.0f)		
                                        color.r = 155;
                                        
			                        else if (perpWallDist< 23)				
                                        color.r = 100;
                                        
			                        else											
                                        color.r = 0;	
                                    break;
                                case 2:  
                                    color = sf::Color::Green; 
                                    if (perpWallDist <= 23 / 4.0f)			
                                        color.g = 255;			
			                        else if (perpWallDist< 23 / 3.0f)		
                                        color.g = 200;
                                        
			                        else if (perpWallDist < 23 / 2.0f)		
                                        color.g = 155;
                                        
			                        else if (perpWallDist < 23)				
                                        color.g = 100;
                                        
			                        else 											
                                        color.g = 0; 
                                    break;
                                case 3:  
                                    color = sf::Color::Blue; 
                                    if (perpWallDist <= 23 / 4.0f)			
                                        color.b = 255;	
			                        else if (perpWallDist< 23 / 3.0f)		
                                        color.b = 200;
                                        
			                        else if (perpWallDist < 23 / 2.0f)		
                                        color.b = 155;
                                        
			                        else if (deltaDistX < 23)				
                                        color.b = 100;
                                        
			                        else											
                                        color.b = 0;    
                                    break; 
                                default: color = sf::Color::Yellow;  
                        }
                        if(worldMap[int(mapX)][int(mapY)]  ==  5 && perpWallDist < 1){
                            posX = 22;
                            posY = 22;
                        }
                        
                        //verLine(x, drawStart, drawEnd, color);
                        
                        sf::Vertex line[2] =
                        {
                                sf::Vertex(sf::Vector2f(x, drawStart), color),
                                sf::Vertex(sf::Vector2f(x, drawEnd), color)
                        };
                        window.draw(line , 2, sf::Lines);
                
                }
                
                fps = clock.getElapsedTime();
                float fpsValue = 1000000/fps.asMicroseconds();
                clock.restart();
                
                double moveSpeed = fps.asSeconds() * 5.0; 
                double rotSpeed = fps.asSeconds() * 2.0; 
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        
                        double oldDirX = dirX;
                        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                        double oldPlaneX = planeX;
                        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        
                        double oldDirX = dirX;
                        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                        double oldPlaneX = planeX;
                        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
                        if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
                        if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
                }
                
        window.display();
                window.clear();
    }

    return EXIT_SUCCESS;
}