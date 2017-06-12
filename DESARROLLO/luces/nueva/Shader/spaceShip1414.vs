#version 330 core

uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;
uniform mat3 NormalMatrix;

in vec4 VertexColor;
in vec3 VertexNormal;
in vec4 VertexPosition;

out vec4 Color;
out vec3 Normal;
out vec4 Position;

void main(void)
{
	Color = VertexColor;
	Normal = normalize(NormalMatrix * VertexNormal);
	Position = MVMatrix * VertexPosition;

	gl_Position = MVPMatrix * VertexPosition;
}
