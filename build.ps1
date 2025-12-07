Remove-Item build -Recurse -Force
mkdir build
Set-Location build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release .. 
cmake --build . --config Release     
Set-Location ..
build\Social-Networking-App.exe
Pause
Clear-Host  