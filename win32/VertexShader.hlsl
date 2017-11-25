
struct vs_in
{
	float4 pos : POSITION;
	float2 uv : TEXTURE_COORD0;
};

struct vs_to_ps
{
	float4 pos : SV_POSITION;
	float2 uv : TEXTURE_COORD0;
};

cbuffer transforms : register(b1)
{
	float scale;
	float offset;
};

vs_to_ps vertex(vs_in i)
{
	vs_to_ps o;
	o.pos = i.pos * float4(1, scale, 1, 1) + float4(0, offset, 0, 0);
	o.uv = i.uv;
	return o;
}