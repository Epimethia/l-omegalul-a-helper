#include "vykas.h"
#include "imgui/imgui.h"
#include <d3d11.h>
#include "raid.h"
#include "HelperFunctions.h"
#include "resource.h"

//static ID3D11ShaderResourceView* ValtanMechOneImg = nullptr;
static RaidMechResourceImage ValtanMechOneImg;
static RaidMech* CurrentRaidMech = nullptr;


bool InitVykasMechs()
{

    // OLD - Gate One Mechanics. Whole thing was removed lmao
    /*
    {
        VykasGateOneMechs.push_back(
            RaidMech(
                "Morphe Split",
                "52",
                "Morphe teleports to the middle and splits into Human \nand Demon Forms. Both parties will fight separate forms.",

                ">Morphe will split into Human and Demon form.\n\n"
                ">[PURPLE] Demon Form:\n - Has less mechanics but does more damage and has more HP.\n - Ground attack indicators are inverted. [Purple] zones are safe.\n\n"
                ">[BLUE] Human Form:\n - Is weaker and has less HP\n - Mechanics affect both parties, and must be called out."
            )
        );

        VykasGateOneMechs.push_back(
            RaidMech(
                "Orb Gates [BLUE FORM]",
                "50",
                "3X+1 Positions. Stand inside initial blast.\nGuide the ball into the gate at the right time and color.",

                ">Morphe will teleport to the centre and begin channeling.\n\n"
                ">After a short delay, an arena wide blast with a safe zone around Morphe will occur. Gates will spawn in 3X+1 position.\n\n"
                ">A summoning circle will note where the initial spawn point of the balls are. Balls will begin moving to the right before following the closest player.\n\n"
                ">Balls will rotate from:\n  [RED] > [BLUE] > [GREEN] > ...\nand repeat 3 times."
            )
        );


        VykasGateOneMechs.push_back(
            RaidMech(
                "Black Blue Orbs [BLUE FORM]",
                "37",
                "Stagger. Absorb the balls based on the mark on your\ncharacter. Call the safe position for the opposite party.",

                ">Morphe will teleport to the centre and begin channeling.\n\n"
                ">Stagger Morphe, after which he will mark each player with a [BLUE] or [BLACK] mark.\n\n"
                ">Move to your position based on the color of the mark on your head:\n   - [BLUE]:5 or 10 O'Clock\n   - [BLACK]:1 or 7 O'Clock\n\n"
                ">Memorize the patterns on the ground (follow your color), and mimic the movement to absorb the orbs flying towards Morphe."
            )
        );


        VykasGateOneMechs.push_back(
            RaidMech(
                "Party Switch",
                "30",
                "Morphe teleports to the middle.Both parties swap arenas.\nAvoid initial explosion.",

                ">Once both Forms have been brought to 30X, they will teleport to the centre to swap. Parties swap arenas.\n\n"
                ">Both Forms will do an initial explosion to start the fight. Stay on the edge of the arena until the blast goes off before fighting.\n\n"
            )
        );


        VykasGateOneMechs.push_back(
            RaidMech(
                "Safe Zone [BLUE FORM]",
                "25",
                "Morphe teleports to the middle, and creates 4 zones. Call\nout the position of the [WHITE] zone for the other party.",

                ">Morphe will teleport to the middle and begin channeling. After a short animation and a (non-damaging) blast, 4 zones will appear in both arenas.\n\n"
                ">The party fighting [BLUE] will be able to see one safe zone, marked as [WHITE].\nThey must call this out for the other party, as they can only see [BLACK] zones.\n\n"
            )
        );


        VykasGateOneMechs.push_back(
            RaidMech(
                "Black Blue Orbs 2 [BLUE FORM]",
                "15",
                "Same as 37X. Stagger. Absorb the balls. Call the safe \nposition for the opposite party.",

                ">Morphe will teleport to the centre and begin channeling.\n\n"
                ">Stagger Morphe, after which he will mark each player with a [BLUE] or [BLACK] mark.\n\n"
                ">Move to your position based on the color of the mark on your head:\n   - [BLUE]:5 or 10 O'Clock\n   - [BLACK]:1 or 7 O'Clock\n\n"
                ">Memorize the patterns on the ground (follow your color), and mimic the movement to absorb the orbs flying towards Morphe."
            )
        );
    }
    */

    // Vykas Gate One Mechs
    {
        VykasGateOneMechs.push_back(
            RaidMech(
                "Patterns to Watch - 01",
                "160-120",
                "Not major mechanics but will hinder the other raid members\nif failed.Act as required.",
                ">Circular Lasers: Spread out and run clockwise until lasers are complete.\n\n"
                ">Purple Ring: [TARGET] Lead the ring away, then stand in safe spot. [OTHER] Avoid large AoE explosion\n"
            )
        );

        VykasGateOneMechs.push_back(
            RaidMech(
                "Color Wings + Cross",
                "120",
                "Collect orbs to determine order. Run to the right clone.\n[RED] = [2][1][0] | [PURPLE] = [0][1][2]",

                ">Vykas splits into 3 shadows that go to a corner of the map each. Each clone will have a different position:\n"
                " - [PURPLE] TWO WINGS UP\n"" - [RED] NO WINGS UP\n"" [BLACK/NO GLOW] ONE WING UP\n\n"
            )
        );

        VykasGateOneMechs.push_back(
            RaidMech(
                "Patterns to Watch - 02",
                "120-66",
                "Not major mechanics but will hinder the other raid members\nif failed. Act as required.",
                ">Circular Lasers: Spread out and run clockwise until lasers are complete.\n\n"
                ">Purple Ring: [TARGET] Lead the ring away, then stand in safe spot. [OTHER] Avoid large AoE explosion.\n\n"
                ">Windmills/Revolving Door: Dodge the doors and ground explosions.\n\n"
                ">Purple Pools/Cones: Take these to the edge of the map and face outwards.\n\n"
            )
        );

        VykasGateOneMechs.push_back(
            RaidMech(
                "Black / Red Orbs",
                "65",
                "Go to assigned position and note the [BLACK/RED] flashes\nthe clones do. Block all the [HIDDEN BLACK] orbs.",

                ">Vykas splits into 3 clones. These clones will flash either [BLACK] or [RED] FIVE times. Notify others of the order.\n\n"
                ">This order is the [HIDDEN] color of the five orbs the clones shoot towards Vykas. All will appear [BLACK]. "
                "Work with your partners to block all [HIDDEN BLACK] orbs and avoid all [HIDDEN RED] orbs.\n\n"
                ">Collecting a [HIDDEN RED] or a second [HIDDEN BLACK] orb without [TIMESTOP/SPLENDID PANACEA] will kill you."
            )
        );

        VykasGateOneMechs.push_back(
            RaidMech(
                "Patterns to Watch - 03",
                "64 - 0",
                "Not major mechanics but will hinder the other raid members\nif failed. Act as required.",
                ">Lust Debuff: Getting hit by 3 attacks will trigger a Purple Pool/Cone mechanic on you.\n\n"
                ">Windmills/Revolving Door: Dodge the doors and ground explosions.\n\n"
                ">Worms: Dodge and kill any worms that trap raid members.\n\n"
                ">Purple Pools/Cones: Take these to the edge of the map and face outwards.\n\n"
            )
        );
        
    }

    // Vykas Gate 3
    {
        VykasGateTwoMechs.push_back(
            RaidMech(
                "Swamp Bridge",
                "170",
                "[SWAMP OF DESPAIR] Create a bridge at 9 oclock. [Desire of Swiftness] Stay away until bridge is created, then gather on the bridge.",
                ""
            )
        );

        VykasGateTwoMechs.push_back(
            RaidMech(
                "Swords and Clones",
                "150",
                "Players with high meter must ping swords. Players without will observe statues. Run to the position that contain both a statue and sword.",
                ""
            )
        );

        VykasGateTwoMechs.push_back(
            RaidMech(
                "Typing Test",
                "135",
                "Cleanse meter using the 12 o'clock orb, and complete the typing test. If players fail, supports use damage reduction/shields.",
                ""
            )
        );

        VykasGateTwoMechs.push_back(
            RaidMech(
                "Typing Test",
                "135",
                "Cleanse meter using the 12 o'clock orb, and complete the typing test. If players fail, supports use damage reduction/shields.",
                ""
            )
        );

        VykasGateTwoMechs.push_back(
            RaidMech(
                "Raid Wide Charm (Vykas Throne)",
                "120",
                "Stack the red pools so that the whole raid gets charmed, to avoid the wipe mech that follows.",
                ""
            )
        );

        VykasGateTwoMechs.push_back(
            RaidMech(
                "Vykas Stagger + Frogs",
                "100",
                "[Cleanse Stagger]: Cleanse at the 3o'clock orb and stagger vykas. Timestop immediately after.\n[Wei Frog]: Kill the bottom orb while raid lead uses Wei on Vykas and top frog.",
                ""
            )
        );

        VykasGateTwoMechs.push_back(
            RaidMech(
                "Second Swamp Bridge",
                "75",
                "[SWAMP OF DESPAIR] Create a bridge at 9 oclock. [Desire of Swiftness] Stay away until bridge is created, then gather on the bridge",
                ""
            )
        );

        VykasGateTwoMechs.push_back(
            RaidMech(
                "Tentacles",
                "55",
                "Party 1 left, Party 2 right. Gain meter and kill tentacles",
                ""
            )
        );

        VykasGateTwoMechs.push_back(
            RaidMech(
                "Final Stagger",
                "0",
                "Face the real Vykas using minimap, and run with the explosions. Stand behind her and stagger.",
                ""
            )
        );

    }
    return true;
}

