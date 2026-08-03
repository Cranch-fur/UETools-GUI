# UETools-GUI
Dumper-7 (SDK) based solution for rapid debugging of Unreal Engine powered titles. Designed for a minimal setup experience: you can have it running within 5 minutes from the initial download.

> [!CAUTION]
> **Disclaimer:** Solution was developed for general use in Unreal Engine powered titles. The author does not condone cheating, modding, or the manipulation of [online competitive games](https://en.wikipedia.org/wiki/List_of_esports_games). The author bears no responsibility for the specific titles or contexts in which the solution is used.

# Dependencies
### [Dumper-7](https://github.com/Encryqed/Dumper-7) & [ImGui](https://github.com/ocornut/imgui)

# Baseline & Environment
```
Unreal Engine: 4.27.2
C++: ISO 20 | C: Legacy MSVC
Windows SDK: "10.0.26100.0"
Build Configuration: Release
```
> [!NOTE]
> Solution is targeting Unreal Engine 4.27.2 as the base. That allows it to be upgraded or downgraded with relative ease; however, certain code segments may require adjustment to accommodate engine-specific differences (e.g., deprecated or not-yet-implemented variables and functions).
>
> Title is considered supported only if Dumper-7 successfully generates a valid SDK.

# Getting Started
1. Download and extract the repository, or clone it via Git.
2. Generate a Dumper-7 SDK for the target title. Pre-compiled Dumper-7 can be found in [Releases](https://github.com/Cranch-fur/UETools-GUI/releases).
> [!TIP]
> Dynamic Link Libraries (DLLs) can be loaded into a target process using tools such as [Cheat Engine](https://www.cheatengine.org/) and [System Informer](https://systeminformer.sourceforge.io/downloads) (formerly Process Hacker). Always make sure your actions comply with the title's EULA and all applicable laws.
3. Replace the contents of `..\SDKs\Dumper7` with the contents of the newly generated, title-specific "CppSDK".
4. Build `UETools-GUI.dll` and load it into the target title process.
> [!TIP]
> When targeting Unreal Engine 5 based titles, it's recommended to uncomment `#define UE5` in `definitions.h`. In many cases that action alone would be enough to adapt entirety of solution for newer engine.

While in the title, press Insert (INS) to toggle the menu.
> [!CAUTION]
> Windows 11 users may encounter a black screen issue with the DirectX 11 rendering API immediately after injecting UETools-GUI. While this issue is not addressed within the project itself, if you experience it, please follow these steps:
> 1) Navigate to the title’s installation directory, then open the following path: `{Title internal name}\Binaries\Win64`.
> 2) Locate the title executable and open its Properties (Right-click → Properties).
> 3) Go to the Compatibility tab and enable the "Disable fullscreen optimizations" feature.
>
> Alternatively, `#define INACTIVE_ZERO_SIZE` in `definitions.h` can be uncommented, although it comes with a set of compromises.

# Great First Experience Titles
## [Lies of P (Unreal Engine 4.27.2)](https://store.steampowered.com/app/1627720)
**[Lies of P DEMO (Unreal Engine 4.27.2)](https://archive.org/details/lies-of-p-demo)**

<img width="460" height="215" alt="FirstEXP_LiesOfP" src="https://github.com/user-attachments/assets/7d21d212-92db-49ac-91eb-977991939129" />

## [Project Borealis Prologue (Unreal Engine 5.4.4)](https://store.steampowered.com/app/2215490)
<img width="460" height="215" alt="FirstEXP_ProjectBorealis" src="https://github.com/user-attachments/assets/d7527f5b-706c-4f05-b8b9-ea0ed6369a4e" />

# Showcase
https://github.com/user-attachments/assets/3bff3c81-3b28-40f1-ba3d-39d9f9793769

<img width="2560" height="1440" alt="UE4.19.0_SpyroReignitedTrilogy" src="https://github.com/user-attachments/assets/69932fff-dab2-4d18-b191-0829e0df8a79" />

<img width="2560" height="1440" alt="UE4.22.3_SamuraiJackBattleThroughTime" src="https://github.com/user-attachments/assets/ebd71b08-2d90-400e-b851-01fe321b6831" />

<img width="2560" height="1440" alt="UE4.27.2_LiesOfPDEMO" src="https://github.com/user-attachments/assets/58ce5ce0-46f0-4478-8245-993db60dea47" />

<img width="2560" height="1440" alt="UE5.1.1_LordsOfTheFallen2023" src="https://github.com/user-attachments/assets/e00d44f6-7cbc-4a0e-87df-772b414ca536" />

<img width="2560" height="1440" alt="UE5.4.4_ProjectBorealisPrologue" src="https://github.com/user-attachments/assets/d21873e6-b262-4afa-a107-e5f273e1aff0" />



