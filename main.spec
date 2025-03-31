# -*- mode: python ; coding: utf-8 -*-
import os

# Use the current working directory as the base path
this_dir = os.getcwd()

a = Analysis(
    ['src/lazy_writer_raphael_senellart/main.py'],
    pathex=[os.path.join(this_dir, 'src')],
    binaries=[],
    # Include the entire 'static' folder from 'src/static'
    datas=[(os.path.join(this_dir, 'src', 'static'), 'static')],
    hiddenimports=[],
    hookspath=[],
    runtime_hooks=[],
    excludes=[],
    noarchive=False,
    optimize=0,
)

pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.datas,  # Ensure datas are passed to include static files
    [],
    name='main',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    upx_exclude=[],
    runtime_tmpdir=None,
    console=True,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
)
