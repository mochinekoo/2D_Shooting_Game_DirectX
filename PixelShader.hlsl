struct VSOutput
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

float4 main(VSOutput IN) : SV_Target
{
    return IN.color;
}