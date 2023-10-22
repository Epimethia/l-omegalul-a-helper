#pragma once

struct ImVec2;


enum class DisplayRaid {
    MENU,
    VALTAN,
    VYKAS,
    CLOWN,
    BRELSHAZA,
    AKKAN,
    ARGOS,
    KAYANGLE
};

bool InitMainMenu();
void ProcessMainMenu(bool& expandedWindow, ImVec2 _MousePos, DisplayRaid& _Raid);