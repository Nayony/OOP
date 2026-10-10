#ifndef CONSTANTS
#define CONSTANTS

namespace MapSettings {
    inline constexpr int InitialWidth = 12;
    inline constexpr int InitialHeight = 12;
    inline constexpr int InitialBlockedCellCount = 10;
    inline constexpr int MinWidth = 12;
    inline constexpr int MaxWidth = 20;
    inline constexpr int MinHeight = 12;
    inline constexpr int MaxHeight = 20;
    inline constexpr int EnemySearchStride = -2;
    constexpr int FactorySize = 2;
    constexpr int FactoryRingSize = 4;
    constexpr int FactoryRingStep = 1;
    constexpr int RobotRingSize = 3;
    constexpr int RobotRingStep = 2;
}

namespace PlayerSettings {
    inline constexpr int MaxHp = 8;
    inline constexpr int MaxEnergy = 2;
    inline constexpr int XpToLevel = 240;
    inline constexpr int Damage = 10;
    inline constexpr int VisibilityRadius = 333;
    inline constexpr int MaxSpeed = 2;
}

namespace RobotSettings {
    inline constexpr int EnemyMaxHp = 10;
    inline constexpr int EnemyMaxEnergy = 1;
    inline constexpr int EnemyXpToLevel = 240;
    inline constexpr int EnemyDamage = 4;
    inline constexpr int EnemyMaxSpeed = 3;
    inline constexpr int MaxFailedMoveAttempts = 10;
    inline constexpr int CurrentHpPerLevel = 2;
    inline constexpr int MaxHpPerLevel = 5;
}

namespace GameSettings {
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

    inline constexpr float MapOffsetX = 20.f;
    inline constexpr float MapOffsetY = 50.f;
    inline constexpr float WindowPaddingMultiplier = 2.f;
    inline constexpr float CenteringDivisor = 2.f;
    inline constexpr float SpecificationSlotDivisor = 4.f;
    inline constexpr float SpecificationTextOffset = 10.f;
    inline constexpr float DamageTextWidthFactor = 1.5f;
    inline constexpr int EndStateTextSize = 100;
    inline constexpr int SpecificationTextSize = 30;
    inline constexpr int RobotTextSize = 20;
    inline constexpr int SpecificationCount = 4;
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
}

#endif