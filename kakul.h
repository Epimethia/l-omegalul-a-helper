#pragma once
#include <vector>;
#include "raid.h"

//Forward declaration of used IMGUI data structures
struct ImVec2;

static int KakulGateOneCounter = 0;
static std::vector<RaidMech> KakulGateOneMechs;

static int KakulGateTwoCounter = 0;
static std::vector<RaidMech> KakulGateTwoMechs;

static int KakulGateThreeCounter = 0;
static std::vector<RaidMech> KakulGateThreeMechs;

bool InitKakulMechs();
void ProcessKakulMechs(bool& expandedWindow, ImVec2 _MousePos);
