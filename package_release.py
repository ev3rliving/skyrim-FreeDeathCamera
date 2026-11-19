"""Package one universal DLL and its corresponding complete source snapshot."""
import hashlib
import json
import zipfile
from pathlib import Path

root=Path(__file__).resolve().parent
out=root/'release/1.2.1'
out.mkdir(parents=True,exist_ok=True)
docs=['README.md','VERIFICATION.md','CHANGELOG.md','COPYING.txt','EXCEPTIONS.md']
dll=root/'build-universal/bin/PostmortemTFC.dll'
install=out/'Free-Death-Camera-1.2.1.zip'
with zipfile.ZipFile(install,'w',zipfile.ZIP_DEFLATED) as z:
    z.write(dll,'SKSE/Plugins/PostmortemTFC.dll')
    z.write(root/'config/PostmortemTFC.ini','SKSE/Plugins/PostmortemTFC.ini')
    for name in docs:z.write(root/name,'Docs/FreeDeathCamera/'+name)
    for p in sorted((root/'licenses').rglob('*')):
        if p.is_file():z.write(p,'Docs/FreeDeathCamera/'+p.relative_to(root).as_posix())
with zipfile.ZipFile(install) as z:
    assert z.testzip() is None
    assert z.read('SKSE/Plugins/PostmortemTFC.dll')==dll.read_bytes()
    assert sum(n.endswith('.dll') for n in z.namelist())==1
    assert not any(n.endswith(('.esp','.esl','.hkx','.lib','.exe')) for n in z.namelist())

source=out/'Free-Death-Camera-1.2.1-Source.zip'
manifest={}
with zipfile.ZipFile(source,'w',zipfile.ZIP_DEFLATED) as z:
    paths=[root/name for name in docs+['CMakeLists.txt','Build.ps1','verify_compatibility.py','package_release.py','.gitignore']]
    for folder in ['src','tests','config','licenses','cmake','dependencies']:
        paths.extend(p for p in (root/folder).rglob('*') if p.is_file())
    for p in sorted(paths):
        rel=p.relative_to(root)
        if any(part in {'.git','__pycache__'} for part in rel.parts):continue
        if p.suffix.lower() in {'.dll','.exe','.lib','.obj','.pdb','.zip','.pyc','.log'}:continue
        data=p.read_bytes()
        z.writestr(rel.as_posix(),data)
        manifest[rel.as_posix()]=hashlib.sha256(data).hexdigest()
    z.writestr('SOURCE-SHA256.json',json.dumps(manifest,indent=2)+'\n')
with zipfile.ZipFile(source) as z:
    assert z.testzip() is None
    for name,sha in manifest.items():assert hashlib.sha256(z.read(name)).hexdigest()==sha
(out/'SHA256SUMS.txt').write_text(''.join(hashlib.sha256(p.read_bytes()).hexdigest()+'  '+p.name+'\n' for p in [install,source]))
for p in [install,source]:print(f'PASS: {p} ({p.stat().st_size} bytes)')
