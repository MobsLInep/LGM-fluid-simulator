struct VSOut {
  @builtin(position) pos: vec4<f32>,
  @location(0) uv: vec2<f32>,
};

@vertex
fn main(@builtin(vertex_index) vid: u32) -> VSOut {
  var p = array<vec2<f32>,3>(
    vec2<f32>(-1.0, -1.0),
    vec2<f32>( 3.0, -1.0),
    vec2<f32>(-1.0,  3.0)
  );
  let pos = p[vid];
  var out: VSOut;
  out.pos = vec4<f32>(pos, 0.0, 1.0);
  out.uv = 0.5 * (pos + vec2<f32>(1.0,1.0));
  return out;
}
