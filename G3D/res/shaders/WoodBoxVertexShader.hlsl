struct VS_INPUT
{
    float4 inPosition : POSITION;
    float2 inTexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
};

cbuffer CameraBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projMatrix;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    matrix camera = transpose(mul(projMatrix, mul(viewMatrix, worldMatrix)));

    output.outPosition = mul(input.inPosition, camera);
    output.outTexCoord = input.inTexCoord;

    return output;
}