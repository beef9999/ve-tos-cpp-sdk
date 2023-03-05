#include "../src/external/json/json.hpp"

#include "model/bucket/GetBucketMirrorBackOutput.h"
#include "model/bucket/MirrorBackRule.h"

void VolcengineTos::GetBucketMirrorBackOutput::fromJsonString(const std::string& input) {
    auto j = nlohmann::json::parse(input);
    if (j.contains("Rules")) {
        nlohmann::json rules = j.at("Rules");
        for (auto& r : rules) {
            MirrorBackRule rule_;
            if (r.contains("ID")) {
                rule_.setId(r.at("ID").get<std::string>());
            }
            if (r.contains("Condition")) {
                nlohmann::json condition = r.at("Condition");
                Condition condition_;
                if (condition.contains("HttpCode")) {
                    condition_.setHttpCode(condition.at("HttpCode").get<int>());
                }
                rule_.setCondition(condition_);
            }
            if (r.contains("Redirect")) {
                auto redirect = r.at("Redirect");
                Redirect redirect_;
                if (redirect.contains("RedirectType")) {
                    redirect_.setRedirectType(StringtoRedirectType[redirect.at("RedirectType").get<std::string>()]);
                }
                if (redirect.contains("FetchSourceOnRedirect")) {
                    redirect_.setFetchSourceOnRedirect(redirect.at("FetchSourceOnRedirect").get<bool>());
                }
                if (redirect.contains("PassQuery")) {
                    redirect_.setPassQuery(redirect.at("PassQuery").get<bool>());
                }
                if (redirect.contains("FollowRedirect")) {
                    redirect_.setFollowRedirect(redirect.at("FollowRedirect").get<bool>());
                }
                if (redirect.contains("MirrorHeader")) {
                    MirrorHeader mirrorHeader_;
                    auto mirrorHeader = redirect.at("MirrorHeader");
                    if (mirrorHeader.contains("PassAll")) {
                        mirrorHeader_.setPassAll(mirrorHeader.at("PassAll").get<bool>());
                    }
                    if (mirrorHeader.contains("Pass")) {
                        mirrorHeader_.setPass(mirrorHeader.at("Pass").get<std::vector<std::string>>());
                    }
                    if (mirrorHeader.contains("Remove")) {
                        mirrorHeader_.setRemove(mirrorHeader.at("Remove").get<std::vector<std::string>>());
                    }
                    redirect_.setMirrorHeader(mirrorHeader_);
                }
                if (redirect.contains("PublicSource")) {
                    auto publicSource = redirect.at("PublicSource");
                    PublicSource publicSource_;
                    if (publicSource.contains("SourceEndpoint")) {
                        SourceEndpoint sourceEndpoint_;
                        auto sourceEndpoint = publicSource.at("SourceEndpoint");
                        if (sourceEndpoint.contains("Primary")) {
                            sourceEndpoint_.setPrimary(sourceEndpoint.at("Primary").get<std::vector<std::string>>());
                        }
                        if (sourceEndpoint.contains("Follower")) {
                            sourceEndpoint_.setFollower(sourceEndpoint.at("Follower").get<std::vector<std::string>>());
                        }
                        publicSource_.setSourceEndpoint(sourceEndpoint_);
                    }
                    redirect_.setPublicSource(publicSource_);
                }
                rule_.setRedirect(redirect_);
            }
            rules_.emplace_back(rule_);
        }
    }
}