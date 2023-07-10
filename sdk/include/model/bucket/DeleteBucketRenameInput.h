#pragma once
#include <string>
#include <utility>
namespace VolcengineTos {
class DeleteBucketRenameInput {
public:
    explicit DeleteBucketRenameInput(std::string bucket) : bucket_(std::move(bucket)) {
    }
    DeleteBucketRenameInput() = default;
    virtual ~DeleteBucketRenameInput() = default;
    const std::string& getBucket() const {
        return bucket_;
    }
    void setBucket(const std::string& bucket) {
        bucket_ = bucket;
    }

private:
    std::string bucket_;
};
}  // namespace VolcengineTos
