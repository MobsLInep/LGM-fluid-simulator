@group(0) @binding(0) var samp: sampler;
@group(0) @binding(1) var tex: texture_2d<f32>;

struct VSOut {
  @builtin(position) pos: vec4<f32>,
  @location(0) uv: vec2<f32>,
};

@fragment
fn main(in: VSOut) -> @location(0) vec4<f32> {
  let c = textureSample(tex, samp, in.uv);
  return c;
}
