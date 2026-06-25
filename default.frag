#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec4 _solidColor;
in float _useSolidColor;

uniform sampler2D tex0;

void main()
{
	if (_useSolidColor > 0.5){
		FragColor = _solidColor;
	}
	else{
		FragColor = texture(tex0, texCoord);
	}
}