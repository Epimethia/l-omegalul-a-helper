#pragma once
#include <string>
#include <vector>
#include "imgui/imgui.h"


struct RaidMech {
    RaidMech(std::string _MechName, std::string _HPBarValue, std::string _QuickRef, std::string _LongRef);
    std::string RaidMechName;
    std::string HealthBarTriggerValue;
    std::string RaidMechQuickRef;
    std::string RaidMechLongRef;
};

enum class DisplayGate {
    GATE_ONE,
    GATE_TWO,
    GATE_THREE,
    GATE_FOUR
};

struct ID3D11ShaderResourceView;

struct RaidMechResourceImage {
    ImVec2 ImgSize;
    ID3D11ShaderResourceView* texture;
};

void ProcessHeaderRows(std::string _TableName, int& GateMechCounter, std::vector<RaidMech>& _RaidMechVect);

static int VykasGateOneCounter = 0;
static int VykasGateTwoCounter = 0;