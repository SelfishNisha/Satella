#include "config.h"

const json defaultConfig = {
  {"Macros", {
    {"Pearl Catch", {
      {"ID", 1},
      {"Enabled", true},
      {"Mod Key", "ALT"},
      {"Key", "Q"},
      {"Slots", {
        {"Pearl", "MOUSE_SIDE_BUTTON_FRONT"},
        {"Wind Charge", "X"}
      }},
      {"Extra", {
        {"Speed", "Medium"}
      }}
    }},

    {"Stun Slam", {
      {"ID", 2},
      {"Enabled", true},
      {"Mod Key", "ALT"},
      {"Key", "W"},
      {"Slots", {
        {"Axe", "2"},
        {"Mace", "1"}
      }},
      {"Extra", {
        {"Switch Back To Slot", ""}
      }}
    }},

    {"Breach Swap", {
      {"ID", 3},
      {"Enabled", false},
      {"Mod Key", "ALT"},
      {"Key", "D"},
      {"Slots", {
        {"Sword", "CAPSLOCK"},
        {"Mace", "C"}
      }}
    }},

    {"Lunge Swap", {
      {"ID", 4},
      {"Enabled", false},
      {"Mod Key", "ALT"},
      {"Key", "S"},
      {"Slots", {
        {"Zero Cooldown", "CAPSLOCK"},
        {"Spear", "Q"}
      }}
    }},

    {"Single Anchor", {
      {"ID", 5},
      {"Enabled", false},
      {"Mod Key", "ALT"},
      {"Key", "A"},
      {"Slots", {
        {"Respawn Anchor", "X"},
        {"Glowstone", "C"},
        {"Totem", "3"},
      }}
    }},

    {"Panic", {
      {"ID", 999},
      {"Enabled", true},
      {"Mod Key", ""},
      {"Key", "F4"},
    }}
  }}
};