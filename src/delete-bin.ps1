$folders = ls -Path .\ -Include bin,obj -Recurse | ? { $_.PSIsContainer }
foreach ($folder in $folders){
    try {
        Write-Host $folder
        Remove-Item $folder -Force -Recurse -ErrorAction SilentlyContinue
    } catch {
      
    }
}