struct Vertex
{
    float3 position;
    float3 normal;
};

StructuredBuffer<Vertex> vertex;

matrix world;
matrix view;
matrix projection;
float color;

struct Output
{
    float4 position : SV_Position;
    float4 normal : NORMAL;
    float4 world_position : WPOSITION;
};

Output main(uint vid : SV_VertexID)
{
    Output o;
    matrix mv = mul(view, world);
    matrix mvp = mul(projection, mv);
    o.position = mul(mvp, float4(vertex[vid].position, 1));
    o.normal = mul(world, float4(vertex[vid].normal, 0));
    o.world_position = mul(world, float4(vertex[vid].position, 1));
    return o;
}