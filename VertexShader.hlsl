cbuffer ConstantBuffer : register(b0)
{
    matrix wvpMatrix;
}

struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

VSOutput main(VSInput IN)
{
    VSOutput OUT;
    OUT.position = mul(float4(IN.position, 1.0f), wvpMatrix);
    OUT.color = IN.color;
    OUT.uv = IN.uv;
    return OUT;
}