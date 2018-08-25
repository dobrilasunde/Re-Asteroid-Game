#version 330

// Uniforms for world transform and view-proj
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// Attribute 0 is position, 1 is tex coords, 2 is RGB color
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec4 inRGBA;

// Add texture coordinate as output
out vec2 fragTexCoord;
out vec4 fragRGBA;

void main()
{
	// Convert position to homogeneous coordinates
	vec4 pos = vec4(inPosition, 1.0);
	// Transform position to world space, then clip space
	gl_Position = pos * uWorldTransform * uViewProj;

	// Transform
	// Pass along the texture coordinate and RGB color to frag shader
	fragTexCoord = inTexCoord;
	fragRGBA = inRGBA;
}
