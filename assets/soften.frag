uniform sampler2D u_texture;
uniform vec2 u_texelSize;
uniform float u_strength;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;

    vec4 center = texture2D(u_texture, uv);
    vec4 left   = texture2D(u_texture, uv + vec2(-u_texelSize.x, 0.0));
    vec4 right  = texture2D(u_texture, uv + vec2( u_texelSize.x, 0.0));
    vec4 up     = texture2D(u_texture, uv + vec2(0.0, -u_texelSize.y));
    vec4 down   = texture2D(u_texture, uv + vec2(0.0,  u_texelSize.y));

    vec4 blur = (center + left + right + up + down) / 5.0;

    gl_FragColor = mix(center, blur, u_strength);
}