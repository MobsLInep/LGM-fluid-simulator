#include "gpu/buffer_manager.h"
#include <algorithm>

namespace lbm::gpu {

BufferManager::BufferId BufferManager::createBuffer(std::size_t size) {
    BufferId id = nextId++;
    buffers[id] = std::vector<std::uint8_t>(size, 0);
    return id;
}

bool BufferManager::uploadData(BufferId id, const void* data, std::size_t size, std::size_t offset) {
    auto it = buffers.find(id);
    if (it == buffers.end() || offset + size > it->second.size()) return false;
    const auto* src = static_cast<const std::uint8_t*>(data);
    std::copy(src, src + size, it->second.begin() + static_cast<std::ptrdiff_t>(offset));
    return true;
}

const std::vector<std::uint8_t>* BufferManager::getBuffer(BufferId id) const {
    auto it = buffers.find(id);
    if (it == buffers.end()) return nullptr;
    return &it->second;
}

void BufferManager::destroyAll() {
    buffers.clear();
}

}

