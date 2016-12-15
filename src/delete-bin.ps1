$folders = ls -Path .\ -Include bin,obj,Debug,Release,ipch -Recurse | ? { $_.PSIsContainer }
foreach ($folder in $folders){
    try {
        Write-Host $folder
        Remove-Item $folder -Force -Recurse -ErrorAction SilentlyContinue
    } catch {
      
    }
}