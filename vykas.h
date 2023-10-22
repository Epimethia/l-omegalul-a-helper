#pragma once
#include <vector>;
#include "raid.h"

//Forward declaration of used IMGUI data structures
struct ImVec2;

//static int VykasGateOneCounter = 0;
//static std::vector<RaidMech> VykasGateOneMechs;

static std::vector<RaidMech> VykasGateOneMechs;

static std::vector<RaidMech> VykasGateTwoMechs;

bool InitVykasMechs();
void ProcessVykasMechs(bool& expandedWindow, ImVec2 _MousePos);
