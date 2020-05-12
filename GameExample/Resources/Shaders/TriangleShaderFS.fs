precision mediump float;

uniform sampler2D u_texture0;
varying vec2 v_uv;
uniform float r;
uniform float R;
uniform vec3 fogcol;
uniform vec3 camera;
varying vec3 pos;
varying vec3 norm;

uniform float ratio;
uniform vec3 ambColor;

uniform int tip0;
uniform int tip1;
uniform int tip2;
uniform int tip3;
uniform int tip4;

uniform vec3 spec0;
uniform vec3 spec1;
uniform vec3 spec2;
uniform vec3 spec3;
uniform vec3 spec4;

uniform vec3 diff0;
uniform vec3 diff1;
uniform vec3 diff2;
uniform vec3 diff3;
uniform vec3 diff4;

uniform vec3 pos0;
uniform vec3 pos1;
uniform vec3 pos2;
uniform vec3 pos3;
uniform vec3 pos4;

uniform vec3 dir0;
uniform vec3 dir1;
uniform vec3 dir2;
uniform vec3 dir3;
uniform vec3 dir4;

uniform vec3 deschidere0;
uniform vec3 deschidere1;
uniform vec3 deschidere2;
uniform vec3 deschidere3;
uniform vec3 deschidere4;

float maxim(in float a,in float b){
if(a>b){
return a;}
return b;
}

void main()
{
//gl_FragColor=texture2D(u_texture,v_uv);
vec4 color=texture2D(u_texture0,v_uv);

float dis=distance(pos,camera);

if(color.a<0.01){
discard;
}
float cl=clamp(dis,r,R);
float alpha=(cl - r)/(R-r);
color=alpha * vec4(fogcol,1.0) + (1.0 - alpha )* color;

vec3 compAmbientala=vec3(color.xyz * ambColor);
int nr_numere=0;

float specpow=0.8;
vec3 suma=vec3(0.0,0.0,0.0);
vec3 camtopos=camera-pos;
vec3 compdifuza;
vec3 compspeculara;
vec3 dir;
if(tip0 != 0){
    //vec3 dir;
    if(tip0 == 1){
        dir=pos - pos0;
    }
    else{
    dir = dir0;
    }
    compdifuza = vec3(vec3(color) * diff0 * max(dot(normalize(norm),normalize(-dir)),0.0));
    compspeculara =vec3(spec0 * pow(maxim(dot(normalize(reflect(normalize(dir),normalize(norm))),normalize(camtopos)),0.0),specpow));
    nr_numere=nr_numere+1;
    suma=suma+compdifuza + compspeculara;
}
/*
if(tip1 != 0){
vec3 dir;
    if(tip1 == 1){
        dir=pos - pos1;
    }
    vec3 compdifuza = vec3(vec3(color) * diff1 * max(dot(normalize(norm),normalize(-dir)),0.0));
    vec3 compspeculara =vec3(spec1 * pow(maxim(dot(reflect(normalize(dir),normalize(norm)),camtopos),0.0),specpow));
    nr_numere=nr_numere+1;
    suma=suma+compdifuza + compspeculara;
}
if(tip2 != 0){
vec3 dir;
    if(tip2 == 1){
        dir=pos - pos1;
    }
    vec3 compdifuza = vec3(vec3(color) * diff2 * maxim(dot(normalize(norm),normalize(-dir)),0.0));
    vec3 compspeculara =vec3(spec2 * pow(maxim(dot(reflect(normalize(dir),normalize(norm)),camtopos),0.0),specpow));
    nr_numere=nr_numere+1;
    suma=suma+compdifuza + compspeculara;
}
if(tip3 != 0){
vec3 dir;
    if(tip3 == 1){
        dir=pos - pos1;
    }
    vec3 compdifuza = vec3(vec3(color) * diff3 * maxim(dot(normalize(norm),normalize(-dir)),0.0));
    vec3 compspeculara =vec3(spec3 * pow(maxim(dot(reflect(normalize(dir),normalize(norm)),camtopos),0.0),specpow));
    nr_numere=nr_numere+1;
    suma=suma+compdifuza + compspeculara;
}
if(tip4 != 0){
    vec3 dir;
    if(tip2 == 1){
        dir=pos - pos1;
    }
    vec3 compdifuza = vec3(vec3(color) * diff4 * maxim(dot(normalize(norm),normalize(-dir)),0.0));
    vec3 compspeculara =vec3(spec4 * pow(maxim(dot(reflect(normalize(dir),normalize(norm)),camtopos),0.0),specpow));
    nr_numere=nr_numere+1;
    suma=suma+compdifuza + compspeculara;
}*/
float alp=color.a;
if(nr_numere>0){
color = vec4(ratio*compAmbientala + (float(1) - ratio)*suma,alp);
}
gl_FragColor=color;
}
