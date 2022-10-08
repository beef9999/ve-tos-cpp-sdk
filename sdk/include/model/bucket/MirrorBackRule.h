#pragma once

#include <string>
#include "Condition.h"
#include "Redirect.h"
namespace VolcengineTos {
class MirrorBackRule {
public:
    const std::string& getId() const {
        return id_;
    }
    void setId(const std::string& id) {
        id_ = id;
    }
    const Condition& getCondition() const {
        return condition_;
    }
    void setCondition(const Condition& condition) {
        condition_ = condition;
    }
    const Redirect& getRedirect() const {
        return redirect_;
    }
    void setRedirect(const Redirect& redirect) {
        redirect_ = redirect;
    }

private:
    std::string id_;
    Condition condition_;
    Redirect redirect_;
};
}  // namespace VolcengineTos