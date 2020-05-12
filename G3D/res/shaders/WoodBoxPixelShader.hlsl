#include "AmbientLight.hlsl"

struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
};

Texture2D objTexture : TEXTURE;
SamplerState objSampleState : SAMPLER;

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 sampleColor = objTexture.Sample(objSampleState, input.inTexCoord);
    float3 ambientLight = ambientLightcolor * ambientLightStrength;
    float3 finalColor = sampleColor * ambientLight;

    return float4(finalColor, 1.0f);
}