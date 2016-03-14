#version 150

in vec4 vPosition;
in vec4 vNormal;
in vec4 vTangent;
in vec4 vBinormal;

in vec2 vTexCoords;

out vec4 fragColour;

uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D AmbientTexture;

uniform vec4 LightDirection = vec4(1, 0, 0, 0);
uniform vec3 CameraPosition;
uniform float SpecPower = 16;
uniform vec3 LightAmbientColour = vec3(0.2, 0.2, 0.2);

void main()
{
    mat3 TBN = mat3(
        normalize(vTangent.xyz),
        normalize(vBinormal.xyz),
        normalize(vNormal.xyz)
    );
    
    vec3 n_ts = texture(NormalTexture, vTexCoords).xyz * 2 - 1;
    vec3 n_ws = normalize(TBN * n_ts);
    
    
    float d = max(0, dot(n_ws, LightDirection.xyz));
    
    vec3 E = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(-LightDirection.xyz, n_ws.xyz);
    
    float s = d * max(0, dot(E, R));
    s = pow(s, SpecPower);
    
    vec3 texColour = texture(DiffuseTexture, vTexCoords).xyz;
    vec3 ambient = LightAmbientColour * texture(AmbientTexture, vTexCoords).xyz * texColour;
    
    vec3 diffuse = d * texColour;
    vec3 spec = texture(SpecularTexture,vTexCoords).xyz * s;
    
	fragColour = vec4(ambient + diffuse + spec, 0.5f);
}