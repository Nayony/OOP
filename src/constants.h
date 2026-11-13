#ifndef CONSTANTS
#define CONSTANTS

namespace MapSettings {
    inline constexpr int InitialWidth = 20;
    inline constexpr int InitialHeight = 20;
    inline constexpr int InitialBlockedCellCount = 10;
    inline constexpr int MaxStatusesOnCell = 2;
    inline constexpr int MinWidth = 20;
    inline constexpr int MaxWidth = 25;
    inline constexpr int MinHeight = 20;
    inline constexpr int MaxHeight = 25;
    inline constexpr int EnemySearchStride = -2;
    constexpr int FactorySize = 2;
    constexpr int FactoryRingSize = 4;
    constexpr int FactoryRingStep = 1;
    constexpr int RobotRingSize = 3;
    constexpr int RobotRingStep = 2;
    
}

namespace PlayerSettings {
    inline constexpr int MaxHp = 8;
    inline constexpr int MaxEnergy = 3;
    inline constexpr int XpToLevel = 80;
    inline constexpr int Damage = 10;
    inline constexpr int VisibilityRadius = 777;//убрать
    inline constexpr int MaxSpeed = 4;
}

namespace RobotSettings {
    inline constexpr int EnemyMaxHp = 100;
    inline constexpr int EnemyMaxEnergy = 2;
    inline constexpr int EnemyXpToLevel = 240;
    inline constexpr int EnemyDamage = 4;
    inline constexpr int EnemyMaxSpeed = 2;
    inline constexpr int MaxFailedMoveAttempts = 10;
    inline constexpr int CurrentHpPerLevel = 2;
    inline constexpr int MaxHpPerLevel = 5;
}

namespace GameSettings {
    inline constexpr int NormalEnemyCount = 3;
    inline constexpr int XpForKill = 80;
}

namespace FactorySettings {
    inline constexpr int SpawnPeriod = 5;
}

namespace CellSettings {
    inline constexpr int ImpassableCost = -1;
    inline constexpr int DefaultMoveCost = 1;
    inline constexpr int DifficultMoveCost = 2;
}

namespace ApplicationSettings {
    inline constexpr int DefaultEnemyCount = 3;
    inline constexpr int WindowWidth = 1300;
    inline constexpr int WindowHeight = 1300;
    inline constexpr int FrameRateLimit = 60;
    inline constexpr char WindowTitle[] = "Baldur's Gate 4";
}

namespace VisualSettings {
    struct Rgba {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char alpha;
    };

    inline constexpr float WindowPaddingMultiplier = 2.f;
    inline constexpr float CenteringDivisor = 2.f;



    inline constexpr float DamageTextWidthFactor = 1.5f;
    inline constexpr int EndStateTextSize = 100;
    inline constexpr int StandartTextSize = 30;
    inline constexpr int SpecificationTextSize = 25;
    inline constexpr int RobotTextSize = 15;
    inline constexpr int AbilityDescriptionSize = 20;
    inline constexpr int SpecificationCount = 6;
    inline constexpr int CrossVertexCount = 4;
    inline constexpr float CellOutlineThickness = 1.f;
    inline constexpr unsigned char VisibleAlpha = 255;
    inline constexpr unsigned char ExploredAlpha = 128;
    inline constexpr unsigned char HiddenOutlineAlpha = 64;

    inline constexpr Rgba PlayerColor{0, 0, 255, 255};
    inline constexpr Rgba EnemyColor{255, 0, 0, 255};
    inline constexpr Rgba HighlightColor{255, 255, 0, 255};
    inline constexpr Rgba TextColor{255, 255, 255, 255};
    inline constexpr Rgba BackgroundColor{0, 0, 0, 255};
    inline constexpr Rgba TransparentColor{0, 0, 0, 0};
    inline constexpr Rgba CrossColor{255, 255, 255, 255};
    inline constexpr Rgba FactoryColor{255, 170, 45, 255};
    inline constexpr Rgba DifficultCellColor{161, 208, 252, 255};
    inline constexpr Rgba CellOutlineColor{91, 183, 186, 255};
    inline constexpr Rgba AbilityCellOutlineColor{120,6,6,255};
    inline constexpr Rgba WhiteColor{255,255,255,255};

    

    inline constexpr float MapMarginLeft = 20;
    inline constexpr float MapMarginRight = 220;
    inline constexpr float MapMarginTop = 80;
    inline constexpr float MapMarginBot = 160;

    inline constexpr float SpecificationTextOffsetX = ApplicationSettings::WindowWidth - VisualSettings::MapMarginRight + 5;
    inline constexpr float SpecificationTextOffsetY = MapMarginTop - 10;
    inline constexpr float SpecificationTextOffsetBetween = 30.f;
    inline constexpr float SpecificationTextOffsetTopic = 50.f;

    inline constexpr float ButtonSize = 60;
    
    inline constexpr float AbilityPanelOffsetY = ApplicationSettings::WindowHeight - VisualSettings::MapMarginBot/2 - ButtonSize/2 ;
    inline constexpr float AbilityPanelOffsetX = 100;
    inline constexpr int AbilitySlotCount = 4;

    
    inline constexpr float GuideAbilityPanelWidth = 560;
    inline constexpr float GuideAbilityPanelHeight = 210;
    inline constexpr float GuideAbilityTopicOffsetY = 5;
    inline constexpr float GuideAbilityDescOffsetX = 5;
    inline constexpr Rgba  GuideAbilityOutlineColor{25,25,33,255};
    
    inline constexpr float OutlineThickness = 7;
    inline constexpr float ButtonOffset = (ApplicationSettings::WindowWidth - AbilityPanelOffsetX   - MapMarginLeft - MapMarginRight - VisualSettings::ButtonSize)/3;
    
    inline constexpr float StatusInfoTextOffsetX = 0;
    inline constexpr float StatusInfoTextOffsetY = 14;
    inline constexpr float StatusInfoTextSize = 12;



}


namespace AbilitiesSettings {
    inline constexpr int StandartEnergyCost = 2;
    inline constexpr int MaxLvl = 3;


    inline constexpr int AroundHitRadius = 1;
    inline constexpr int AroundHitRadiusDelta = 1;

    inline constexpr int FarHitRadius = 3;
    inline constexpr int FarHitBonusDamage = 2;
    inline constexpr int FarHitDamageDelta = 2;
    
    inline constexpr int HealPower = 1;
    inline constexpr int HealPowerDelta = 1;
    inline constexpr int HealEnergyCost = 1;
    
    inline constexpr int TeleportRadius = 3;
    inline constexpr int TeleportEnergyCost = 2;
    inline constexpr int TeleportEnergyCostDelta = -1;


}

namespace StatusesSettings {
    inline constexpr int MaxStatusesCount = 4;

    inline constexpr int OverloadDuration = 1;
    
    inline constexpr int BurnDuration = 3;
    inline constexpr int BurnDamage = 2;
    
    inline constexpr int SlowthDuration = 1;
    
    inline constexpr int ShieldEndurance = 2;
    inline constexpr int MiniShieldDuration = 2;
}
namespace TimeSettings {
    inline constexpr float FlashDamageDur = 0.5;
    inline constexpr float AroundHitDur = 1.3;

}

#endif
