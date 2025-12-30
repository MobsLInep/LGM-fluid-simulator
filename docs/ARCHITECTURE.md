Architecture

- math/: vector, constants, config
- simulation/: grid (fA/fB ping-pong), simulator (collide/stream/boundary)
 - simulation/: grid (fA/fB ping-pong), simulator (collide/stream/boundary)
   - Collision: BGK with D2Q9 `w`, `c`, `cs2`; optional body force
   - Boundary: bounce-back at `y=0` and `y=H-1` using `opposite[]`
   - Streaming: pull from neighbors; periodic in X; Y-boundary uses bounce-back when OOB or neighbor is wall
- gpu/: GPUContext, BufferManager, ComputePipeline, Renderer (stubs)
- ui/: InputHandler (stub), Visualization metrics
- core/: Application orchestrates initialize → run → shutdown
- shaders/: WGSL kernels for future GPU pipelines
 - run behavior: 200 frames; impulse at frame 10; per-frame profiling and diagnostics
