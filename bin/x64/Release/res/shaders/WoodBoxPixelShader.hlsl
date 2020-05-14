#include "AmbientLight.hlsl"

struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
};

Texture2D objTexture : TEXTURE;
Texture2D nmap : TEXTURE;
SamplerState objSampleState : SAMPLER;

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 sampleColor = (float3)(objTexture.Sample(objSampleState, input.inTexCoord));
    float3 ambientLight = ambientLightcolor * ambientLightStrength;
    float3 finalColor = sampleColor * ambientLight;

    return float4(finalColor, 1.0f);
}