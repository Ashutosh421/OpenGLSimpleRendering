#version 120

attribute vec3 position;
attribute vec2 textCord;
attribute vec3 normal;

varying vec2 textCord0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	textCord0 = textCord;
	normal0 = (transform * vec4(normal, 0.0)).xyz;
}