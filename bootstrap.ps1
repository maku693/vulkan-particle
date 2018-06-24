Set-StrictMode -Version Latest

Push-Location

$vsWhereExe = "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
Write-Output "vswhere.exe found: $vsWhereExe"
if (!(Test-Path $vsWhereExe)) {
    throw "Could not find vswhere.exe."
}

$vsInstallationPath = & $vsWhereExe -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
Write-Output "Visual Studio installation path: $vsInstallationPath"
if (! $vsInstallationPath) {
    throw "Could not find Visuall Studio installation with Visual C++."
}

$vsDevCmdBat = "${vsInstallationPath}\Common7\Tools\VsDevCmd.bat"
Write-Output "VsDevCmd.bat found: $vsDevCmdBat"
if (!(Test-Path $vsDevCmdBat)) {
    throw "Could not find VsDevCmd.bat."
}

$cmakeExe = Get-Command "cmake.exe"
if (! $cmakeExe) {
    throw "Could not find cmake.exe."
}

$ninjaExe = Get-Command "ninja.exe"
if (! $ninjaExe) {
    throw "Could not find ninja.exe."
}

& $Env:ComSpec /s /c "`"$vsDevCmdBat`" -no_logo && set" | ForEach-Object {
    $name, $value = $_ -split '=', 2
    Set-Content "Env:\$name" $value
    Write-Debug "Environment variable set: Env:\$name"
}

Set-Location $PSScriptRoot
$buildDir = "build"
Remove-Item $buildDir -Recurse
New-Item $buildDir -ItemType "directory" | Out-Null
Set-Location $buildDir

Write-Output "Generating build system..."
& $cmakeExe -G Ninja ..

Pop-Location
