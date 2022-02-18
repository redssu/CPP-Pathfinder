cls
g++ -g $(Get-ChildItem -Path .\ -Filter *.cpp -Recurse -File -Name) -o pathfinder.exe
.\pathfinder.exe