#version 330 core

in vec3 v_color;


out vec4 FragColor;



void main()
{
    //FragColor = vec4(01.0f,0,1.0f,1.0f) ;
    FragColor = vec4(v_color,1.0);
}