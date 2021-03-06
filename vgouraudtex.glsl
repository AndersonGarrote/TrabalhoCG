#version 130

in vec4 vPosition;
in vec3 vNormal;
attribute mediump vec2 vTextureCoord;


uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
uniform vec4 lightPosition;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float shininess;
uniform  sampler2D  texColorMap;

out vec4 vColor;

void main ()
{
        vec4 eyePosition = modelMatrix * vPosition ;
        gl_Position = projectionMatrix * modelViewMatrix * vPosition ;
        vec3 N = normalize( normalMatrix * vNormal );
        vec3 L = normalize( lightPosition.xyz - eyePosition.xyz );
        vec3 E = normalize( - eyePosition.xyz );
        vec3 R = reflect (-E, N);
        float NdotL = dot (N, L);
        float Kd = max (NdotL , 0.0) ;
        float Ks = ( NdotL < 0.0) ? 0.0 : pow ( max ( dot (R, E), 0.0), shininess );
        vec4 diffuse = Kd * diffuseProduct ;
        vec4 specular = Ks * specularProduct ;
        vec4 ambient = ambientProduct ;
        vColor = (ambient + diffuse + specular) * texture2D(texColorMap , vTextureCoord);
        vColor.a = 1.0;
}
