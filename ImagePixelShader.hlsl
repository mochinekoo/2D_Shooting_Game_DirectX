Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

struct PSInput
{
    float4 position : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

float4 main(PSInput IN) : SV_Target
{
    return texture0.Sample(sampler0, IN.uv);
}
