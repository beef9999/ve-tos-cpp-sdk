#pragma once

#include <string>
#include <vector>
#include "../src/external/json/json.hpp"
#include "CORSRule.h"
namespace VolcengineTos {
class PutBucketCORSInput {
public:
    const std::string& getBucket() const {
        return bucket_;
    }
    void setBucket(const std::string& bucket) {
        bucket_ = bucket;
    }
    const std::vector<CORSRule>& getRules() const {
        return rules_;
    }
    void setRules(const std::vector<CORSRule>& rules) {
        rules_ = rules;
    }
    std::string toJsonString() const {
        nlohmann::json j;
        nlohmann::json ruleArray = nlohmann::json::array();
        for (auto& r : rules_) {
            nlohmann::json rule;
            if (!r.getAllowedOrigins().empty()) {
                nlohmann::json ao(r.getAllowedOrigins());
                rule["AllowedOrigins"] = ao;
            }
            if (!r.getAllowedMethods().empty()) {
                nlohmann::json am(r.getAllowedMethods());
                rule["AllowedMethods"] = am;
            }
            if (!r.getAllowedHeaders().empty()) {
                nlohmann::json ah(r.getAllowedHeaders());
                rule["AllowedHeaders"] = ah;
            }
            if (!r.getExposeHeaders().empty()) {
                nlohmann::json eh(r.getExposeHeaders());
                rule["ExposeHeaders"] = eh;
            }
            if (r.getMaxAgeSeconds() != 0) {
                rule["MaxAgeSeconds"] = std::to_string(r.getMaxAgeSeconds());
            }
            ruleArray.push_back(rule);
        }
        return j.dump();
    }

private:
    std::string bucket_;
    std::vector<CORSRule> rules_;
};
}  // namespace VolcengineTos