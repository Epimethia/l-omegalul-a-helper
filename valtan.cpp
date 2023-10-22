#include "valtan.h"
#include "imgui/imgui.h"
#include <d3d11.h>
#include "raid.h"
#include "HelperFunctions.h"
#include "resource.h"

//static ID3D11ShaderResourceView* ValtanMechOneImg = nullptr;
static RaidMechResourceImage ValtanMechOneImg;
static RaidMech* CurrentRaidMech = nullptr;

bool InitValtanMechs()
{
    //Gate One Mechanics
    {
        ValtanGateOneMechs.push_back(
            RaidMech(
                "Leader Leguru Split",

                "45",
                "Avoid centre explosion. DPS Red Wolf.\n",

                ">The Dark Mountain Predator will channel and split into two wolves."
                "\n\n>Avoid the centre explosion after he teleports."
                "\n\n>You will then fight the Red Wolf, Leader Leguru."
            )
        );

        ValtanGateOneMechs.push_back(
            RaidMech(
                "Invasion - Destroyer Lucas",

                "40",
                "Blue Wolf invades. Split up the wolves.\n"
                "Gold buff - attack Blue Wolf.Leaves at X35.",

                ">Destroyer Lucas [Blue] will invade the arena."
                "\n\n>The first player hit by each wolf will get a target. The wolves aggro towards the targeted players."
                "\n\n>The wolves gain a massive damage reduction buff when near each other. Use the aggros to position the bosses away from each other to avoid this."
                "\n\n>Players with the [Gold Buff] should attack the invader, while the others should attack the main wolf."
            )
        );

        ValtanGateOneMechs.push_back(
            RaidMech(
                "First Orbs - Leader Luguru",
                "30",
                "Go to position. Collect orb and stagger the boss.\n""Blue Wolf will appear after.",
                "Leader Leguru will teleport to the middle and begin channeling. \n\n>Go to your predetermined position and collect your orb in order before staggering the boss. \n\n>Short DPS window before Destroyer Lucas, the Blue Wolf appears."
            )
        );

        ValtanGateOneMechs.push_back(
            RaidMech(
                "Invasion - Leader Luguru",
                "25",
                "Same as X40 Invasion. Red Wolf leaves at X20.\n",
                "Same as the first Invasion, but the opposite wolf. \n\n>First player hit by each boss will get a target on their head, allowing them to split the bosses.  \n\n>Players with the Gold Buff should attack the invader."
            )
        );

        ValtanGateOneMechs.push_back(
            RaidMech(
                "Second Orbs - Destroyer Lucas",
                "15",
                "Same as X30 Orbs.\n""Ground explosions after. Wei - run to 6 o'clock.",
                "Destroyer Lucas will teleport to the middle and begin channeling. Go to your predetermined position and collect your orb in order before staggering the boss. Short DPS window before Destroyer Lucas begins doing ground explosions and recombinding into The Dark Mountain Predator."
            )
        );
    }

    //Valtan Gate Two Mechs
    {
        ValtanGateTwoMechs.push_back(
            RaidMech(
                "Charges, Pillar Break and Destruction",
                "160",
                "Aim Valtan's charges at nearby pillars. Pick up Blue Orbs.\n[Weak Point] to break Valtan's armour stacks.",
                "Valtan will pick a random player and stomp twice before charging at them. Bait him to charge into one of the four pillars on the map.\n"
                "When Valtan hits "
            )
        );

        ValtanGateTwoMechs.push_back(
            RaidMech(
                "Axe Wipe",
                "130",
                "Valtan does arena wipe. Survive by having Blue Orb aura \nor using [Sidereal Balthor]",
                "TODO Long Description."
            )
        );

        ValtanGateTwoMechs.push_back(
            RaidMech(
                "Cone Attack",
                "105",
                "Hide behind pillar. If targeted, aim cone away from raid \nmembers. Get to safety before attack.",
                "TODO Long Description."
            )
        );

        ValtanGateTwoMechs.push_back(
            RaidMech(
                "First Arena Break",
                "88",
                "Head to the middle to determine the safe side of the arena \nto avoid falling off.",
                "TODO Long Description."
            )
        );

        ValtanGateTwoMechs.push_back(
            RaidMech(
                "Scripted Counter",
                "64",
                "Dodge Centre stomp and place puddles together. Counter Valtan after animation.",
                "TODO Long Description."
            )
        );


        ValtanGateTwoMechs.push_back(
            RaidMech(
                "Second Arena Break",
                "34",
                "Head to the broken side of the arena to avoid falling off.",
                "TODO Long Description."
            )
        );


        ValtanGateTwoMechs.push_back(
            RaidMech(
                "Ghost Transition",
                "15",
                "Gather at 9'oclock to avoid the pizza attacks\nTimestop, [Sidereal Balthor] or run around the arena while dodging slams and pillars.",
                "TODO Long Description."
            )
        );

        ValtanGateTwoMechs.push_back(
            RaidMech(
                "Ghost Phase",
                "30 - 0",
                "DPS Valtan while dodging his ground slams, spins and grabs. \nGhosts at the map edge.",
                "TODO Long Description."
            )
        );
    }

    if (!LoadTextureFromFile("./Resources/Legion Raid Icons/valtan.png", &ValtanMechOneImg.texture)) {
        return false;
    }

    return true;
}

