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
    OUT.position = float4(IN.position, 1.0);
    OUT.color = IN.color;
    OUT.uv = IN.uv;
    return OUT;
}