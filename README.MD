# Memory Card Annihilator

A powerful tool for memory card management.

Originally made by ffgriever (with GFX design by berion)

Project revised by El_isra

## Changes

> The following changes were applied:

- Compilable on PS2DEV v1.0
- Native support for exFAT Filesystem, no more messing with the "no IOP reset" flag
- Supports ProtoKernel PS2s (`SCPH-10000` & `SCPH-15000`)
- Alternative builds, each capable of either:
  - Handling Arcade Memory Card  (`COH-H10020`)
  - Handling Developer Memory Card (`SCPH-10020 T`)
  - Handling Prototype Memory Card (?)

## Release package

Inside the release package you will find several folders, here's what each one offers:

- `mca_legacy`: MCA with the original modules. Nothing too different from the older versions.
- `mca_new`: USB drivers replaced with modules from the latest SDK to offer exFAT USB support. Uses homebrew memory card modules instead of console OSD modules, making the program compatible with ProtoKernel PS2s in the process.
- `mca_Arcade`: Supports exFAT USB and reads arcade memory cards instead of normal ones.
- `mca_Prototype`: Supports exFAT USB and reads prototype memory cards instead of normal ones.
- `mca_Developer`: Supports exFAT USB and reads developer memory cards (and TDB StartUp Cards) instead of normal ones.

## Translators and proofreaders

- Brazilian Portuguese: Venão
- English: ffgriever
- French: Gnom, unversdelait
- German: H4ndy, TnA
- Italian: xeeynamo
- Polish: ffgriever
- Spanish: El_Patas, HWNJ
- Turkish: Grey_Wolf, Rockman98
- Russian: dimm0505, alex_wallace

An alternative Brazilian Portuguese translation was made by:
- Germanno, DanielSantos and gledson999
