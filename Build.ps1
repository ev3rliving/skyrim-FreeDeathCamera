param(
    [string]$CMake = 'cmake',
    [string]$Generator = 'Visual Studio 17 2022'
)
$ErrorActionPreference = 'Stop'
$taskBuild = Join-Path $PSScriptRoot 'build'
$taskStage = Join-Path $PSScriptRoot 'package'
$taskArguments = @('-S', $PSScriptRoot, '-B', $taskBuild, '-G', $Generator)
if ($Generator -like 'Visual Studio*') { $taskArguments += @('-A', 'x64') }
else { $taskArguments += '-DCMAKE_BUILD_TYPE=Release' }
& $CMake @taskArguments
if ($LASTEXITCODE -ne 0) { throw 'CMake configuration failed.' }
& $CMake --build $taskBuild --config Release --parallel 2
if ($LASTEXITCODE -ne 0) { throw 'Compilation failed.' }
$taskCMakeCommand = (Get-Command $CMake -ErrorAction Stop).Source
$taskCTest = Join-Path (Split-Path $taskCMakeCommand -Parent) 'ctest.exe'
& $taskCTest --test-dir $taskBuild -C Release --output-on-failure
if ($LASTEXITCODE -ne 0) { throw 'Camera motion tests failed.' }
& $CMake --install $taskBuild --config Release --prefix $taskStage
if ($LASTEXITCODE -ne 0) { throw 'Packaging failed.' }
$taskPluginOutput = Join-Path $PSScriptRoot 'Data/SKSE/Plugins'
New-Item -ItemType Directory -Path $taskPluginOutput -Force | Out-Null
Copy-Item -LiteralPath (Join-Path $taskStage 'SKSE/Plugins/PostmortemTFC.dll') -Destination $taskPluginOutput -Force
# Keep a user's edited INI on subsequent builds.
$taskIniOutput = Join-Path $taskPluginOutput 'PostmortemTFC.ini'
if (-not (Test-Path -LiteralPath $taskIniOutput)) {
    Copy-Item -LiteralPath (Join-Path $taskStage 'SKSE/Plugins/PostmortemTFC.ini') -Destination $taskPluginOutput
}
Write-Host "Staged mod files: $taskStage"
Write-Host "Updated project DLL: $taskPluginOutput"

