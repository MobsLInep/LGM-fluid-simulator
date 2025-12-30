@group(0) @binding(0) var<storage, read> inBuf: array<f32>;
@group(0) @binding(1) var<storage, read_write> outBuf: array<f32>;
const cs2: f32 = 1.0 / 3.0;
const w: array<f32,9> = array<f32,9>(4.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0);
const cx: array<i32,9> = array<i32,9>(0,1,0,-1,0,1,-1,-1,1);
const cy: array<i32,9> = array<i32,9>(0,0,1,0,-1,1,1,-1,-1);
@group(0) @binding(2) var<uniform> uTau: f32;
@group(0) @binding(3) var<uniform> uWidth: i32;
@group(0) @binding(4) var<uniform> uHeight: i32;
@group(0) @binding(5) var<storage, read> walls: array<u32>;
@compute @workgroup_size(8,8)
fn main(@builtin(global_invocation_id) gid: vec3<u32>) {
  let x: i32 = i32(gid.x);
  let y: i32 = i32(gid.y);
  if (x >= uWidth || y >= uHeight) { return; }
  let base: i32 = (y * uWidth + x) * 9;
  if (walls[y * uWidth + x] != 0u) {
    for (var k: i32 = 0; k < 9; k = k + 1) {
      outBuf[(base + k)] = inBuf[(base + k)];
    }
    return;
  }
  var rho: f32 = 0.0;
  for (var k: i32 = 0; k < 9; k = k + 1) { rho = rho + inBuf[(base + k)]; }
  var ux: f32 = 0.0; var uy: f32 = 0.0;
  for (var k: i32 = 0; k < 9; k = k + 1) {
    ux = ux + inBuf[(base + k)] * f32(cx[k]);
    uy = uy + inBuf[(base + k)] * f32(cy[k]);
  }
  ux = ux / rho; uy = uy / rho;
  let uu: f32 = ux*ux + uy*uy;
  for (var k: i32 = 0; k < 9; k = k + 1) {
    let cu: f32 = f32(cx[k]) * ux + f32(cy[k]) * uy;
    let feq: f32 = w[k] * rho * (1.0 + 3.0*cu/cs2 + 4.5*(cu*cu)/(cs2*cs2) - 1.5*uu/cs2);
    let fin: f32 = inBuf[(base + k)];
    outBuf[(base + k)] = fin - (fin - feq) / uTau;
  }
}
