#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------        
//Floor Data

//ground surafce vertex points
std::vector<float> floorVertexArray = {
    //positions         colors 											textures    Normals
    -0.5f, -0.5f, 0.0f,	73.0f / 255.0f, 73.0f / 255.0f, 71.0f / 255.0f,	0.0f, 0.0f,	0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f,	73.0f / 255.0f, 73.0f / 255.0f, 71.0f / 255.0f,	0.0f, 1.0f,	0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,	73.0f / 255.0f, 73.0f / 255.0f, 71.0f / 255.0f,	1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f,	73.0f / 255.0f, 73.0f / 255.0f, 71.0f / 255.0f,	1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
};

std::vector<unsigned int> floorVertexLayout = { 3, 3, 2, 3 };

//creating indexes for index buffer to avoid dupilicate vertices
std::vector<unsigned int> floorIndexes = {
    0, 1, 2,
    2, 3, 0
};

std::vector<glm::vec3> floorVertexInstances;

std::vector<glm::vec3>& getFloorVertexInstances() {
    int gridSize = 100;
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
    //positions			//textures         //Normals        

    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 1.0f, //0
     1.0f, -1.0f, 1.0f,  1.0f, 0.0f, 1.0f, //1        7--------6
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, //2       /|       /|
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, //3      4--------5 | 
    -1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f, //4  =>  | |      | |
     1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f, //5      | 3------|-2
     1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, //6      |/       |/
    -1.0f, 1.0f, -1.0f,  0.0f, 1.0f, 0.0f, //7      0--------1  
};

std::vector<unsigned int> cubeVertexLayout = { 3, 3 };

//creating indexes for index buffer to avoid dupilicate vertices when creating a cube
std::vector<unsigned int> cubeIndexes = {
    1, 2, 6, //Right Face
    6, 5, 1,

    0, 4, 7, //Left Face
    7, 3, 0,

    4, 5, 6, //Top Face
    6, 7, 4,

    0, 3, 2, //Bottom Face
    2, 1, 0,

    0, 1, 5, // Back Face
    5, 4, 0,

    3, 7, 6, // Front Face
    6, 2, 3,
};

//cubemap images for block
std::vector<std::string> cubeMapFaces = {
    "Resources/Textures/Block/right.jpg",
    "Resources/Textures/Block/left.jpg",
    "Resources/Textures/Block/top.jpg",
    "Resources/Textures/Block/bottom.jpg",
    "Resources/Textures/Block/front.jpg",
    "Resources/Textures/Block/back.jpg",
};