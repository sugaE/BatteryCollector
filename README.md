# BatteryCollector
Following Unreal Tutorial[【C++ 3rd Person Battery Collector Power Up Game (v4.9)-哔哩哔哩】](https://b23.tv/KijVDM);

Some fixes due to engine upgrade;



### Env & Editor & Engine Version:
MacOS;
VSCode;
4.26.2;



## VSCode Problems:
### To work with vscode
1. Preference > Source Code > Source Code Editor > Visual Studio Code.
2. Restart the Editor.
3. File > Generate Visual Studio Code Project.
It will automatically generate a large project with dependency and engine file.

### intelliSense
If your intelliSense isn't working well, it is not your fault.

Mine works 5 seconds every half day.

I believe it's due to huge engine file and my (5-year-old) laptop needed to be replaced.

But generally, if the intelliSense gives warnings on swiching mode due to default compiler, you should try to add `"compilerPath": "/usr/bin/clang++"` to `.vscode/c_cpp_properties.json` file to force it use clang.
(Or change vscode default setting then restart vscode)



## Code and Blueprint Problems:
(Some fixes are marked in code in form of "FIX: Pxx")
### P17:
#### P:
Cast To BatteryCollectorCharacter was pruned because its Exec pin is not connected, the connected value is not available and will instead be read as default
This blueprint (self) is not a BatteryCollectorCharacter, therefore ' Target ' must have a connection.
#### F:
Right Click on "Cast To BatteryCollectorCharacter" Node and choose "Cast -> Convert to pure cast" so that the Exec pin will be gone and therefore Get Current Power will always get a Target.

Same for Cast to BatteryCollectorGameMode and Get Power To Win.

![Screenshot 2021-05-24 at 02 46 03](https://user-images.githubusercontent.com/10446823/119273607-4665c100-bc3e-11eb-8b79-f3c3d84da9dc.png)


### P18:
#### P:
```bash
2021-05-24 05:38:04.607 UnrealHeaderTool[1981:25796] [UE4] LogCompile: /Users/Windy/code/project/unreal/BatteryCollector/Source/BatteryCollector/BatteryCollectorGameMode.h(12): Error: Invalid BlueprintType enum base - currently only uint8 supported
2021-05-24 05:38:04.609 UnrealHeaderTool[1981:25796] [UE4] Error: Invalid BlueprintType enum base - currently only uint8 supported
```
#### F:
`enum class EBatteryPlayState : uint8 { ... }`

### P20:
#### P:
```bash
/Users/Windy/code/project/unreal/BatteryCollector/Source/BatteryCollector/BatteryCollectorGameMode.cpp:131:39: error: member access into incomplete type 'UPawnMovementComponent'
                        MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
                                                           ^
/Users/Shared/Epic Games/UE_4.26/Engine/Intermediate/Build/Mac/x86_64/UE4/Inc/Engine/Pawn.generated.h:16:7: note: forward declaration of 'UPawnMovementComponent'
class UPawnMovementComponent;
      ^
1 error generated.
```
#### F:
add dependency `#include "GameFramework/PawnMovementComponent.h"`


## Other Possible Problems:
#### P: UE4 Build Precompiled Header Fatal Error
```bash
fatal error: file '/usr/include/x86_64-linux-gnu/asm/unistd.h' has been modified since the precompiled header '/home/mynewuser/Downloads/UnrealEngine/Engine/Intermediate/Build/Linux/B4D820EA/CrashReportClient/Development/Core/CorePrivatePCH.h.gch' was built note: please rebuild precompiled header '/home/mynewuser/Downloads/UnrealEngine/Engine/Intermediate/Build/Linux/B4D820EA/CrashReportClient/Development/Core/CorePrivatePCH.h.gch'

make: *** [CrashReportClient] Error 5 16:40:46: The process "/usr/bin/make" exited with code 2. Error while building/deploying project UE4 (kit: Unreal Engine 4_Kit) When executing step "Make"
```
#### F: Run `BatteryCollector xxx xxx Clean` AND `BatteryCollectorEditor xxx xxx Clean` from vscode
ref: https://answers.unrealengine.com/questions/412349/linux-ue4-build-precompiled-header-fatal-error.html

#### P: Invalid option value 'EPlaying' in  Select
Really strange error. Successfully run seconds ago then poped up this error.
#### F: Relaunching the Unreal Editor fixed the problem.
