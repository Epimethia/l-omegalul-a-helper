#pragma once
#include "mainmenu.h"
#include "HelperFunctions.h"
#include "imgui/imgui.h"
#include "raid.h"

static RaidMechResourceImage ValtanIcon;
static RaidMechResourceImage VykasIcon;
static RaidMechResourceImage ClownIcon;
static RaidMechResourceImage BrelshazaIcon;
static RaidMechResourceImage AkkanIcon;
static RaidMechResourceImage ArgosIcon;
static RaidMechResourceImage KayangleIcon;


bool InitMainMenu() {

    if (!LoadTextureFromFile("./Resources/Legion Raid Icons/valtan.png", &ValtanIcon.texture)) return false;
    if (!LoadTextureFromFile("./Resources/Legion Raid Icons/vykas.png", &VykasIcon.texture)) return false;
    if (!LoadTextureFromFile("./Resources/Legion Raid Icons/clown.png", &ClownIcon.texture)) return false;
    if (!LoadTextureFromFile("./Resources/Legion Raid Icons/brelshaza.png", &BrelshazaIcon.texture)) return false;
    if (!LoadTextureFromFile("./Resources/Legion Raid Icons/akkan.png", &AkkanIcon.texture)) return false;
    if (!LoadTextureFromFile("./Resources/Legion Raid Icons/argos.png", &ArgosIcon.texture)) return false;
    if (!LoadTextureFromFile("./Resources/Legion Raid Icons/kayangle.png", &KayangleIcon.texture)) return false;

    return true;
}

void ProcessMainMenu(bool& expandedWindow, ImVec2 _MousePos, DisplayRaid& _Raid)
{
    expandedWindow = true;
    ImVec2 IconSize = { 55,55 };

    ImGui::SeparatorText("LEGION RAIDS");
    if (ImGui::BeginTable("Raid Table", 2, ImGuiTableFlags_Borders)) {
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 400.0f);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        ImGui::Text("VALTAN");
        ImGui::TableNextColumn();
        ImGui::Button("G1");
        ImGui::SameLine(); ImGui::Button("G2");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("VYKAS");
        ImGui::TableNextColumn();
        ImGui::Button("G1");
        ImGui::SameLine();  ImGui::Button("G2");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("KAKUL-SAYDON");
        ImGui::TableNextColumn();
        ImGui::Button("G1");
        ImGui::SameLine();  ImGui::Button("G2");
        ImGui::SameLine(); ImGui::Button("G3");
        ImGui::SameLine(); ImGui::Button("G4 - Bingo");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("BRELSHAZA");
        ImGui::TableNextColumn();
        ImGui::Button("G1");
        ImGui::SameLine(); ImGui::Button("G2");
        ImGui::SameLine();  ImGui::Button("G3");
        ImGui::SameLine(); ImGui::Button("G4");
    }
    ImGui::EndTable();

    ImGui::SeparatorText("OTHER RAIDS");
    if (ImGui::BeginTable("Raid Table", 2, ImGuiTableFlags_Borders)) {
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 400.0f);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("KAYANGLE");
        ImGui::TableNextColumn();
        ImGui::Button("G1");
        ImGui::SameLine();
        ImGui::Button("G2");
        ImGui::SameLine();
        ImGui::Button("G3");
    }
    ImGui::EndTable();

    /*
    if(ImGui::BeginTable("RaidTable", 6, ImGuiTableFlags_Borders)) {

        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 65.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 65.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 125.0f);
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        //Valtan
        {
            if(ImGui::ImageButton(ValtanIcon.texture, IconSize)) _Raid = DisplayRaid::VALTAN;

            ImGui::TableNextColumn();
            ImGui::Text("VALTAN");
            ImGui::Button("G1");
            ImGui::SameLine();
            ImGui::Button("G2");
        }

        ImGui::TableNextColumn();

        //Vykas
        {
            if(ImGui::ImageButton(VykasIcon.texture, IconSize)) _Raid = DisplayRaid::VYKAS;

            ImGui::TableNextColumn();
            ImGui::Text("VYKAS");
            ImGui::Button("G1");
            ImGui::SameLine();
            ImGui::Button("G2");
        }

        ImGui::TableNextColumn();

        //Kakul-Saydon
        {
            if(ImGui::ImageButton(ClownIcon.texture, IconSize)) _Raid = DisplayRaid::CLOWN;

            ImGui::TableNextColumn();
            ImGui::Text("KAKUL-SAYDON");
            ImGui::Button("G1");
            ImGui::SameLine();
            ImGui::Button("G2");
            ImGui::SameLine();
            ImGui::Button("G3");
            ImGui::Button("G4 - Bingo");
        }

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        //Brelshaza
        {
            if(ImGui::ImageButton(BrelshazaIcon.texture, IconSize)) _Raid = DisplayRaid::BRELSHAZA;

            ImGui::TableNextColumn();
            ImGui::Text("BRELSHAZA");
            ImGui::Button("G1");
            ImGui::SameLine();
            ImGui::Button("G2");
            ImGui::Button("G3");
            ImGui::SameLine();
            ImGui::Button("G4");
        }

        //Akkan
        {
            ImGui::TableNextColumn();
            if(ImGui::ImageButton(AkkanIcon.texture, IconSize)) _Raid = DisplayRaid::AKKAN;
            ImGui::TableNextColumn();

            ImGui::Text("AKKAN");
            ImGui::Button("G1");
            ImGui::SameLine();
            ImGui::Button("G2");
            ImGui::Button("G3");
        }
    }
    ImGui::EndTable();
    ImGui::NewLine();
    ImGui::SeparatorText("OTHER RAIDS");

    if (ImGui::BeginTable("RaidTable2", 6, ImGuiTableFlags_Borders)) {

        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 115.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 115.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 125.0f);
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        //Argos
        {
            if(ImGui::ImageButton(ArgosIcon.texture, IconSize)) _Raid = DisplayRaid::ARGOS;;

            ImGui::TableNextColumn();
            ImGui::Text("Argos");
            ImGui::Button("G1");
            ImGui::SameLine();
            ImGui::Button("G2");
            ImGui::SameLine();
            ImGui::Button("G3");
        }

        ImGui::TableNextColumn();

        //Kayangle
        {
            if(ImGui::ImageButton(KayangleIcon.texture, IconSize)) _Raid = DisplayRaid::KAYANGLE;

            ImGui::TableNextColumn();
            ImGui::Text("Kayangle");
            ImGui::Button("G1");
            ImGui::SameLine();
            ImGui::Button("G2");
            ImGui::SameLine();
            ImGui::Button("G3");

        }
    }
    ImGui::EndTable();

    */
}
