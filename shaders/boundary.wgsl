@group(0) @binding(0) var<storage, read> inBuf: array<f32>;
@group(0) @binding(1) var<storage, read_write> outBuf: array<f32>;
@group(0) @binding(2) var<storage, read> walls: array<u32>;
@group(0) @binding(3) var<uniform> uWidth: i32;
@group(0) @binding(4) var<uniform> uHeight: i32;
const opp: array<i32,9> = array<i32,9>(0,3,4,1,2,7,8,5,6);
@compute @workgroup_size(8,8)
fn main(@builtin(global_invocation_id) gid: vec3<u32>) {
  let x: i32 = i32(gid.x);
  let y: i32 = i32(gid.y);
  if (x >= uWidth || y >= uHeight) { return; }
  if (walls[y * uWidth + x] == 0u) { return; }
  let base: i32 = (y * uWidth + x) * 9;
  for (var k: i32 = 0; k < 9; k = k + 1) {
    outBuf[(base + k)] = inBuf[(base + opp[k])];
  }
}