void ProcessValtanMechs(bool& expandedWindow, ImVec2 _MousePos)
{

    switch (ValtanGateProgress) {

        case DisplayGate::GATE_ONE: {
            CurrentRaidMech = &ValtanGateOneMechs[ValtanGateOneCounter];
            ValtanGateTwoCounter = 0;

            ProcessHeaderRows("Valtan Gate One", ValtanGateOneCounter, ValtanGateOneMechs);

            if (expandedWindow = ImGui::CollapsingHeader("More Details")) {

                if (ImGui::BeginTable("More Details", 2)) {
                    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 250);

                    ImGui::TableNextColumn();
                    ImGui::Image((void*)ValtanMechOneImg.texture, { 250, 250 });

                    ImGui::TableNextColumn();
                    ImGui::TextWrapped(CurrentRaidMech->RaidMechLongRef.c_str());
                    ImGui::EndTable();

                }
            }
            ImGui::EndTabItem();
            break;
        }

        case DisplayGate::GATE_TWO: {
            CurrentRaidMech = &ValtanGateTwoMechs[ValtanGateTwoCounter];
            ValtanGateOneCounter = 0;

            ProcessHeaderRows("Valtan Gate Two", ValtanGateTwoCounter, ValtanGateTwoMechs);

            if (expandedWindow = ImGui::CollapsingHeader("More Details")) {

                if (ImGui::BeginTable("More Details", 2)) {
                    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 250);

                    ImGui::TableNextColumn();
                    ImGui::Image((void*)ValtanMechOneImg.texture, { 250, 250 });

                    ImGui::TableNextColumn();
                    ImGui::TextWrapped(CurrentRaidMech->RaidMechLongRef.c_str());
                    ImGui::EndTable();
                }
            }

            ImGui::EndTabItem();
            break;
        }
        default:
            break;
    }
    
}

//
//
//void ProcessValtanMechs(bool& expandedWindow, ImVec2 _MousePos)
//{
//
//    if (ImGui::BeginTabBar("Valtan Gates")) {
//
//        if (ImGui::BeginTabItem("Valtan Gate One")) {
//            CurrentRaidMech = &ValtanGateOneMechs[ValtanGateOneCounter];
//            ValtanGateTwoCounter = 0;
//
//            ProcessHeaderRows("Valtan Gate One", ValtanGateOneCounter, ValtanGateOneMechs);
//
//
//            if (expandedWindow = ImGui::CollapsingHeader("More Details")) {
//
//                if (ImGui::BeginTable("More Details", 2)) {
//                    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 250);
//
//                    ImGui::TableNextColumn();
//                    ImGui::Image((void*)ValtanMechOneImg.texture, { 250, 250 });
//
//                    ImGui::TableNextColumn();
//                    ImGui::TextWrapped(CurrentRaidMech->RaidMechLongRef.c_str());
//                    ImGui::EndTable();
//
//                }
//            }
//            ImGui::EndTabItem();
//        }
//
//        if (ImGui::BeginTabItem("Valtan Gate Two")) {
//            CurrentRaidMech = &ValtanGateTwoMechs[ValtanGateTwoCounter];
//            ValtanGateOneCounter = 0;
//
//            ProcessHeaderRows("Valtan Gate Two", ValtanGateTwoCounter, ValtanGateTwoMechs);
//
//            if (expandedWindow = ImGui::CollapsingHeader("More Details")) {
//
//                if (ImGui::BeginTable("More Details", 2)) {
//                    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 250);
//
//                    ImGui::TableNextColumn();
//                    ImGui::Image((void*)ValtanMechOneImg.texture, { 250, 250 });
//
//                    ImGui::TableNextColumn();
//                    ImGui::TextWrapped(CurrentRaidMech->RaidMechLongRef.c_str());
//                    ImGui::EndTable();
//                }
//            }
//
//            ImGui::EndTabItem();
//        }
//    }
//    ImGui::EndTabBar();
//}
