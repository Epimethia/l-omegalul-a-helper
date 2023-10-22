#include "raid.h"


RaidMech::RaidMech(std::string _MechName, std::string _HPBarValue, std::string _QuickRef, std::string _LongRef)
{
    RaidMechName = _MechName;
    HealthBarTriggerValue = _HPBarValue;
    RaidMechQuickRef = _QuickRef;
    RaidMechLongRef = _LongRef;
}


void ProcessHeaderRows(std::string _TableName, int& GateMechCounter, std::vector<RaidMech>& _RaidMechVect)
{
    RaidMech CurrentRaidMech = _RaidMechVect[GateMechCounter];
    // Header Row Setup (Mech Name, Health Bar Value, Brief Description, [Prv. / Nxt.] Buttons)
    if (ImGui::BeginTable(_TableName.c_str(), 3)) {

        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 300.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 30.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 30.0f);

        ImGui::TableHeadersRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text(std::string(" >  " + CurrentRaidMech.HealthBarTriggerValue + "X - " + CurrentRaidMech.RaidMechName).c_str());

        ImGui::TableSetColumnIndex(1);
        ImGui::Indent(3.0f);
        ImGui::Text("Prv.", 1, 1);

        ImGui::TableSetColumnIndex(2);
        ImGui::Indent(3.0f);
        ImGui::Text("Nxt.", 2, 2);

        ImGui::TableNextRow(0, 30.0f);
        ImGui::TableSetColumnIndex(0);
        ImGui::Text(CurrentRaidMech.RaidMechQuickRef.c_str());
        ImGui::TableSetColumnIndex(1);
        ImGui::Indent(6.0f);
        if (ImGui::ArrowButton("##PrevMech", ImGuiDir_Left)) {

            (GateMechCounter > 0) ? GateMechCounter-- : GateMechCounter = 0;

        }
        ImGui::TableSetColumnIndex(2);
        ImGui::Indent(8.0f);
        if (ImGui::ArrowButton("##NextMech", ImGuiDir_Right)) {
            int GateTwoMechSize = _RaidMechVect.size() - 1;
            GateMechCounter < GateTwoMechSize ?
                GateMechCounter++ :
                GateMechCounter = GateTwoMechSize;

        }
        ImGui::EndTable();
        ImGui::Unindent();
    }
}