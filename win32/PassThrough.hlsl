struct ps_in
{
    float4 pos : SV_POSITION;
    float2 uv : TEXTURE_COORD0;
};

texture2D source;
SamplerState sourceSampler : register(s0);

float trapezoid(float x) {
    return clamp(abs(frac(x) * 8.0 - 4.0) - 2.0, -1.0, 1.0);
}

float4 pixel(ps_in input) : SV_Target
{
    float2 uv = input.uv;
    float distance = 1.0 - uv.y;
    float angle = uv.x;

    float x = trapezoid(angle);
    float y = trapezoid(angle + 0.25);

    float2 xy = float2(x, y) * distance;

    xy = xy * 0.5 + 0.5;

    return source.Sample(sourceSampler, xy);
}
