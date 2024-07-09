struct Output
{
    float4 t0 : SV_Target0;
    float4 t1 : SV_Target1;
};

matrix world;
matrix view;
matrix projection;
float color;

struct Input
{
    float4 position : SV_Position;
    float4 normal : NORMAL;
    float4 world_position : WPOSITION;
    float2 uv : UV;
};

Texture2D<float4> albedo_texture : register(t4);
Texture2D<float4> emissive_texture : register(t5);

RaytracingAccelerationStructure scene : register(t6);
SamplerState sampler0 : register(s0);

Output main(Input i)
{
    Output o;
    o.t0 = color;

    float3 light_direction = normalize(i.world_position.xyz - float3(0, 0, 1000));

    float diffuse = saturate(dot(i.normal.xyz, -light_direction));

    float3 albedo = albedo_texture.Sample(sampler0, i.uv).rgb;

    float3 emissive = emissive_texture.Sample(sampler0, i.uv).rgb;

    o.t1 = float4((albedo * diffuse) + emissive, 1);

    RayQuery<RAY_FLAG_CULL_NON_OPAQUE|RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES|RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH> query;

    RayDesc ray;
    ray.Origin = i.world_position.xyz;
    ray.TMin = 0.01;
    ray.TMax = length(float3(0, 0, 1000) - i.world_position.xyz);
    ray.Direction = float3(0, 0, 1);

    query.TraceRayInline(scene, 0, 0xffffffff, ray);

    query.Proceed();

    if (query.CommittedStatus() == COMMITTED_TRIANGLE_HIT)
    {
        o.t1 *= float4(0.1, 0.1, 0.1, 1);
    }

    return o;
}