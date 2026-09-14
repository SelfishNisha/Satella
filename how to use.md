# How To Use Satella

## Config Format

Each macro's config is made up of 6 parts:

1. **Name**: identifies the macro (`Pearl Catch`, `Stun Slam`, Etc.)
2. **ID**: this is a important key in the code, do not touch.
3. **Enabled**: can be `true` or `false`, you guessed it? it enables and disables the macro :3
4. **Mod Key**: the modifying key (`alt`, `control`, `ctrl`, `shift`, `win`, `windows`).
5. **Key**: the key that must be pressed alongside the `Mod Key` to activate the macro (if mod key is empty the macro will be activated whenever the `key` is pressed)
6. **Slots**: it contains the hotkeys to the item's position in hotbar.

Example:

```json
"Pearl Catch": {
  "ID": 1,
  "Enabled": true,
  "Mod Key": "ALT",
  "Key": "Q",
  "Slots": {
    "Pearl": "MOUSE_SIDE_BUTTON_FRONT",
    "Wind Charge": "X"
  }
},
```

You may have noticed values like `MOUSE_SIDE_BUTTON_FRONT`, these refer to mouse side buttons:

| Value   | Meaning                  |
| ------- | ------------------------ |
| `MOUSE_SIDE_BUTTON_FRONT` | Mouse side button, front |
| `MOUSE_SIDE_BUTTON_BACK` | Mouse side button, back  |

> does this even need explaning?

Use these anywhere a slot expects a keybind that is bounded to a mouse side button.

--- 

## Triggering Macros

Triggering macros are those that perform an action one time.

- Perl Catch
- Stun Slam
- Lunge Swap
- Breach Swap
- Anchor
