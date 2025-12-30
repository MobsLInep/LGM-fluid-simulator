#pragma once
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace lbm::gpu {

class BufferManager {
public:
    using BufferId = uint32_t;

    BufferId createBuffer(std::size_t size);
    bool uploadData(BufferId id, const void* data, std::size_t size, std::size_t offset = 0);
    const std::vector<std::uint8_t>* getBuffer(BufferId id) const;
    void destroyAll();

private:
    std::unordered_map<BufferId, std::vector<std::uint8_t>> buffers;
    BufferId nextId = 1;
};

}

