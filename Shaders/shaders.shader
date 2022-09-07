#shader FloorVertexShader
#version 330 core

layout(location = 0) in vec3 aGridPos;
layout(location = 1) in vec3 aGridColor;
layout(location = 2) in vec2 aGridTexture;
layout(location = 3) in vec3 gridNormals;
layout(location = 4) in vec3 gridOffsetPos;

out vec3 vertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 objPos;

uniform mat4 u_Model_View_Projection;
uniform mat4 u_Model;

void main() {
	vertexColor = aGridColor;
	TexCoord = aGridTexture;
	Normal = mat3(transpose(inverse(u_Model))) * gridNormals;
	objPos = vec3(u_Model * vec4(aGridPos + gridOffsetPos, 1.0));
	gl_Position = u_Model_View_Projection * vec4(aGridPos + gridOffsetPos, 1.0);
}

// ---------------------------------------------------------------------------------- 

#shader FloorFragmentShader
#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

uniform sampler2D customTexture;

void main() {	
	FragColor = vec4(vertexColor.rgb, 1.0);
}

// ---------------------------------------------------------------------------------- 

#shader CubeVertexShader
#version 330 core

layout(location = 0) in vec3 aCubePos;
layout(location = 1) in vec3 cubeTexCoord;
// layout(location = 2) in vec3 cubeNormals;

out vec3 vertexColor;
out vec3 TexCoord;
// out vec3 Normal;
out vec3 objPos;

uniform mat4 u_Model_View_Projection;
uniform mat4 u_Model;

void main() {
	vertexColor = vec3(114.0/255.0, 76.0/255.0, 249.0/255.0);		
	TexCoord = vec3(aCubePos.x, aCubePos.y, -aCubePos.z);
	// Normal = mat3(transpose(inverse(u_Model))) * cubeNormals;
	objPos = vec3(u_Model * vec4(aCubePos, 1.0));
	gl_Position = u_Model_View_Projection * vec4(aCubePos, 1.0);
}

// ---------------------------------------------------------------------------------- 

#shader CubeFragmentShader
#version 330 core

in vec3 vertexColor;
in vec3 TexCoord;

out vec4 FragColor;

uniform samplerCube cubemap;

void main() {
	FragColor = texture(cubemap, TexCoord);	
	// FragColor = vec4(vertexColor.rgb, 1.0);
}

// ---------------------------------------------------------------------------------- 
