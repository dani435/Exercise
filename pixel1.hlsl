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
};

Output main(Input i)
{
    Output o;
    o.t0 = color;

    float3 light_direction = normalize(i.world_position.xyz - float3(0, 0, 1));

    float diffuse = saturate(dot(i.normal.xyz, -light_direction));

    float3 ambient = float3(0, 0.3, 0);

    float3 reflection = reflect(light_direction, i.normal.xyz);

    float3 view_direction = normalize(i.world_position.xyz - float3(0, 0, 1));

    float specular_factor = saturate(dot(reflection, view_direction));

    float3 specular = pow(float3(1, 1, 1) * specular_factor, 32);

    o.t1 = float4(float3(1, 0, 1) * diffuse, 1) + float4(ambient, 0) + float4(specular, 0);

    return o;
}