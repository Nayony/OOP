#include "AbilityInfo.h"

AbilityInfo::AbilityInfo()
    : _names{"AroundHit", "FarHit", "Heal", "Teleport"},
      _descriptions{
          "Deals damage equal to the character's attack to all\nnearby enemies.\n\nStandart Cost: 2\nRadius upgrade: 1/2\nUnlocked at max lvl: Overload",
          "Deals damage to one chosen enemy within 3 cells.\n\n\nStandart Cost: 2\nDamage upgrade: +2/+4\nUnlocked at max lvl: Burn",
          "Restores HP to the user.\n\n\nStandart Cost: 1\nHeal upgrade: 1/2\nUnlocked at max lvl: Overheal (shield)",
          "Teleports the user to a chosen free cell within 3 cells.\n\n\nStandart Cost: 2\nEnergy upgrade: 2/1\nUnlocked at max lvl: None"
      }
{}

const std::string& AbilityInfo::GetName(int abilityId) const {
    if (abilityId < 1 || static_cast<std::size_t>(abilityId - 1) >= _names.size()) {
        return _names.front();
    }
    return _names.at(static_cast<std::size_t>(abilityId - 1));
}

const std::string& AbilityInfo::GetDescription(int abilityId) const {
    if (abilityId < 1 || static_cast<std::size_t>(abilityId - 1) >= _descriptions.size()) {
        return _descriptions.front();
    }
    return _descriptions.at(static_cast<std::size_t>(abilityId - 1));
}