#pragma once
#include <vector>;
#include "raid.h"

//Forward declaration of used IMGUI data structures
struct ImVec2;

static DisplayGate ValtanGateProgress = DisplayGate::GATE_ONE;
static int ValtanGateOneCounter = 0;
static std::vector<RaidMech> ValtanGateOneMechs;

static int ValtanGateTwoCounter = 0;
static std::vector<RaidMech> ValtanGateTwoMechs;

bool InitValtanMechs();
void ProcessValtanMechs(bool& expandedWindow, ImVec2 _MousePos);


