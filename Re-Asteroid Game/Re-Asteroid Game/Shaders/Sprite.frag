// Request GLSL 3.3
#version 330

// Tex coord and RGB color input from vertex shader
in vec2 fragTexCoord;
in vec4 fragRGBA;

// This corresponds to the output color to the color buffer
out vec4 outColor;

// This is used for the texture sampling
uniform sampler2D uTexture;

void main()
{
	// Sample color from texture
	outColor = (texture(uTexture, fragTexCoord) + fragRGBA) / 2.0;
}
