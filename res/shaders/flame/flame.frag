#version 400 core

in vec2 texCoord;
flat in float flame;

out vec4 fragColor;

uniform sampler1D noise;
uniform float time;
uniform int screenX;

void main() {
    float v = texture(noise, float(gl_FragCoord.x)/screenX*mod(gl_PrimitiveID * time*0.1 , 1)).r;
    if(flame>0.5f)
        fragColor = vec4(1,0.4 + 0.3*(texCoord.y),0.3+ 0.2 * texCoord.y,exp(v*v)*texCoord.y*(texCoord.y* v*0.5 + (1-v)*(0.5+0.5*v) * 0.5f* abs(0.2*sin(5.23*time) + 0.3*cos(10.23*time))));
    else
        fragColor = vec4(1,0.4 + 0.4*(texCoord.y),0.6,texCoord.y*(0.5 + (0.5+0.5*v) * 0.5f* abs(0.1*sin(v*5.23*time) + 0.15*cos(v*10.23*time))));
}