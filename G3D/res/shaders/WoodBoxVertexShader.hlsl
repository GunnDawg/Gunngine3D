#include "Transform.hlsl"

struct VS_INPUT
{
    float4 inPosition : POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
};

struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
    float3 outNormal : NORMAL;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    output.outPosition = mul(input.inPosition, WVP);
    output.outTexCoord = input.inTexCoord;
    output.outNormal = input.inNormal;

    return output;
}