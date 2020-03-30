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

cbuffer CBuff
{
    matrix transform;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.outPosition = mul(input.inPosition, transform);
    output.outTexCoord = input.inTexCoord;
    
    return output;
}