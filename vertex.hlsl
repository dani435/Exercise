Buffer<uint> vertex_index : register(t0);
Buffer<float3> vertex_position: register(t1);
Buffer<float3> vertex_normal: register(t2);
Buffer<float2> vertex_uv: register(t3);

matrix world;
matrix view;
matrix projection;
float color;

struct Output
{
    float4 position : SV_Position;
    float4 normal : NORMAL;
    float4 world_position : WPOSITION;
    float2 uv : UV;
};

Output main(uint vid : SV_VertexID)
{
    uint index = vertex_index[vid];
    Output o;
    matrix mv = mul(view, world);
    matrix mvp = mul(projection, mv);
    o.position = mul(mvp, float4(vertex_position[index], 1));
    o.normal = mul(world, float4(vertex_normal[index], 0));
    o.world_position = mul(world, float4(vertex_position[index], 1));
    o.uv = vertex_uv[index];
    return o;
}