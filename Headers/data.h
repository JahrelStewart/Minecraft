#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------        
//Floor Data

//ground surafce vertex points
std::vector<float> floorVertexArray = {
    //positions         colors												textures    Normals
    -0.5f, -0.5f, 0.0f,	170.0f / 255.0f, 185.0f / 255.0f, 207.0f / 255.0f,	0.0f, 0.0f,	0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f,	170.0f / 255.0f, 185.0f / 255.0f, 207.0f / 255.0f,	0.0f, 1.0f,	0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,	170.0f / 255.0f, 185.0f / 255.0f, 207.0f / 255.0f,	1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f,	170.0f / 255.0f, 185.0f / 255.0f, 207.0f / 255.0f,	1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
};

std::vector<unsigned int> floorVertexLayout = { 3, 3, 2, 3 };

//creating indexes for index buffer to avoid dupilicate vertices
std::vector<unsigned int> floorIndexes = {
    0, 1, 2,
    2, 3, 0
};

std::vector<glm::vec3> floorVertexInstances;

std::vector<glm::vec3>& getFloorVertexInstances() {
    int gridSize = 10;
    int totalTiles = (int) (pow(gridSize, 2.0) + 0.5);

    //We create the 100 x 100 grid here to avoid calling the draw-call many times. This will boost performance	
    int gridIndex = 0;
    //offset centers all tiles around the origin for both X and Y planes....later will rotate the model 90 degrees so that it flat on the XZ plane
    float gridOffset = float((gridSize / 2.0f) - 0.5f);
    //Draw each tile row by row on the XY plane
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            glm::vec3 quadPos;
            quadPos.x = (float) (j - gridOffset);
            quadPos.y = (float) (i - gridOffset);
            quadPos.z = 0.0f;
            floorVertexInstances.push_back(quadPos);
        }
    }

    return floorVertexInstances;
}


//-----------------------------------------------------------------------------------------------------------------------------------        
//Cube Data

std::vector<float> cubeVertexArray = {
    //positions			//textures  //Normals        
    //Back Face
    -2.0f, -2.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, //0
     2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, //1
     2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, //2    
    -2.0f,  2.0f, -2.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, //3   

    //Front Face
    -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //4
     2.0f, -2.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //5
     2.0f,  2.0f, 2.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   //6        
    -2.0f,  2.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   //7

    //Left Face
    -2.0f,  2.0f,  2.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, //8
    -2.0f,  2.0f, -2.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, //9
    -2.0f, -2.0f, -2.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //10    
    -2.0f, -2.0f,  2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, //11

    //Right Face
     2.0f,  2.0f,  2.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //12
     2.0f,  2.0f, -2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //13
     2.0f, -2.0f, -2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  //14     
     2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  //15

    // Bottom Face
    -2.0f, -2.0f, -2.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //16
     2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, //17
     2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, //18     
    -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //19

    //Top Face
    -2.0f, 2.0f, -2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   //20
     2.0f, 2.0f, -2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   //21
     2.0f, 2.0f,  2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   //22     
    -2.0f, 2.0f,  2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,   //23
};

std::vector<unsigned int> cubeVertexLayout = { 3, 2, 3 };

//creating indexes for index buffer to avoid dupilicate vertices when creating a cube
std::vector<unsigned int> cubeIndexes = {
    0, 1, 2, //Back Face
    2, 3, 0,

    4, 5, 6, //Front Face
    6, 7, 4,

    8, 9, 10, //Left Face
    10, 11, 8,

    12, 13, 14, //Right Face
    14, 15, 12,

    16, 17, 18, // Bottom Face
    18, 19, 16,

    20, 21, 22, // Top Face
    22, 23, 20
};