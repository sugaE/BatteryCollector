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
#### P17:

###### P:
Cast To BatteryCollectorCharacter was pruned because its Exec pin is not connected, the connected value is not available and will instead be read as default
This blueprint (self) is not a BatteryCollectorCharacter, therefore ' Target ' must have a connection.
###### F:
Right Click on "Cast To BatteryCollectorCharacter" Node and choose "Cast -> Convert to pure cast" so that the Exec pin will be gone and therefore Get Current Power will always get a Target.

Same for Cast to BatteryCollectorGameMode and Get Power To Win.

![Screenshot 2021-05-24 at 02 46 03](https://user-images.githubusercontent.com/10446823/119273607-4665c100-bc3e-11eb-8b79-f3c3d84da9dc.png)
