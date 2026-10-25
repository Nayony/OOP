#ifndef ABILITY_INFO_H
#define ABILITY_INFO_H

#include <string>
#include <vector>

class AbilityInfo {
public:
    AbilityInfo();

    const std::string& GetName(int abilityId) const;
    const std::string& GetDescription(int abilityId) const;

private:
    std::vector<std::string> _names;
    std::vector<std::string> _descriptions;
};

#endif