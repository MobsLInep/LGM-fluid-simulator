@group(0) @binding(0) var<storage, read> inBuf: array<f32>;
@group(0) @binding(1) var<storage, read_write> outBuf: array<f32>;
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
  for (var k: i32 = 0; k < 9; k = k + 1) {
    var nx: i32 = x - cx[k];
    var ny: i32 = y - cy[k];
    if (nx < 0) { nx = uWidth - 1; }
    if (nx >= uWidth) { nx = 0; }
    if (ny < 0) { ny = 0; }
    if (ny >= uHeight) { ny = uHeight - 1; }
    let srcBase: i32 = (ny * uWidth + nx) * 9;
    outBuf[(base + k)] = inBuf[(srcBase + k)];
  }
}
