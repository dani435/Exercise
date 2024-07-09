RWBuffer<uint> target0 : register(u0);

RWBuffer<uint> target1 : register(u1);

RWTexture2D<float4> target2 : register(u2);

float color;

[numthreads(1, 1, 1)]
void main(uint3 tid : SV_DispatchThreadId)
{
	target0[0] = 0x11223344;
    target0[1] = 0x55667788;
    target0[2] = 0x9900aabb;
    target0[3] = 0xccddeeff;

    target1[0] = 0xdeadbeef;

    target2[tid.xy] = float4(color, 0, 0, 1);
}
