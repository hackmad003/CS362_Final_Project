foreach ($folder in Get-ChildItem -Directory) {
    ./install.ps1 $folder
}

