#include "../src/external/json/json.hpp"

#include "model/object/DownloadFileObjectInfo.h"

std::string VolcengineTos::DownloadFileObjectInfo::dump() {
    nlohmann::json j;
    j["ETag"] = eTag_;
    j["HashCrc64ecma"] = hashCrc64ecma_;
    j["LastModified"] = lastModified_;
    j["ObjectSize"] = objectSize_;
    return j.dump();
}
void VolcengineTos::DownloadFileObjectInfo::load(const std::string& info) {
    auto j = nlohmann::json::parse(info);
    if (j.contains("ETag"))
        j.at("ETag").get_to(eTag_);
    if (j.contains("HashCrc64ecma"))
        j.at("HashCrc64ecma").get_to(hashCrc64ecma_);
    if (j.contains("LastModified"))
        j.at("LastModified").get_to(lastModified_);
    if (j.contains("ObjectSize"))
        j.at("ObjectSize").get_to(objectSize_);
}
