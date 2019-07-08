#version 130

in vec3 fNormal;
in vec4 eyePosition;
in vec3 normalInter;
varying mediump vec2 fTextureCoord;

uniform vec4 lightPosition;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float shininess;
uniform  sampler2D  texColorMap;

out vec4 fColor;

void main ()
{

    vec3 N = normalize( normalInter );
    vec3 L = normalize( lightPosition.xyz - eyePosition.xyz );
    vec3 E = normalize( - eyePosition.xyz );
    vec3 R = reflect (-E, N);
    float NdotL = dot (N, L);
    float Kd = max (NdotL , 0.0) ;
    float Ks = ( NdotL < 0.0) ? 0.0 : pow ( max ( dot (R, E), 0.0), shininess );
    vec4 diffuse = Kd * diffuseProduct ;
    vec4 specular = Ks * specularProduct ;
    vec4 ambient = ambientProduct ;
    //fColor = (ambient + diffuse + specular) * texture2D(texColorMap , fTextureCoord) ;
    fColor = texture2D(texColorMap , fTextureCoord);
    fColor.a = 1.0;

}
