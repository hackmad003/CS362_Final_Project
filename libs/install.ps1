param(
    [Parameter(Mandatory=$true)]
    [string]$LibraryName
)

# Path to the library folder you want to copy
$Source = Join-Path $PSScriptRoot $LibraryName

# Destination: Documents/Arduino/libraries
$ArduinoLibDir = Join-Path $env:OneDrive "Documents\Arduino\libraries"

# Create directory if missing
if (-Not (Test-Path $ArduinoLibDir)) {
    New-Item -ItemType Directory -Path $ArduinoLibDir | Out-Null
}

$Destination = Join-Path $ArduinoLibDir $LibraryName

# Remove the old library if it exists
if (Test-Path $Destination) {
    Remove-Item -Recurse -Force $Destination
}

# Copy the library
Copy-Item -Recurse -Force $Source $Destination

Write-Host "Installed $LibraryName to $ArduinoLibDir"

