@group(0) @binding(0) var<storage, read> dist: array<f32>;
@group(0) @binding(1) var<storage, read_write> outImg: array<u32>;
@group(0) @binding(2) var<uniform> uWidth: i32;
@group(0) @binding(3) var<uniform> uHeight: i32;
const cx: array<i32,9> = array<i32,9>(0,1,0,-1,0,1,-1,-1,1);
const cy: array<i32,9> = array<i32,9>(0,0,1,0,-1,1,1,-1,-1);
@compute @workgroup_size(8,8)
fn main(@builtin(global_invocation_id) gid: vec3<u32>) {
  let x: i32 = i32(gid.x);
  let y: i32 = i32(gid.y);
  if (x >= uWidth || y >= uHeight) { return; }
  let base: i32 = (y * uWidth + x) * 9;
  var rho: f32 = 0.0;
  var ux: f32 = 0.0; var uy: f32 = 0.0;
  for (var k: i32 = 0; k < 9; k = k + 1) {
    let f: f32 = dist[(base + k)];
    rho = rho + f;
    ux = ux + f * f32(cx[k]);
    uy = uy + f * f32(cy[k]);
  }
  ux = ux / rho; uy = uy / rho;
  let s: f32 = sqrt(ux*ux + uy*uy);
  let v: f32 = clamp(s * 10.0, 0.0, 1.0);
  let color: u32 = (u32(v * 255.0) << 16) | (u32((1.0 - v) * 255.0) << 8);
  outImg[y * uWidth + x] = color;
}