void ProcessVykasMechs(bool& expandedWindow, ImVec2 _MousePos)
{

    if (ImGui::BeginTabBar("Vykas Gates")) {

        // DEPRECATED: Gate One was deleted. Saved for posterity's sake.
        /*
        if (ImGui::BeginTabItem("Vykas Gate One")) {
            CurrentRaidMech = &VykasGateOneMechs[VykasGateOneCounter];
            VykasGateTwoCounter, VykasGateThreeCounter = 0;
            if (ImGui::BeginTable("table1", 3))
            {

                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 410.0f);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 30.0f);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 30.0f);

                ImGui::TableHeadersRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextWrapped(std::string(" >  " + CurrentRaidMech->HealthBarTriggerValue + "X - " + CurrentRaidMech->RaidMechName).c_str());

                ImGui::TableSetColumnIndex(1);
                ImGui::Indent(3.0f);
                ImGui::Text("Prv.", 1, 1);

                ImGui::TableSetColumnIndex(2);
                ImGui::Indent(3.0f);
                ImGui::Text("Nxt.", 2, 2);

                ImGui::TableNextRow(0, 30.0f);
                ImGui::TableSetColumnIndex(0);
                ImGui::Text(CurrentRaidMech->RaidMechQuickRef.c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::Indent(6.0f);
                if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {

                    (VykasGateOneCounter > 0) ? VykasGateOneCounter-- : VykasGateOneCounter = 0;

                }
                ImGui::TableSetColumnIndex(2);
                ImGui::Indent(8.0f);
                if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
                    int GateOneMechSize = VykasGateOneMechs.size() - 1;
                    VykasGateOneCounter < GateOneMechSize ? VykasGateOneCounter++ : VykasGateOneCounter = GateOneMechSize;

                }

                ImGui::EndTable();
            }
            ImGui::Unindent();

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
        }

        */


        // Vykas Gate One Tab
        if (ImGui::BeginTabItem("Gate One")) {
            CurrentRaidMech = &VykasGateOneMechs[VykasGateOneCounter];
            VykasGateTwoCounter = 0;

            ProcessHeaderRows("Vykas Gate One", VykasGateOneCounter, VykasGateOneMechs);

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
        }

       
        if (ImGui::BeginTabItem("Gate Two")) {
            CurrentRaidMech = &VykasGateTwoMechs[VykasGateTwoCounter];
            VykasGateOneCounter = 0;

            ProcessHeaderRows("Vykas Gate Two", VykasGateTwoCounter, VykasGateTwoMechs);

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
        }

    }
}

